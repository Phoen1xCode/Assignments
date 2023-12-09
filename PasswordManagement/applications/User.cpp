// User.cpp
// Created by Jake Jia on 2023/11/30.
// Done by Jake Jia on 2023/12/8
// 用户类的具体实现

#include "../models/User.h"
#include "../lib/bcrypt/include/bcrypt.h"
#include <string>
#include <utility>

namespace PasswordManagement {
    User::User() {
        this->username = "";
        this->password = "";
    }
    User::User(std::string username, std::string password) {
        this->username = std::move(username);
        this->password = std::move(password);
    }

    User::User(const User &other) {
        this->username = other.username;
        this->password = other.password;
    }

    std::string User::getUsername() const {
        return this->username;
    }

    std::string User::getPassword() const {
        return this->password;
    }

    bool User::isRightPassword(const std::string& cin_password) const {
        return bcrypt::validatePassword(cin_password, getPassword());
    }

}


