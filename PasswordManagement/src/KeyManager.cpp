// KeyManager.cpp
// Created by Jake Jia on 2023/12/15.
//


#include "../include/KeyManager.h"
#include "../lib/json/json.hpp"
namespace PasswordManagement {
    using json = nlohmann::json;

/* ------------------------------------------------------------------------------------------------------------------ */
    // �򵥵Ŀ����������
    std::string Caesar_encryptPassword(const std::string& plainPassword)  {
        std::string encryptedPassword;
        for (char c : plainPassword) {
            // ֻ����ɴ�ӡ�ַ�
            if (isprint(c)) {
                // ѭ����λ 3 ��λ��
                encryptedPassword += std::to_string((c + 3 - 32) % 95 + 32);
            } else {
                encryptedPassword += c;
            }
        }
        return encryptedPassword;
    }

    // �򵥵Ŀ����������
    std::string Caesar_decryptPassword(const std::string& encryptedPassword)  {
        std::string decryptedPassword;
        for (char c : encryptedPassword) {
            // ֻ����ɴ�ӡ�ַ�
            if (isprint(c)) {
                // ѭ����λ�� 3 ��λ��
                decryptedPassword += std::to_string((c - 3 - 32 + 95) % 95 + 32);
            } else {
                decryptedPassword += c;
            }
        }
        return decryptedPassword;
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� AES-128 ��Կ
    CryptoPP::SecByteBlock generateKey() {
        CryptoPP::AutoSeededRandomPool prng; // ����һ�������������
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH); // AES-128����Կ����
        prng.GenerateBlock(key, key.size()); // ������Կ
        // �����Կ�����Ƿ�ΪAES-128
        if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH) {
            throw std::runtime_error("Invalid key size.");
        } else {
            return key; // �������ɵ���Կ
        }
    }

    // ����Կת��Ϊ Base64 �ַ���
    std::string KeyToBase64(const CryptoPP::SecByteBlock& key) {
        std::string base64Key;
        CryptoPP::Base64Encoder encoder;
        encoder.Attach(new CryptoPP::StringSink(base64Key));
        encoder.Put(key.data(), key.size());
        encoder.MessageEnd();
        // �����������
        std::string encryptBase64Key;
        encryptBase64Key = Caesar_encryptPassword(base64Key);

        return encryptBase64Key;
    }

    // �� Base64 �ַ�������Ϊ��Կ
    CryptoPP::SecByteBlock Base64ToKey(const std::string& encryptBase64Key) {
        std::string decodedKey;

        // �����������
        std::string base64Key;
        base64Key = Caesar_decryptPassword(encryptBase64Key);

        CryptoPP::Base64Decoder decoder;
        decoder.Attach(new CryptoPP::StringSink(decodedKey));
        decoder.Put(reinterpret_cast<const CryptoPP::byte *>(base64Key.data()), base64Key.size());
        decoder.MessageEnd();

        // ʹ�û����ų�ʼ���б��� SecByteBlock ����
        return {reinterpret_cast<const CryptoPP::byte *>(decodedKey.data()), decodedKey.size()};
    }

    // ����Կ���浽 JSON �ļ�
    void SaveKeyToJSON(const CryptoPP::SecByteBlock& key) {
        std::string encryptBase64Key = KeyToBase64(key);

        json j;
        j["key"] = encryptBase64Key;

        std::ofstream outFile("key.json");
        if (!outFile.is_open()) {
            throw std::runtime_error("Could not open file for writing.");
        } else {
            outFile << j.dump(4); // ���� JSON ���ݣ�����Ϊ 4 ���ո�
            outFile.close();
        }
    }

    // �� JSON �ļ���ȡ��Կ
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

    // ��װ
    void keyInitialization() {
        CryptoPP::SecByteBlock key = generateKey();
        SaveKeyToJSON(key);
    }
    void keyLoad(CryptoPP::SecByteBlock& key) {
        key = ReadKeyFromJSON();
    }
}
