// PasswordManager.h
// Created by Jake Jia on 2023/11/30.
//

#ifndef PASSWORDMANAGEMENT_PASSWORDMANAGER_H
#define PASSWORDMANAGEMENT_PASSWORDMANAGER_H
#include <string>
#include "User.h"
#include "ConfigManager.h"

namespace PasswordManagement {
    class PasswordManager {
    public:


        void userInitialize(ConfigManager& configFile, std::string& username, std::string& password); // 进行用户初始化
        void userLogin(User &user); // 用户登陆界面
        void managePasswords(); // // 控制台 密码管理器界面基本逻辑


    private:
        bool loginLicense; // 用户登陆许可
        bool isExit; // 是否退出程序
    };

}


#endif //PASSWORDMANAGEMENT_PASSWORDMANAGER_H
