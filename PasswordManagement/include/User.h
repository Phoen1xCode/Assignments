// User.h
// Created by Jake Jia on 2023/11/30.
// �û���

#ifndef PASSWORDMANAGEMENT_USER_H
#define PASSWORDMANAGEMENT_USER_H

#include <string>

namespace PasswordManagement {
    class User {
    public:
        User(); // Ĭ�Ϲ��캯��
        User(std::string username, std::string password, bool loginLicense = false); // ���캯��
        User(const User& other); // // ���ƹ��캯��

        std::string getUsername() const; // ��ȡ�û���
        std::string getPassword() const; // ��ȡ����(����)
        bool getLoginLicense() const; // ��ȡ�û���½���

        void setUsername(const std::string& newUsername); // �������û���
        void setPassword(const std::string& newPassword); // ����������
        void setLoginLicense(const bool& newLoginLicense); // �����û���½���

        bool isRightPassword(const std::string& cin_password) const; // �ж������Ƿ���ȷ

        void userLogin(); // �û���½����

    private:
        std::string username; // �û���
        std::string password; // ����
        bool loginLicense; // �û���½���
    };

}

#endif //PASSWORDMANAGEMENT_USER_H
