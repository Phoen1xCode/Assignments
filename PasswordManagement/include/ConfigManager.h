// ConfigManager.h
// Created by Jake Jia on 2023/12/2.
// �û������ļ�������

#ifndef PASSWORDMANAGEMENT_CONFIGMANAGER_H
#define PASSWORDMANAGEMENT_CONFIGMANAGER_H

#include <string>
#include "../lib/json/json.hpp"

namespace PasswordManagement {
    class ConfigManager {
    public:
        // Ĭ�Ϲ��캯��
        ConfigManager();

        // ���캯��
        ConfigManager(std::string configPath);

        // ���ƹ��캯��
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
