#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <limits>
#include "../include/Homework.h"
#include "../lib/json.hpp"
using json = nlohmann::json;
namespace DailylifeAssistant {
    Homework::Homework(std::string name, std::string subject, std::string content,
                       std::string type, std::string ddl,
                       bool completed, bool contentPrepared, bool presentationPrepared)
            : name(std::move(name)), subject(std::move(subject)), content(std::move(content)), type(std::move(type)), ddl(std::move(ddl)),
              completed(false), contentPrepared(false), presentationPrepared(false) {}

    Homework::Homework(const Homework& other)
            : name(other.name), subject(other.subject), content(other.content),
              type(other.type), ddl(other.ddl), completed(other.completed),
              contentPrepared(other.contentPrepared), presentationPrepared(other.presentationPrepared) {}

    std::string Homework::getName() const {
        return name;
    }

    std::string Homework::getSubject() const {
        return subject;
    }

    std::string Homework::getContent() const {
        return content;
    }

    std::string Homework::getType() const {
        return type;
    }

    std::string Homework::getDDL() const {
        return ddl;
    }



    void Homework::markCompleted() {
        completed = true;
    }

    void Homework::markContentPrepared() {
        contentPrepared = true;
    }

    void Homework::markPresentationPrepared() {
        presentationPrepared = true;
    }


    // 将 Homework 对象序列化为 JSON
    void to_json(json& j, const Homework& hw) {
        j = json{{"name", hw.getName()},
                 {"subject", hw.getSubject()},
                 {"content", hw.getContent()},
                 {"type", hw.getType()},
                 {"ddl", hw.getDDL()},
                 {"completed", hw.completed},
                 {"contentPrepared", hw.contentPrepared},
                 {"presentationPrepared", hw.presentationPrepared}};
    }

// 从 JSON 反序列化为 Homework 对象
    void from_json(const json& j, Homework& hw) {
        // 使用 value 方法提供默认值，以防 JSON 中缺少某些键
        hw = Homework(
                j.at("name").get<std::string>(),
                j.at("subject").get<std::string>(),
                j.at("content").get<std::string>(),
                j.at("type").get<std::string>(),
                j.at("ddl").get<std::string>(),
                j.value("completed", false), // 使用 value 方法提供默认值 false
                j.value("contentPrepared", false),
                j.value("presentationPrepared", false)
        );
    }



    bool HomeworkManager::compareAssignmentsByDdl(const Homework &a1, const Homework &a2) {
        std::tm tm1 = parseDdlString(a1.getDDL());
        std::tm tm2 = parseDdlString(a2.getDDL());
        return std::mktime(&tm1) < std::mktime(&tm2);
    }

    std::tm HomeworkManager::parseDdlString(const std::string &ddlString) {
        std::tm tm = {};
        std::istringstream ss(ddlString);
        ss >> std::get_time(&tm, "%Y-%m-%d");

        // Check if the parsing was successful
        if (ss.fail()) {
            throw std::runtime_error("Failed to parse date string: " + ddlString);
        }

        return tm;
    }

    void HomeworkManager::sortAssignmentsByDdl() {
        std::sort(homework.begin(), homework.end(), compareAssignmentsByDdl);
    }

    void HomeworkManager::addAssignment() {
        // 输入作业信息
        std::string name, subject, content, type, ddl;
        std::cout << "请输入科目：";
        std::cin >> subject;
        std::cout << "请输入作业内容：";
        std::cin >> content;
        std::cout << "请选择方式（1.常规作业/2.展示作业）：";
        int hchoice;
        std::cin >> hchoice;

        // 作业类型选择
        while (true) {
            if (hchoice == 1) {
                type = "常规作业";
                break;
            } else if (hchoice == 2) {
                type = "展示作业";
                break;
            }
                // 纠错机制
            else {
                std::cout << "无效的选择，请重新输入！" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> hchoice;
            }
        }

        bool hvalidDate = false;
        while (!hvalidDate) {
            std::cout << "请输入截止日期（YYYY-MM-DD）：";
            std::cin >> ddl;

            // 调用函数进行判断
            hvalidDate = validateDate(ddl);
            // 判断日期格式是否正确且合理
            if (!hvalidDate) {
                std::cout << "日期格式不正确或日期不合理，请重新输入。" << std::endl;
            }
        }

        // 若各项内容合理，则添加作业
        Homework assignment(name, subject, content, type, ddl, false, false, false);
        homework.push_back(assignment);
        std::cout << "作业已添加。" << std::endl;
    }

