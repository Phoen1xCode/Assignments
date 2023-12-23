#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <conio.h>
#include <cstdlib>
#include<chrono>
#include<thread>    //设置休眠时间的
#include "../include/summary.h"
#include"../include/type.h"
#include "../include/ledger.h"
#include "../include/date.h"
#include "../include/account.h"
namespace finance {
    //主要用于生发总结的数据
    extern std::vector<Ledger*> Book;
    extern std::vector<Account*> all_subaccount;

    std::vector<double> sum_io_daily() {
        std::vector<double> daily_sum;  // 按日统计收入与支出，返回 vector 中元素的顺序为：收入，支出，净收支
        double sum_in = 0, sum_out = 0, net = 0;
        bool temp;

        std::cout << "请输入您想查看报表的具体日期" << std::endl;  // 只有按日来算没有综合报表
        int y = 2023, m = 1, d = 1;
        do {
            std::cout << "请选择年月日：";
            std::this_thread::sleep_for(std::chrono::seconds(1));
            while (true) {
                system("cls");
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
            int year = y, month = m, day = d;
            Date d(year, month, day, 12, 12);

            temp = d.IsDateLegal();
            if (temp) {
                break;
            }
            else {
                std::cout << "请保证您的年月日相匹配，请重新输入" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        } while (true);
        std::vector<Ledger*>::iterator it = Book.begin();
        Date target_date(y, m, d);
        for (; it < Book.end(); it++) {
            if ((*it)->date == target_date) {
                break;
            }
        }
        if (it == Book.end() - 1) {
            std::cout << "没有该日期的数据" << std::endl;
            return {};  // 这里需要外界函数对返回类型是否有效进行检查
        }
        for (; (*it)->date == target_date; it++) {
            if ((*it)->in_or_out) {
                sum_in += (*it)->transaction_amount;
            }
            else {
                sum_out += (*it)->transaction_amount;
            }
        }
        net = sum_in - sum_out;
        daily_sum.push_back(sum_in);
        daily_sum.push_back(sum_out);
        daily_sum.push_back(net);
        return daily_sum;
    }

    std::vector<std::vector<double>> sum_all_monthly() {
        std::cout << "请输入您想查看月报表的年份与月份" << std::endl;
        int year, month, day = 1;
        std::cin >> year >> month;
        Date target_date(year, month, day);  // 创建比较的日期
        std::vector<Ledger*>::iterator it = Book.begin();

        std::vector<double> io_sum;      // 收支数组
        double sum_in = 0, sum_out = 0, net = 0;  // 储存顺序为收入、支出、净收支

        std::vector<double> type_sum;  // 储存类型汇总的数组，数序为"医疗" , "食品" ,"住房", "交通" , "娱乐", "工资" ,"投资" ,"社交","储蓄", "其他"
        double medicine = 0, food = 0, housing = 0;  // 其他把自定义的包含进去了
        double transportation = 0, entertainment = 0, salary = 0;
        double investment = 0, social = 0, savings = 0, other = 0;

        int n = all_subaccount.size();
        std::vector<double> account_sum(n, 0);  // 储存账户汇总的数组，按照 all_subaccount 的顺序一一对应
        std::vector<std::string> account_name;
        for (auto temp_it : all_subaccount) {
            std::string temp_str;
            temp_str = temp_it->get_name();
            account_name.push_back(temp_str);
        }

        // 补充对投资的精细统计，忘掉了，哈哈
        std::vector<double> invest_haha(2, 0);

        for (; it != Book.end(); it++) {
            if ((*it)->date == target_date) {  // 首先进行日期的判断

                // 收支归纳
                if ((*it)->in_or_out) {
                    sum_in += (*it)->transaction_amount;
                }
                else {
                    sum_out += (*it)->transaction_amount;
                }

                // 类型归纳
                if ((*it)->sle_type == "医疗") {  // 0
                    medicine -= (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "食品") {  // 1
                    food -= (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "住房") {  // 2
                    housing -= (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "交通") {  // 3
                    transportation -= (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "娱乐") {  // 4
                    entertainment -= (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "工资") {  // 5
                    salary += (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "投资") {  // 6
                    if ((*it)->in_or_out) {
                        investment += (*it)->transaction_amount;
                        invest_haha[0] += (*it)->transaction_amount;
                    }
                    else
                        investment -= (*it)->transaction_amount;
                    invest_haha[1] += (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "社交") {  // 7
                    social -= (*it)->transaction_amount;
                }
                else if ((*it)->sle_type == "储蓄") {  // 8
                    savings += (*it)->transaction_amount;
                }
                else {  // 9
                    if ((*it)->in_or_out) {
                        other += (*it)->transaction_amount;
                    }
                    else
                        other -= (*it)->transaction_amount;
                }

                // 账户归纳
                for (int i = 0; i < n; i++) {
                    if (*((*it)->subaccount) == account_name[i]) {
                        if ((*it)->in_or_out) {
                            account_sum[i] += (*it)->transaction_amount;
                            break;
                        }
                        else {
                            account_sum[i] -= (*it)->transaction_amount;
                            break;
                        }
                    }
                }
                if ((*(it + 1))->date != target_date) {
                    break;
                }
            }
        }
        net = sum_in - sum_out;
        io_sum.push_back(sum_in);  //这一部分时单针对收支而言
        io_sum.push_back(sum_out);
        io_sum.push_back(net);

        type_sum.push_back(medicine);
        type_sum.push_back(food);
        type_sum.push_back(housing);
        type_sum.push_back(transportation);
        type_sum.push_back(entertainment);
        type_sum.push_back(salary);
        type_sum.push_back(investment);
        type_sum.push_back(social);
        type_sum.push_back(savings);
        type_sum.push_back(other);

        std::vector<std::vector<double>> all_sum;
        all_sum.push_back(io_sum);
        all_sum.push_back(type_sum);
        all_sum.push_back(account_sum);
        all_sum.push_back(invest_haha);  // 先回报，后投入
        return all_sum;
    }

    std::vector<std::vector<double>> sum_all_yearly() {
        std::cout << "请输入您想查看年报表的年份" << std::endl;
        int year, month = 1, day = 28;
        std::cin >> year;
        Type temp_type;
        Date target_date(year, month, day);  // 创建比较的日期
        std::vector<Ledger*>::iterator it = Book.begin();
        std::vector<double> io_sum;
        double sum_in = 0, sum_out = 0, net = 0;

        std::vector<double> type_sum(10, 0);
        std::vector<std::string> type_name(temp_type.predefined_type.begin(), temp_type.predefined_type.end());

        std::vector<double> account_sum(all_subaccount.size(), 0);
        std::vector<std::string> account_name;
        int n = all_subaccount.size();
        for (auto temp_it : all_subaccount) {
            std::string temp_str;
            temp_str = temp_it->get_name();
            account_name.push_back(temp_str);
        }
        std::vector<double> invest_haha(2, 0);

        for (; it != Book.end(); it++) {
            std::vector<Account*>::iterator temp_it = all_subaccount.begin();
            if ((*it)->date == target_date) {  // 首先进行日期的判断
                // 收支汇总
                if ((*it)->in_or_out) {
                    sum_in += (*it)->transaction_amount;
                }
                else {
                    sum_out += (*it)->transaction_amount;
                }

                // 类型汇总
                for (int i = 0; i < 10; i++) {
                    if ((*it)->sle_type == type_name[i] && (i == 5 || i == 8)) {
                        type_sum[i] += (*it)->transaction_amount;
                        break;
                    }
                    else if ((*it)->sle_type == type_name[i] && i == 6) {
                        if ((*it)->in_or_out) {  // 使用一点哈希函数的基本思想
                            type_sum[i] += (*it)->transaction_amount;
                            invest_haha[0] += (*it)->transaction_amount;
                        }
                        else {
                            type_sum[i] -= (*it)->transaction_amount;
                            invest_haha[1] += (*it)->transaction_amount;
                        }
                        break;
                    }
                    else if ((*it)->sle_type == type_name[i] && (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7)) {
                        type_sum[i] -= (*it)->transaction_amount;
                        break;
                    }
                    else {
                        if ((*it)->in_or_out) {
                            type_sum[i] += (*it)->transaction_amount;
                        }
                        else {
                            type_sum[i] -= (*it)->transaction_amount;
                        }
                        break;
                    }
                }
                // 账户汇总
                for (int i = 0; i < n; i++) {
                    if (*((*it)->subaccount) == account_name[i]) {
                        if ((*it)->in_or_out) {
                            account_sum[i] += (*it)->transaction_amount;
                            break;
                        }
                        else {
                            account_sum[i] -= (*it)->transaction_amount;
                            break;
                        }
                    }
                }
                if ((*(it + 1))->date != target_date) {
                    break;
                }
            }
        }
        net = sum_in - sum_out;
        io_sum.push_back(sum_in);
        io_sum.push_back(sum_out);
        io_sum.push_back(net);
        std::vector<std::vector<double>> all_sum;
        all_sum.push_back(io_sum);
        all_sum.push_back(type_sum);
        all_sum.push_back(account_sum);
        all_sum.push_back(invest_haha);
        return all_sum;
    }
    //这个是要和analyse搭配起来使用的
}