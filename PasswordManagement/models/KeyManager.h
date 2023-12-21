// KeyManager.h
// Created by Jake Jia on 2023/12/15.
// 管理密钥

/*  基本逻辑
 *  软件初始化
 *      生成密钥-保存密钥(key-base64key-encryptBase64Key-json)
 *  软件运行
 *      载入密钥(json-encryptBase64Key-base64key-key)
 */

#include <fstream>
#include "../lib/cryptopp/aes.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/modes.h"
#include "../lib/cryptopp/osrng.h"
// #include "base64.h"

#ifndef PASSWORDMANAGEMENT_KEYMANAGER_H
#define PASSWORDMANAGEMENT_KEYMANAGER_H

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
    // 生成 AES-128 密钥
    CryptoPP::SecByteBlock generateKey();

    // 将密钥转换为 Base64 字符串
    std::string KeyToBase64(const CryptoPP::SecByteBlock &key);

    // 将 Base64 字符串解码为密钥
    CryptoPP::SecByteBlock Base64ToKey(const std::string &base64Key);

    // 将密钥保存到 JSON 文件
    void SaveKeyToJSON(const CryptoPP::SecByteBlock &key);

    // 从 JSON 文件读取密钥
    CryptoPP::SecByteBlock ReadKeyFromJSON();

    // 简单的凯撒密码加密
    std::string Caesar_encryptPassword(const std::string &plainPassword);

    // 简单的凯撒密码解密
    std::string Caesar_decryptPassword(const std::string &encryptedPassword);

/* ------------------------------------------------------------------------------------------------------------------ */

    void keyInitialization();
    void keyLoad(CryptoPP::SecByteBlock& key);
}

#endif //PASSWORDMANAGEMENT_KEYMANAGER_H
