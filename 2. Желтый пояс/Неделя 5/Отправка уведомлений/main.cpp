#include <iostream>
#include <string>

using namespace std;

class INotifier {
public:
    virtual void Notify(const string &message) const = 0;
};

class SmsNotifier : public INotifier {
    const string mNumber;
public:
    SmsNotifier(const string &number) : mNumber(number) {}

    virtual void Notify(const string &message) const override {
        SendSms(mNumber, message);
    }
};

class EmailNotifier : public INotifier {
    const string mEmail;
public:
    EmailNotifier(const string &email) : mEmail(email) {}

    virtual void Notify(const string &message) const override {
        SendEmail(mEmail, message);
    }
};
