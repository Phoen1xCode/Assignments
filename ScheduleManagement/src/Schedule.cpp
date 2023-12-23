#include "../include/Schedule.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

namespace DailylifeAssistant {







    // 检查日期是否合法
    bool isDateValid(const std::string &date) {
        // 格式检查
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            return false;
        }
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        // 月份日期检查
        if (month < 1 || month > 12) {
            return false;
        }
        if (day < 1 || day > 31) {
            return false;
        }

        // 闰年2月判定
        if (month == 2) {
            if (day > 29) {
                return false;
            }
            if (day == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))) {
                return false;
            }
        }
        // 月份对应天数检查
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }
        return true;
    }

    // 添加事件
    void Schedule::addEvent() {
        std::string content;
        int startHour;
        int startMinute;
        int endHour;
        int endMinute = 59;
        std::string location;
        std::string requirement;
        std::string date;

        std::cout << "请输入日期（格式：YYYY-MM-DD）：";
        while (std::cin >> date) {
            // 检查日期格式是否正确
            if (isDateValid(date)) {
                break;
            }
                // 纠错机制
            else {
                std::cout << "无效选项，请重新输入日期（格式：YYYY-MM-DD）：" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        std::cout << "请输入日程内容：";
        std::cin.ignore();
        std::getline(std::cin, content);

        std::cout << "请输入起始小时（0-23）：";
        while (!(std::cin >> startHour) || startHour < 0 || startHour > 23) {
            std::cout << "无效选项，请重新输入起始小时（0-23）：" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "请输入起始分钟（0-59）：";
        while (!(std::cin >> startMinute) || startMinute < 0 || startMinute > 59) {
            std::cout << "无效选项，请重新输入起始分钟（0-59）：" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "请输入结束小时（0-23）：";
        while (!(std::cin >> endHour) || endHour < 0 || endHour > 23 ||
               !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) {
            std::cout << "无效选项，请重新输入结束小时（0-23）：" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "请输入结束分钟（0-59）：";
        while (!(std::cin >> endMinute) || endMinute < 0 || endMinute > 59 ||
               !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) {
            std::cout << "无效选项，请重新输入结束分钟（0-59）：" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "请输入地点：";
        std::cin.ignore();
        std::getline(std::cin, location);

        std::cout << "请输入要求：";
        std::getline(std::cin, requirement);

        events.push_back(Event(content, startHour, startMinute, endHour, endMinute, location, requirement, date));
        std::cout << "日程添加成功！" << std::endl;
    }

    // 按照结束时间进行排序
    void Schedule::sortByEndTime() {
        std::sort(events.begin(), events.end(), [](const Event &event1, const Event &event2) {
            // 先进行日期的比较
            if (event1.date != event2.date) {
                return event1.date < event2.date;
            }
                // 日期相同先比小时
            else if (event1.endHour != event2.endHour) {
                return event1.endHour < event2.endHour;
            }
                // 日期，小时均相同比较分钟
            else {
                return event1.endMinute < event2.endMinute;
            }
        });
    }

    // 标记完成
    void Schedule::markEventAsDone() {
        std::string content;
        std::cout << "请输入要标记为已完成的日程名字：";
        std::cin >> content;
        bool found = false;

        // 通过内容进行检索
        for (auto &event: events) {
            if (event.content == content) {
                found = true;
                event.completed = true;
                std::cout << "已标记内容为 " << content << " 的日程为已完成！" << std::endl;
                break;
            }
        }

        // 未找到日程反馈
        if (!found) {
            std::cout << "没有找到内容为 " << content << " 的日程！" << std::endl;
        }
    }

    // 展示日程表
    void Schedule::showEvents() {
        // 先调用函数进行排序
        sortByEndTime();
        std::cout << "日程表：" << std::endl;

        // 已完成标记
        for (const auto &event: events) {
            std::cout << (event.completed ? "[已完成] " : "") << event << std::endl;
        }
    }

    // 搜索日程
    void Schedule::searchEventByContent() {
        std::string content;
        std::cout << "请输入要搜索的日程内容：";
        std::cin >> content;
        bool found = false;

        // 通过内容进行检索
        for (auto &event: events) {
            if (event.content == content) {
                found = true;
                std::cout << event << std::endl;
            }
        }

        // 未找到时反馈
        if (!found) {
            std::cout << "没有找到内容为 " << content << " 的日程！" << std::endl;
        }
    }

    // 删除日程
    void Schedule::deleteEvent() {
        std::string content;
        std::cout << "请输入要删除的日程内容：";
        std::cin >> content;
        bool found = false;

        // 通过内容进行检索
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->content == content) {
                found = true;
                events.erase(it);
                std::cout << "已删除内容为 " << content << " 的日程！" << std::endl;
                break;
            }
        }

        // 未找到时反馈
        if (!found) {
            std::cout << "没有找到内容为 " << content << " 的日程！" << std::endl;
        }
    }

    void to_json(nlohmann::json& j, const Event& e) {
        j = nlohmann::json{
                {"content", e.content},
                {"startHour", e.startHour},
                {"startMinute", e.startMinute},
                {"endHour", e.endHour},
                {"endMinute", e.endMinute},
                {"location", e.location},
                {"requirement", e.requirement},
                {"completed", e.completed},
                {"date", e.date}
        };
    }

    void from_json(const nlohmann::json& j, Event& e) {
        j.at("content").get_to(e.content);
        j.at("startHour").get_to(e.startHour);
        j.at("startMinute").get_to(e.startMinute);
        j.at("endHour").get_to(e.endHour);
        j.at("endMinute").get_to(e.endMinute);
        j.at("location").get_to(e.location);
        j.at("requirement").get_to(e.requirement);
        j.at("completed").get_to(e.completed);
        j.at("date").get_to(e.date);
    }

    void Schedule::saveEventsToJson(const std::string &filename) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file for writing: " + filename);
        }

        nlohmann::json json_data = events; // This will use the to_json function
        file << json_data.dump(4); // Pretty print with 4 spaces indent
        file.close();
    }

//    void Schedule::loadEventsFromJson(const std::string &filename) {
//        std::ifstream file(filename);
//        if (!file.is_open()) {
//            throw std::runtime_error("Unable to open file for reading: " + filename);
//        }
//
//        nlohmann::json json_data;
//        file >> json_data;
//        file.close();
//
//        events = json_data.get<std::vector<Event>>(); // This will use the from_json function
//    }
}
