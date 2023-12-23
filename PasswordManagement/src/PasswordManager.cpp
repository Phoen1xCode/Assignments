// PasswordManager.h
// Created by Jake Jia on 2023/11/30.
//

#include <string>
#include <iostream>
#include <conio.h>
#include "../include/PasswordManager.h"
#include "../include/PasswordUtils.h"
#include "../include/CredentialManager.h"
#include "../lib/bcrypt/include/bcrypt.h"


namespace PasswordManagement {

    void PasswordManager::userInitialize(ConfigManager &configFile, std::string &username, std::string &password) {
        // 初始化
        std::cout << "初始化过程已启动。" << std::endl;
        /* -------------------------------------------------------------------------------------------------- */

        // 用户配置文件初始化
        // 输入用户名
        std::cout << "请输入您的用户名。" << std::endl;
        std::cout << "用户名：";
        std::getline(std::cin, username);
        while (username.empty()) {
            std::cout << "用户名不能为空。" << std::endl;
            std::cout << "请重新输入您的用户名。" << std::endl;
            std::cout << "用户名：";
            std::getline(std::cin, username);
        }

        // 输入密码
        std::cout << "请输入您的密码。" << std::endl;
        std::cout << "密码：";
        password = getHiddenInput();

        // 检查密码强度
        while (!isStrongPassword(password)) {
            std::cout << "您的密码太弱。请重新输入。" << std::endl;
            std::cout << "密码：";
            password = getHiddenInput();
        }

        std::string verify_password;
        std::cout << "请确认您的密码。" << std::endl;
        std::cout << "确认密码：";
        verify_password = getHiddenInput();

        while (password != verify_password) {
            std::cout << "两次输入的密码不匹配。" << std::endl;
            std::cout << "请重新输入以确认密码。" << std::endl;
            std::cout << "确认密码：";
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
        if (!configFile.findConfigFile()) { // 检查是否有用户配置文件
            configFile.createConfigFile(); // 没有则创建一个空的默认用户配置文件
            userInitialize(configFile, username, password); // 进行初始化
        } else if (!configFile.checkConfigFile()) {
            userInitialize(configFile, username, password); // 进行初始化
        } else {
            configFile.readConfigFile(username, password); // 有则读取配置文件中的用户名和密码
        }

        PasswordManagement::User admin(username, password);
        admin.userLogin(); // 用户登陆界面
        if (!admin.getLoginLicense()) { // 尝试次数超过三次 关闭程序
            std::cout << "尝试次数太多。正在退出..." << std::endl;
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
        while (true) {
            /* -------------------------------------------------------------------------------------------------- */
            std::cout << "密码管理器" << std::endl;
            std::cout << "0. 退出" << std::endl; // 退出程序
            std::cout << "1. 添加密码" << std::endl; // 添加密码凭证
            std::cout << "2. 删除密码" << std::endl; // 删除密码凭证
            std::cout << "3. 查看所有项目" << std::endl; // 查看密码凭证
            std::cout << "4. 修改密码" << std::endl; // 修改密码凭证
            std::cout << "5. 搜索密码" << std::endl; // 搜索密码凭证
            std::cout << "6. 生成随机密码" << std::endl; // 生成随机密码
            /* -------------------------------------------------------------------------------------------------- */

            std::cout << "请输入您的选择：";
            std::cin >> choice;
            clearScreen();
            switch (choice) {
                case 0:
                    std::cout << "正在退出程序..." << std::endl;
                    return;
                case 1:
                    addPassword();
                    saveCredentialsToFile(this->credentials);
                    clearScreen();
                    break;
                case 2:
                    removePassword();
                    saveCredentialsToFile(this->credentials);
                    std::cout << "请按任意键继续..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 3:
                    displayItemNames();
                    std::cout << "请按任意键继续..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 4:
                    changePassword();
                    saveCredentialsToFile(this->credentials);
                    std::cout << "请按任意键继续..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 5:
                    searchForPassword();
                    std::cout << "请按任意键继续..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 6:
                    generateRandomPassword();
                    break;
                default:
                    std::cout << "无效选项！" << std::endl;
                    break;
            }
        }
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    void PasswordManager::addPassword() {
        int type;

        std::cout << "选择要添加的凭证类型：" << std::endl;
        std::cout << "0. 凭证" << std::endl;
        std::cout << "1. 网站凭证" << std::endl;
        std::cout << "2. 银行卡凭证" << std::endl;
        std::cout << "3. 软件凭证" << std::endl;
        std::cout << "4. Wifi 凭证" << std::endl;
        std::cout << "请输入您的选择：";
        std::cin >> type;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略直到遇到换行符的所有字符

        switch (type) {
            case 0: { // 凭证
                std::string itemName, username, password;

                std::cout << "输入项目名称：";
                std::getline(std::cin, itemName);

                std::cout << "输入用户名：";
                std::getline(std::cin, username);

                std::cout << "输入密码：";
                std::getline(std::cin, password);

                // 加密密码
                password = encryptPassword(password, this->key);

                credentials.push_back(std::make_unique<Credential>(itemName, username, password));
                break;
            }
            case 1: { // 网站凭证
                std::string itemName, username, password;
                std::string websiteURL;

                std::cout << "输入项目名称：";
                std::getline(std::cin, itemName);

                std::cout << "输入用户名：";
                std::getline(std::cin, username);

                std::cout << "输入密码：";
                std::getline(std::cin, password);

                // 加密密码
                password = encryptPassword(password, this->key);

                std::cout << "输入网站 URL：";
                std::getline(std::cin, websiteURL);

                credentials.push_back(std::make_unique<WebsiteCredential>(itemName, username, password, websiteURL));
                break;
            }
            case 2: { // 银行卡凭证
                std::string itemName, username, password;
                std::string bankName, cardNumber;

                std::cout << "输入项目名称：";
                std::getline(std::cin, itemName);

                std::cout << "输入银行名称：";
                std::getline(std::cin, bankName);

                std::cout << "输入卡号：";
                std::getline(std::cin, cardNumber);

                std::cout << "输入用户名：";
                std::getline(std::cin, username);

                std::cout << "输入密码：";
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

                std::cout << "输入项目名称：";
                std::getline(std::cin, itemName);

                std::cout << "输入软件名称：";
                std::getline(std::cin, softwareName);

                std::cout << "输入许可证密钥：";
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

                std::cout << "输入项目名称：";
                std::getline(std::cin, itemName);

                std::cout << "输入SSID：";
                std::getline(std::cin, ssid);

                std::cout << "输入密码：";
                std::getline(std::cin, password);

                credentials.push_back(std::make_unique<WifiCredential>(itemName, username, password, ssid));
                break;
            }
            default:
                std::cout << "无效类型！" << std::endl;
                break;
        }
        std::cout << "凭证添加成功！" << std::endl;
    }

    void PasswordManager::removePassword() {
        displayItemNames();
        std::string itemName;
        std::cout << "输入要删除密码的项目名称：";
        std::cin >> itemName;

        auto it = std::find_if(credentials.begin(), credentials.end(),
                               [&itemName](const std::unique_ptr<Credential> &credential) {
                                   return credential->getItemName() == itemName;
                               });

        if (it != credentials.end()) {
            credentials.erase(it);
            std::cout << "密码删除成功！" << std::endl;
        } else {
            std::cout << "未找到密码！" << std::endl;
        }
    }

    void PasswordManager::displayItemNames() {
        int count = 1;

        std::cout << "项目：" << std::endl;
        for (const auto &credential : credentials) {
            std::cout << count << ". ";
            std::cout << "项目名称：" << credential->getItemName();
            std::cout << std::endl;
            count++;
        }
    }

    void PasswordManager::changePassword() {
        displayItemNames();

        std::string itemName, newPassword;
        std::cout << "输入要更改密码的项目名称：";
        std::cin >> itemName;
        std::cout << "输入新密码：";
        std::cin >> newPassword;

        // 加密密码
        newPassword = encryptPassword(newPassword, this->key);

        for (auto &credential: credentials) {
            if (credential->getItemName() == itemName) {
                // 在这里无需动态转换，因为 setPassword 是基类的方法
                credential->setPassword(newPassword);
                std::cout << "密码更改成功！" << std::endl;
                return;
            }
        }
        std::cout << "未找到密码！" << std::endl;
    }

    void PasswordManager::searchForPassword() {
        displayItemNames();

        std::string itemName;
        std::cout << "输入要搜索密码的项目名称：";
        std::cin >> itemName;

        for (const auto &credential: credentials) {
            if (credential->getItemName() == itemName) {
                std::cout << "/* ----------------------------------------------------------- */" << std::endl;
                credential->display();
                std::cout << "/* ----------------------------------------------------------- */" << std::endl;

                std::cout << "是否显示明文密码？（y/n）" << std::endl;
                std::cout << "请输入您的选择：";
                char choice;
                std::cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    std::string cipherPassword = credential->getPassword();
                    std::string plainPassword = decryptPassword(cipherPassword, this->key);
                    std::cout << "密码：" << plainPassword << std::endl;
                } else {
                    std::cout << "无效选项！" << std::endl;
                    return;
                }
            }
        }
    }

    void PasswordManager::generateRandomPassword() {
        std::cout << "请输入生成的随机密码长度（>= 6）：";

        int length;
        std::cin >> length;

        std::string randomPassword = generatePassword(length);
        std::cout << "生成的密码：" << randomPassword << std::endl;

        std::cout << "是否将密码复制到剪贴板？（y/n）" << std::endl;
        std::cout << "请输入您的选择：";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (CopyTextToClipboard(randomPassword)) {
                std::cout << "密码已复制到剪贴板。" << std::endl;
            } else {
                std::cout << "复制密码到剪贴板失败。" << std::endl;
            }
        }
        clearScreen();
    }

    void PasswordManager::clearScreen() {
        Sleep(500);
        system("cls");
    }



}