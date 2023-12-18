#pragma once
#include<vector>

class Ledger;
class Account;
//收支的汇总模块
std::vector<double> sum_io_daily();    //按日汇总收支（不支持生成其他类型的报表,因为没有太大意义）

std::vector<std::vector<double>> sum_all_monthly();    //按月汇总收支

std::vector<std::vector<double>> sum_all_yearly();    //按年汇总收支