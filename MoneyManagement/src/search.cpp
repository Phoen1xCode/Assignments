#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <conio.h>
#include <cstdlib>
#include <chrono>
#include <thread>    //设置休眠时间的
#include "search.h"
#include "../include/ledger.h"
#include "../include/date.h"


namespace finance {
    // 搜寻对应的日期
    void search_by_date_print() {
        int y = 2023, m = 1, d = 1;
        bool temp = true;

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
                    case 80:    //下箭头
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
            Date d(year, month, day);
            temp = d.IsDateLegal();
            if (temp) {
                break;
            }
            else {
                std::cout << "请保证您的年月日相匹配，请重新输入" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        } while (true);
        std::cout << std::endl;
        Date target_date(y, m, d);
        auto it = Book.begin();
        for (; it != Book.end(); it++) {
            if ((*it)->date == target_date) {
                (*it)->ledger_show();
                auto nextIt = std::next(it);  // 获取下一个迭代器,不直接使用it++避免指向end使得无效
                if (nextIt != Book.end() && (*nextIt)->date == target_date) {
                    continue;
                }
                else {
                    break;
                }
            }
            if (it == Book.end() - 1 && (*it)->date != target_date) {
                std::cout << "未找到该日期对应的账目" << std::endl;
            }
        }
    }

    void search_by_month_print() {
        int y = 2023, m = 1, day = 1;
        std::cout << "请选择年月：";
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
        std::cout << std::endl;
        Date target_date(y, m, day);
        auto it = Book.begin();
        for (; it != Book.end(); it++) {
            if ((*it)->date == target_date) {
                (*it)->ledger_show();
                auto nextIt = std::next(it);  // 获取下一个迭代器,不直接使用it++避免指向end使得无效
                if (nextIt != Book.end() && (*nextIt)->date == target_date) {
                    continue;
                }
                else {
                    break;
                }
            }
            if (it == Book.end() - 1 && (*it)->date != target_date) {
                std::cout << "未找到该日期对应的账目" << std::endl;
            }
        }
    }

    void search_by_year_print() {
        int year, month = 1, day = 28;
        std::cout << "请输入年：";
        std::cin >> year;
        std::cout << std::endl;
        Date target_date(year, month, day);
        auto it = Book.begin();
        for (; it != Book.end(); it++) {
            if ((*it)->date == target_date) {
                (*it)->ledger_show();
                auto nextIt = std::next(it);  // 获取下一个迭代器,不直接使用it++避免指向end使得无效
                if (nextIt != Book.end() && (*nextIt)->date == target_date) {
                    continue;
                }
                else {
                    break;
                }
            }
            if (it == Book.end() - 1 && (*it)->date != target_date) {
                std::cout << "未找到该日期对应的账目" << std::endl;
            }
        }
    }
}
