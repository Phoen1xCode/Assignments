// User.cpp
// Created by Jake Jia on 2023/11/30.
// 用户类的具体实现

#include <utility>
#include <iostream>
#include "../include/User.h"
#include "../include/PasswordUtils.h"
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
        int numberOfAttempts = 0; // 密码输入尝试次数，一共三次
        std::string cin_password; // 用户输入的密码

        std::cout << "欢迎使用 0Password ，" << this->getUsername() << std::endl;
        std::cout << "请输入密码。" << std::endl;

        while(numberOfAttempts < 3) {
            std::cout << "密码：";
            cin_password = PasswordManagement::getHiddenInput(); // 隐藏密码输入

            if (!this->isRightPassword(cin_password)) { // 密码错误
                bool wrongPassword = false;
                setLoginLicense(wrongPassword);
                std::cout << "密码错误！请重新输入！" << std::endl;
                numberOfAttempts++;
                std::cout << "剩余尝试次数：" << 3 - numberOfAttempts << "。" << std::endl;
            } else { // 密码正确
                bool rightPassword = true;
                setLoginLicense(rightPassword);
                break;
            }
        }

        if (numberOfAttempts == 3) {
            std::cout << "密码输入错误次数过多，账户已被锁定。" << std::endl;
        } else {
            std::cout << "密码正确，登录成功。" << std::endl;
        }
    }

}


