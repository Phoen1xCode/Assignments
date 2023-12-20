// main.cpp
// Created by Jake Jia on 2023/11/30.
// 密码管理器程序

#include "models/PasswordManager.h"

int main() {

    PasswordManagement::PasswordManager passwordManager;
    if(!passwordManager.loginPasswordManagement())
        return 0;
    else // 运行程序
        passwordManager.managePasswords();


    return 0;
}
