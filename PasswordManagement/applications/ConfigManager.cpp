// ConfigManager.cpp
// Created by Jake Jia on 2023/12/2.
// 用户配置文件类具体实现

#include <iostream>
#include <fstream>
#include <utility>
#include "../models/ConfigManager.h"

namespace PasswordManagement {
    using json = nlohmann::json;

    ConfigManager::ConfigManager() {
        this->configPath = "config.json";
    }

    ConfigManager::ConfigManager(std::string configPath) {
        this->configPath = std::move(configPath);
    }

    ConfigManager::ConfigManager(const ConfigManager &other) {
        this->configPath = other.configPath;
    }

    bool ConfigManager::findConfigFile() {
        std::ifstream configFile(this->configPath);
        return configFile.good();
    }

    void ConfigManager::createConfigFile() {
        json configJson = {
                {"username", ""},
                {"password", ""}
        };
        std::ofstream configFile(this->configPath);

        if(!configFile.is_open()) {
            std::cerr << "Failed to create configuration file." << std::endl;
            return;
        }

        configFile << configJson.dump(4);
        configFile.close();
   }

    bool ConfigManager::checkConfigFile() {
        std::ifstream configFile(this->configPath);
        if (!configFile.is_open()) {
            std::cerr << "Unable to open the configuration file." << std::endl;
            return false;
        }

        try {
            json configJson;
            configFile >> configJson;

            return !configJson.at("username").get<std::string>().empty() &&
                   !configJson.at("password").get<std::string>().empty();
        } catch (const json::parse_error& e) {
            std::cerr << "Configuration file content is not valid JSON: " << e.what() << std::endl;
        } catch (const json::out_of_range& e) {
            std::cerr << "Configuration file is missing required fields: " << e.what() << std::endl;
        }

        return false;
    }


    void ConfigManager::readConfigFile(std::string &username, std::string &password) {
        std::ifstream configFile(this->configPath);
        if(!configFile.is_open()) {
            std::cerr << "Failed to open configuration file." << std::endl;
            throw std::runtime_error("Failed to open configuration file.");
        } else {
            json configJson;
            try {
                configFile >> configJson;
            } catch (const json::parse_error& e) {
                std::cerr << "Configuration file content is not valid JSON: " << e.what() << std::endl;
                configFile.close();
                throw;
            }
            configFile.close();

            username = configJson.value("username", "");
            password = configJson.value("password", "");
        }
    }

    void ConfigManager::saveConfigFile(const std::string &username, const std::string &password) {
        json configJson = {
                {"username", username},
                {"password", password}
        };

        std::ofstream configFile(this->configPath);
        if (!configFile.is_open()) {
            std::cerr << "Failed to open configuration file." << std::endl;
            return;
        }

        configFile << configJson.dump(4);
        configFile.close();
    }
} // PasswordManagement