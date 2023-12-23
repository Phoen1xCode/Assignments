// PasswordUtils.cpp
// Created by Jake Jia on 2023/12/1.
// ���빤�ߵľ���ʵ��

#include "../include/PasswordUtils.h"

namespace PasswordManagement {

    // ����ǿ����
    std::string generatePassword(int length) {
        // �������ĸ��ַ������ֱ����Сд��ĸ����д��ĸ�����ֺ������ַ�
        const std::string lowerCase = "abcdefghijklmnopqrstuvwxyz";
        const std::string upperCase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string numbers = "0123456789";
        const std::string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";

        // passwordCharacters �ַ��������������ַ�������ϣ���������Сд��ĸ����д��ĸ�����ֺ������ַ�
        const std::string passwordCharacters = lowerCase + upperCase + numbers + specialChars;
        std::string password;

        // ʹ�� std::random_device �� std::mt19937 �����������������
        std::random_device rd;
        std::mt19937 generator(rd());

        // ʹ�� std::uniform_int_distribution �����ɾ��ȷֲ�������������� passwordCharacters ��ѡȡ�ַ���������
        std::uniform_int_distribution<std::string::size_type> distribution(0, passwordCharacters.size() - 1);

        for (std::string::size_type i = 0; i < static_cast<std::string::size_type>(length); ++i) {
            password += passwordCharacters[distribution(generator)];
        }

        // ʹ��ѭ���������ɵ����룬����Ƿ����Сд��ĸ����д��ĸ�����ֺ������ַ�
        bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

        for (char ch : password) {
            if (lowerCase.find(ch) != std::string::npos) hasLower = true;
            else if (upperCase.find(ch) != std::string::npos) hasUpper = true;
            else if (numbers.find(ch) != std::string::npos) hasDigit = true;
            else if (specialChars.find(ch) != std::string::npos) hasSpecial = true;
        }

        // ������벻���㸴����Ҫ��ͨ���ݹ���� generatePassword ���������������룬ֱ������Ҫ��Ϊֹ
        if (!(hasLower && hasUpper && hasDigit && hasSpecial)) {
            return generatePassword(length); // Regenerate if requirements not met
        }

        // ʹ�� std::shuffle ���������ɵ�������д��ң���ȷ������������
        std::shuffle(password.begin(), password.end(), generator);

        return password;
    }

    // �������ǿ�� ǿ���뷵��true �����뷵��false
    bool isStrongPassword(const std::string& password) {
        // ������볤���Ƿ���8��20λ֮��
        if (password.length() < 8 || password.length() > 20) {
            return false;
        }

        bool hasDigit = false;
        bool hasUpper = false;
        bool hasLower = false;
        bool hasSpecial = false;

        // ����һ�������ַ���������Ը�����Ҫ�޸��������
        const std::string specialChars = "!@#$%^&*()-_=+[]{}|;:,.<>?";

        // ���������е�ÿ���ַ�
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

        // ��������Ƿ�������֡���д��ĸ��Сд��ĸ�������ַ�
        if (!hasDigit || !hasUpper || !hasLower || !hasSpecial) {
            return false;
        }

        // �������������������������Ϊ��ǿ����
        return true;
    }


// ���Windowsƽ̨
#if defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#include <windows.h>

    // getHiddenInput() �����Ŀ�ƽ̨ʵ�� ���ؿ���̨����
    std::string getHiddenInput() {
        std::string password; // ����һ���ַ����������洢����
        char ch; // ����һ���ַ��������洢ÿ��������ַ�
        while ((ch = _getch()) != '\r') { // ѭ��ֱ���û����»س������س���Windows���� '\r'��
            if (ch == '\b' && !password.empty()) { // ����û��������˸���������벻Ϊ��
                password.pop_back(); // ɾ�������ַ����е����һ���ַ�
                std::cout << "\b \b"; // �ڿ���̨��ɾ��һ���Ǻ�
            } else if (ch != '\b') { // �������Ĳ����˸��
                password.push_back(ch); // ��������ַ���ӵ������ַ���
                std::cout << '*'; // �ڿ���̨����ʾһ���Ǻ�
            }
        }
        std::cout << std::endl; // ���û����»س��������һ�����з�
        return password; // ��������������ַ���
    }

    // CopyTextToClipboard() ����

