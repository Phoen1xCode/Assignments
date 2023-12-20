// Credential.cpp
// Created by Jake Jia on 2023/12/5.
//

#include <iostream>
#include <utility>
#include "../models/Credential.h"

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
    // Identity 类默认构造函数实现
    Identity::Identity() {
        this->name = "";
        this->gender = "";
        this->birthdate = "";
        this->stuentID = "";
        this->email = "";
        this->phoneNumber = "";
    }

    // Identity 类构造函数实现
    Identity::Identity(std::string name,
                       std::string gender,
                       std::string birthdate,
                       std::string studentID,
                       std::string email,
                       std::string phoneNumber) {
        this->name = std::move(name);
        this->gender = std::move(gender);
        this->birthdate = std::move(birthdate);
        this->stuentID = std::move(studentID);
        this->email = std::move(email);
        this->phoneNumber = std::move(phoneNumber);
    }

    // 复制构造函数
    Identity::Identity(const Identity &other) {
        this->name = other.name;
        this->gender = other.gender;
        this->birthdate = other.birthdate;
        this->stuentID = other.stuentID;
        this->email = other.email;
        this->phoneNumber = other.phoneNumber;
    }

    // Identity 类成员函数实现

    std::string Identity::getName() const {
        return this->name;
    }

    std::string Identity::getGender() const {
        return this->gender;
    }

    std::string Identity::getBirthdate() const {
        return this->birthdate;
    }

    std::string Identity::getStudentID() const {
        return this->stuentID;
    }

    std::string Identity::getEmail() const {
        return this->email;
    }

    std::string Identity::getPhoneNumber() const {
        return this->phoneNumber;
    }

    // 显示个人身份信息
    void Identity::display() const {
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Gender: " << this->gender << std::endl;
        std::cout << "Birthdate: " << this->birthdate << std::endl;
        std::cout << "StudentID: " << this->stuentID << std::endl;
        std::cout << "Email: " << this->email << std::endl;
        std::cout << "Phone Number: " << this->phoneNumber << std::endl;
    }

    void Identity::setName(const std::string& newName) {
        this->name = newName;
    }

    void Identity::setGender(const std::string&newGender) {
        this->gender = newGender;
    }

    void Identity::setBirthday(const std::string& newBirthday) {
        this->birthdate = newBirthday;
    }

    void Identity::setStudentID(const std::string& newStudentID) {
        this->birthdate = newStudentID;
    }

    void Identity::setEmail(const std::string& newEmail) {
        this->email = newEmail;
    }

    void Identity::setPhoneNumber(const std::string& newPhoneNumber) {
        this->phoneNumber = newPhoneNumber;
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    // Credential 类构造函数实现
    Credential::Credential(std::string itemName,
                           std::string username,
                           std::string password) {
        this->itemName = std::move(itemName);
        this->username = std::move(username);
        this->password = std::move(password);
    }

    // Credential 类复制构造函数实现
    Credential::Credential(const Credential &other) {
        this->itemName = other.itemName;
        this->username = other.username;
        this->password = other.password;
    }

    // Credential 类成员函数实现
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
        std::cout << "Item Name: " << this->itemName << std::endl;
        std::cout << "Username: " << this->username << std::endl;
        std::cout << "Password: " << this->password << std::endl;
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
    // WebsiteCredential 类默认构造函数实现
    WebsiteCredential::WebsiteCredential() : Credential() {
        this->websiteURL = "";
    }

    // WebsiteCredential 类构造函数实现
    WebsiteCredential::WebsiteCredential(std::string itemName,
                                         std::string username,
                                         std::string password,
                                         std::string websiteURL)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->websiteURL = std::move(websiteURL);
    }

    // WebsiteCredential 类复制构造函数实现
    WebsiteCredential::WebsiteCredential(const WebsiteCredential& other)
            : Credential(other) {
        this->websiteURL = other.websiteURL;
    }

    // 获取网站 URL
    std::string WebsiteCredential::getWebsiteURL() const {
        return this->websiteURL;
    }

    // 显示网站凭据信息
    void WebsiteCredential::display() const {
        Credential::display();
        std::cout << "Website URL: " << this->websiteURL << std::endl;
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
    // BankCardCredential 类构造函数实现
    BankCardCredential::BankCardCredential(std::string itemName,
                                           std::string username,
                                           std::string password,
                                           std::string bankName,
                                           std::string cardNumber)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->bankName = std::move(bankName);
        this->cardNumber = std::move(cardNumber);
    }

    // BankCardCredential 类复制构造函数实现
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

    // 显示银行卡凭据信息
    void BankCardCredential::display() const {
        Credential::display();
        std::cout << "Bank Name: " << this->bankName << std::endl;
        std::cout << "Card Number: " << this->cardNumber << std::endl;
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
    // SoftwareCredential 类构造函数实现
    SoftwareCredential::SoftwareCredential(std::string itemName,
                                           std::string username,
                                           std::string password,
                                           std::string softwareName,
                                           std::string licenseKey)
        : Credential(std::move(itemName), std::move(username), std::move(password)) {
        this->softwareName = std::move(softwareName);
        this->licenseKey = std::move(licenseKey);
    }

    // SoftwareCredential 类复制构造函数实现
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
        std::cout << "Software Name: " << this->softwareName << std::endl;
        std::cout << "License Key: " << this->licenseKey << std::endl;
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
    // WifiCredential 类构造函数实现
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
