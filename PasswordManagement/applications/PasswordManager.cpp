// PasswordManager.h
// Created by Jake Jia on 2023/11/30.
//

#include <string>
#include <iostream>
#include <conio.h>
#include "../models/PasswordManager.h"
#include "../models/PasswordUtils.h"
#include "../models/CredentialManager.h"
#include "../lib/bcrypt/include/bcrypt.h"


namespace PasswordManagement {

    void PasswordManager::userInitialize(ConfigManager& configFile, std::string &username, std::string &password) {
        // 初始化
        std::cout << "Initialization process started." << std::endl;
        /* -------------------------------------------------------------------------------------------------- */

        // 用户配置文件初始化
        // 输入用户名
        std::cout << "Please enter your username." << std::endl;
        std::cout << "Username:";
        std::getline(std::cin, username);
        while(username.empty()) {
            std::cout << "Username cannot be empty." << std::endl;
            std::cout << "Please enter your username again." << std::endl;
            std::cout << "Username:";
            std::getline(std::cin, username);
        }

        // 输入密码
        std::cout << "Please enter your password." << std::endl;
        std::cout << "Password:";
        password = getHiddenInput();

        // 检查密码强度
        while(!isStrongPassword(password)) {
            std::cout << "Your password is too weak. Please enter it again."<< std::endl;
            std::cout << "Password:";
            password = getHiddenInput();
        }

        std::string verify_password;
        std::cout << "Please confirm your password." << std::endl;
        std::cout << "Confirm password:";
        verify_password = getHiddenInput();

        while(password != verify_password) {
            std::cout << "The passwords entered twice do not match. " << std::endl;
            std::cout << "Please re-enter to confirm the password." << std::endl;
            std::cout << "Confirm password:";
            verify_password = getHiddenInput();
        }

        // 加密密码
        password = bcrypt::generateHash(password);

        // 将用户名和加密后的密码写入config.json文件
        configFile.saveConfigFile(username, password);

        /* -------------------------------------------------------------------------------------------------- */

        // 密钥文件初始化
        keyInitialization();

        /* -------------------------------------------------------------------------------------------------- */
        clearScreen();
    }

