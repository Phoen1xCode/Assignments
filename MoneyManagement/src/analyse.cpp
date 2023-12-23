#define FMT_HEADER_ONLY 
#include <fmt/core.h>
#include <fmt/color.h>
#include "../include/analyse.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

//这个是需要summary部分的函数传入一个包含各个方面数据的向量，要搭配使用
namespace finance {
    double in_to_out_rate(std::vector<std::vector<double>> all_sum) {    //收支比
        double result = all_sum.at(0).at(0) / all_sum.at(0).at(1);
        return result;
    }

    double storage_rate(std::vector<std::vector<double>> all_sum) {     //储蓄率
        double result1 = all_sum.at(1).at(9) / all_sum.at(0).at(1);
        double result2 = all_sum.at(0).at(2) / all_sum.at(0).at(0);
        double result = result1 > result2 ? result1 : result2;
        return result;
    }

    double ROI(std::vector<std::vector<double>> all_sum) {        //投资回报率
        if (all_sum.at(3).at(0) != 0) {
            return 0;
        }
        else {
            if (all_sum.at(3).at(1) == 0) {
                return 0;
            }
            else {
                return (all_sum.at(3).at(0) / all_sum.at(3).at(1));
            }
        }
    }

    double EG(std::vector<std::vector<double>> all_sum) {
        double eg = 0.0;
        if (all_sum.at(0).at(1) != 0) {
            eg = all_sum.at(1).at(1) / all_sum.at(0).at(1);
        }
        eg = -eg;
        return eg;
    }

    double CSI(std::vector<std::vector<double>> all_sum) {
        double csi = 0.0;
        if (all_sum.at(0).at(1) != 0) {
            csi = (all_sum.at(1).at(0) + all_sum.at(1).at(1) + all_sum.at(1).at(2) + all_sum.at(1).at(3)) / all_sum.at(0).at(1);
        }
        csi = -csi;
        return csi;
    }


    void analyse_daily(std::vector<double> all_sum) {
        fmt::print("您当天共支出：");
        fmt::print(fg(fmt::color::cyan), "{:.f2}\n", all_sum[0]);
        fmt::print("共收入：");
        fmt::print(fg(fmt::color::cyan), "{}\n", all_sum[1]);
        fmt::print("净收支为：");
        fmt::print(fg(fmt::color::cyan), "{}", all_sum[2]);
    }

    void analyse_summary(std::vector<std::vector<double>> all_sum) {
        std::ostringstream summary;

        double inOutRate = in_to_out_rate(all_sum);
        double storRate = storage_rate(all_sum);
        double roi = ROI(all_sum);
        double eg = EG(all_sum);
        double csi = CSI(all_sum);
        double a = all_sum.at(1).at(0), b = all_sum.at(1).at(1), c = all_sum.at(1).at(2), d = all_sum.at(1).at(3), e = all_sum.at(1).at(4),
            f = all_sum.at(1).at(5), g = all_sum.at(1).at(6), h = all_sum.at(1).at(7), i = all_sum.at(1).at(8), j = all_sum.at(1).at(9);
        fmt::print(fg(fmt::color::yellow) | fmt::emphasis::bold, "您的消费结构如下：\n");
        fmt::print("医疗：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", a);             //给出消费结构的基本信息
        fmt::print("食品：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", b);
        fmt::print("住房：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", c);
        fmt::print("交通：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", d);
        fmt::print("娱乐：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", e);
        fmt::print("工资：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", f);
        fmt::print("投资：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", g);
        fmt::print("社交：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}      ", h);
        fmt::print("储蓄：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", i);
        fmt::print("其他：");
        fmt::print(fg(fmt::color::cyan), "{:10.2f}\n", j);

        // 综合收支比和储蓄率分析
        summary << "您的收支比为：" << inOutRate << "，储蓄率为：" << storRate << "。";
        if (inOutRate > 1.2 && storRate >= 0.3) {
            summary << "您的财务状况非常健康，收入远高于支出，且有很好的储蓄习惯。";
        }
        else if (inOutRate > 1 && storRate >= 0.2) {
            summary << "您的财务状况良好，收入高于支出，储蓄习惯合理。";
        }
        else if (inOutRate > 0.8 && storRate >= 0.1) {
            summary << "您的财务状况尚可，但收支平衡和储蓄空间有限，建议注意消费和储蓄。";
        }
        else {
            summary << "您的支出可能超过或接近收入，且储蓄率较低，需要关注收支管理和提高储蓄。";
        }
        summary << std::endl;
        // 投资回报率分析
        if (roi != 0) {
            summary << "投资回报率为：" << roi << "。";
            if (roi > 0.1) {
                summary << "您的投资效果显著，可以考虑继续保持或优化现有策略。";
            }
            else if (roi > 0) {
                summary << "您的投资有一定收益，但效果不是很显著，可能需要调整策略。";
            }
            else {
                summary << "您的投资目前未带来预期收益，建议重新评估和调整投资策略。";
            }

            summary << std::endl;
        }
        else
            summary << "您目前还没有投资习惯" << std::endl;
        // 生活质量和消费习惯分析
        summary << "恩格尔系数为：" << eg << "，消费结构指数为：" << csi << "。";
        if (eg < 0.3 && csi < 0.4) {
            summary << "您的生活质量很高，基本生活消费占比低，拥有较大的自由消费空间。";
        }
        else if (eg < 0.4 && csi < 0.5) {
            summary << "您的生活质量良好，有合理的基本生活消费和自由消费空间。";
        }
        else if (eg < 0.5 && csi < 0.6) {
            summary << "您的生活质量尚可，但基本生活消费占比较高，建议关注优化消费。";
        }
        else {
            summary << "您的基本生活消费占比高，自由消费空间有限，需要关注和调整日常开支。";
        }

        // 打印之前对各个数据的分析
        std::string su = summary.str();
        fmt::print(fg(fmt::color::yellow), "{}\n", su);
        double overall_score = inOutRate + storRate + roi + eg + csi;
        overall_score /= 5; // 取平均值，总体来查看经济状况
        fmt::print(fg(fmt::color::blue) | fmt::emphasis::bold, "综合评估：\n");
        if (overall_score > 0.8) {
            fmt::print(fg(fmt::color::cyan), "财务状况优秀，精明的投资与储蓄策略取得显著成果，请持续保持稳健的财务规划。\n");
        }
        else if (overall_score > 0.5) {
            fmt::print(fg(fmt::color::orange), "财务状况良好，但存在一些改进的空间，建议关注投资战略和生活支出平衡，这将帮助您进一步提高您的财务状况。\n");
        }
        else {
            fmt::print(fg(fmt::color::red), "财务状况较差，请重点关注收支平衡和储蓄，制定合适的消费规划以改善整体经济状况，这也将提高您的生活质量。\n");
        }
    }
}
