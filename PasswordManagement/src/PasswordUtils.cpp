// PasswordUtils.cpp
// Created by Jake Jia on 2023/12/1.
// 密码工具的具体实现

#include "../include/PasswordUtils.h"

namespace PasswordManagement {

    // 生成强密码
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

    // 检查密码强度 强密码返回true 弱密码返回false
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


// 检测Windows平台
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>

    // getHiddenInput() 函数的跨平台实现 隐藏控制台输入
    std::string getHiddenInput() {
        std::string password; // 定义一个字符串变量来存储密码
        char ch; // 定义一个字符变量来存储每次输入的字符
        while ((ch = _getch()) != '\r') { // 循环直到用户按下回车键（回车在Windows中是 '\r'）
            if (ch == '\b' && !password.empty()) { // 如果用户输入了退格键并且密码不为空
                password.pop_back(); // 删除密码字符串中的最后一个字符
                std::cout << "\b \b"; // 在控制台上删除一个星号
            } else if (ch != '\b') { // 如果输入的不是退格键
                password.push_back(ch); // 将输入的字符添加到密码字符串
                std::cout << '*'; // 在控制台上显示一个星号
            }
        }
        std::cout << std::endl; // 当用户按下回车键后，输出一个换行符
        return password; // 返回输入的密码字符串
    }

    // CopyTextToClipboard() 函数

    bool CopyTextToClipboard(const std::string &text) {
        // 打开剪贴板
        if (!OpenClipboard(nullptr)) {
            return false;
        }

        // 清空剪贴板
        EmptyClipboard();

        // 分配全局内存对象，注意加1是为了末尾的空字符
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(char));
        if (!hGlobal) {
            CloseClipboard();
            return false;
        }

        // 锁定内存，准备写入数据
        char *pGlobal = static_cast<char *>(GlobalLock(hGlobal));
        memcpy(pGlobal, text.c_str(), text.size() + 1);
        GlobalUnlock(hGlobal);

        // 设置剪贴板数据
        if (!SetClipboardData(CF_TEXT, hGlobal)) {
            CloseClipboard();
            GlobalFree(hGlobal);
            return false;
        }

        // 关闭剪贴板
        CloseClipboard();

        // 如果SetClipboardData成功，系统会接管全局内存对象，不需要手动释放
        return true;
    }

// 检测Unix/Linux/Mac OS X平台
#elif defined(__unix__) || defined(__unix) || defined(__APPLE__) && defined(__MACH__)
#include <termios.h>
#include <unistd.h>

    std::string getHiddenInput() {
        std::string password;
        termios oldt, newt;
        char ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        while ((ch = getchar()) != '\n' && ch != EOF) {
            password += ch;
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return password;
    }
#endif

/* ------------------------------------------------------------------------------------------------------------------ */
    // AES加密算法实现

    // plainText:需要加密的明文字符串 | key:加密密钥 使用CryptoPP::SecByteBlock类型来确保安全地处理密钥
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
        // return ivStr + cipherText; // 返回IV和加密后的字符串
        std::string encryptedData = ivStr + cipherText;

        // 对加密数据进行Base64编码
        std::string base64EncryptedData;
        CryptoPP::StringSource ss(encryptedData, true,
                                  new CryptoPP::Base64Encoder(
                                          new CryptoPP::StringSink(base64EncryptedData)
                                  )
        );

        return base64EncryptedData; // 返回Base64编码的字符串
    }

    // cipherText:要解密的密文字符串 | key:解密密钥 使用CryptoPP::SecByteBlock类型来确保安全地处理密钥
    std::string decryptPassword(const std::string& base64CipherTextAndIv, const CryptoPP::SecByteBlock& key) {
        // 对Base64编码的数据进行解码
        std::string encryptedData;
        CryptoPP::StringSource ss(base64CipherTextAndIv, true,
                                  new CryptoPP::Base64Decoder(
                                          new CryptoPP::StringSink(encryptedData)
                                  )
        );

        // 从解码后的数据中提取IV
        CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
        std::memcpy(iv, encryptedData.data(), CryptoPP::AES::BLOCKSIZE);

        // 提取实际的密文
        std::string cipherText = encryptedData.substr(CryptoPP::AES::BLOCKSIZE);

        std::string decryptedText;
        CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        // 创建解密过滤器
        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
        // 将密文放入解密过滤器中
        stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());
        // 完成解密操作
        stfDecryptor.MessageEnd();

        return decryptedText; // 返回解密后的明文
    }

/* ------------------------------------------------------------------------------------------------------------------ */
} // PasswordUtils