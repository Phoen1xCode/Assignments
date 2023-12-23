// PasswordManager.h
// Created by Jake Jia on 2023/11/30.
//

#include <string>
#include <iostream>
#include <conio.h>
#include "../include/PasswordManager.h"
#include "../include/PasswordUtils.h"
#include "../include/CredentialManager.h"
#include "../lib/bcrypt/include/bcrypt.h"


namespace PasswordManagement {

    void PasswordManager::userInitialize(ConfigManager &configFile, std::string &username, std::string &password) {
        // ��ʼ��
        std::cout << "��ʼ��������������" << std::endl;
        /* -------------------------------------------------------------------------------------------------- */

        // �û������ļ���ʼ��
        // �����û���
        std::cout << "�����������û�����" << std::endl;
        std::cout << "�û�����";
        std::getline(std::cin, username);
        while (username.empty()) {
            std::cout << "�û�������Ϊ�ա�" << std::endl;
            std::cout << "���������������û�����" << std::endl;
            std::cout << "�û�����";
            std::getline(std::cin, username);
        }

        // ��������
        std::cout << "�������������롣" << std::endl;
        std::cout << "���룺";
        password = getHiddenInput();

        // �������ǿ��
        while (!isStrongPassword(password)) {
            std::cout << "��������̫�������������롣" << std::endl;
            std::cout << "���룺";
            password = getHiddenInput();
        }

        std::string verify_password;
        std::cout << "��ȷ���������롣" << std::endl;
        std::cout << "ȷ�����룺";
        verify_password = getHiddenInput();

        while (password != verify_password) {
            std::cout << "������������벻ƥ�䡣" << std::endl;
            std::cout << "������������ȷ�����롣" << std::endl;
            std::cout << "ȷ�����룺";
            verify_password = getHiddenInput();
        }

        // ��������
        password = bcrypt::generateHash(password);

        // ���û����ͼ��ܺ������д��config.json�ļ�
        configFile.saveConfigFile(username, password);

        /* -------------------------------------------------------------------------------------------------- */

        // ��Կ�ļ���ʼ��
        keyInitialization();

        /* -------------------------------------------------------------------------------------------------- */
        clearScreen();
    }

    bool PasswordManager::loginPasswordManagement() {
        std::string username, password; // username �û��� | password ����
        std::string configFileName = "config.json";

        PasswordManagement::ConfigManager configFile(configFileName);
        if (!configFile.findConfigFile()) { // ����Ƿ����û������ļ�
            configFile.createConfigFile(); // û���򴴽�һ���յ�Ĭ���û������ļ�
            userInitialize(configFile, username, password); // ���г�ʼ��
        } else if (!configFile.checkConfigFile()) {
            userInitialize(configFile, username, password); // ���г�ʼ��
        } else {
            configFile.readConfigFile(username, password); // �����ȡ�����ļ��е��û���������
        }

        PasswordManagement::User admin(username, password);
        admin.userLogin(); // �û���½����
        if (!admin.getLoginLicense()) { // ���Դ����������� �رճ���
            std::cout << "���Դ���̫�ࡣ�����˳�..." << std::endl;
            return false;
        } else {
            return true;
        }
    }

