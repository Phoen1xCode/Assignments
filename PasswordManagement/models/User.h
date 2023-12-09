// User.h
// Created by Jake Jia on 2023/11/30.
// Done by Jake Jia on 2023/12/8
// 用户类

#include <string>

#ifndef PASSWORDMANAGEMENT_USER_H
#define PASSWORDMANAGEMENT_USER_H

namespace PasswordManagement {
    class User {
    public:

        User(); // 默认构造函数
        User(std::string username, std::string password); // 构造函数
        User(const User& other); // // 复制构造函数

        bool isRightPassword(const std::string& cin_password) const; // 判断密码是否正确

        std::string getUsername() const; // 获取用户名
        std::string getPassword() const; // 获取密码 密文

    private:
        std::string username; // 用户名
        std::string password;// 密码
    };
}

#endif //PASSWORDMANAGEMENT_USER_H
