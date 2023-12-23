// Credential.h
// Created by Jake Jia on 2023/12/5.
//



#ifndef PASSWORDMANAGEMENT_CREDENTIAL_H
#define PASSWORDMANAGEMENT_CREDENTIAL_H
#include <string>
#include "../include/PasswordUtils.h"

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
//    // ���� Identity �࣬���ڴ洢���������Ϣ
//    class Identity {
//    public:
//        // Ĭ�Ϲ��캯��
//        Identity();
//
//        // ���캯��
//        Identity(std::string name,
//                 std::string gender,
//                 std::string birthdate,
//                 std::string stuentID,
//                 std::string email,
//                 std::string phoneNumber);
//
//        // ���ƹ��캯��
//        Identity(const Identity& other);
//        // ��������
//        ~Identity() = default;
//
//        std::string getName() const; // ��ȡ����
//        std::string getGender() const; // ��ȡ�Ա�
//        std::string getBirthdate() const; // ��ȡ��������
//        std::string getStudentID() const; // ��ȡѧ��
//        std::string getEmail() const; // ��ȡ�����ʼ���ַ
//        std::string getPhoneNumber() const; // ��ȡ�绰����
//
//        void display() const; // ��ʾ�����Ϣ
//
//        void setName(const std::string& newName);
//        void setGender(const std::string& newGender);
//        void setBirthday(const std::string& newBirthday);
//        void setStudentID(const std::string& newStudentID);
//        void setEmail(const std::string& newEmail);
//        void setPhoneNumber(const std::string& newPhoneNumber);
//
//    private:
//        std::string name; // ����
//        std::string gender; // �Ա�
//        std::string birthdate; // ����
//        std::string stuentID; // ѧ��
//        std::string email; // ����
//        std::string phoneNumber; // �绰����
//    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� Credential �࣬���ڴ洢ƾ����Ϣ
    class Credential {
    public:
        // Ĭ�Ϲ��캯��
        Credential() = default;
        // ���캯��
        Credential(std::string itemName, std::string username, std::string password);
        // ���ƹ��캯��
        Credential(const Credential& other);
        // ��������
        ~Credential() = default;

        std::string getItemName() const; // ��ȡ��Ŀ����
        std::string getUsername() const; // ��ȡ�û���
        std::string getPassword() const; // ��ȡ����

        virtual void display() const; // ��ʾƾ����Ϣ

        virtual void setItemName(const std::string& newItemName); // ������Ŀ����
        virtual void setUsername(const std::string& newUsername); // �����û���
        virtual void setPassword(const std::string& newPassword); // ��������

    protected:
        std::string itemName; // ��Ŀ����
        std::string username; // �û���
        std::string password; // ����
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� WebsiteCredential �࣬���ڴ洢��վƾ����Ϣ���̳��� Credential ��
    class WebsiteCredential : public Credential {
    public:
        // Ĭ�Ϲ��캯��
        WebsiteCredential();
        // ���캯��
        WebsiteCredential(std::string itemName,
                          std::string username,
                          std::string password,
                          std::string websiteURL);
        // ���ƹ��캯��
        WebsiteCredential(const WebsiteCredential& other);
        // ��������
        ~WebsiteCredential() = default;

        std::string getWebsiteURL() const; // ��ȡ��վ URL

        void display() const override; // ��ʾ��վƾ����Ϣ

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setWebsiteURL(const std::string& newWebsiteURL);
    private:
        std::string websiteURL; // URL
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� BankCardCredential �࣬���ڴ洢���п�ƾ����Ϣ���̳��� Credential ��
    class BankCardCredential : public Credential {
    public:
        // Ĭ�Ϲ��캯��
        BankCardCredential() = default;
        // ���캯��
        BankCardCredential(std::string itemName,
                           std::string username,
                           std::string password,
                           std::string bankName,
                           std::string cardNumber);
        // ���ƹ��캯��
        BankCardCredential(const BankCardCredential& other);
        // ��������
        ~BankCardCredential() = default;

        std::string getBankName() const; // ��ȡ��������
        std::string getCardNumber() const; // ��ȡ����

        void display() const override; // ��ʾ���п�ƾ����Ϣ

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setBankName(const std::string& newBankName);
        void setCardNumber(const std::string& newCardNumber);

    private:
        // ˽�г�Ա����
        std::string bankName;
        std::string cardNumber;
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� SoftwareCredential �࣬���ڴ洢���ƾ����Ϣ���̳��� Credential ��
    class SoftwareCredential : public Credential {
    public:
        // Ĭ�ϸ��ƹ��캯��
        SoftwareCredential() = default;
        // ���캯��
        SoftwareCredential(std::string itemName,
                           std::string username,
                           std::string password,
                           std::string softwareName,
                           std::string licenseKey);
        // ���ƹ��캯��
        SoftwareCredential(const SoftwareCredential& other);
        // ��������
        ~SoftwareCredential() = default;

        std::string getSoftwareName() const; // ��ȡ�������
        std::string getLicenseKey() const; // ��ȡ���֤��Կ
        void display() const override; // ��ʾ���ƾ����Ϣ

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setSoftwareName(const std::string& newSoftwareName);
        void setLicenseKey(const std::string& newLicenseKey);

    private:
        std::string softwareName; // �������
        std::string licenseKey; // ���֤��Կ
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // ���� WifiCredential �࣬���ڴ洢 Wi-Fi ƾ����Ϣ���̳��� Credential ��
    class WifiCredential : public Credential {
    public:
        // Ĭ�Ϲ��캯��
        WifiCredential() = default;
        // ���캯��
        WifiCredential(std::string itemName,
                       std::string username,
                       std::string password,
                       std::string ssid);
        // ���ƹ��캯��
        WifiCredential(const WifiCredential& other);

        std::string getSsid() const; // ��ȡ SSID
        void display() const override; // ��ʾ Wi-Fi ƾ����Ϣ

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setSSID(const std::string& newSSID);

    private:
        std::string ssid; // SSID
    };

/* ------------------------------------------------------------------------------------------------------------------ */
} // PasswordManagement

#endif //PASSWORDMANAGEMENT_CREDENTIAL_H
