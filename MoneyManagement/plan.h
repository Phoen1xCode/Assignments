#pragma once
#include"summary.h"
#include"ledger.h"
#include<map>
#include<string>
#include"date.h"
#include"data_in_out.h"
//注意：对应的ledger全部in_or_out全为0才行

class Plan {
private:
    double plan_out_sum;
    std::map<std::string, double> plan_out_type;
public:
    friend void plan_storage(MYSQL* conn);
    Plan();
    Plan(double plan_out_sum, std::map<std::string, double> plan_out_type);
    double get_plan_out_sum();                            //两个接口
    std::map<std::string, double> get_plan_out_type();
    void plan_print();
    void monitor();       //计划的监管系统
};

extern std::vector<Plan> plan_collection;  //由于plan针对的是当前的月份，因此只要对容器最后面的plan进行提取就行了
void create_plan();
