#include <iostream>
#include <string>
#include <vector>


class Human {

protected:
    const std::string mName;

private:
    const std::string mType;

public:
    Human(const std::string &name, const std::string &type) : mName(name),
                                                              mType(type) {}

    std::string GetName() const {
        return mName;
    }

    std::string GetProfession() const {
        return mType;
    }

    virtual void Walk(const std::string &) const {};
};


class Student : public Human {

private:
    const std::string mFavouriteSong;

public:
    Student(const std::string &name, const std::string favouriteSong) : Human(name, "Student"),
                                                                        mFavouriteSong(favouriteSong) {}

    void Learn() const {
        std::cout << "Student: " << mName << " learns" << std::endl;
    }

    void SingSong() const {
        std::cout << "Student: " << mName << " sings a song: " << mFavouriteSong << std::endl;
    }

    void Walk(const std::string &destination) const override {
        std::cout << "Student: " << mName << " walks to: " << destination << std::endl;
        SingSong();
    }
};


class Teacher : public Human {

private:
    const std::string mSubject;

public:
    Teacher(const std::string &name, const std::string &subject) : Human(name, "Teacher"),
                                                                   mSubject(subject) {}

    void Teach() const {
        std::cout << "Teacher: " << mName << " teaches: " << mSubject << std::endl;
    }
};


class Policeman : public Human {

public:
    Policeman(const std::string &name) : Human(name, "Policeman") {}

    void Check(const Human &person) const {
        std::cout << "Policeman: " << mName << " checks " << person.GetProfession() << ". ";
        std::cout << person.GetProfession() << "'s name is: " << person.GetName() << std::endl;
    }
};


void VisitPlaces(Human &person, const std::vector<std::string> &places) {
    for (const auto place : places) {
        person.Walk(place);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
