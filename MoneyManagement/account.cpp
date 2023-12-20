#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
#include"account.h"

std::vector<Account*> all_subaccount = {};

// 交互函数辅助创建账户，利用Account为抽象类的性质，实现指针的宽使用
void create_account() {
    std::string n, h, num;
    int m;
    Account* a = nullptr;
    std::cout << "请输入账户名：";
    std::cin >> n;
    std::cout << "请输入账户持有人姓名：";
    std::cin >> h;
    std::cout << "请输入账户id：";
    std::cin >> num;
    while (true) {
        std::cout << "请输入账户余额：";
        std::cin >> m;
        if (m <= 100000000000000.00&&m>=0) {
            break;
        }
        else {
            std::cout << "富哥（婆），麻烦您认真输入，你的资产已经超过中国外汇储备了" << std::endl;
        }
    }
    a = new Account(n, h, num, m);
    all_subaccount.push_back(a);
    std::cout << "账户创建成功！即将退出账户创建界面" << std::endl;
}

//-----------Account---------------
// 构造函数
Account::Account(std::string n, std::string h, std::string num, double m) : name(n), holder(h), number(num), money(m) {}


// 基础数据成员的外部接口
std::string Account::get_name() {
    return name;
}
std::string Account::get_holder() {
    return holder;
}
std::string Account::get_number() {
    return number;
}
double Account::get_money() {
    return money;
}

// 修改账户信息的函数
void Account::set_name(std::string n) {
    name = n;
}
void Account::set_holder(std::string h) {
    holder = h;
}
void Account::set_number(std::string n) {
    number = n;
}
void Account::set_money(double m) {
    money = m;
}

// 展现账户信息
void Account::account_show() {
    std::cout << std::left << std::setw(10) << "holder: ";
    fmt::print(fg(fmt::color::yellow), "{:^30}\n", holder);
    std::cout << std::setw(10) <<"number: ";
    fmt::print(fg(fmt::color::yellow), "{:^30}\n", number);
    std::cout << std::setw(10) << "money: ";
    fmt::print(fg(fmt::color::yellow), "{:^30}\n", money);
}

// 取钱
void Account::withdraw(int m) {
    money -= m;
}

// 存钱
void Account::deposit(int m) {
    money += m;
}

void Account::warning() {};

Account::~Account() {};

bool Account::operator ==(Account& a) {
    std::string temp = this->get_name();
    if (temp == a.get_name()) {
        return true;
    }
    else {
        return false;
    }
}

bool Account::operator ==(std::string& a) {
    std::string temp = this->get_name();
    if (temp == a) {
        return true;
    }
    else {
        return false;
    }
}