    /* ------------------------------------------------------------------------------------------------------------------ */
    void PasswordManager::managePasswords() {
        clearScreen();
        /* -------------------------------------------------------------------------------------------------- */
        // �� key.json ������Կ
        keyLoad(this->key);
        // �� credentials.json �����ѱ��������
        loadCredentialsFromFile(this->credentials);
        /* -------------------------------------------------------------------------------------------------- */

        /* -------------------------------------------------------------------------------------------------- */
        int choice;
        while (true) {
            /* -------------------------------------------------------------------------------------------------- */
            std::cout << "���������" << std::endl;
            std::cout << "0. �˳�" << std::endl; // �˳�����
            std::cout << "1. �������" << std::endl; // �������ƾ֤
            std::cout << "2. ɾ������" << std::endl; // ɾ������ƾ֤
            std::cout << "3. �鿴������Ŀ" << std::endl; // �鿴����ƾ֤
            std::cout << "4. �޸�����" << std::endl; // �޸�����ƾ֤
            std::cout << "5. ��������" << std::endl; // ��������ƾ֤
            std::cout << "6. �����������" << std::endl; // �����������
            /* -------------------------------------------------------------------------------------------------- */

            std::cout << "����������ѡ��";
            std::cin >> choice;
            clearScreen();
            switch (choice) {
                case 0:
                    std::cout << "�����˳�����..." << std::endl;
                    return;
                case 1:
                    addPassword();
                    saveCredentialsToFile(this->credentials);
                    clearScreen();
                    break;
                case 2:
                    removePassword();
                    saveCredentialsToFile(this->credentials);
                    std::cout << "�밴���������..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 3:
                    displayItemNames();
                    std::cout << "�밴���������..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 4:
                    changePassword();
                    saveCredentialsToFile(this->credentials);
                    std::cout << "�밴���������..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 5:
                    searchForPassword();
                    std::cout << "�밴���������..." << std::endl;
                    _getch();
                    clearScreen();
                    break;
                case 6:
                    generateRandomPassword();
                    break;
                default:
                    std::cout << "��Чѡ�" << std::endl;
                    break;
            }
        }
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    void PasswordManager::addPassword() {
        int type;

        std::cout << "ѡ��Ҫ��ӵ�ƾ֤���ͣ�" << std::endl;
        std::cout << "0. ƾ֤" << std::endl;
        std::cout << "1. ��վƾ֤" << std::endl;
        std::cout << "2. ���п�ƾ֤" << std::endl;
        std::cout << "3. ���ƾ֤" << std::endl;
        std::cout << "4. Wifi ƾ֤" << std::endl;
        std::cout << "����������ѡ��";
        std::cin >> type;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ����ֱ���������з��������ַ�

        switch (type) {
            case 0: { // ƾ֤
                std::string itemName, username, password;

                std::cout << "������Ŀ���ƣ�";
                std::getline(std::cin, itemName);

                std::cout << "�����û�����";
                std::getline(std::cin, username);

                std::cout << "�������룺";
                std::getline(std::cin, password);

                // ��������
                password = encryptPassword(password, this->key);

                credentials.push_back(std::make_unique<Credential>(itemName, username, password));
                break;
            }
            case 1: { // ��վƾ֤
                std::string itemName, username, password;
                std::string websiteURL;

                std::cout << "������Ŀ���ƣ�";
                std::getline(std::cin, itemName);

                std::cout << "�����û�����";
                std::getline(std::cin, username);

                std::cout << "�������룺";
                std::getline(std::cin, password);

                // ��������
                password = encryptPassword(password, this->key);

                std::cout << "������վ URL��";
                std::getline(std::cin, websiteURL);

                credentials.push_back(std::make_unique<WebsiteCredential>(itemName, username, password, websiteURL));
                break;
            }
            case 2: { // ���п�ƾ֤
                std::string itemName, username, password;
                std::string bankName, cardNumber;

                std::cout << "������Ŀ���ƣ�";
                std::getline(std::cin, itemName);

                std::cout << "�����������ƣ�";
                std::getline(std::cin, bankName);

                std::cout << "���뿨�ţ�";
                std::getline(std::cin, cardNumber);

                std::cout << "�����û�����";
                std::getline(std::cin, username);

                std::cout << "�������룺";
                std::getline(std::cin, password);

                // ��������
                password = encryptPassword(password, this->key);

                credentials.push_back(
                        std::make_unique<BankCardCredential>(itemName, username, password, bankName, cardNumber));
                break;
            }
            case 3: {
                std::string itemName, username, password;
                std::string softwareName, licenseKey;

                std::cout << "������Ŀ���ƣ�";
                std::getline(std::cin, itemName);

                std::cout << "����������ƣ�";
                std::getline(std::cin, softwareName);

                std::cout << "�������֤��Կ��";
                std::getline(std::cin, licenseKey);

                // ��������
                password = encryptPassword(licenseKey, this->key);
                // ����ƾ֤
                licenseKey = encryptPassword(licenseKey, this->key);

                credentials.push_back(
                        std::make_unique<SoftwareCredential>(itemName, username, password, softwareName, licenseKey));
                break;
            }
            case 4: {
                std::string itemName, username, password;
                std::string ssid;

                std::cout << "������Ŀ���ƣ�";
                std::getline(std::cin, itemName);

                std::cout << "����SSID��";
                std::getline(std::cin, ssid);

                std::cout << "�������룺";
                std::getline(std::cin, password);

                credentials.push_back(std::make_unique<WifiCredential>(itemName, username, password, ssid));
                break;
            }
            default:
                std::cout << "��Ч���ͣ�" << std::endl;
                break;
        }
        std::cout << "ƾ֤��ӳɹ���" << std::endl;
    }

    void PasswordManager::removePassword() {
        displayItemNames();
        std::string itemName;
        std::cout << "����Ҫɾ���������Ŀ���ƣ�";
        std::cin >> itemName;

        auto it = std::find_if(credentials.begin(), credentials.end(),
                               [&itemName](const std::unique_ptr<Credential> &credential) {
                                   return credential->getItemName() == itemName;
                               });

        if (it != credentials.end()) {
            credentials.erase(it);
            std::cout << "����ɾ���ɹ���" << std::endl;
        } else {
            std::cout << "δ�ҵ����룡" << std::endl;
        }
    }

    void PasswordManager::displayItemNames() {
        int count = 1;

        std::cout << "��Ŀ��" << std::endl;
        for (const auto &credential : credentials) {
            std::cout << count << ". ";
            std::cout << "��Ŀ���ƣ�" << credential->getItemName();
            std::cout << std::endl;
            count++;
        }
    }

    void PasswordManager::changePassword() {
        displayItemNames();

        std::string itemName, newPassword;
        std::cout << "����Ҫ�����������Ŀ���ƣ�";
        std::cin >> itemName;
        std::cout << "���������룺";
        std::cin >> newPassword;

        // ��������
        newPassword = encryptPassword(newPassword, this->key);

        for (auto &credential: credentials) {
            if (credential->getItemName() == itemName) {
                // ���������趯̬ת������Ϊ setPassword �ǻ���ķ���
                credential->setPassword(newPassword);
                std::cout << "������ĳɹ���" << std::endl;
                return;
            }
        }
        std::cout << "δ�ҵ����룡" << std::endl;
    }

    void PasswordManager::searchForPassword() {
        displayItemNames();

        std::string itemName;
        std::cout << "����Ҫ�����������Ŀ���ƣ�";
        std::cin >> itemName;

        for (const auto &credential: credentials) {
            if (credential->getItemName() == itemName) {
                std::cout << "/* ----------------------------------------------------------- */" << std::endl;
                credential->display();
                std::cout << "/* ----------------------------------------------------------- */" << std::endl;

                std::cout << "�Ƿ���ʾ�������룿��y/n��" << std::endl;
                std::cout << "����������ѡ��";
                char choice;
                std::cin >> choice;

                if (choice == 'y' || choice == 'Y') {
                    std::string cipherPassword = credential->getPassword();
                    std::string plainPassword = decryptPassword(cipherPassword, this->key);
                    std::cout << "���룺" << plainPassword << std::endl;
                } else {
                    std::cout << "��Чѡ�" << std::endl;
                    return;
                }
            }
        }
    }

    void PasswordManager::generateRandomPassword() {
        std::cout << "���������ɵ�������볤�ȣ�>= 6����";

        int length;
        std::cin >> length;

        std::string randomPassword = generatePassword(length);
        std::cout << "���ɵ����룺" << randomPassword << std::endl;

        std::cout << "�Ƿ����븴�Ƶ������壿��y/n��" << std::endl;
        std::cout << "����������ѡ��";
        char choice;
        std::cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            if (CopyTextToClipboard(randomPassword)) {
                std::cout << "�����Ѹ��Ƶ������塣" << std::endl;
            } else {
                std::cout << "�������뵽������ʧ�ܡ�" << std::endl;
            }
        }
        clearScreen();
    }

    void PasswordManager::clearScreen() {
        Sleep(500);
        system("cls");
    }



}