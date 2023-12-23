// CredentialManager.cpp
// Created by Jake Jia on 2023/12/8.
//

#include <fstream>
#include <string>
#include "../include/CredentialManager.h"
#include "../include/PasswordUtils.h"

namespace PasswordManagement {

    using json = nlohmann::json;
/* ------------------------------------------------------------------------------------------------------------------ */
    // Credential
    // 将 Credential 对象转换为 JSON
    void to_json(json& j, const Credential& c) {
        j = json{{"type", "Credential"},
                 {"itemName", c.getItemName()},
                 {"username", c.getUsername()},
                 {"password", c.getPassword()}};
    }

    // 从 JSON 对象转换回 Credential 对象
    void from_json(const json& j, Credential& c) {
        c = Credential(j.at("itemName").get<std::string>(),
                       j.at("username").get<std::string>(),
                       j.at("password").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // WebsiteCredential
    // 将 WebsiteCredential 对象转换为 JSON
    void to_json(json& j, const WebsiteCredential& wc) {
        j = json{{"type", "WebsiteCredential"},
                 {"itemName", wc.getItemName()},
                 {"username", wc.getUsername()},
                 {"password", wc.getPassword()},
                 {"websiteURL", wc.getWebsiteURL()}};
    }

    // 从 JSON 对象转换回 WebsiteCredential 对象
    void from_json(const json& j, WebsiteCredential& wc) {
        wc = WebsiteCredential(j.at("itemName").get<std::string>(),
                               j.at("username").get<std::string>(),
                               j.at("password").get<std::string>(),
                               j.at("websiteURL").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // BankCardCredential
    // 将 BankCredential 对象转换为 JSON
    void to_json(json& j, const BankCardCredential& bcc) {
        j = json{{"type", "BankCardCredential"},
                 {"itemName", bcc.getItemName()},
                 {"username", bcc.getUsername()},
                 {"password", bcc.getPassword()},
                 {"bankName", bcc.getBankName()},
                 {"cardNumber", bcc.getCardNumber()}};
    }

    // 从 JSON 对象转换回 BankCredential 对象
    void from_json(const json& j, BankCardCredential& bcc) {
        bcc = BankCardCredential(j.at("itemName").get<std::string>(),
                                 j.at("username").get<std::string>(),
                                 j.at("password").get<std::string>(),
                                 j.at("bankName").get<std::string>(),
                                 j.at("cardNumber").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // SoftwareCredential
    // 将 SoftwareCredential 对象转换为 JSON
    void to_json(json& j, const SoftwareCredential& sc) {
        j = json{{"type", "SoftwareCredential"},
                 {"itemName", sc.getItemName()},
                 {"username", sc.getUsername()},
                 {"password", sc.getPassword()},
                 {"softwareName", sc.getSoftwareName()},
                 {"licenseKey", sc.getLicenseKey()}};
    }

    // 从 JSON 对象转换回 SoftwareCredential 对象
    void from_json(const json& j, SoftwareCredential& sc) {
        sc = SoftwareCredential(j.at("itemName").get<std::string>(),
                                j.at("username").get<std::string>(),
                                j.at("password").get<std::string>(),
                                j.at("softwareName").get<std::string>(),
                                j.at("licenseKey").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // WifiCredential
    // 将 WifiCredential 对象转换为 JSON
    void to_json(json& j, const WifiCredential& wc) {
        j = json{{"type", "WifiCredential"},
                 {"itemName", wc.getItemName()},
                 {"username", wc.getUsername()},
                 {"password", wc.getPassword()},
                 {"ssid", wc.getSsid()}};
    }

    // 从 JSON 对象转换回 WifiCredential 对象
    void from_json(const json& j, WifiCredential& wc) {
        wc = WifiCredential(j.at("itemName").get<std::string>(),
                            j.at("username").get<std::string>(),
                            j.at("password").get<std::string>(),
                            j.at("ssid").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */

    // 加载凭据从文件
    void loadCredentialsFromFile(std::vector<std::unique_ptr<Credential>>& credentials) {
        std::ifstream file("Credentials.json");
        if (!file.is_open()) {
            // 文件不存在，创建一个空的JSON数组并保存
            json emptyJsonArray = json::array();
            std::ofstream outFile("Credentials.json");
            outFile << emptyJsonArray.dump(4); // 保存格式化的JSON
            outFile.close();
            return; // 文件是新创建的，没有凭据可加载
        }

        json j;
        file >> j;
        file.close();

        for (const auto& item : j) {
            std::string type = item.at("type").get<std::string>();
            if (type == "Credential") {
                credentials.push_back(std::make_unique<Credential>(item.get<Credential>()));
            } else if (type == "WebsiteCredential") {
                credentials.push_back(std::make_unique<WebsiteCredential>(item.get<WebsiteCredential>()));
            } else if (type == "BankCardCredential") {
                credentials.push_back(std::make_unique<BankCardCredential>(item.get<BankCardCredential>()));
            } else if (type == "SoftwareCredential") {
                credentials.push_back(std::make_unique<SoftwareCredential>(item.get<SoftwareCredential>()));
            } else if (type == "WifiCredential") {
                credentials.push_back(std::make_unique<WifiCredential>(item.get<WifiCredential>()));
            } else {
                throw std::runtime_error("Unknown credential type");
            }
        }
    }

    // 保存凭据到文件
    void saveCredentialsToFile(const std::vector<std::unique_ptr<Credential>>& credentials) {
        json j = json::array(); // 创建一个JSON数组

        for (const auto& credential : credentials) {
            json credentialJson;
            // 根据凭据的实际类型，使用相应的to_json函数
            if (dynamic_cast<WebsiteCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<WebsiteCredential*>(credential.get()));
            } else if (dynamic_cast<BankCardCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<BankCardCredential*>(credential.get()));
            } else if (dynamic_cast<SoftwareCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<SoftwareCredential*>(credential.get()));
            } else if (dynamic_cast<WifiCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<WifiCredential*>(credential.get()));
            } else {
                to_json(credentialJson, *credential); // 默认为基础Credential类型
            }
            j.push_back(credentialJson); // 将凭据JSON对象添加到数组中
        }

        std::ofstream outFile("Credentials.json");
        if (!outFile.is_open()) {
            throw std::runtime_error("Unable to open file for writing");
        }

        outFile << j.dump(4); // 保存格式化的JSON
        outFile.close();
    }





} // PasswordManagement