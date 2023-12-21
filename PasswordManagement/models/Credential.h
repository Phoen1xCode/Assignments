// Credential.h
// Created by Jake Jia on 2023/12/5.
//



#ifndef PASSWORDMANAGEMENT_CREDENTIAL_H
#define PASSWORDMANAGEMENT_CREDENTIAL_H
#include <string>
#include "PasswordUtils.h"

namespace PasswordManagement {

/* ------------------------------------------------------------------------------------------------------------------ */
    // 定义 Identity 类，用于存储个人身份信息
    class Identity {
    public:
        // 默认构造函数
        Identity();

        // 构造函数
        Identity(std::string name,
                 std::string gender,
                 std::string birthdate,
                 std::string stuentID,
                 std::string email,
                 std::string phoneNumber);

        // 复制构造函数
        Identity(const Identity& other);
        // 析构函数
        ~Identity() = default;

        std::string getName() const; // 获取姓名
        std::string getGender() const; // 获取性别
        std::string getBirthdate() const; // 获取出生日期
        std::string getStudentID() const; // 获取学号
        std::string getEmail() const; // 获取电子邮件地址
        std::string getPhoneNumber() const; // 获取电话号码

        void display() const; // 显示身份信息

        void setName(const std::string& newName);
        void setGender(const std::string& newGender);
        void setBirthday(const std::string& newBirthday);
        void setStudentID(const std::string& newStudentID);
        void setEmail(const std::string& newEmail);
        void setPhoneNumber(const std::string& newPhoneNumber);

    private:
        std::string name; // 姓名
        std::string gender; // 性别
        std::string birthdate; // 生日
        std::string stuentID; // 学号
        std::string email; // 邮箱
        std::string phoneNumber; // 电话号码
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // 定义 Credential 类，用于存储凭据信息
    class Credential {
    public:
        // 默认构造函数
        Credential() = default;
        // 构造函数
        Credential(std::string itemName, std::string username, std::string password);
        // 复制构造函数
        Credential(const Credential& other);
        // 析构函数
        ~Credential() = default;

        std::string getItemName() const; // 获取项目名称
        std::string getUsername() const; // 获取用户名
        std::string getPassword() const; // 获取密码

        virtual void display() const; // 显示凭据信息

        virtual void setItemName(const std::string& newItemName); // 更改项目名称
        virtual void setUsername(const std::string& newUsername); // 更改用户名
        virtual void setPassword(const std::string& newPassword); // 更改密码

    protected:
        std::string itemName; // 项目名称
        std::string username; // 用户名
        std::string password; // 密码
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // 定义 WebsiteCredential 类，用于存储网站凭据信息，继承自 Credential 类
    class WebsiteCredential : public Credential {
    public:
        // 默认构造函数
        WebsiteCredential();
        // 构造函数
        WebsiteCredential(std::string itemName,
                          std::string username,
                          std::string password,
                          std::string websiteURL);
        // 复制构造函数
        WebsiteCredential(const WebsiteCredential& other);
        // 析构函数
        ~WebsiteCredential() = default;

        std::string getWebsiteURL() const; // 获取网站 URL

        void display() const override; // 显示网站凭据信息

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setWebsiteURL(const std::string& newWebsiteURL);
    private:
        std::string websiteURL; // URL
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // 定义 BankCardCredential 类，用于存储银行卡凭据信息，继承自 Credential 类
    class BankCardCredential : public Credential {
    public:
        // 默认构造函数
        BankCardCredential() = default;
        // 构造函数
        BankCardCredential(std::string itemName,
                           std::string username,
                           std::string password,
                           std::string bankName,
                           std::string cardNumber);
        // 复制构造函数
        BankCardCredential(const BankCardCredential& other);
        // 析构函数
        ~BankCardCredential() = default;

        std::string getBankName() const; // 获取银行名称
        std::string getCardNumber() const; // 获取卡号

        void display() const override; // 显示银行卡凭据信息

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setBankName(const std::string& newBankName);
        void setCardNumber(const std::string& newCardNumber);

    private:
        // 私有成员变量
        std::string bankName;
        std::string cardNumber;
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // 定义 SoftwareCredential 类，用于存储软件凭据信息，继承自 Credential 类
    class SoftwareCredential : public Credential {
    public:
        // 默认复制构造函数
        SoftwareCredential() = default;
        // 构造函数
        SoftwareCredential(std::string itemName,
                           std::string username,
                           std::string password,
                           std::string softwareName,
                           std::string licenseKey);
        // 复制构造函数
        SoftwareCredential(const SoftwareCredential& other);
        // 析构函数
        ~SoftwareCredential() = default;

        std::string getSoftwareName() const; // 获取软件名称
        std::string getLicenseKey() const; // 获取许可证密钥
        void display() const override; // 显示软件凭据信息

        void setItemName(const std::string& newItemName) override;
        void setUsername(const std::string& newUsername) override;
        void setPassword(const std::string& newPassword) override;
        void setSoftwareName(const std::string& newSoftwareName);
        void setLicenseKey(const std::string& newLicenseKey);

    private:
        std::string softwareName; // 软件名称
        std::string licenseKey; // 许可证密钥
    };

/* ------------------------------------------------------------------------------------------------------------------ */
    // 定义 WifiCredential 类，用于存储 Wi-Fi 凭据信息，继承自 Credential 类
    class WifiCredential : public Credential {
    public:
        // 默认构造函数
        WifiCredential() = default;
        // 构造函数
        WifiCredential(std::string itemName,
                       std::string username,
                       std::string password,
                       std::string ssid);
        // 复制构造函数
        WifiCredential(const WifiCredential& other);

        std::string getSsid() const; // 获取 SSID
        void display() const override; // 显示 Wi-Fi 凭据信息

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
