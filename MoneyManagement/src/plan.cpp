#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/color.h>
#include "../include/plan.h"
#include <map>
#include <string>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <vector>
#include <iterator>

namespace finance {

    std::vector<Plan> plan_collection = {};

    void create_plan() {
        Plan plan;
        plan_collection.push_back(plan);
    }

    Plan::Plan() {
        fmt::print("请输入你下个月的计划支出总额： ");
        std::cin >> plan_out_sum;

        fmt::print("请对接下来一个月的各项支出做大概安排： \n");
        std::string str = "医疗";
        double temp;
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "食品";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "住房";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "交通";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "娱乐";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "投资";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "社交";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        str = "其他";
        fmt::print("{}： ", str);
        std::cin >> temp;
        plan_out_type.insert(std::make_pair(str, temp));
        fmt::print("您的未来规划创建完毕，我们将在本月内对您的消费进行监督与提醒\n");
    }

    Plan::Plan(double plan_out_sum, std::map<std::string, double> plan_out_type) : plan_out_sum(plan_out_sum), plan_out_type(plan_out_type) {}

    double Plan::get_plan_out_sum() {
        return plan_out_sum;
    }

    std::map<std::string, double> Plan::get_plan_out_type() {
        return plan_out_type;
    }

    void Plan::plan_print() {
        fmt::print("计划总支出：{}￥\n", plan_out_sum);
        fmt::print("计划支出类型：\n");
        auto it = plan_out_type.begin();
        for (int i = 0; it != plan_out_type.end(); it++) {
            fmt::print("{:<5}:  {:<10.2f}￥", it->first, it->second);
            i++;
            if (i == 4) {
                fmt::print("\n");
            }
        }
    }

    void Plan::monitor() {
        auto monitor_it = (Book.end() - 1);
        Date monitor_date = (*monitor_it)->date;
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
                if (it != Book.rend() && (it + 1) != Book.rend() && (*(it + 1))->date != monitor_date) {
                    break;
                }
            }
        }
        if (out_sum > this->plan_out_sum) {
            fmt::print(fg(fmt::color::red), "计划支出超标，请注意！\n");
            fmt::print("计划支出：{}￥\n", this->plan_out_sum);
            fmt::print("实际支出： ");
            fmt::print(fg(fmt::color::red), "{}", out_sum);
            fmt::print("￥\n");
            fmt::print("超计划支出： ");
            double after = out_sum - this->plan_out_sum;
            fmt::print(fg(fmt::color::red), "{}", after);
            fmt::print("￥\n");
        }
        else {
            fmt::print("计划支出未超标,可用预算： {}￥\n", this->plan_out_sum - out_sum);
        }
        for (int i = 0; i < 8; i++) {
            if (type_arr[i] > plan_out_type[name_arr[i]]) {
                fmt::print(fg(fmt::color::red), "{}支出超标，请注意！\n", name_arr[i]);
                fmt::print("计划支出：{}￥\n", plan_out_type[name_arr[i]]);
                fmt::print("实际支出：{}￥\n", type_arr[i]);
                fmt::print("超计划支出： {}￥\n", type_arr[i] - plan_out_type[name_arr[i]]);
            }
            else {
                fmt::print("{}支出未超标,可用预算： {}￥\n", name_arr[i], plan_out_type[name_arr[i]] - type_arr[i]);
            }
        }
    }
}
