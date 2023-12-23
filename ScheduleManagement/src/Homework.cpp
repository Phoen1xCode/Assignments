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


    // �� Homework �������л�Ϊ JSON
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

// �� JSON �����л�Ϊ Homework ����
    void from_json(const json& j, Homework& hw) {
        // ʹ�� value �����ṩĬ��ֵ���Է� JSON ��ȱ��ĳЩ��
        hw = Homework(
                j.at("name").get<std::string>(),
                j.at("subject").get<std::string>(),
                j.at("content").get<std::string>(),
                j.at("type").get<std::string>(),
                j.at("ddl").get<std::string>(),
                j.value("completed", false), // ʹ�� value �����ṩĬ��ֵ false
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
        // ������ҵ��Ϣ
        std::string name, subject, content, type, ddl;
        std::cout << "�������Ŀ��";
        std::cin >> subject;
        std::cout << "��������ҵ���ݣ�";
        std::cin >> content;
        std::cout << "��ѡ��ʽ��1.������ҵ/2.չʾ��ҵ����";
        int hchoice;
        std::cin >> hchoice;

        // ��ҵ����ѡ��
        while (true) {
            if (hchoice == 1) {
                type = "������ҵ";
                break;
            } else if (hchoice == 2) {
                type = "չʾ��ҵ";
                break;
            }
                // �������
            else {
                std::cout << "��Ч��ѡ�����������룡" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin >> hchoice;
            }
        }

        bool hvalidDate = false;
        while (!hvalidDate) {
            std::cout << "�������ֹ���ڣ�YYYY-MM-DD����";
            std::cin >> ddl;

            // ���ú��������ж�
            hvalidDate = validateDate(ddl);
            // �ж����ڸ�ʽ�Ƿ���ȷ�Һ���
            if (!hvalidDate) {
                std::cout << "���ڸ�ʽ����ȷ�����ڲ��������������롣" << std::endl;
            }
        }

        // ���������ݺ����������ҵ
        Homework assignment(name, subject, content, type, ddl, false, false, false);
        homework.push_back(assignment);
        std::cout << "��ҵ����ӡ�" << std::endl;
    }

    // ���������ȷ������
    bool HomeworkManager::validateDate(const std::string &date) {
        // ��֤���ڸ�ʽ
        std::stringstream ss(date);
        int year, month, day;
        char delimiter;
        ss >> year >> delimiter >> month >> delimiter >> day;

        // ��֤��ʽ��ȷ
        if (ss.fail() || delimiter != '-' || ss.peek() != EOF) {
            return false;
        }

        // ��֤���ں�����
        if (month < 1 || month > 12 || day < 1 || day > 31) {
            return false;
        }

        // ����·ݶ�Ӧ�������Ƿ���ȷ
        int daysInMonth;
        if (month == 2) {
            // ������жϣ��ܱ�4���������ܱ�100�����������ܱ�400����
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

        // ������ں�����true
        return true;
    }

    // ��ʾ��ҵ�б�
    void HomeworkManager::displayAssignmentList() {
        sortAssignmentsByDdl();
        std::cout << "��ֹ����  - ��Ŀ    - ��ҵ" << std::endl;
        for (const auto &assignment: homework) {
            std::cout << assignment.getDDL() << " - " << assignment.getSubject() << " - " << assignment.getContent()
                      << std::endl;
        }
    }

    // �����ҵ���
    void HomeworkManager::markAssignmentCompleted() {
        // ����������ʾ
        std::string name;
        std::cout << "������Ҫ�����ɵ���ҵ���ƣ�";
        std::cin.ignore();
        std::getline(std::cin, name);

        bool found = false;
        // ������ҵ��
        for (int i = 0; i < homework.size(); i++) {
            // ������Ӧ����ҵ
            if (homework[i].getName() == name) {
                found = true;
                // չʾ����ҵ�ı��
                if (homework[i].getType() == "չʾ��ҵ") {
                    // ѡ��������ʾ
                    std::cout << "��ѡ��Ҫ��ǵ�����׼����ɻ�����̨׼����ɣ�" << std::endl;
                    std::cout << "1. ����׼�����" << std::endl;
                    std::cout << "2. ��̨׼�����" << std::endl;

                    // ʵ�ֶ�Ӧѡ��
                    int choice;
                    std::cin >> choice;

                    // ѡ��������
                    switch (choice) {
                        case 1:
                            homework[i].markContentPrepared();
                            std::cout << "չʾ����׼����ɡ�" << std::endl;
                            break;
                        case 2:
                            homework[i].markPresentationPrepared();
                            std::cout << "չʾ��̨׼����ɡ�" << std::endl;
                            break;
                        default:
                            std::cout << "��Ч��ѡ��" << std::endl;
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                    // ��������ҵ�ı��
                else {
                    homework[i].markCompleted();
                    std::cout << "��ҵ����ɡ�" << std::endl;
                    homework.erase(homework.begin() + i);
                }
                break;
            }
        }

        // δ���ҵ���Ӧ����ҵ����
        if (!found) {
            std::cout << "δ�ҵ�����Ϊ " << name << " ����ҵ��" << std::endl;
        }
    }

    // ɾ����ҵ
    void HomeworkManager::deleteAssignment() {
        // ����������ʾ
        std::string name;
        std::cout << "������Ҫɾ������ҵ���ƣ�";
        std::cin.ignore();
        std::getline(std::cin, name);

        bool found = false;
        for (int i = 0; i < homework.size(); i++) {
            // ������Ӧ��ҵ
            if (homework[i].getName() == name) {
                found = true;
                homework.erase(homework.begin() + i);
                std::cout << "��ҵ��ɾ����" << std::endl;
                break;
            }
        }

        // δ�ҵ���Ӧ��ҵ����
        if (!found) {
            std::cout << "δ�ҵ�����Ϊ " << name << " ����ҵ��" << std::endl;
        }
    }

    void HomeworkManager::saveAssignmentsToJson(const std::string &filename) {
        json j;
        for (const auto& hw : homework) {
            j.push_back(hw);
        }
        std::ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // ���� JSON ���ݵ��ļ�������Ϊ 4 ���ո�
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