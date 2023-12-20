#define FMT_HEADER_ONLY  
#include <iostream>
#include <fmt/core.h>
#include <fmt/color.h>
#include<iostream>
#include<iomanip>
#include <conio.h>
#include<string>
#include<cstdio>
#include<vector>
#include<chrono>
#include<thread>    //设置休眠时间的
#include"plan.h"
#include"account.h"
#include"ledger.h"
#include"summary.h"
#include"analyse.h"
#include"plan.h"
#include"data_in_out.h"
#include"search.h"
#include<mysql.h>


const char* host = "127.0.0.1";  //本地主机
const char* user = "root";              //名字，默认root
const char* pw = "ZYl/20050507";        //密码
const int port = 3306;                  //端口号，默认
const char* a_database = "account";     //数据库名字   
const char* l_database = "ledger";      //在使用 MySQL C API 中的函数时，通常需要传递 C 风格的字符串而不是 std::string 对象。
const char* p_database = "plan";

std::vector<std::string> function_part_main = { "    账户      ","    账本      ","    报表      ","    规划      ","    退出      " };
std::vector<std::string> function_part_account = { "    创建账户    ","    查看账户    ","      退出      " };
std::vector<std::string> function_part_ledger = { "  录入账目  ","  查看账本  ","  账目检索  ","    退出    " };
std::vector<std::string> way = { "年","月","日" };

void display_options(int selectedOption,std::vector<std::string> function_part) {
    system("cls");
    fmt::print("请选择功能模块:\n");
    int n = size(function_part);
    for (int i = 1; i <= n; ++i) {
        fmt::print("{}{}\n", function_part[i - 1], (i == selectedOption) ? "<-" : "  ");
    }
}

