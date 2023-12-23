// CredentialManager.h
// Created by Jake Jia on 2023/12/8.
//

#ifndef PASSWORDMANAGEMENT_CREDENTIALMANAGER_H
#define PASSWORDMANAGEMENT_CREDENTIALMANAGER_H
#include "Credential.h"
#include "../lib/json/json.hpp"
#include "../lib/cryptopp/aes.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/modes.h"
#include "../lib/cryptopp/osrng.h"

namespace PasswordManagement {

    using json = nlohmann::json;
/* ------------------------------------------------------------------------------------------------------------------ */
    // 保存JSON文件
    // Credential
    void to_json(json& j, const Credential& c); // 将 Credential 对象转换为 JSON
    void from_json(const json& j, Credential& c); // 从 JSON 对象转换回 Credential 对象

    // WebsiteCredential
    void to_json(json& j, const WebsiteCredential& wc);
    void from_json(const json& j, WebsiteCredential& wc);

    // BankCardCredential
    void to_json(json& j, const BankCardCredential& bcc);
    void from_json(const json& j, BankCardCredential& bcc);

    // SoftwareCredential
    void to_json(json& j, const SoftwareCredential& sc);
    void from_json(const json& j, SoftwareCredential& sc);

    // WifiCredential
    void to_json(json& j, const WifiCredential& wc);
    void from_json(const json& j, WifiCredential& wc);

/* ------------------------------------------------------------------------------------------------------------------ */
    // 加载凭据从文件
    void loadCredentialsFromFile(std::vector<std::unique_ptr<Credential>>& credentials);
    // 保存凭据到文件
    void saveCredentialsToFile(const std::vector<std::unique_ptr<Credential>>& credentials);




} // PasswordManagement

#endif //PASSWORDMANAGEMENT_CREDENTIALMANAGER_H
