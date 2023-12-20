#pragma once
#include"summary.h"
#include"ledger.h"
#include"type.h"
#include"date.h"
//基本的衡量系数
//收支比，看有没有透支消费
double in_to_out_rate(std::vector<std::vector<double>> all_sum);
//储蓄率，看应对风险的能力
double storage_rate(std::vector<std::vector<double>> all_sum);

//return on investment，投资回报率
double ROI(std::vector<std::vector<double>> all_sum);

//生活质量的衡量系数
//恩格尔系数
double EG(std::vector<std::vector<double>> all_sum);
//消费结构指数    必要开支占总支出的比例
double CSI(std::vector<std::vector<double>> all_sum);

void analyse_daily(std::vector<double> all_sum);
void analyse_summary(std::vector<std::vector<double>> all_sum);
