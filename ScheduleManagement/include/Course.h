#ifndef COURSE_H
#define COURSE_H

#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include "../lib/json.hpp"

namespace DailylifeAssistant
{
    // ����Course��
    class Course
    {
    private:
        // �����������
        int day;
        std::string weekday;
        int start_time;
        int end_time;
        std::string name;
        std::string building;
        int room;
        std::string sname;
        std::string memory;

        // ���徲̬����
        static int special;
        static int remind;

    public:
        // ���嶯̬���飬�������뼰�޸���Ϣ
        std::vector<Course> course_table;
        std::vector<Course> special_course;
        std::vector<Course> remind_course;

        // ���������������躯��
        void inputRegularCourse();
        void inputCourse(Course& course, std::vector<Course>& courseList);
        void modifyVariousCourse();
        void modifyCourse(std::vector<Course>& courseList);
        void deleteCourse();
        void inputSpecialCourse();
        void remindCourse();
        void arrangeVariousCourse();
        void arrangeCourse(std::vector<Course>& courseList);
        void showCourse();
        void showSpecialCourse();
        void showRegularCourse();
        void showRemindCourse();

        // JSON��д����
        // ��ȡ�γ̱�json�ļ�
        static std::vector<Course> loadCourseTable(const std::string& filename)
        {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }

            nlohmann::json j;
            file >> j;

            std::vector<Course> course_table;
            for (const auto& course_json : j) {
                Course course;
                course.fromJson(course_json);
                course_table.push_back(course);
            }

            return course_table;
        }

        // ����γ̱�json�ļ�
        static void saveCourseTable(const std::string& filename, const std::vector<Course>& course_table)
        {
            nlohmann::json j;
            for (const auto& course : course_table) {
                j.push_back(course.toJson());
            }

            std::ofstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
            file << j.dump(4);
        }

        // ��ȡ����γ�json�ļ�
        static std::vector<Course> loadSpecialCourses(const std::string& filename)
        {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }

            nlohmann::json j;
            file >> j;

            std::vector<Course> special_courses;
            for (const auto& course_json : j) {
                Course course;
                course.fromJson(course_json);
                special_courses.push_back(course);
            }

            return special_courses;
        }

        // ��������γ�json�ļ�
        static void saveSpecialCourses(const std::string& filename, const std::vector<Course>& special_courses)
        {
            nlohmann::json j;
            for (const auto& course : special_courses) {
                nlohmann::json course_json = course.toJson();
                if (course.sname.empty()) {
                    course_json.erase("sname");
                }
                j.push_back(course_json);
            }

            std::ofstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
            file << j.dump(4);
        }

        // ��ȡ���ѿγ�json�ļ�
        static std::vector<Course> loadRemindCourses(const std::string& filename)
        {
            std::ifstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }

            nlohmann::json j;
            file >> j;

            std::vector<Course> remind_courses;
            for (const auto& course_json : j) {
                Course course;
                course.fromJson(course_json);
                remind_courses.push_back(course);
            }

            return remind_courses;
        }

        // �������ѿγ�json�ļ�
        static void saveRemindCourses(const std::string& filename, const std::vector<Course>& remind_courses)
        {
            nlohmann::json j;
            for (const auto& course : remind_courses) {
                nlohmann::json course_json;
                course_json["name"] = course.name;
                if (!course.memory.empty()) {
                    course_json["memory"] = course.memory;
                }
                j.push_back(course_json);
            }

            std::ofstream file(filename);
            if (!file.is_open()) {
                throw std::runtime_error("Failed to open file: " + filename);
            }
            file << j.dump(4);
        }

        // JSON���л�����
        // ��Course�������л�ΪJSON����
        nlohmann::json toJson() const
        {
            nlohmann::json j;
            j["day"] = day;
            j["weekday"] = weekday;
            j["start_time"] = start_time;
            j["end_time"] = end_time;
            j["name"] = name;
            j["building"] = building;
            j["room"] = room;
            if (!sname.empty()) {
                j["sname"] = sname;
            }
            if (!memory.empty()) {
                j["memory"] = memory;
            }
            return j;
        }

        // ��JSON�����з����л���Course����
        void fromJson(const nlohmann::json& j)
        {
            day = j["day"];
            weekday = j["weekday"];
            start_time = j["start_time"];
            end_time = j["end_time"];
            name = j["name"];
            building = j["building"];
            room = j["room"];
            if (j.count("sname") > 0) {
                sname = j["sname"];
            }
            if (j.count("memory") > 0) {
                memory = j["memory"];
            }
        }

    };
}

#endif
