// KeyManager.h
// Created by Jake Jia on 2023/12/15.
// ������Կ

/*  �����߼�
 *  �����ʼ��
 *      ������Կ-������Կ(key-base64key-encryptBase64Key-json)
 *  �������
 *      ������Կ(json-encryptBase64Key-base64key-key)
 */

#include <fstream>
#include "../lib/cryptopp/aes.h"
#include "../lib/cryptopp/filters.h"
#include "../lib/cryptopp/modes.h"
#include "../lib/cryptopp/osrng.h"
#include "base64.h"

#ifndef PASSWORDMANAGEMENT_KEYMANAGER_H
#define PASSWORDMANAGEMENT_KEYMANAGER_H

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� AES-128 ��Կ
    CryptoPP::SecByteBlock generateKey();

    // ����Կת��Ϊ Base64 �ַ���
    std::string KeyToBase64(const CryptoPP::SecByteBlock &key);

    // �� Base64 �ַ�������Ϊ��Կ
    CryptoPP::SecByteBlock Base64ToKey(const std::string &base64Key);

    // ����Կ���浽 JSON �ļ�
    void SaveKeyToJSON(const CryptoPP::SecByteBlock &key);

    // �� JSON �ļ���ȡ��Կ
    CryptoPP::SecByteBlock ReadKeyFromJSON();

    // �򵥵Ŀ����������
    std::string Caesar_encryptPassword(const std::string &plainPassword);

    // �򵥵Ŀ����������
    std::string Caesar_decryptPassword(const std::string &encryptedPassword);

/* ------------------------------------------------------------------------------------------------------------------ */

    void keyInitialization();
    void keyLoad(CryptoPP::SecByteBlock& key);
}

#endif //PASSWORDMANAGEMENT_KEYMANAGER_H
