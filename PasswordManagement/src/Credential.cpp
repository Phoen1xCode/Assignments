// Credential.cpp
// Created by Jake Jia on 2023/12/5.
//

#include <iostream>
#include <utility>
#include "../include/Credential.h"

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
//    // Identity ��Ĭ�Ϲ��캯��ʵ��
//    Identity::Identity() {
//        this->name = "";
//        this->gender = "";
//        this->birthdate = "";
//        this->stuentID = "";
//        this->email = "";
//        this->phoneNumber = "";
//    }
//
//    // Identity �๹�캯��ʵ��
//    Identity::Identity(std::string name,
//                       std::string gender,
//                       std::string birthdate,
//                       std::string studentID,
//                       std::string email,
//                       std::string phoneNumber) {
//        this->name = std::move(name);
//        this->gender = std::move(gender);
//        this->birthdate = std::move(birthdate);
//        this->stuentID = std::move(studentID);
//        this->email = std::move(email);
//        this->phoneNumber = std::move(phoneNumber);
//    }
//
//    // ���ƹ��캯��
//    Identity::Identity(const Identity &other) {
//        this->name = other.name;
//        this->gender = other.gender;
//        this->birthdate = other.birthdate;
//        this->stuentID = other.stuentID;
//        this->email = other.email;
//        this->phoneNumber = other.phoneNumber;
//    }
//
//    // Identity ���Ա����ʵ��
//
//    std::string Identity::getName() const {
//        return this->name;
//    }
//
//    std::string Identity::getGender() const {
//        return this->gender;
//    }
//
//    std::string Identity::getBirthdate() const {
//        return this->birthdate;
//    }
//
//    std::string Identity::getStudentID() const {
//        return this->stuentID;
//    }
//
//    std::string Identity::getEmail() const {
//        return this->email;
//    }
//
//    std::string Identity::getPhoneNumber() const {
//        return this->phoneNumber;
//    }
//
//    // ��ʾ���������Ϣ
//    void Identity::display() const {
//        std::cout << "������" << this->name << std::endl;
//        std::cout << "�Ա� " << this->gender << std::endl;
//        std::cout << "����: " << this->birthdate << std::endl;
//        std::cout << "ѧ��: " << this->stuentID << std::endl;
//        std::cout << "���� " << this->email << std::endl;
//        std::cout << "�绰���� " << this->phoneNumber << std::endl;
//    }
//
//    void Identity::setName(const std::string& newName) {
//        this->name = newName;
//    }
//
//    void Identity::setGender(const std::string&newGender) {
//        this->gender = newGender;
//    }
//
//    void Identity::setBirthday(const std::string& newBirthday) {
//        this->birthdate = newBirthday;
//    }
//
//    void Identity::setStudentID(const std::string& newStudentID) {
//        this->birthdate = newStudentID;
//    }
//
//    void Identity::setEmail(const std::string& newEmail) {
//        this->email = newEmail;
//    }
//
//    void Identity::setPhoneNumber(const std::string& newPhoneNumber) {
//        this->phoneNumber = newPhoneNumber;
//    }

