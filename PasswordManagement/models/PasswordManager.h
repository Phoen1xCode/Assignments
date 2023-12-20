// PasswordManager.h
// Created by Jake Jia on 2023/11/30.
//


#ifndef PASSWORDMANAGEMENT_PASSWORDMANAGER_H
#define PASSWORDMANAGEMENT_PASSWORDMANAGER_H

#include <string>
#include <windows.h>
#include "User.h"
#include "KeyManager.h"
#include "Credential.h"
#include "ConfigManager.h"
#include "../lib/cryptopp/aes.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/modes.h"
#include "../lib/cryptopp/osrng.h"


namespace PasswordManagement {
    class PasswordManager {
    public:

        bool loginPasswordManagement(); // 登录界面

        void managePasswords(); // 控制台 密码管理器界面基本逻辑

        void addPassword();

        void removePassword();

        void displayItemNames();

        void changePassword();

        void searchForPassword();

        void generateRandomPassword();

        void userInitialize(ConfigManager& configFile, std::string& username, std::string& password); // 进行用户初始化

        inline void clearScreen();



    private:
        std::vector<std::unique_ptr<Credential>> credentials; // Store pointers to Credential objects
        CryptoPP::SecByteBlock key;
    };

}


#endif //PASSWORDMANAGEMENT_PASSWORDMANAGER_H