    // 检测日期正确合理性
    bool HomeworkManager::validateDate(const std::string &date) {
        // 验证日期格式
        std::stringstream ss(date);
        int year, month, day;
        char delimiter;
        ss >> year >> delimiter >> month >> delimiter >> day;

        // 验证格式正确
        if (ss.fail() || delimiter != '-' || ss.peek() != EOF) {
            return false;
        }

        // 验证日期合理性
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            return false;
        }

        // 检查月份对应的天数是否正确
        int daysInMonth;
        if (month == 2) {
            // 闰年的判断：能被4整除但不能被100整除，或者能被400整除
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            daysInMonth = isLeapYear ? 29 : 28;
        } else if (month == 4 || month == 6 || month == 9 || month == 11) {
            daysInMonth = 30;
        } else {
            daysInMonth = 31;
        }

        if (day > daysInMonth) {
            return false;
        }

        // 如果日期合理返回true
        return true;
    }

    // 显示作业列表
    void HomeworkManager::displayAssignmentList() {
        sortAssignmentsByDdl();
        std::cout << "截止日期  - 科目    - 作业" << std::endl;
        for (const auto &assignment: homework) {
            std::cout << assignment.getDDL() << " - " << assignment.getSubject() << " - " << assignment.getContent()
                      << std::endl;
        }
    }

    // 标记作业完成
    void HomeworkManager::markAssignmentCompleted() {
        // 输入内容提示
        std::string name;
        std::cout << "请输入要标记完成的作业名称：";
        std::cin.ignore();
        std::getline(std::cin, name);

        bool found = false;
        // 遍历作业本
        for (int i = 0; i < homework.size(); i++) {
            // 检索对应的作业
            if (homework[i].getName() == name) {
                found = true;
                // 展示类作业的标记
                if (homework[i].getType() == "展示作业") {
                    // 选择各项功能提示
                    std::cout << "请选择要标记的内容准备完成还是上台准备完成：" << std::endl;
                    std::cout << "1. 内容准备完成" << std::endl;
                    std::cout << "2. 上台准备完成" << std::endl;

                    // 实现对应选择
                    int choice;
                    std::cin >> choice;

                    // 选择标记内容
                    switch (choice) {
                        case 1:
                            homework[i].markContentPrepared();
                            std::cout << "展示内容准备完成。" << std::endl;
                            break;
                        case 2:
                            homework[i].markPresentationPrepared();
                            std::cout << "展示上台准备完成。" << std::endl;
                            break;
                        default:
                            std::cout << "无效的选择。" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                    // 常规类作业的标记
                else {
                    homework[i].markCompleted();
                    std::cout << "作业已完成。" << std::endl;
                    homework.erase(homework.begin() + i);
                }
                break;
            }
        }

        // 未查找到对应的作业反馈
        if (!found) {
            std::cout << "未找到名称为 " << name << " 的作业。" << std::endl;
        }
    }

    // 删除作业
    void HomeworkManager::deleteAssignment() {
        // 输入内容提示
        std::string name;
        std::cout << "请输入要删除的作业名称：";
        std::cin.ignore();
        std::getline(std::cin, name);

        bool found = false;
        for (int i = 0; i < homework.size(); i++) {
            // 检索对应作业
            if (homework[i].getName() == name) {
                found = true;
                homework.erase(homework.begin() + i);
                std::cout << "作业已删除。" << std::endl;
                break;
            }
        }

        // 未找到对应作业反馈
        if (!found) {
            std::cout << "未找到名称为 " << name << " 的作业。" << std::endl;
        }
    }

    void HomeworkManager::saveAssignmentsToJson(const std::string &filename) {
        json j;
        for (const auto& hw : homework) {
            j.push_back(hw);
        }
        std::ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // 保存 JSON 数据到文件，缩进为 4 个空格
            file.close();
        } else {
            throw std::runtime_error("Unable to open file for writing: " + filename);
        }

    }

//    void HomeworkManager::loadAssignmentsFromJson(const std::string &filename) {
//        std::ifstream file(filename);
//        if (file.is_open()) {
//            json j;
//            file >> j; // Load the JSON array from the file
//            homework.clear(); // Clear existing homework assignments
//            for (const auto& item : j) {
//                homework.push_back(item.get<Homework>()); // Deserialize each JSON object into a Homework object
//            }
//            file.close();
//        } else {
//            throw std::runtime_error("Unable to open file for reading: " + filename);
//        }
//    }


}