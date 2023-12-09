//
// Created by Jake Jia on 2023/12/5.
//

#include <utility>

#include "../models/Credential.h"

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
    // Identity 类构造函数实现
    Identity::Identity(std::string name,
                       std::string gender,
                       std::string birthdate,
                       std::string stuentId,
                       std::string email,
                       std::string phoneNumber) {
        this->name = std::move(name);
        this->gender = std::move(gender);
        this->birthdate = std::move(birthdate);
        this->stuentId = std::move(stuentId);
        this->email = std::move(email);
        this->phoneNumber = std::move(phoneNumber);
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

    std::string Identity::getStudentId() const {
        return this->stuentId;
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
        std::cout << "StudentID: " << this->stuentId << std::endl;
        std::cout << "Email: " << this->email << std::endl;
        std::cout << "Phone Number: " << this->phoneNumber << std::endl;
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

    // 显示凭据信息
    void Credential::display() const {
        std::cout << "Item Name: " << itemName << std::endl;
        std::cout << "Username: " << username << std::endl;
        std::cout << "Password: " << password << std::endl;
    }

//    // 更改密码
//    void Credential::changePassword(const std::string& newPassword) {
//        password = newPassword;
//    }


/* ------------------------------------------------------------------------------------------------------------------ */
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

    // 获取银行名称
    std::string BankCardCredential::getBankName() const {
        return this->bankName;
    }

    // 获取卡号
    std::string BankCardCredential::getCardNumber() const {
        return this->cardNumber;
    }

    // 显示银行卡凭据信息
    void BankCardCredential::display() const {
        Credential::display();
        std::cout << "Bank Name: " << this->bankName << std::endl;
        std::cout << "Card Number: " << this->cardNumber << std::endl;
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

    // 获取软件名称
    std::string SoftwareCredential::getSoftwareName() const {
        return this->softwareName;
    }

    // 获取许可证密钥
    std::string SoftwareCredential::getLicenseKey() const {
        return this->licenseKey;
    }

    // 显示软件凭据信息
    void SoftwareCredential::display() const {
        Credential::display();
        std::cout << "Software Name: " << this->softwareName << std::endl;
        std::cout << "License Key: " << this->licenseKey << std::endl;
    }

/* ------------------------------------------------------------------------------------------------------------------ */

    // WifiCredential 类构造函数实现
    WifiCredential::WifiCredential(std::string itemName, std::string username, std::string password, std::string ssid)
        : Credential(std::move(itemName), std::move(username), std::move(password)), ssid(std::move(ssid)) {}

    // 获取 SSID
    std::string WifiCredential::getSsid() const {
        return ssid;
    }

    // 显示 Wi-Fi 凭据信息
    void WifiCredential::display() const {
        Credential::display();
        std::cout << "SSID: " << ssid << std::endl;
    }

}
