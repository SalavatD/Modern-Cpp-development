#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <string_view>
#include <algorithm>

using namespace std;

class Domain {
    vector<string> mDomainTokens;
public:
    explicit Domain(const string &domains) {
        string token;
        for (const auto &c : domains) {
            if (c == '.') {
                mDomainTokens.push_back(token);
                token = "";
            } else {
                token += c;
            }
        }
        mDomainTokens.push_back(token);
    }

    bool IsSubdomain(const Domain &subdomain) const {
        if (mDomainTokens.size() < subdomain.mDomainTokens.size()) {
            return false;
        }
        size_t i = 0;
        for (const auto &token : subdomain.mDomainTokens) {
            if (token != mDomainTokens.at(i)) {
                return false;
            }
            i++;
        }
        return true;
    }
};


class DomainChecker {
public:
    void AddDomain(const string &domain) {
        mBannedDomains[Hash(domain)].push_back(Domain(domain));
    }

    bool CheckDomain(const string &domain) const {
        if (!mBannedDomains.count(Hash(domain))) {
            return false;
        }
        const Domain domainToCheck = Domain(domain);
        const auto &bannedDomains = mBannedDomains.at(Hash(domain));
        for (const Domain &bannedDomain : bannedDomains) {
            if (domainToCheck.IsSubdomain(bannedDomain)) {
                return true;
            }
        }
        return false;
    }

private:
    unordered_map<string, vector<Domain>> mBannedDomains;

    static string Hash(string_view domain) {
        return string(domain.substr(0, domain.find('.')));
    }
};


int main() {
    DomainChecker domainChecker;
    int count;
    string domain;
    cin >> count;
    for (int i = 0; i < count; i++) {
        cin >> domain;
        reverse(begin(domain), end(domain));
        domainChecker.AddDomain(domain);
    }
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> domain;
        reverse(begin(domain), end(domain));
        if (domainChecker.CheckDomain(domain)) {
            cout << "Bad\n";
        } else {
            cout << "Good\n";
        }
    }
    return 0;
}
