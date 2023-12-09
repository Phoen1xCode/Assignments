// PasswordUtils.cpp
// Created by Jake Jia on 2023/12/1.
// 密码工具的具体实现

#include "../models/PasswordUtils.h"
#include <string>
#include <random>
#include <algorithm>

namespace PasswordManagement {

    // 生成随机密码
    // 返回 生成的密码
    std::string generatePassword(int length) {
        // 定义了四个字符串，分别包含小写字母、大写字母、数字和特殊字符
        const std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
        const std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string numbers = "0123456789";
        const std::string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";

        // passwordCharacters 字符串包含了所有字符集的组合，即包含了小写字母、大写字母、数字和特殊字符
        const std::string passwordCharacters = lowerCase + upperCase + numbers + specialChars;
        std::string password;

        // 使用 std::random_device 和 std::mt19937 来创建随机数生成器
        std::random_device rd;
        std::mt19937 generator(rd());

        // 使用 std::uniform_int_distribution 来生成均匀分布的随机索引，从 passwordCharacters 中选取字符构成密码
        std::uniform_int_distribution<std::string::size_type> distribution(0, passwordCharacters.size() - 1);

        for (std::string::size_type i = 0; i < static_cast<std::string::size_type>(length); ++i) {
            password += passwordCharacters[distribution(generator)];
        }

        // 使用循环遍历生成的密码，检查是否包含小写字母、大写字母、数字和特殊字符
        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

        for (char ch : password) {
            if (lowerCase.find(ch) != std::string::npos) hasLower = true;
            else if (upperCase.find(ch) != std::string::npos) hasUpper = true;
            else if (numbers.find(ch) != std::string::npos) hasDigit = true;
            else if (specialChars.find(ch) != std::string::npos) hasSpecial = true;
        }

        // 如果密码不满足复杂性要求，通过递归调用 generatePassword 函数重新生成密码，直到满足要求为止
        if (!(hasLower && hasUpper && hasDigit && hasSpecial)) {
            return generatePassword(length); // Regenerate if requirements not met
        }

        // 使用 std::shuffle 函数对生成的密码进行打乱，以确保密码的随机性
        std::shuffle(password.begin(), password.end(), generator);

        return password;
    }

    // 检查密码强度
    // 强密码返回true 弱密码返回false
    bool isStrongPassword(const std::string& password) {
        // 检查密码长度是否在8到20位之间
        if (password.length() < 8 || password.length() > 20) {
            return false;
        }

        bool hasDigit = false;
        bool hasUpper = false;
        bool hasLower = false;
        bool hasSpecial = false;

        // 定义一个特殊字符集，你可以根据需要修改这个集合
        const std::string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";

        // 遍历密码中的每个字符
        for (char ch : password) {
            if (std::isdigit(ch)) {
                hasDigit = true;
            } else if (std::isupper(ch)) {
                hasUpper = true;
            } else if (std::islower(ch)) {
                hasLower = true;
            } else if (specialChars.find(ch) != std::string::npos) {
                hasSpecial = true;
            }
        }

        // 检查密码是否包含数字、大写字母、小写字母和特殊字符
        if (!hasDigit || !hasUpper || !hasLower || !hasSpecial) {
            return false;
        }

        // 如果密码满足所有条件，则认为是强密码
        return true;
    }


// 生成一个AES-128密钥并检查其长度
//    CryptoPP::AutoSeededRandomPool prng;
//    CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH); // AES-128的密钥长度
//    prng.GenerateBlock(key, key.size());
//
//    检查密钥长度是否为AES-128所需的16字节
//    if (key.size() != CryptoPP::AES::DEFAULT_KEYLENGTH) {
//      throw std::runtime_error("Invalid key size.");
//    }




//    在使用加密算法时，初始化向量（IV）是确保相同的明文在不同的加密操作中产生不同密文的关键。这有助于增强安全性，特别是在使用块加密模式（如CBC模式）时。
//    为了正确处理IV，你需要遵循以下步骤：
//    生成IV：在加密操作开始时，生成一个随机的IV。这通常由加密库的随机数生成器完成，如CryptoPP::AutoSeededRandomPool。
//    存储IV：加密后，你需要将IV存储在一个地方，以便解密时可以使用。通常的做法是将IV附加到密文的前面，因为IV不需要保密，只需要不可预测。
//    传输IV：将密文和IV一起传输给解密方。确保在传输过程中IV不会被篡改。
//    解密时使用IV：在解密操作开始时，从传输的数据中提取IV，并使用它来初始化解密算法。

    // 使用AES算法加密
    // // plainText:需要加密的明文字符串 | key:加密密钥 使用CryptoPP::SecByteBlock类型来确保安全地处理密钥
    std::string encryptPassword(const std::string& plainText, const CryptoPP::SecByteBlock& key) {
        CryptoPP::AutoSeededRandomPool prng; // 创建一个CryptoPP::AutoSeededRandomPool对象，用于生成随机数
        CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; // 定义一个字节数组iv，用作初始化向量(IV)，其大小与AES的块大小相同
        prng.GenerateBlock(iv, sizeof(iv)); // 使用prng.GenerateBlock方法生成随机的IV

        std::string cipherText; // 创建一个空的cipherText字符串，用于存储加密后的文本

        CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

        // 创建CryptoPP::StreamTransformationFilter对象，用于执行实际的加密操作，并将结果输出到cipherText字符串中
        CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
        // 将明文数据放入加密过滤器中
        stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
        stfEncryptor.MessageEnd(); // 调用MessageEnd方法完成加密操作

        // 将IV附加到密文前面
        std::string ivStr(reinterpret_cast<const char*>(iv), CryptoPP::AES::BLOCKSIZE);
        return cipherText; // 返回加密后的字符串
    }
    // 使用AES算法解密
    // // cipherText:要解密的密文字符串 | key:解密密钥 使用CryptoPP::SecByteBlock类型来确保安全地处理密钥
    std::string decryptPassword(const std::string& cipherTextAndIv, const CryptoPP::SecByteBlock& key) {
        // 从传入的数据中提取IV
        CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
        std::memcpy(iv, cipherTextAndIv.data(), CryptoPP::AES::BLOCKSIZE);

        // 提取实际的密文
        std::string cipherText = cipherTextAndIv.substr(CryptoPP::AES::BLOCKSIZE);

        std::string decryptedText;
        CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
        stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());
        stfDecryptor.MessageEnd();

        return decryptedText;
    }



} // PasswordUtils