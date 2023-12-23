#pragma once
#include<vector>
#include<string>
#include<fstream>
#include"date.h"
#include"summary.h"           //友元所需
//此处的账户并不完全等效于银行账户本身，其创建的目的是帮助用户清楚收支途径
//并非是直接针对银行账户展开管理，所以不会有利息(仅针对银行卡而非信用卡)等部分元素（书上有相关部分，所以没必要写一些重复的东西）
namespace finance {
    class Ledger;

    class Account {
        std::string name;     //账户的名字，例如支付宝等
        std::string holder;
        std::string number;   //因为难记，所以不打算拿这个进行比较
        double money;
    public:
        friend std::vector<double> sum_io_daily();
        friend std::vector<std::vector<double>> sum_all_monthly();
        friend std::vector<std::vector<double>> sum_all_yearly();
        friend class Ledger;

        Account(std::string n, std::string h, std::string num, double m);
        std::string get_name();               //各类私有数据成员的接口
        std::string get_holder();
        std::string get_number();
        double get_money();
        void set_name(std::string n);            //--------主要用于用户自己修改内容，因为可能会出现无法记入账目的内容改变
        void set_holder(std::string h);
        void set_number(std::string n);
        void set_money(double m);               //------------------------------------------------------------------ 
        void withdraw(int sum);                 //存取相关的函数，由于改变账户的状态（主要是money）
        void deposit(int sum);
        void account_show();
        ~Account();
        bool operator == (Account& a);
        bool operator ==(std::string& a);
    };

    //与普通的账户基本没有什么区别
    void create_account();    //辅助创建账户的哈纳树

    extern std::vector<Account*> all_subaccount;
}