    bool PasswordManager::loginPasswordManagement() {
        std::string username, password; // username 用户名 | password 密码
        std::string configFileName = "config.json";

        PasswordManagement::ConfigManager configFile(configFileName);
        if(!configFile.findConfigFile() ) { // 检查是否有用户配置文件
            configFile.createConfigFile(); // 没有则创建一个空的默认用户配置文件
            userInitialize(configFile, username, password); // 进行初始化
        } else if(!configFile.checkConfigFile()) {
            userInitialize(configFile, username, password); // 进行初始化
        } else {
            configFile.readConfigFile(username, password); // 有则读取配置文件中的用户名和密码
        }

        PasswordManagement::User admin(username, password);
        admin.userLogin(); // 用户登陆界面
        if(!admin.getLoginLicense()) { // 尝试次数超过三次 关闭程序
            std::cout << "Too many attempts. Exiting..." << std::endl;
            return false;
        } else {
            return true;
        }
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    void PasswordManager::managePasswords() {
        clearScreen();
        /* -------------------------------------------------------------------------------------------------- */
        // 从 key.json 载入密钥
        keyLoad(this->key);
        // 从 credentials.json 载入已保存的数据
        loadCredentialsFromFile(this->credentials);
        /* -------------------------------------------------------------------------------------------------- */

        /* -------------------------------------------------------------------------------------------------- */
        int choice;
        while(true) {
            /* -------------------------------------------------------------------------------------------------- */
            std::cout << "Password Manager" << std::endl;
            std::cout << "0. Exit" << std::endl; // 退出程序
            std::cout << "1. Add a password" << std::endl; // 添加密码凭证
            std::cout << "2. Remove a password" << std::endl; // 删除密码凭证
            std::cout << "3. View all Item" << std::endl; // 查看密码凭证
            std::cout << "4. Change a password" << std::endl; // 修改密码凭证
            std::cout << "5. Search for a password" << std::endl; // 搜索密码凭证
            std::cout << "6. Generate random password" << std::endl; // 生成随机密码
            /* -------------------------------------------------------------------------------------------------- */

            std::cout << "Enter your choice:";
            std::cin >> choice;
            clearScreen();
            switch (choice) {
                case 0:
                    std::cout << "Exiting program..." << std::endl;
                    return;
                case 1:
                    addPassword();
                    saveCredentialsToFile(this->credentials);
                    clearScreen();
                    break;
                case 2:
                    removePassword();
                    saveCredentialsToFile(this->credentials);
                    std::cout << "Press any key to continue..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 3:
                    displayItemNames();
                    std::cout << "Press any key to continue..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 4:
                    changePassword();
                    saveCredentialsToFile(this->credentials);
                    std::cout << "Press any key to continue..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 5:
                    searchForPassword();
                    std::cout << "Press any key to continue..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 6:
                    generateRandomPassword();
                    break;
                default:
                    std::cout << "Invalid option!" << std::endl;
                    break;
            }
        }
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    void PasswordManager::addPassword() {
        int type;

        std::cout << "Select type of credential to add:" << std::endl;
        std::cout << "0. Credential" << std::endl;
        std::cout << "1. Website Credential" << std::endl;
        std::cout << "2. Bank Card Credential" << std::endl;
        std::cout << "3. Software Credential" << std::endl;
        std::cout << "4. Wifi Credential" << std::endl;
        std::cout << "Please enter your choice:";
        std::cin >> type;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略直到遇到换行符的所有字符

        switch(type) {
            case 0: { // Credential
                std::string itemName, username, password;

                std::cout << "Enter item name:";
                std::getline(std::cin, itemName);

                std::cout << "Enter username:";
                std::getline(std::cin, username);

                std::cout << "Enter password:";
                std::getline(std::cin, password);

                // 加密密码
                password = encryptPassword(password, this->key);

                credentials.push_back(std::make_unique<Credential>(itemName, username, password));
                break;
            }
            case 1: { // Website Credential
                std::string itemName, username, password;
                std::string websiteURL;

                std::cout << "Enter item name:";
                std::getline(std::cin, itemName);

                std::cout << "Enter username:";
                std::getline(std::cin, username);

                std::cout << "Enter password:";
                std::getline(std::cin, password);

                // 加密密码
                password = encryptPassword(password, this->key);

                std::cout << "Enter website URL:";
                std::getline(std::cin, websiteURL);

                credentials.push_back(std::make_unique<WebsiteCredential>(itemName, username, password, websiteURL));
                break;
            }
            case 2: { // Bank Card Credential
                std::string itemName, username, password;
                std::string bankName, cardNumber;

                std::cout << "Enter item name:";
                std::getline(std::cin, itemName);

                std::cout << "Enter bank name:";
                std::getline(std::cin, bankName);

                std::cout << "Enter card number:";
                std::getline(std::cin, cardNumber);

                std::cout << "Enter username:";
                std::getline(std::cin, username);

                std::cout << "Enter password:";
                std::getline(std::cin, password);

                // 加密密码
                password = encryptPassword(password, this->key);

                credentials.push_back(
                        std::make_unique<BankCardCredential>(itemName, username, password, bankName, cardNumber));
                break;
            }
            case 3: {
                std::string itemName, username, password;
                std::string softwareName, licenseKey;

                std::cout << "Enter item name:";
                std::getline(std::cin, itemName);

                std::cout << "Enter software name:";
                std::getline(std::cin, softwareName);

                std::cout << "Enter license key:";
                std::getline(std::cin, licenseKey);

                // 加密密码
                password = encryptPassword(licenseKey, this->key);
                // 加密凭证
                licenseKey = encryptPassword(licenseKey, this->key);

                credentials.push_back(
                        std::make_unique<SoftwareCredential>(itemName, username, password, softwareName, licenseKey));
                break;
            }
            case 4: {
                std::string itemName, username, password;
                std::string ssid;

                std::cout << "Enter item name:";
                std::getline(std::cin, itemName);

                std::cout << "Enter SSID:";
                std::getline(std::cin, ssid);

                std::cout << "Enter password:";
                std::getline(std::cin, password);

                credentials.push_back(std::make_unique<WifiCredential>(itemName, username, password, ssid));
                break;
            }
            default:
                std::cout << "Invalid type!" << std::endl;
                break;
        }
        std::cout << "Credential added successfully!" << std::endl;

    }

    void PasswordManager::removePassword() {
        displayItemNames();
        std::string itemName;
        std::cout << "Enter item name of the password to remove:";
        std::cin >> itemName;

        auto it = std::find_if(credentials.begin(), credentials.end(),
                               [&itemName](const std::unique_ptr<Credential> &credential) {
                                   return credential->getItemName() == itemName;
                               });

        if (it != credentials.end()) {
            credentials.erase(it);
            std::cout << "Password removed successfully!" << std::endl;
        } else {
            std::cout << "Password not found!" << std::endl;
        }
    }

    void PasswordManager::displayItemNames() {
        int count = 1;
        for (const auto& credential : credentials) {
            std::cout << count << ". ";
            std::cout << "Item Name: " << credential->getItemName();
            std::cout << std::endl;
            count++;
        }
    }


    void PasswordManager::changePassword() {
        displayItemNames();

        std::string itemName, newPassword;
        std::cout << "Enter item name of the password to change:";
        std::cin >> itemName;
        std::cout << "Enter new password:";
        std::cin >> newPassword;

        // 加密密码
        newPassword = encryptPassword(newPassword, this->key);

        for (auto &credential: credentials) {
            if (credential->getItemName() == itemName) {
                // No need for dynamic casting here since setPassword is a method of the base class
                credential->setPassword(newPassword);
                std::cout << "Password changed successfully!" << std::endl;
                return;
            }
        }
        std::cout << "Password not found!" << std::endl;
    }

    void PasswordManager::searchForPassword() {
        displayItemNames();

        std::string itemName;
        std::cout << "Enter item name of the password to search for: ";
        std::cin >> itemName;

        for (const auto &credential: credentials) {
            if (credential->getItemName() == itemName) {
                std::cout << "/* ----------------------------------------------------------- */" << std::endl;
                credential->display();
                std::cout << "/* ----------------------------------------------------------- */" << std::endl;


                std::cout << "Would you like to show the plain password? (y/n)" << std::endl;
                std::cout << "Please enter your choice:";
                char choice;
                std::cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    std::string cipherPassword = credential->getPassword();
                    std::string plainPassword = decryptPassword(cipherPassword, this->key);
                    std::cout << "Password:" << plainPassword << std::endl;
                } else {
                    std::cout << "Invalid options!" << std::endl;
                    return;
                }
            } else {
                std::cout << "Password not found!" << std::endl;
            }
        }
    }

    void PasswordManager::generateRandomPassword() {
        std::cout << "Please enter the length oh the random password:";

        int length;
        std::cin >> length;

        std::string randomPassword = generatePassword(length);
        std::cout << "Generated password: " << randomPassword << std::endl;

        std::cout << "Would you like to copy the password to the clipboard? (y/n)" << std::endl;
        std::cout << "Please enter your choice:";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (CopyTextToClipboard(randomPassword)) {
                std::cout << "Password copied to clipboard." << std::endl;
            } else {
                std::cout << "Failed to copy password to clipboard." << std::endl;
            }
        }
        clearScreen();
    }

    void PasswordManager::clearScreen() {
        Sleep(500);
        system("cls");
    }



}