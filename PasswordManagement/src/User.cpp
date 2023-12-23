// User.cpp
// Created by Jake Jia on 2023/11/30.
// �û���ľ���ʵ��

#include <utility>
#include <iostream>
#include "../include/User.h"
#include "../include/PasswordUtils.h"
#include "../lib/bcrypt/include/bcrypt.h"

namespace PasswordManagement {
    User::User() {
        this->username = "";
        this->password = "";
        this->loginLicense = false;
    }

    User::User(std::string username,
               std::string password,
               bool loginLicense) {
        this->username = std::move(username);
        this->password = std::move(password);
        this->loginLicense = loginLicense;
    }

    User::User(const User &other) {
        this->username = other.username;
        this->password = other.password;
        this->loginLicense = other.loginLicense;
    }

    std::string User::getUsername() const {
        return this->username;
    }

    std::string User::getPassword() const {
        return this->password;
    }

    bool User::getLoginLicense() const {
        return this->loginLicense;
    }

    void User::setUsername(const std::string& newUsername) {
        this->username = newUsername;
    }

    void User::setPassword(const std::string& newPassword) {
        this->password = newPassword;
    }

    void User::setLoginLicense(const bool& newLoginLicense) {
        this->loginLicense = newLoginLicense;
    }

    bool User::isRightPassword(const std::string& cin_password) const {
        return bcrypt::validatePassword(cin_password, getPassword());
    }

    void User::userLogin() {
        int numberOfAttempts = 0; // �������볢�Դ�����һ������
        std::string cin_password; // �û����������

        std::cout << "��ӭʹ�� 0Password ��" << this->getUsername() << std::endl;
        std::cout << "���������롣" << std::endl;

        while(numberOfAttempts < 3) {
            std::cout << "���룺";
            cin_password = PasswordManagement::getHiddenInput(); // ������������

            if (!this->isRightPassword(cin_password)) { // �������
                bool wrongPassword = false;
                setLoginLicense(wrongPassword);
                std::cout << "����������������룡" << std::endl;
                numberOfAttempts++;
                std::cout << "ʣ�ೢ�Դ�����" << 3 - numberOfAttempts << "��" << std::endl;
            } else { // ������ȷ
                bool rightPassword = true;
                setLoginLicense(rightPassword);
                break;
            }
        }

        if (numberOfAttempts == 3) {
            std::cout << "�����������������࣬�˻��ѱ�������" << std::endl;
        } else {
            std::cout << "������ȷ����¼�ɹ���" << std::endl;
        }
    }

}


