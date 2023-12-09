#include <vector>
#include <string>
#include <algorithm>

class Credential {
private:
    std::string projectName;
    std::string username;
    std::string password; // 加密后的密码

public:
    Credential(const std::string& projectName, const std::string& username, const std::string& password)
        : projectName(projectName), username(username), password(password) {}

    const std::string& getProjectName() const { return projectName; }
    const std::string& getUsername() const { return username; }
    const std::string& getPassword() const { return password; }

    // ... 其他成员函数 ...
};

class CredentialManager {
private:
    std::vector<Credential> credentials;

public:
    void addCredential(const Credential& credential) {
        credentials.push_back(credential);
    }

    std::vector<Credential> searchByProjectName(const std::string& projectName) const {
        std::vector<Credential> results;
        std::copy_if(credentials.begin(), credentials.end(), std::back_inserter(results),
                     [&projectName](const Credential& credential) {
                         return credential.getProjectName() == projectName;
                     });
        return results;
    }

    std::vector<Credential> searchByUsername(const std::string& username) const {
        std::vector<Credential> results;
        std::copy_if(credentials.begin(), credentials.end(), std::back_inserter(results),
                     [&username](const Credential& credential) {
                         return credential.getUsername() == username;
                     });
        return results;
    }

    // ... 其他成员函数 ...
};
