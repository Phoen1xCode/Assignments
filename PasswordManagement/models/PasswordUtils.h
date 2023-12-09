// PasswordUtils.h
// Created by Jake Jia on 2023/12/1.
// 与密码相关的工具
#include <string>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include "../lib/cryptopp/aes.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/modes.h"
#include "../lib/cryptopp/osrng.h"


#ifndef PASSWORDMANAGEMENT_PASSWORDUTILS_H
#define PASSWORDMANAGEMENT_PASSWORDUTILS_H


namespace PasswordManagement {

    std::string generatePassword(int length = 12); // 生成随机密码 length为密码长度

    bool isStrongPassword(const std::string& password); // 判断密码强度

    std::string encryptPassword(const std::string& plainText, const CryptoPP::SecByteBlock& key); // 加密字符串
    // plainText:需要加密的明文字符串 | key:加密密钥 使用CryptoPP::SecByteBlock类型来确保安全地处理密钥

    std::string decryptPassword(const std::string& cipherTextAndIv, const CryptoPP::SecByteBlock& key); // 解密字符串
    // cipherText:要解密的密文字符串  | key:解密密钥 使用CryptoPP::SecByteBlock类型来确保安全地处理密钥

} // PasswordUtils

#endif //PASSWORDMANAGEMENT_PASSWORDUTILS_H