int main() {
    std::cout << "数据加载中，请耐心等候" << std::endl;
    //数据的读入模块，在主函数中接入数据库算了
    MYSQL* a_conn = mysql_init(NULL);
    MYSQL* l_conn = mysql_init(NULL);
    MYSQL* p_conn = mysql_init(NULL);
    mysql_options(a_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    mysql_options(l_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    mysql_options(p_conn, MYSQL_SET_CHARSET_NAME, "GBK");
    mysql_real_connect(a_conn, host, user, pw, a_database, port, NULL, 0);
    mysql_real_connect(l_conn, host, user, pw, l_database, port, NULL, 0);
    mysql_real_connect(p_conn, host, user, pw, p_database, port, NULL, 0);
    account_reclaim(a_conn);
    ledger_reclaim(l_conn);
    plan_reclaim(p_conn);

    std::cout << "加载完毕，启动！" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
    //以上部分已经没有问题了
    while (true) {
        if (all_subaccount.empty()) {
            std::cout << "您现在还没有账户，无法正常使用基本功能，请您先创建一个账户" << std::endl;
            create_account();
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else
            break;
    }

    int selection = 1;
    while (true) {
        while (true) {
            display_options(selection, function_part_main);
            int n = size(function_part_main);
            char input = _getch(); // 从键盘获取字符

            if (input == -32) { // 如果是方向键
                input = _getch(); // 获取方向键的具体键值

                switch (input) {
                case 72: // 上箭头
                    selection = (1 > (selection - 1)) ? 1 : (selection - 1);
                    break;
                case 80: // 下箭头
                    selection = (n < (selection + 1)) ? n : (selection + 1);
                    break;
                }
            }
            else if (input == '\r') { // Enter键
                if (selection != 5) {
                    fmt::print("即将进入{}模块\n", function_part_main[selection - 1]);
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    break;
                }
                else
                    break;
            }
        }
        system("cls");
        switch (selection) {
        case 1: {
            while (true) {
                int selection1 = 1;
                while (true) {
                    display_options(selection1, function_part_account);
                    int n = size(function_part_account);
                    char input1 = _getch(); // 从键盘获取字符

                    if (input1 == -32) {
                        input1 = _getch();

                        switch (input1) {
                        case 72: // 上箭头
                            selection1 = (1 > (selection1 - 1)) ? 1 : (selection1 - 1);
                            break;
                        case 80: // 下箭头
                            selection1 = (n < (selection1 + 1)) ? n : (selection1 + 1);
                            break;
                        }
                    }
                    else if (input1 == '\r') { // Enter键
                        if (selection1 != 3) {
                            fmt::print("即将进入{}模块\n", function_part_account[selection1 - 1]);
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        else
                            break;
                    }
                }
                system("cls");
                switch (selection1) {
                case 1: {
                    create_account();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    break;
                }
                case 2: {
                    for (auto it : all_subaccount) {
                        it->account_show();
                        std::cout << std::endl;
                    }
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "退出账户查看请按Backspace（该界面将于2min后自动关闭）");
                    char input1_1 = _getch();
                    if (input1_1 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 3: {
                    break;
                }
                }
                if (selection1 == 3) {
                    break;
                }
            }
            break;
        }
        case 2: {
            while (true) {
                int selection2 = 1;
                while (true) {
                    display_options(selection2, function_part_ledger);
                    int n = size(function_part_ledger);
                    char input2 = _getch(); // 从键盘获取字符

                    if (input2 == -32) {
                        input2 = _getch();

                        switch (input2) {
                        case 72: // 上箭头
                            selection2 = (1 > (selection2 - 1)) ? 1 : (selection2 - 1);
                            break;
                        case 80: // 下箭头
                            selection2 = (n < (selection2 + 1)) ? n : (selection2 + 1);
                            break;
                        }
                    }
                    else if (input2 == '\r') { // Enter键
                        if (selection2 != 4) {
                            fmt::print("即将进入{}模块\n", function_part_ledger[selection2 - 1]);
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            break;
                        }
                        else
                            break;
                    }
                }
                switch (selection2) {
                case 1: {
                    create_ledger();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "退出账目创建请按Backspace（该界面将于2min后自动关闭）");
                    char input2_1 = _getch();
                    if (input2_1 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 2: {
                    system("cls");
                    for (auto it = Book.rbegin(); it != Book.rend(); ++it) {
                        (*it)->ledger_show();
                        std::cout << std::endl;
                    }
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "退出账目查看请按Backspace（该界面将于2min后自动关闭）");
                    char input2_2 = _getch();
                    if (input2_2 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 3: {
                    int temp = 1;

                    while (true) {
                        system("cls");
                        fmt::print("请选择你的检索方式：按{}检索\n", way[temp-1]);
                        char input2_4 = _getch();
                        if (input2_4 == -32) {
                            input2_4 = _getch();
                            switch (input2_4) {
                            case 80:    //下
                                temp = ((temp - 1) > 1) ? (temp - 1) : 1;
                                break;
                            case 72:    //上
                                temp = ((temp + 1) < 3) ? (temp + 1) : 3;
                                break;
                            }
                        }
                        else if (input2_4 == '\r') {
                            break;
                        }
                    }
                    if (temp == 1) {
                        search_by_year_print();
                    }
                    else if (temp == 2) {
                        search_by_month_print();
                    }
                    else
                        search_by_date_print();
                    //统一结束操作
                    fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "退出账目查看请按Backspace（该界面将于2min后自动关闭）");
                    char input2_4_1 = _getch();
                    if (input2_4_1 == 8)
                        break;

                    std::this_thread::sleep_for(std::chrono::seconds(120));
                    break;
                }
                case 4: {
                    break;
                }
                }
                if (selection2 == 4) {
                    break;
                }
            }
            break;
        }
        case 3: {
            int temp = 1;

            while (true) {
                system("cls");
                fmt::print("请选择您想查看的报表类型：");
                fmt::print("{}报表\n", way[temp-1]);
                char input3 = _getch();
                if (input3 == -32) {
                    input3 = _getch();
                    switch (input3) {
                    case 80:    //下
                        temp = ((temp - 1) > 1) ? (temp - 1) : 1;
                        break;
                    case 72:    //上
                        temp = ((temp + 1) < 3) ? (temp + 1) : 3;
                        break;
                    }
                }
                else if (input3 == '\r') {
                    break;
                }
            }
            if (temp == 1) {
                std::vector<double> temp_vector = sum_io_daily();
                std::cout << std::endl << "按日查看无法为您生成有价值的报表，只能为您提供一些基本的数据" << std::endl;
                analyse_daily(temp_vector);
            }
            else if (temp == 2) {
                std::vector<std::vector<double>> temp_vector = sum_all_monthly();
                analyse_summary(temp_vector);
            }
            else {
                std::vector<std::vector<double>> temp_vector = sum_all_yearly();
                analyse_summary(temp_vector);
            }
            fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "退出报表查看请按Backspace（该界面将于2min后自动关闭）");
            char input3_1 = _getch();
            if (input3_1 == 8)
                break;

            std::this_thread::sleep_for(std::chrono::seconds(120));
            break;
        }
        case 4: {
            create_plan();
            fmt::print(fg(fmt::color::cyan) | fmt::emphasis::bold, "退出请按Backspace（该界面将于2min后自动关闭）");
            char input4 = _getch();
            if (input4 == 8)
                break;

            std::this_thread::sleep_for(std::chrono::seconds(120));
            break;
        }
        case 5:
            break;
        }
        if (selection == 5)
            break;
    }
    plan_storage(p_conn);      //和上面的顺序相反，保证基础的最后储存          
    ledger_storage(l_conn);
    account_storage(a_conn);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
