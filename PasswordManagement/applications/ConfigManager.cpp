// ConfigManager.cpp
// Created by Jake Jia on 2023/12/2.
//

#include "../models/ConfigManager.h"
#include <fstream>
#include <utility>
#include <iostream>

namespace PasswordManagement {

    ConfigManager::ConfigManager(std::string configPath) {
        this->configPath = std::move(configPath);
    }

    ConfigManager::ConfigManager(ConfigManager &other) {
        this->configPath = other.configPath;
    }

    std::string ConfigManager::getConfigPath() const {
        return this->configPath;
    }

    bool ConfigManager::findConfigFile() {
        std::ifstream configFile(this->configPath);
        return configFile.good();
    }

    void ConfigManager::createConfigFile() {
        std::ofstream configFile(this->configPath);
        if (configFile.is_open()) {
            configFile << "username:" << std::endl; // 写入默认配置
            configFile << "password:" << std::endl;
            configFile.close();
            // std::cout << "已创建 config.txt 文件并写入默认用户名和密码." << std::endl;
        } else {
            std::cerr << "无法创建 config.txt 文件." << std::endl;
        }
    }

    bool ConfigManager::checkConfigFile() {
        std::ifstream configFile(this->configPath);

        if(!configFile.is_open()) {
            std::cerr << "无法打开 config.txt 文件." << std::endl;
        }
        std::string line; // 存储每次从文件中读取的一行内容
        // 使用 std::getline 函数从配置文件 (configFile) 中读取一行内容，并将其存储到 line 变量中
        // 这个循环会一直执行，直到读取到文件末尾
        while (std::getline(configFile, line)) {
            size_t colonPos = line.find(':');

            // 使用 find(':') 函数查找当前行中是否包含冒号 :，返回冒号在字符串中的位置
            // 如果找到了冒号，则 colonPos 将存储冒号的位置（索引值），否则 colonPos 将等于 std::string::npos，表示没有找到冒号
            if (colonPos != std::string::npos) {
                // 使用 substr 函数从当前行中提取从开头到冒号之前的部分，即键的部分，并将其存储到 key 变量中
                std::string key = line.substr(0, colonPos);
                // 使用 substr 函数从当前行中提取从冒号后到行末的部分，即值的部分，并将其存储到 value 变量中
                std::string value = line.substr(colonPos + 1);
                if (key.empty()) {
                    configFile.close();
                    return false;
                }
            }
        }
        configFile.close();
        return true;
    }

    void ConfigManager::readConfigFile(std::string &username, std::string &password) {
        std::ifstream configFile(this->configPath);

        if (!configFile.is_open()) {
            std::cerr << "无法打开 config.txt 文件." << std::endl;
        }

        std::string line; // 存储每次从文件中读取的一行内容
        // 使用 std::getline 函数从配置文件 (configFile) 中读取一行内容，并将其存储到 line 变量中
        // 这个循环会一直执行，直到读取到文件末尾
        while (std::getline(configFile, line)) {
            size_t colonPos = line.find(':');

            // 使用 find(':') 函数查找当前行中是否包含冒号 :，返回冒号在字符串中的位置
            // 如果找到了冒号，则 colonPos 将存储冒号的位置（索引值），否则 colonPos 将等于 std::string::npos，表示没有找到冒号
            if (colonPos != std::string::npos) {
                // 使用 substr 函数从当前行中提取从开头到冒号之前的部分，即键的部分，并将其存储到 key 变量中
                std::string key = line.substr(0, colonPos);
                // 使用 substr 函数从当前行中提取从冒号后到行末的部分，即值的部分，并将其存储到 value 变量中
                std::string value = line.substr(colonPos + 1);
                if (key == "username") {
                    username = value;
                } else if (key == "password") {
                    password = value;
                }
            }
        }
        configFile.close();
    }

    void ConfigManager::saveConfigFile(std::string &username, std::string &password) {
        std::ofstream configFile(this->configPath);
        if(configFile.is_open()) {
            configFile << "username:" << username << std::endl;
            configFile << "password:" << password << std::endl;
            configFile.close();
            // std::cout << "Credentials saved successfully." << std::endl;
        } else {
            std::cerr << "无法打开 config.txt 文件." << std::endl;
        }
    }

} // PasswordManagement