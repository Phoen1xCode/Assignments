// User.h
// Created by Jake Jia on 2023/11/30.
// 用户类

#ifndef PASSWORDMANAGEMENT_USER_H
#define PASSWORDMANAGEMENT_USER_H

#include <string>

namespace PasswordManagement {
    class User {
    public:
        User(); // 默认构造函数
        User(std::string username, std::string password, bool loginLicense = false); // 构造函数
        User(const User& other); // // 复制构造函数

        std::string getUsername() const; // 获取用户名
        std::string getPassword() const; // 获取密码(密文)
        bool getLoginLicense() const; // 获取用户登陆许可

        void setUsername(const std::string& newUsername); // 设置新用户名
        void setPassword(const std::string& newPassword); // 设置新密码
        void setLoginLicense(const bool& newLoginLicense); // 设置用户登陆许可

        bool isRightPassword(const std::string& cin_password) const; // 判断密码是否正确

        void userLogin(); // 用户登陆界面

    private:
        std::string username; // 用户名
        std::string password; // 密码
        bool loginLicense; // 用户登陆许可
    };

}

#endif //PASSWORDMANAGEMENT_USER_H