    bool CopyTextToClipboard(const std::string &text) {
        // �򿪼�����
        if (!OpenClipboard(nullptr)) {
            return false;
        }

        // ��ռ�����
        EmptyClipboard();

        // ����ȫ���ڴ����ע���1��Ϊ��ĩβ�Ŀ��ַ�
        HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(char));
        if (!hGlobal) {
            CloseClipboard();
            return false;
        }

        // �����ڴ棬׼��д������
        char *pGlobal = static_cast<char *>(GlobalLock(hGlobal));
        memcpy(pGlobal, text.c_str(), text.size() + 1);
        GlobalUnlock(hGlobal);

        // ���ü���������
        if (!SetClipboardData(CF_TEXT, hGlobal)) {
            CloseClipboard();
            GlobalFree(hGlobal);
            return false;
        }

        // �رռ�����
        CloseClipboard();

        // ���SetClipboardData�ɹ���ϵͳ��ӹ�ȫ���ڴ���󣬲���Ҫ�ֶ��ͷ�
        return true;
    }

// ���Unix/Linux/Mac OS Xƽ̨
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
    // AES�����㷨ʵ��

    // plainText:��Ҫ���ܵ������ַ��� | key:������Կ ʹ��CryptoPP::SecByteBlock������ȷ����ȫ�ش�����Կ
    std::string encryptPassword(const std::string& plainText, const CryptoPP::SecByteBlock& key) {
        CryptoPP::AutoSeededRandomPool prng; // ����һ��CryptoPP::AutoSeededRandomPool�����������������
        CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE]; // ����һ���ֽ�����iv��������ʼ������(IV)�����С��AES�Ŀ��С��ͬ
        prng.GenerateBlock(iv, sizeof(iv)); // ʹ��prng.GenerateBlock�������������IV

        std::string cipherText; // ����һ���յ�cipherText�ַ��������ڴ洢���ܺ���ı�

        CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, iv);

        // ����CryptoPP::StreamTransformationFilter��������ִ��ʵ�ʵļ��ܲ�����������������cipherText�ַ�����
        CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(cipherText));
        // ���������ݷ�����ܹ�������
        stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plainText.c_str()), plainText.length());
        stfEncryptor.MessageEnd(); // ����MessageEnd������ɼ��ܲ���

        // ��IV���ӵ�����ǰ��
        std::string ivStr(reinterpret_cast<const char*>(iv), CryptoPP::AES::BLOCKSIZE);
        // return ivStr + cipherText; // ����IV�ͼ��ܺ���ַ���
        std::string encryptedData = ivStr + cipherText;

        // �Լ������ݽ���Base64����
        std::string base64EncryptedData;
        CryptoPP::StringSource ss(encryptedData, true,
                                  new CryptoPP::Base64Encoder(
                                          new CryptoPP::StringSink(base64EncryptedData)
                                  )
        );

        return base64EncryptedData; // ����Base64������ַ���
    }

    // cipherText:Ҫ���ܵ������ַ��� | key:������Կ ʹ��CryptoPP::SecByteBlock������ȷ����ȫ�ش�����Կ
    std::string decryptPassword(const std::string& base64CipherTextAndIv, const CryptoPP::SecByteBlock& key) {
        // ��Base64��������ݽ��н���
        std::string encryptedData;
        CryptoPP::StringSource ss(base64CipherTextAndIv, true,
                                  new CryptoPP::Base64Decoder(
                                          new CryptoPP::StringSink(encryptedData)
                                  )
        );

        // �ӽ�������������ȡIV
        CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
        std::memcpy(iv, encryptedData.data(), CryptoPP::AES::BLOCKSIZE);

        // ��ȡʵ�ʵ�����
        std::string cipherText = encryptedData.substr(CryptoPP::AES::BLOCKSIZE);

        std::string decryptedText;
        CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, iv);

        // �������ܹ�����
        CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedText));
        // �����ķ�����ܹ�������
        stfDecryptor.Put(reinterpret_cast<const unsigned char*>(cipherText.c_str()), cipherText.size());
        // ��ɽ��ܲ���
        stfDecryptor.MessageEnd();

        return decryptedText; // ���ؽ��ܺ������
    }

/* ------------------------------------------------------------------------------------------------------------------ */
} // PasswordUtils