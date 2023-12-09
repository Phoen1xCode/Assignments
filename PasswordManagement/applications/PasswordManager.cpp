// PasswordManager.h
// Created by Jake Jia on 2023/11/30.
//

#include <iostream>
#include <string>
#include "../lib/bcrypt/include/bcrypt.h"
#include "../models/PasswordManager.h"
#include "../models/PasswordUtils.h"



namespace PasswordManagement {
    PasswordManager::PasswordManager(bool loginLicense/* = false */, bool isExit/* = false */) {
        this->loginLicense = loginLicense;
        this->isExit = isExit;
    }

    bool PasswordManager::getLoginLicense() const {
        return this->loginLicense;
    }
    bool PasswordManager::getIsExit() const {
        return this->isExit;
    }

    void PasswordManager::userInitialize(ConfigManager& configFile, std::string &username, std::string &password) {
        // 开始进行初始化
        std::cout << "Initializing..." << std::endl;

        // 输入用户名
        std::cout << "Please enter username:";
        std::getline(std::cin, username);

        // 输入密码
        std::cout << "Please enter password:";
        std::getline(std::cin, password);

        // 检查密码强度
        while(!isStrongPassword(password)) {
            std::cout << "The password is too weak. Please enter it again." << std::endl;
            std::cout << "Please enter password: ";
            std::getline(std::cin, password);
        }

        // 加密密码
        password = bcrypt::generateHash(password);

        // 将用户名和加密后的密码写入config.txt文件
        configFile.saveConfigFile(username, password);
    }

    void PasswordManager::userLogin(User &user) {
        int numberOfAttempts = 1; // 密码输入尝试次数 一共三次
        std::string cin_password; // 用户的输入的密码
        std::cout << "Welcome to the passwordmanagent, " << user.getUsername() << std::endl;
        std::cout << "Please enter the password." << std::endl;
        while (numberOfAttempts <= 3) {
            std::cout << "Password:";
            std::getline(std::cin, cin_password);

            if (!user.isRightPassword(cin_password)) { // 密码错误
                std::cout << "Password Wrong! Please enter again!" << std::endl;
                std::cout << 3 - numberOfAttempts << " attempts left." << std::endl;
                numberOfAttempts++;
            } else { // 密码正确
                this->loginLicense = true;
                break;
            }
        }
    }

    void PasswordManager::managePasswords() {
        std::cout << "Password Manager" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "1. Add a password" << std::endl;
        std::cout << "2. Remove a password" << std::endl;
        std::cout << "3. View all passwords" << std::endl;
        std::cout << "4. Search for a password" << std::endl; // 新功能：搜索密码


        do {
            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch(choice) {
                case '0':
                    std::cout << "" << std::endl;
                    this->isExit = true;
                    break;
                case '1':
                    // std::string new_username, new_password;
                    std::cout << "输入用户名：";
                    // std::cin >> new_username;
                    std::cout << "输入密码：";
                    // std::cin >> new_password;
                    // passwordManager.addPassword(username, password);
                    break;
                default:
                    std::cout << "Invalid option!" << std::endl;
                    break;
            }


        } while(!this->getIsExit());
    }
}

