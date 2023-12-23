#pragma once
#include<vector>
#include<string>
#include"date.h"        
#include"account.h"
#include"summary.h"
#include"plan.h"

namespace finance {
    //一条条的账目
    class Plan;
    class Account;
    class Ledger {
    private:
        friend std::vector<double> sum_io_daily();
        friend std::vector<std::vector<double>> sum_all_monthly();
        friend std::vector<std::vector<double>> sum_all_yearly();
        friend class Plan;

        std::string transaction_partners;
        Account* subaccount;              //以指针的方式将Account类的一个对象传入ledger以实现同步更改
        bool in_or_out;                  //0 for out,1 for in
        double transaction_amount;
        std::string sle_type;        //这个是储存类型的实体
        std::string note;
    public:
        Date date;
        //有备注的初始化(有无无所谓，不过是默认备注是否会被覆盖掉而已)
        Ledger(Date d, std::string tp, Account* sa, bool ioo, double ta, std::string st, std::string n);
        void ledger_show();
        std::string get_transaction_partners();
        std::string get_subaccount();
        int get_in_or_out();
        std::string get_sle_type();                //方便分析系统获取
        std::string get_note();
        double get_transaction_amount();           //主要是为了方便后期统计支出或者收入
        void expense();              //将账单映射到账户上
        bool operator<(const Ledger& l)const;
    };

    void create_ledger();

    extern std::vector<Ledger*> Book;      //用于收录所有账目的指针
    //指针没有处理好
}