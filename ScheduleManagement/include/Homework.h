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
        // ���캯��
        Homework(std::string name, std::string subject, std::string content,
                 std::string type, std::string ddl,
                 bool completed, bool contentPrepared, bool presentationPrepared);
        //
        Homework(const Homework& other);
        // ��ȡ��ҵ����
        std::string getName() const;

        // ��ȡ��Ŀ��Ϣ
        std::string getSubject() const;

        // ��ȡ������Ϣ
        std::string getContent() const;

        // ��ȡ��ҵ����
        std::string getType() const;

        // ��ȡ��ҵddl
        std::string getDDL() const;


        // �����ҵ���
        void markCompleted();

        // �������׼�����
        void markContentPrepared();

        // ���չʾ��̨׼�����
        void markPresentationPrepared();

        bool completed; // �Ƿ����
        bool contentPrepared; // ����׼����ɱ�־
        bool presentationPrepared; // չʾ��̨׼����ɱ�־

        friend void to_json(json& j, const Homework& hw);
        friend void from_json(const json& j, Homework& hw);

    private:
        std::string name; // ��ҵ����
        std::string subject; // ��Ŀ
        std::string content; // ��ҵ����
        std::string type; // ��ҵ����
        std::string ddl; // ��ֹ����

    };


    // �������ܺ���
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