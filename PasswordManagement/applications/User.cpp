// User.cpp
// Created by Jake Jia on 2023/11/30.
// 用户类的具体实现

#include <utility>
#include <iostream>
#include "../models/User.h"
#include "../models/PasswordUtils.h"
#include "../lib/bcrypt/include/bcrypt.h"

namespace PasswordManagement {
    User::User() {
        this->username = "";
        this->password = "";
        this->loginLicense = false;
    }

    User::User(std::string username,
               std::string password,
               bool loginLicense) {
        this->username = std::move(username);
        this->password = std::move(password);
        this->loginLicense = loginLicense;
    }

    User::User(const User &other) {
        this->username = other.username;
        this->password = other.password;
        this->loginLicense = other.loginLicense;
    }

    std::string User::getUsername() const {
        return this->username;
    }

    std::string User::getPassword() const {
        return this->password;
    }

    bool User::getLoginLicense() const {
        return this->loginLicense;
    }

    void User::setUsername(const std::string& newUsername) {
        this->username = newUsername;
    }

    void User::setPassword(const std::string& newPassword) {
        this->password = newPassword;
    }

    void User::setLoginLicense(const bool& newLoginLicense) {
        this->loginLicense = newLoginLicense;
    }

    bool User::isRightPassword(const std::string& cin_password) const {
        return bcrypt::validatePassword(cin_password, getPassword());
    }

    void User::userLogin() {
        int numberOfAttempts = 0; // 密码输入尝试次数 一共三次
        std::string cin_password; // 用户的输入的密码

        std::cout << "Welcome to the PasswordManagement, " << this->getUsername() << std::endl;
        std::cout << "Please enter the password." << std::endl;

        while(numberOfAttempts < 3) {
            std::cout << "Password:";
            cin_password = PasswordManagement::getHiddenInput(); // 隐藏密码输入

            if (!this->isRightPassword(cin_password)) { // 密码错误
                bool wrongPassword = false;
                setLoginLicense(wrongPassword);
                std::cout << "Password Wrong! Please enter again!" << std::endl;
                numberOfAttempts++;
                std::cout << 3 - numberOfAttempts << " attempts left." << std::endl;
            } else { // 密码正确
                bool rightPassword = true;
                setLoginLicense(rightPassword);
                break;
            }
        }
    }

}


