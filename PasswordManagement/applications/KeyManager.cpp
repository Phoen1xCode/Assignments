// KeyManager.cpp
// Created by Jake Jia on 2023/12/15.
//


#include "../models/KeyManager.h"
#include "../lib/json/json.hpp"
namespace PasswordManagement {
    using json = nlohmann::json;

/* ------------------------------------------------------------------------------------------------------------------ */
    // 简单的凯撒密码加密
    std::string Caesar_encryptPassword(const std::string& plainPassword)  {
        std::string encryptedPassword;
        for (char c : plainPassword) {
            // 只处理可打印字符
            if (isprint(c)) {
                // 循环移位 3 个位置
                encryptedPassword += std::to_string((c + 3 - 32) % 95 + 32);
            } else {
                encryptedPassword += c;
            }
        }
        return encryptedPassword;
    }

    // 简单的凯撒密码解密
    std::string Caesar_decryptPassword(const std::string& encryptedPassword)  {
        std::string decryptedPassword;
        for (char c : encryptedPassword) {
            // 只处理可打印字符
            if (isprint(c)) {
                // 循环移位回 3 个位置
                decryptedPassword += std::to_string((c - 3 - 32 + 95) % 95 + 32);
            } else {
                decryptedPassword += c;
            }
        }
        return decryptedPassword;
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    // 生成 AES-128 密钥
    CryptoPP::SecByteBlock generateKey() {
        CryptoPP::AutoSeededRandomPool prng; // 创建一个随机数生成器
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH); // AES-128的密钥长度
        prng.GenerateBlock(key, key.size()); // 生成密钥
        // 检查密钥长度是否为AES-128
        if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH) {
            throw std::runtime_error("Invalid key size.");
        } else {
            return key; // 返回生成的密钥
        }
    }

    // 将密钥转换为 Base64 字符串
    std::string KeyToBase64(const CryptoPP::SecByteBlock& key) {
        std::string base64Key;
        CryptoPP::Base64Encoder encoder;
        encoder.Attach(new CryptoPP::StringSink(base64Key));
        encoder.Put(key.data(), key.size());
        encoder.MessageEnd();
        // 凯撒密码加密
        std::string encryptBase64Key;
        encryptBase64Key = Caesar_encryptPassword(base64Key);

        return encryptBase64Key;
    }

    // 将 Base64 字符串解码为密钥
    CryptoPP::SecByteBlock Base64ToKey(const std::string& encryptBase64Key) {
        std::string decodedKey;

        // 凯撒密码解密
        std::string base64Key;
        base64Key = Caesar_decryptPassword(encryptBase64Key);

        CryptoPP::Base64Decoder decoder;
        decoder.Attach(new CryptoPP::StringSink(decodedKey));
        decoder.Put(reinterpret_cast<const CryptoPP::byte *>(base64Key.data()), base64Key.size());
        decoder.MessageEnd();

        // 使用花括号初始化列表返回 SecByteBlock 对象
        return {reinterpret_cast<const CryptoPP::byte *>(decodedKey.data()), decodedKey.size()};
    }

    // 将密钥保存到 JSON 文件
    void SaveKeyToJSON(const CryptoPP::SecByteBlock& key) {
        std::string encryptBase64Key = KeyToBase64(key);

        json j;
        j["key"] = encryptBase64Key;

        std::ofstream outFile("key.json");
        if (!outFile.is_open()) {
            throw std::runtime_error("Could not open file for writing.");
        } else {
            outFile << j.dump(4); // 保存 JSON 数据，缩进为 4 个空格
            outFile.close();
        }
    }

    // 从 JSON 文件读取密钥
    CryptoPP::SecByteBlock ReadKeyFromJSON() {
        std::ifstream inFile("key.json");
        if (!inFile.is_open()) {
            throw std::runtime_error("Could not open file for reading.");
        } else {
            json j;
            inFile >> j;
            inFile.close();

            std::string encryptBase64Key = j["key"].get<std::string>();
            return Base64ToKey(encryptBase64Key);
        }
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    // 封装
    void keyInitialization() {
        CryptoPP::SecByteBlock key = generateKey();
        SaveKeyToJSON(key);
    }
    void keyLoad(CryptoPP::SecByteBlock& key) {
        key = ReadKeyFromJSON();
    }
}
