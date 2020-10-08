#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Email {
    string from;
    string to;
    string body;
};

inline istream &operator>>(istream &stream, Email &email) {
    getline(stream, email.from);
    getline(stream, email.to);
    getline(stream, email.body);
    return stream;
}

inline ostream &operator<<(ostream &stream, const Email &email) {
    return stream << email.from << '\n' << email.to << '\n' << email.body << '\n';
}

class Worker {
    unique_ptr<Worker> mNext;
public:
    virtual ~Worker() = default;

    virtual void Process(unique_ptr<Email> email) = 0;

    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const {
        if (mNext) {
            mNext->Process(move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next) {
        if (mNext) {
            mNext->SetNext(move(next));
        } else {
            mNext = move(next);
        }
    }
};

class Reader : public Worker {
    vector<unique_ptr<Email>> mEmails;
public:
    // реализуйте класс
    explicit Reader(istream &input) {
        Email email;
        while (input >> email) {
            mEmails.emplace_back(make_unique<Email>(move(email)));
        }
    }

    void Run() override {
        for (unique_ptr<Email> &email : mEmails) {
            PassOn(move(email));
        }
    }

    void Process(unique_ptr<Email> email) override {
        Run();
    }
};

class Filter : public Worker {
public:
    using Function = function<bool(const Email &)>;
private:
    const Function mFunction;
public:
    // реализуйте класс
    explicit Filter(const Function &function) : mFunction(function) {}

    void Process(unique_ptr<Email> email) override {
        if (mFunction(*email))
            PassOn(move(email));
    }
};


class Copier : public Worker {
public:
    // реализуйте класс
    explicit Copier(const string &recipient) : mRecipient(recipient) {}

    void Process(unique_ptr<Email> email) override {
        unique_ptr<Email> new_email = nullptr;
        if (mRecipient != email->to) {
            new_email = make_unique<Email>(Email{email->from, mRecipient, email->body});
        }

        PassOn(move(email));

        if (new_email)
            PassOn(move(new_email));
    }

private:
    const string mRecipient;
};


class Sender : public Worker {
public:
    // реализуйте класс
    explicit Sender(ostream &output) : stream(output) {}

    void Process(unique_ptr<Email> email) override {
        stream << *email;
        PassOn(move(email));
    }

private:
    ostream &stream;
};

// реализуйте класс
class PipelineBuilder {
    unique_ptr<Worker> mHead;
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream &in) {
        mHead = make_unique<Reader>(in);
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter) {
        mHead->SetNext(make_unique<Filter>(move(filter)));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(string recipient) {
        mHead->SetNext(make_unique<Copier>(recipient));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder &Send(ostream &out) {
        mHead->SetNext(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build() {
        return move(mHead);
    }
};

void TestSanity() {
    string input = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "ralph@example.com\n"
            "erich@example.com\n"
            "I do not make mistakes of that kind\n"
    );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "erich@example.com\n"
            "richard@example.com\n"
            "Are you sure you pressed the right button?\n"
    );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
