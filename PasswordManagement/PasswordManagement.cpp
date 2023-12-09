// main.cpp
// Created by Jake Jia on 2023/11/30.
// 密码管理器程序


#include <string>
#include <iostream>
#include "models/User.h"
#include "models/PasswordUtils.h"
#include "models/PasswordManager.h"
#include "models/ConfigManager.h"

int main() {
    std::string username, password; // username 用户名 | password 密码
    bool loginLicense = false; // 用户登陆许可

    std::string configFileName = "config.txt";

    PasswordManagement::ConfigManager configFile(configFileName);
    PasswordManagement::PasswordManager passwordManager;

    // 检查是否有用户配置文件
    if(!configFile.findConfigFile()) {
        configFile.createConfigFile(); // 没有则创建一个空的默认用户配置文件
        passwordManager.userInitialize(configFile, username, password); // 进行初始化
    } else if(!configFile.checkConfigFile()) {
        passwordManager.userInitialize(configFile, username, password); // 进行初始化
    } else {
        configFile.readConfigFile(username, password); // 有则读取配置文件中的用户名和密码
    }

    PasswordManagement::User admin(username, password);
    // 用户登陆界面
    passwordManager.userLogin(admin);
    // 尝试次数超过三次 关闭程序
    if(!passwordManager.getLoginLicense()) {
        std::cout << "Too many attempts. Exiting..." << std::endl;
        return 0;
    }

    // 密码管理器控制台界面
    passwordManager.managePasswords();


    return 0;
}