/* ------------------------------------------------------------------------------------------------------------------ */

    // Credential �๹�캯��ʵ��
    Credential::Credential(std::string itemName,
                           std::string username,
                           std::string password) {
        this->itemName = std::move(itemName);
        this->username = std::move(username);
        this->password = std::move(password);
    }

    // Credential �ิ�ƹ��캯��ʵ��
    Credential::Credential(const Credential &other) {
        this->itemName = other.itemName;
        this->username = other.username;
        this->password = other.password;
    }

    // Credential ���Ա����ʵ��
    std::string Credential::getItemName() const {
        return itemName;
    }

    std::string Credential::getUsername() const {
        return username;
    }

    std::string Credential::getPassword() const {
        return password;
    }

    void Credential::display() const {
        std::cout << "��Ŀ����: " << this->itemName << std::endl;
        std::cout << "�û���: " << this->username << std::endl;
        std::cout << "����: " << this->password << std::endl;
    }

    void Credential::setItemName(const std::string &newItemName) {
        this->itemName = newItemName;
    }

    void Credential::setUsername(const std::string &newUsername) {
        this->username = newUsername;
    }


    void Credential::setPassword(const std::string& newPassword) {
        this->password = newPassword;
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    // WebsiteCredential ��Ĭ�Ϲ��캯��ʵ��
    WebsiteCredential::WebsiteCredential() : Credential() {
        this->websiteURL = "";
    }

    // WebsiteCredential �๹�캯��ʵ��
    WebsiteCredential::WebsiteCredential(std::string itemName,
                                         std::string username,
                                         std::string password,
                                         std::string websiteURL)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->websiteURL = std::move(websiteURL);
    }

    // WebsiteCredential �ิ�ƹ��캯��ʵ��
    WebsiteCredential::WebsiteCredential(const WebsiteCredential& other)
            : Credential(other) {
        this->websiteURL = other.websiteURL;
    }

    // ��ȡ��վ URL
    std::string WebsiteCredential::getWebsiteURL() const {
        return this->websiteURL;
    }

    // ��ʾ��վƾ����Ϣ
    void WebsiteCredential::display() const {
        Credential::display();
        std::cout << "��վ URL: " << this->websiteURL << std::endl;
    }

    void WebsiteCredential::setItemName(const std::string &newItemName) {
        Credential::setItemName(newItemName);
    }

    void WebsiteCredential::setUsername(const std::string &newUsername) {
        Credential::setUsername(newUsername);
    }

    void WebsiteCredential::setPassword(const std::string &newPassword) {
        Credential::setPassword(newPassword);
    }

    void WebsiteCredential::setWebsiteURL(const std::string &newWebsiteURL) {
        this->websiteURL = newWebsiteURL;
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    // BankCardCredential �๹�캯��ʵ��
    BankCardCredential::BankCardCredential(std::string itemName,
                                           std::string username,
                                           std::string password,
                                           std::string bankName,
                                           std::string cardNumber)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->bankName = std::move(bankName);
        this->cardNumber = std::move(cardNumber);
    }

    // BankCardCredential �ิ�ƹ��캯��ʵ��
    BankCardCredential::BankCardCredential(const BankCardCredential &other)
        : Credential(other) {
        this->bankName = other.bankName;
        this->cardNumber = other.cardNumber;
    }

    std::string BankCardCredential::getBankName() const {
        return this->bankName;
    }

    std::string BankCardCredential::getCardNumber() const {
        return this->cardNumber;
    }

    // ��ʾ���п�ƾ����Ϣ
    void BankCardCredential::display() const {
        Credential::display();
        std::cout << "��������: " << this->bankName << std::endl;
        std::cout << "����: " << this->cardNumber << std::endl;
    }

    void BankCardCredential::setItemName(const std::string& newItemName) {
        Credential::setItemName(newItemName);
    }

    void BankCardCredential::setUsername(const std::string& newUsername) {
        Credential::setUsername(newUsername);
    }

    void BankCardCredential::setPassword(const std::string& newPassword) {
        Credential::setPassword(newPassword);
    }

    void BankCardCredential::setBankName(const std::string &newBankName) {
        this->bankName = newBankName;
    }

    void BankCardCredential::setCardNumber(const std::string &newCardNumber) {
        this->cardNumber = newCardNumber;
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    // SoftwareCredential �๹�캯��ʵ��
    SoftwareCredential::SoftwareCredential(std::string itemName,
                                           std::string username,
                                           std::string password,
                                           std::string softwareName,
                                           std::string licenseKey)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->softwareName = std::move(softwareName);
        this->licenseKey = std::move(licenseKey);
    }

    // SoftwareCredential �ิ�ƹ��캯��ʵ��
    SoftwareCredential::SoftwareCredential(const SoftwareCredential& other)
        : Credential(other) {
        this->softwareName = other.softwareName;
        this->licenseKey = other.licenseKey;
    }

    std::string SoftwareCredential::getSoftwareName() const {
        return this->softwareName;
    }

    std::string SoftwareCredential::getLicenseKey() const {
        return this->licenseKey;
    }

    void SoftwareCredential::display() const {
        Credential::display();
        std::cout << "�������: " << this->softwareName << std::endl;
        std::cout << "���֤��Կ: " << this->licenseKey << std::endl;
    }

    void SoftwareCredential::setItemName(const std::string &newItemName) {
        Credential::setItemName(newItemName);
    }

    void SoftwareCredential::setUsername(const std::string &newUsername) {
        Credential::setUsername(newUsername);
    }

    void SoftwareCredential::setPassword(const std::string &newPassword) {
        Credential::setPassword(newPassword);
    }

    void SoftwareCredential::setSoftwareName(const std::string &newSoftwareName) {
        this->softwareName = newSoftwareName;
    }

    void SoftwareCredential::setLicenseKey(const std::string &newLicenseKey) {
        this->licenseKey = newLicenseKey;
    }

/* ------------------------------------------------------------------------------------------------------------------ */
    // WifiCredential �๹�캯��ʵ��
    WifiCredential::WifiCredential(std::string itemName,
                                   std::string username,
                                   std::string password,
                                   std::string ssid)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->ssid = std::move(ssid);
    }

    WifiCredential::WifiCredential(const WifiCredential &other)
    : Credential(other) {
        this->ssid = other.ssid;
    }

    std::string WifiCredential::getSsid() const {
        return ssid;
    }

    void WifiCredential::display() const {
        Credential::display();
        std::cout << "SSID: " << this->ssid << std::endl;
    }

    void WifiCredential::setItemName(const std::string &newItemName) {
        Credential::setItemName(newItemName);
    }

    void WifiCredential::setUsername(const std::string &newUsername) {
        Credential::setUsername(newUsername);
    }

    void WifiCredential::setPassword(const std::string &newPassword) {
        Credential::setPassword(newPassword);
    }

    void WifiCredential::setSSID(const std::string &newSSID) {
        this->ssid = newSSID;
    }

/* ------------------------------------------------------------------------------------------------------------------ */


} // PasswordManagement
