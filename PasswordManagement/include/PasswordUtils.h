// PasswordUtils.h
// Created by Jake Jia on 2023/12/1.
// ��������صĹ���

#ifndef PASSWORDMANAGEMENT_PASSWORDUTILS_H
#define PASSWORDMANAGEMENT_PASSWORDUTILS_H

#include <string>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include "base64.h"
#include "../lib/cryptopp/aes.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/modes.h"
#include "../lib/cryptopp/osrng.h"



namespace PasswordManagement {

    std::string generatePassword(int length = 12); // ����������� lengthΪ���볤��

    bool isStrongPassword(const std::string& password); // �ж�����ǿ��

    std::string getHiddenInput(); // ʵ����������ʱ������

    bool CopyTextToClipboard(const std::string &text);

    CryptoPP::SecByteBlock generateKey(); // ����AES-128��Կ

    std::string KeyToBase64(const CryptoPP::SecByteBlock& key); // ����Կת��Ϊ Base64 �ַ���

    CryptoPP::SecByteBlock Base64ToKey(const std::string& base64Key); // �� Base64 �ַ�������Ϊ��Կ

    std::string encryptPassword(const std::string& plainText, const CryptoPP::SecByteBlock& key); // �����ַ���
    // plainText:��Ҫ���ܵ������ַ��� | key:������Կ ʹ��CryptoPP::SecByteBlock������ȷ����ȫ�ش�����Կ

    std::string decryptPassword(const std::string& cipherTextAndIv, const CryptoPP::SecByteBlock& key); // �����ַ���
    // cipherText:Ҫ���ܵ������ַ���  | key:������Կ ʹ��CryptoPP::SecByteBlock������ȷ����ȫ�ش�����Կ



} // PasswordUtils

#endif //PASSWORDMANAGEMENT_PASSWORDUTILS_H
