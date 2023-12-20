#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include "plan.h"
#include <map>
#include <string>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <iterator>

std::vector<Plan> plan_collection = {};

void create_plan() {
    Plan plan;
    plan_collection.push_back(plan);
}

Plan::Plan() {
    std::cout << "请输入你下个月的计划支出总额： ";
    std::cin >> plan_out_sum;

    std::cout << "请对接下来一个月的各项支出做大概安排： " << std::endl;
    std::string str = "医疗";
    double temp;
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "食品";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "住房";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "交通";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "娱乐";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "投资";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "社交";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    str = "其他";
    std::cout << str << "： ";
    std::cin >> temp;
    plan_out_type.insert(std::make_pair(str, temp));
    std::cout << "您的未来规划创建完毕，我们将在本月内对您的消费进行监督与提醒" << std::endl;
}

Plan::Plan(double plan_out_sum, std::map<std::string, double> plan_out_type) : plan_out_sum(plan_out_sum), plan_out_type(plan_out_type) {}
//专门在和数据库交互的时候调用

double Plan::get_plan_out_sum() {
    return plan_out_sum;
}

std::map<std::string, double> Plan::get_plan_out_type() {
    return plan_out_type;
}

void Plan::plan_print() {
    std::cout << "计划总支出：" << plan_out_sum << "￥" << std::endl;
    std::cout << "计划支出类型：" << std::endl;
    auto it = plan_out_type.begin();
    for (int i = 0; it != plan_out_type.end(); it++) {
        std::cout << std::setw(5) << std::left << it->first << ":  " << std::setw(10) << std::left << std::fixed << std::setprecision(2) << it->second << std::setw(5) << std::left << "￥" << std::endl;
        i++;
        if (i == 4) {
            std::cout << std::endl;
        }
    }
}

void Plan::monitor() {      //每创建一次账目就会触发一次检测，判断当前状态与计划
    auto monitor_it = (Book.end() - 1);
    Date monitor_date = (*monitor_it)->date;    //选取最新的日期对应的月份进行检测
    monitor_date.day_reset(1);
    std::vector<double> type_arr(8, 0);
    std::vector<std::string> name_arr{ "医疗", "食品", "住房", "交通", "娱乐", "投资", "社交", "其他" };
    double out_sum = 0;
    for (auto it = Book.rbegin(); it != Book.rend(); it++) {
        if ((*it)->date == monitor_date && !((*it)->in_or_out)) {
            out_sum += (*it)->transaction_amount;
            if ((*it)->sle_type == "医疗") {
                type_arr[0] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "食品") {
                type_arr[1] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "住房") {
                type_arr[2] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "交通") {
                type_arr[3] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "娱乐") {
                type_arr[4] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "投资") {
                type_arr[5] += (*it)->transaction_amount;
            }
            else if ((*it)->sle_type == "社交") {
                type_arr[6] += (*it)->transaction_amount;
            }
            else {
                type_arr[7] += (*it)->transaction_amount;
            }
            if (it != Book.rend() && (it + 1) != Book.rend() && (*(it + 1))->date != monitor_date) { //避免迭代器越界（啊啊啊！！！迭代器好麻烦啊，早知道不用了）
                break;
            }

        }
    }
    if (out_sum > this->plan_out_sum) {
        fmt::print(fg(fmt::color::red), "计划支出超标，请注意！\n");
        std::cout << "计划支出：" << this->plan_out_sum << "￥" << std::endl;
        std::cout << "实际支出： ";
        fmt::print(fg(fmt::color::red), "{}", out_sum);
        std::cout << "￥" << std::endl;
        std::cout << "超计划支出： ";
        double after = out_sum - this->plan_out_sum;
        fmt::print(fg(fmt::color::red), "{}", after);
        std::cout << "￥" << std::endl;
    }
    else {
        std::cout << "计划支出未超标,可用预算： " << this->plan_out_sum - out_sum << "￥" << std::endl;
    }
    for (int i = 0; i < 8; i++) {
        if (type_arr[i] > plan_out_type[name_arr[i]]) {
            fmt::print(fg(fmt::color::red), "{}支出超标，请注意！\n", name_arr[i]);
            std::cout << "计划支出：" << plan_out_type[name_arr[i]] << "￥" << std::endl;
            std::cout << "实际支出：" << type_arr[i] << "￥" << std::endl;
            std::cout << "超计划支出： " << type_arr[i] - plan_out_type[name_arr[i]] << "￥" << std::endl;
        }
        else {
            std::cout << name_arr[i] << "支出未超标,可用预算： " << plan_out_type[name_arr[i]] - type_arr[i] << "￥" << std::endl;
        }
    }
}
