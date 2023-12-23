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
    // �� Credential ����ת��Ϊ JSON
    void to_json(json& j, const Credential& c) {
        j = json{{"type", "Credential"},
                 {"itemName", c.getItemName()},
                 {"username", c.getUsername()},
                 {"password", c.getPassword()}};
    }

    // �� JSON ����ת���� Credential ����
    void from_json(const json& j, Credential& c) {
        c = Credential(j.at("itemName").get<std::string>(),
                       j.at("username").get<std::string>(),
                       j.at("password").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // WebsiteCredential
    // �� WebsiteCredential ����ת��Ϊ JSON
    void to_json(json& j, const WebsiteCredential& wc) {
        j = json{{"type", "WebsiteCredential"},
                 {"itemName", wc.getItemName()},
                 {"username", wc.getUsername()},
                 {"password", wc.getPassword()},
                 {"websiteURL", wc.getWebsiteURL()}};
    }

    // �� JSON ����ת���� WebsiteCredential ����
    void from_json(const json& j, WebsiteCredential& wc) {
        wc = WebsiteCredential(j.at("itemName").get<std::string>(),
                               j.at("username").get<std::string>(),
                               j.at("password").get<std::string>(),
                               j.at("websiteURL").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // BankCardCredential
    // �� BankCredential ����ת��Ϊ JSON
    void to_json(json& j, const BankCardCredential& bcc) {
        j = json{{"type", "BankCardCredential"},
                 {"itemName", bcc.getItemName()},
                 {"username", bcc.getUsername()},
                 {"password", bcc.getPassword()},
                 {"bankName", bcc.getBankName()},
                 {"cardNumber", bcc.getCardNumber()}};
    }

    // �� JSON ����ת���� BankCredential ����
    void from_json(const json& j, BankCardCredential& bcc) {
        bcc = BankCardCredential(j.at("itemName").get<std::string>(),
                                 j.at("username").get<std::string>(),
                                 j.at("password").get<std::string>(),
                                 j.at("bankName").get<std::string>(),
                                 j.at("cardNumber").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // SoftwareCredential
    // �� SoftwareCredential ����ת��Ϊ JSON
    void to_json(json& j, const SoftwareCredential& sc) {
        j = json{{"type", "SoftwareCredential"},
                 {"itemName", sc.getItemName()},
                 {"username", sc.getUsername()},
                 {"password", sc.getPassword()},
                 {"softwareName", sc.getSoftwareName()},
                 {"licenseKey", sc.getLicenseKey()}};
    }

    // �� JSON ����ת���� SoftwareCredential ����
    void from_json(const json& j, SoftwareCredential& sc) {
        sc = SoftwareCredential(j.at("itemName").get<std::string>(),
                                j.at("username").get<std::string>(),
                                j.at("password").get<std::string>(),
                                j.at("softwareName").get<std::string>(),
                                j.at("licenseKey").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */
    // WifiCredential
    // �� WifiCredential ����ת��Ϊ JSON
    void to_json(json& j, const WifiCredential& wc) {
        j = json{{"type", "WifiCredential"},
                 {"itemName", wc.getItemName()},
                 {"username", wc.getUsername()},
                 {"password", wc.getPassword()},
                 {"ssid", wc.getSsid()}};
    }

    // �� JSON ����ת���� WifiCredential ����
    void from_json(const json& j, WifiCredential& wc) {
        wc = WifiCredential(j.at("itemName").get<std::string>(),
                            j.at("username").get<std::string>(),
                            j.at("password").get<std::string>(),
                            j.at("ssid").get<std::string>());
    }
/* ------------------------------------------------------------------------------------------------------------------ */

    // ����ƾ�ݴ��ļ�
    void loadCredentialsFromFile(std::vector<std::unique_ptr<Credential>>& credentials) {
        std::ifstream file("Credentials.json");
        if (!file.is_open()) {
            // �ļ������ڣ�����һ���յ�JSON���鲢����
            json emptyJsonArray = json::array();
            std::ofstream outFile("Credentials.json");
            outFile << emptyJsonArray.dump(4); // �����ʽ����JSON
            outFile.close();
            return; // �ļ����´����ģ�û��ƾ�ݿɼ���
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

    // ����ƾ�ݵ��ļ�
    void saveCredentialsToFile(const std::vector<std::unique_ptr<Credential>>& credentials) {
        json j = json::array(); // ����һ��JSON����

        for (const auto& credential : credentials) {
            json credentialJson;
            // ����ƾ�ݵ�ʵ�����ͣ�ʹ����Ӧ��to_json����
            if (dynamic_cast<WebsiteCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<WebsiteCredential*>(credential.get()));
            } else if (dynamic_cast<BankCardCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<BankCardCredential*>(credential.get()));
            } else if (dynamic_cast<SoftwareCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<SoftwareCredential*>(credential.get()));
            } else if (dynamic_cast<WifiCredential*>(credential.get()) != nullptr) {
                to_json(credentialJson, *dynamic_cast<WifiCredential*>(credential.get()));
            } else {
                to_json(credentialJson, *credential); // Ĭ��Ϊ����Credential����
            }
            j.push_back(credentialJson); // ��ƾ��JSON������ӵ�������
        }

        std::ofstream outFile("Credentials.json");
        if (!outFile.is_open()) {
            throw std::runtime_error("Unable to open file for writing");
        }

        outFile << j.dump(4); // �����ʽ����JSON
        outFile.close();
    }





} // PasswordManagement