#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include<iostream>
#include <conio.h>
#include <cstdlib>
#include<string>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<chrono>
#include<thread>    //设置休眠时间的
#include"type.h"
#include "ledger.h"

// 初始化Books
std::vector<Ledger*> Book = {};

// 创建一个账单的交互函数，其目的是收集数据，但构造函数会在创建这条账目的时候自动调用expense()来对账户进行实时修改
// 如何解决传入账户的选择？
void create_ledger() {
    int y = 2023, m = 1, d = 1, h = 0, min = 0;
    std::string tp, n = "~";
    // subaccount则用之前已经建立好的账户对象
    bool ioo;
    double ta;
    Type type;
    std::string st;     // 设置交易类型

    bool temp = true;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    do {
        while (true) {
            system("cls");
            std::cout << "请选择交易时间(年月日时分)：" << std::endl;
            std::cout << std::endl;
            std::cout << "年: " << y;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //下箭头
                    y = ((y - 1) > 1) ? (y - 1) : 1;
                    break;
                case 72:  //上箭头
                    y = ((y + 1) < 2030) ? (y + 1) : 2030;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}\n", y);
            std::cout << "月: " << m;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //下箭头
                    m = ((m - 1) > 1) ? (m - 1) : 1;
                    break;
                case 72:  //上箭头
                    m = ((m + 1) < 12) ? (m + 1) : 12;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}.{}\n", y, m);
            std::cout << "日: " << d;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //下箭头
                    d = ((d - 1) > 1) ? (d - 1) : 1;
                    break;
                case 72:  //上箭头
                    d = ((d + 1) < 31) ? (d + 1) : 31;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}.{}.{}\n", y, m, d);
            std::cout << "小时: " << h;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //下箭头
                    h = ((h - 1) > 0) ? (h - 1) : 0;
                    break;
                case 72:  //上箭头
                    h = ((h + 1) < 24) ? (h + 1) : 24;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        while (true) {
            system("cls");
            fmt::print("{}.{}.{}  {}\n", y, m, d, h);
            std::cout << "分: " << min;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //下箭头
                    min = ((min - 1) > 0) ? (min - 1) : 0;
                    break;
                case 72:  //上箭头
                    min = ((min + 1) < 60) ? (min + 1) : 60;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        int year = y, month = m, day = d, minute = min, hour = h;
        Date d(year, month, day, hour, minute);
        temp = d.IsDateLegal();
        if (temp) {
            break;
        }
        else {
            std::cout << "请保证您的年月日相匹配，请重新输入" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }while (true);
    Date date(y, m, d, h, min);
    
    system("cls");
    std::cout << "请输入交易方：";
    std::cin >> tp;

    std::vector<Account*>::iterator it;
    it = all_subaccount.begin();  // 选定交易账户时要确保交易账户信息不为空，相关检测放在主函数中执行
    while (true) {
        system("cls");
        std::cout << "请选择交易账户： " << (*it)->get_name();
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //下箭头
                if (it == all_subaccount.begin()) {
                    break;
                }
                else {
                    it--;
                    break;
                }
            case 72:  //上箭头
                if (it == (all_subaccount.end() - 1))
                    break;
                else {
                    it++;
                    break;
                }
            }
        }
        else if (input == '\r') {
            break;
        }
    }

    system("cls");
    std::cout << "请输入交易金额：";
    std::cin >> ta;
    ta = abs(ta);

    std::vector<std::string> inout = { "支出","收入" };
    int i = 0;
    while (true) {
        system("cls");
        std::cout << "请选择收入/支出： " << inout[i];
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //下箭头
                i = ((i - 1) > 0) ? (i - 1) : 0;
                break;
            case 72:  //上箭头
                i = ((i + 1) < 1) ? (i + 1) : 1;
                break;
            }
        }
        else if (input == '\r') {
            if (i == 0)
                ioo = false;
            else
                ioo = true;
            break;
        }
    }

    // 交易类型
    system("cls");
    type.show_alltype();
    std::string user_define = "A";
    std::vector<std::string> yes_or_no = { "是","否" };
    int j = 0;
    while (true) {
        system("cls");
        std::cout << "您是否需要自定义消费类型：";
        std::cout << yes_or_no[j];
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //下箭头
                j = ((j - 1) > 0) ? (j - 1) : 0;
                break;
            case 72:  //上箭头
                j = ((j + 1) < 1) ? (j + 1) : 1;
                break;
            }
        }
        else if (input == '\r') {
            break;
        }
    }
    int type_num = 1;
    if (j==1) {
        while (true) {
            system("cls");
            type.show_alltype();
            std::cout << "请选择消费类型: " << type_num;
            char input = _getch();
            if (input == -32) {
                input = _getch();
                switch (input) {
                case 80:   //下箭头
                    type_num = ((type_num - 1) > 1) ? (type_num - 1) : 1;
                    break;
                case 72:  //上箭头
                    type_num = ((type_num + 1) < 10) ? (type_num + 1) : 10;
                    break;
                }
            }
            else if (input == '\r') {
                break;
            }
        }
        st = type.predefined_type[type_num - 1];
    }
    else {
        system("cls");
        std::cout << "请输入自定义交易类型：";
        std::cin >> user_define;
        type.add_userdefined_type(user_define);
        st = user_define;            //既然添加了自定义类型，就说明就是要使用这个类型，就么必要再选择了
    }
    //这里不适用选择的方式了，只给有的标准处理

    int yon = 0;
    while (true) {
        system("cls");
        std::cout << "您是否需要添加备注：";
        std::cout << yes_or_no[yon];
        char input = _getch();
        if (input == -32) {
            input = _getch();
            switch (input) {
            case 80:   //下箭头
                yon = ((yon - 1) > 0) ? (yon - 1) : 0;
                break;
            case 72:  //上箭头
                yon = ((yon + 1) < 1) ? (yon + 1) : 1;
                break;
            }
        }
        else if (input == '\r') {
            break;
        }
    }
    if (yon == 0) {
        system("cls");
        std::cout << "请输入备注：";
        std::cin >> n;
    }
    std::cout << std::endl;
    Ledger* l = new Ledger(date, tp, (*it), ioo, ta, st, n);
    l->expense();
    Book.push_back(l);
    std::sort(Book.begin(), Book.end(), [](const Ledger* a, const Ledger* b) {
        return *a < *b;
        });
    system("cls");
    if (!ioo) {
        if (!plan_collection.empty()) {
            auto plan_ptr = (plan_collection.end() - 1);
            (*plan_ptr).monitor();
        }
        else
            std::cout << "您现在还未创建任何规划，建议您创建规划以激活监督功能" << std::endl;
    }
}

