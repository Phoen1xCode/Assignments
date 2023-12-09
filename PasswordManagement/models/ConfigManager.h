// ConfigManager.h
// Created by Jake Jia on 2023/12/2.
// 文件控制类

#ifndef PASSWORDMANAGEMENT_CONFIGMANAGER_H
#define PASSWORDMANAGEMENT_CONFIGMANAGER_H

#include <string>

namespace PasswordManagement {
    class ConfigManager {
    public:
        // 构造函数
        ConfigManager(std::string configPath);

        // 复制构造函数
        ConfigManager(ConfigManager& other);

        std::string getConfigPath() const;

        bool findConfigFile();
        void createConfigFile();
        bool checkConfigFile();
        void readConfigFile(std::string &username, std::string &password);
        void saveConfigFile(std::string &username, std::string &password);
    private:
        std::string configPath;
    };

} // PasswordManagement

#endif //PASSWORDMANAGEMENT_CONFIGMANAGER_H
