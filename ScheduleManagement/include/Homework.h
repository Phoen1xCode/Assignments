#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <limits>
#include <iomanip>
#include "../lib/json.hpp"
#include <fstream>

using json = nlohmann::json;
namespace DailylifeAssistant {
    // Homework Class
    class Homework {
    public:
        // 构造函数
        Homework(std::string name, std::string subject, std::string content,
                 std::string type, std::string ddl,
                 bool completed, bool contentPrepared, bool presentationPrepared);
        //
        Homework(const Homework& other);
        // 获取作业名称
        std::string getName() const;

        // 获取科目信息
        std::string getSubject() const;

        // 获取内容信息
        std::string getContent() const;

        // 获取作业类型
        std::string getType() const;

        // 获取作业ddl
        std::string getDDL() const;


        // 标记作业完成
        void markCompleted();

        // 标记内容准备完成
        void markContentPrepared();

        // 标记展示上台准备完成
        void markPresentationPrepared();

        bool completed; // 是否完成
        bool contentPrepared; // 内容准备完成标志
        bool presentationPrepared; // 展示上台准备完成标志

        friend void to_json(json& j, const Homework& hw);
        friend void from_json(const json& j, Homework& hw);

    private:
        std::string name; // 作业名称
        std::string subject; // 科目
        std::string content; // 作业内容
        std::string type; // 作业类型
        std::string ddl; // 截止日期

    };


    // 各个功能函数
    class HomeworkManager {
    public:
        void addAssignment();
        bool validateDate(const std::string &date);
        void displayAssignmentList();
        void markAssignmentCompleted();
        void deleteAssignment();



        void saveAssignmentsToJson(const std::string& filename);
        void loadAssignmentsFromJson(const std::string& filename);

    private:
        static bool compareAssignmentsByDdl(const Homework &a1, const Homework &a2);
        static std::tm parseDdlString(const std::string &ddlString);
        void sortAssignmentsByDdl();
        std::vector<Homework> homework;
    };
    void to_json(json& j, const Homework& hw);
    void from_json(const json& j, Homework& hw);
}

#endif