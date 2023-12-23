#include "../include/Schedule.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

namespace DailylifeAssistant {







    // ��������Ƿ�Ϸ�
    bool isDateValid(const std::string &date) {
        // ��ʽ���
        if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
            return false;
        }
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
        int day = std::stoi(date.substr(8, 2));

        // �·����ڼ��
        if (month < 1 || month > 12) {
            return false;
        }
        if (day < 1 || day > 31) {
            return false;
        }

        // ����2���ж�
        if (month == 2) {
            if (day > 29) {
                return false;
            }
            if (day == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))) {
                return false;
            }
        }
        // �·ݶ�Ӧ�������
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
            return false;
        }
        return true;
    }

    // ����¼�
    void Schedule::addEvent() {
        std::string content;
        int startHour;
        int startMinute;
        int endHour;
        int endMinute = 59;
        std::string location;
        std::string requirement;
        std::string date;

        std::cout << "���������ڣ���ʽ��YYYY-MM-DD����";
        while (std::cin >> date) {
            // ������ڸ�ʽ�Ƿ���ȷ
            if (isDateValid(date)) {
                break;
            }
                // �������
            else {
                std::cout << "��Чѡ��������������ڣ���ʽ��YYYY-MM-DD����" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        std::cout << "�������ճ����ݣ�";
        std::cin.ignore();
        std::getline(std::cin, content);

        std::cout << "��������ʼСʱ��0-23����";
        while (!(std::cin >> startHour) || startHour < 0 || startHour > 23) {
            std::cout << "��Чѡ�������������ʼСʱ��0-23����" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "��������ʼ���ӣ�0-59����";
        while (!(std::cin >> startMinute) || startMinute < 0 || startMinute > 59) {
            std::cout << "��Чѡ�������������ʼ���ӣ�0-59����" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "���������Сʱ��0-23����";
        while (!(std::cin >> endHour) || endHour < 0 || endHour > 23 ||
               !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) {
            std::cout << "��Чѡ��������������Сʱ��0-23����" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "������������ӣ�0-59����";
        while (!(std::cin >> endMinute) || endMinute < 0 || endMinute > 59 ||
               !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) {
            std::cout << "��Чѡ�����������������ӣ�0-59����" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "������ص㣺";
        std::cin.ignore();
        std::getline(std::cin, location);

        std::cout << "������Ҫ��";
        std::getline(std::cin, requirement);

        events.push_back(Event(content, startHour, startMinute, endHour, endMinute, location, requirement, date));
        std::cout << "�ճ���ӳɹ���" << std::endl;
    }

    // ���ս���ʱ���������
    void Schedule::sortByEndTime() {
        std::sort(events.begin(), events.end(), [](const Event &event1, const Event &event2) {
            // �Ƚ������ڵıȽ�
            if (event1.date != event2.date) {
                return event1.date < event2.date;
            }
                // ������ͬ�ȱ�Сʱ
            else if (event1.endHour != event2.endHour) {
                return event1.endHour < event2.endHour;
            }
                // ���ڣ�Сʱ����ͬ�ȽϷ���
            else {
                return event1.endMinute < event2.endMinute;
            }
        });
    }

    // ������
    void Schedule::markEventAsDone() {
        std::string content;
        std::cout << "������Ҫ���Ϊ����ɵ��ճ����֣�";
        std::cin >> content;
        bool found = false;

        // ͨ�����ݽ��м���
        for (auto &event: events) {
            if (event.content == content) {
                found = true;
                event.completed = true;
                std::cout << "�ѱ������Ϊ " << content << " ���ճ�Ϊ����ɣ�" << std::endl;
                break;
            }
        }

        // δ�ҵ��ճ̷���
        if (!found) {
            std::cout << "û���ҵ�����Ϊ " << content << " ���ճ̣�" << std::endl;
        }
    }

    // չʾ�ճ̱�
    void Schedule::showEvents() {
        // �ȵ��ú�����������
        sortByEndTime();
        std::cout << "�ճ̱�" << std::endl;

        // ����ɱ��
        for (const auto &event: events) {
            std::cout << (event.completed ? "[�����] " : "") << event << std::endl;
        }
    }

    // �����ճ�
    void Schedule::searchEventByContent() {
        std::string content;
        std::cout << "������Ҫ�������ճ����ݣ�";
        std::cin >> content;
        bool found = false;

        // ͨ�����ݽ��м���
        for (auto &event: events) {
            if (event.content == content) {
                found = true;
                std::cout << event << std::endl;
            }
        }

        // δ�ҵ�ʱ����
        if (!found) {
            std::cout << "û���ҵ�����Ϊ " << content << " ���ճ̣�" << std::endl;
        }
    }

    // ɾ���ճ�
    void Schedule::deleteEvent() {
        std::string content;
        std::cout << "������Ҫɾ�����ճ����ݣ�";
        std::cin >> content;
        bool found = false;

        // ͨ�����ݽ��м���
        for (auto it = events.begin(); it != events.end(); ++it) {
            if (it->content == content) {
                found = true;
                events.erase(it);
                std::cout << "��ɾ������Ϊ " << content << " ���ճ̣�" << std::endl;
                break;
            }
        }

        // δ�ҵ�ʱ����
        if (!found) {
            std::cout << "û���ҵ�����Ϊ " << content << " ���ճ̣�" << std::endl;
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
