//
// Created by Jake Jia on 2023/12/5.
//

#ifndef PASSWORDMANAGEMENT_CREDENTIAL_H
#define PASSWORDMANAGEMENT_CREDENTIAL_H

#include <string>
#include <iostream>


namespace PasswordManagement { // 定义 PasswordManagement 命名空间
    // 定义 Identity 类，用于存储个人身份信息
    // 武汉大学 学子定制
    class Identity {
    public:
        // 构造函数
        Identity(std::string name,
                 std::string gender,
                 std::string birthdate,
                 std::string stuentId,
                 std::string email,
                 std::string phoneNumber);

        // 获取姓名
        std::string getName() const;
        // 获取性别
        std::string getGender() const;
        // 获取出生日期
        std::string getBirthdate() const;
        // 获取学号
        std::string getStudentId() const;
        // 获取电子邮件地址
        std::string getEmail() const;
        // 获取电话号码
        std::string getPhoneNumber() const;
        // 显示身份信息
        void display() const;

    private:
        // 私有成员变量
        std::string name;
        std::string gender;
        std::string birthdate;
        std::string stuentId; // 学号
        std::string email;
        std::string phoneNumber;
    };

    // 定义 Credential 类，用于存储凭据信息
    class Credential {
    public:
        // 构造函数
        Credential(std::string itemName, std::string username, std::string password);
        // 复制构造函数
        Credential(const Credential& other);

        // 获取项目名称
        std::string getItemName() const;
        // 获取用户名
        std::string getUsername() const;
        // 获取密码
        std::string getPassword() const;
        // 显示凭据信息
        virtual void display() const;


        // 更改密码
//        virtual void changePassword(const std::string& newPassword);

    protected:
        std::string itemName; // 项目名称
        std::string username; // 用户名
        std::string password; // 密码
    };

    // 定义 WebsiteCredential 类，用于存储网站凭据信息，继承自 Credential 类
    class WebsiteCredential : public Credential {
    public:
        // 构造函数
        WebsiteCredential(std::string itemName, std::string username, std::string password, std::string websiteURL);
        // 复制构造函数
        WebsiteCredential(const WebsiteCredential& other);

        // 获取网站 URL
        std::string getWebsiteURL() const;
        // 显示网站凭据信息
        void display() const override;

    private:
        // 私有成员变量
        std::string websiteURL;
    };

    // 定义 BankCardCredential 类，用于存储银行卡凭据信息，继承自 Credential 类
    class BankCardCredential : public Credential {
    public:
        // 构造函数
        BankCardCredential(std::string itemName, std::string username, std::string password, std::string bankName, std::string cardNumber);
        // 复制构造函数
        BankCardCredential(const BankCardCredential& other);
        // 获取银行名称
        std::string getBankName() const;
        // 获取卡号
        std::string getCardNumber() const;
        // 显示银行卡凭据信息
        void display() const override; 

    private:
        // 私有成员变量
        std::string bankName;
        std::string cardNumber;
    };




/* To-Do
    过期提醒:对于某些凭据（如银行卡、软件许可证），可能需要在它们过期前提醒用户更新或检查。
*/



    // 定义 SoftwareCredential 类，用于存储软件凭据信息，继承自 Credential 类
    class SoftwareCredential : public Credential {
    public:
        // 构造函数
        SoftwareCredential(std::string itemName, std::string username, std::string password, std::string softwareName, std::string licenseKey);
        // 复制构造函数
        SoftwareCredential(const SoftwareCredential& other);
        // 获取软件名称
        std::string getSoftwareName() const;
        // 获取许可证密钥
        std::string getLicenseKey() const;
        // 显示软件凭据信息
        void display() const override;

    private:
        // 私有成员变量
        std::string softwareName;
        std::string licenseKey;
    };

    // 定义 WifiCredential 类，用于存储 Wi-Fi 凭据信息，继承自 Credential 类
    class WifiCredential : public Credential {
    public:
        // 构造函数
        WifiCredential(std::string itemName, std::string username, std::string password, std::string ssid);
        // 获取 SSID
        std::string getSsid() const;
        // 显示 Wi-Fi 凭据信息
        void display() const override;

    private:
        // 私有成员变量
        std::string ssid;
    };
} // PasswordManagement 命名空间结束

#endif //PASSWORDMANAGEMENT_CREDENTIAL_H // 结束头文件保护