Ledger::Ledger(Date d, std::string tp, Account* sa, bool ioo, double ta, std::string st, std::string n) :
    date(d), transaction_partners(tp), subaccount(sa), in_or_out(ioo), transaction_amount(ta), sle_type(st), note(n)
{}

void Ledger::ledger_show() {
    date.date_speshow();
    std::cout << "   ";
    std::cout << transaction_partners;
    std::cout << "   ";
    std::cout << subaccount->get_name();
    std::cout << "   ";
    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "{:.2f}", transaction_amount);
    std::cout << "   ";
    std::cout << sle_type;
    std::cout << "   ";
    std::cout << note << std::endl;
}

std::string Ledger::get_transaction_partners() {
    return transaction_partners;
}

std::string Ledger::get_subaccount() {
    return subaccount->get_name();
}

int Ledger::get_in_or_out() {
    if (in_or_out) {
        return 1;
    }
    else {
        return 0;
    }
}



std::string Ledger::get_note() {
    return note;
}

// 获取收支类型
std::string Ledger::get_sle_type() {
    return sle_type;
}

// 交易额的接口
double Ledger::get_transaction_amount() {
    return transaction_amount;
}

// 根据用户录入账目情况对相应账户进行修改
// 同时也意味着用户必须先录入账户信息
void Ledger::expense() {
    if (in_or_out)
        subaccount->deposit(get_transaction_amount());
    else
        subaccount->withdraw(get_transaction_amount());
}

bool Ledger::operator<(const Ledger& l) const {
    return date < l.date;
}
