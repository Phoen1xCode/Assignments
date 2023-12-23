#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <fstream>
#include <iomanip>
#include "../lib/json.hpp"

namespace DailylifeAssistant {
    class Event {
    public:
        std::string content;
        int startHour;
        int startMinute;
        int endHour;
        int endMinute;
        std::string location;
        std::string requirement;
        bool completed;
        std::string date;

        Event(std::string content, int startHour, int startMinute, int endHour, int endMinute,
              std::string location, std::string requirement, std::string date)
                : content(std::move(content)), startHour(startHour), startMinute(startMinute), endHour(endHour),
                  endMinute(endMinute), location(std::move(location)), requirement(std::move(requirement)), completed(false), date(std::move(date)) {}

        void markAsCompleted() {
            completed = true;
        }

        bool isCompleted() const {
            return completed;
        }

        friend std::ostream &operator<<(std::ostream &os, const Event &event) {
            os << "���ڣ�" << event.date << std::endl;
            os << "���ݣ�" << event.content << std::endl;
            os << "��ʼʱ�䣺" << event.startHour << ":" << event.startMinute << std::endl;
            os << "����ʱ�䣺" << event.endHour << ":" << event.endMinute << std::endl;
            os << "�ص㣺" << event.location << std::endl;
            os << "Ҫ��" << event.requirement << std::endl;
            os << "״̬��" << (event.completed ? "�����" : "δ���") << std::endl;
            return os;
        }
    };

    class Schedule {

    public:
        void addEvent();
        void sortByEndTime();
        void markEventAsDone();
        void showEvents();
        void searchEventByContent();
        void deleteEvent();

        void saveEventsToJson(const std::string &filename);
        void loadEventsFromJson(const std::string &filename);

    private:
        std::vector<Event> events;

        bool isStartTimeBeforeEndTime(int startHour, int startMinute, int endHour, int endMinute) {
            if (startHour < endHour) {
                return true;
            } else if (startHour == endHour && startMinute < endMinute) {
                return true;
            }
            return false;
        }

    };

    void to_json(nlohmann::json& j, const Event& e);
    void from_json(const nlohmann::json& j, Event& e);

}

#endif