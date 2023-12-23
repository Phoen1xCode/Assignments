// ConfigManager.h
// Created by Jake Jia on 2023/12/2.
// 用户配置文件控制类

#ifndef PASSWORDMANAGEMENT_CONFIGMANAGER_H
#define PASSWORDMANAGEMENT_CONFIGMANAGER_H

#include <string>
#include "../lib/json/json.hpp"

namespace PasswordManagement {
    class ConfigManager {
    public:
        // 默认构造函数
        ConfigManager();

        // 构造函数
        ConfigManager(std::string configPath);

        // 复制构造函数
        ConfigManager(const ConfigManager& other);


        bool findConfigFile();
        void createConfigFile();
        bool checkConfigFile();
        void readConfigFile(std::string &username, std::string &password);
        void saveConfigFile(const std::string &username, const std::string &password);

    private:
        std::string configPath;
    };

} // PasswordManagement

#endif //PASSWORDMANAGEMENT_CONFIGMANAGER_H
