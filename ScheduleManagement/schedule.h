#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// 变量管理
class Event
{
public:
    string content;
    int startHour;
    int startMinute;
    int endHour;
    int endMinute;
    string location;
    string requirement;
    bool completed;
    string date;

public:
    // 构造函数
    Event(const string& content, int startHour, int startMinute, int endHour, int endMinute, const string& location, const string& requirement, const string& date)
        : content(content), startHour(startHour), startMinute(startMinute), endHour(endHour), endMinute(endMinute), location(location), requirement(requirement), completed(false), date(date) {}

    // 将事件标记为已完成
    void markAsCompleted()
    {
        completed = true;
    }

    // 检查事件是否已完成
    bool isCompleted() const
    {
        return completed;
    }

    // 友元函数，用于将事件信息输出到流中
    friend ostream& operator<<(ostream& os, const Event& event)
    {
        os << "日期：" << event.date << endl;                                          // 输出日期
        os << "内容：" << event.content << endl;                                      // 输出日程内容
        os << "起始时间：" << event.startHour << ":" << event.startMinute << endl;     // 输出起始时间
        os << "结束时间：" << event.endHour << ":" << event.endMinute << endl;         // 输出结束时间
        os << "地点：" << event.location << endl;                                     // 输出地点
        os << "要求：" << event.requirement << endl;                                  // 输出要求
        os << "状态：" << (event.completed ? "已完成" : "未完成") << endl;            // 输出状态
        return os;
    }
};

// 各个功能管理
class Schedule
{
private:
    vector<Event> events;
    // 辅助函数：判断起始时间是否在结束时间之前
    bool isStartTimeBeforeEndTime(int startHour, int startMinute, int endHour, int endMinute) const
    {
        // 先比较小时
        if (startHour < endHour)
        {
            return true;
        }
        // 小时相同时比较分钟
        else if (startHour == endHour && startMinute < endMinute)
        {
            return true;
        }
        return false;
    }

public:
    // 各个功能函数
    void addEvent();
    void sortByEndTime();
    void markEventAsDone();
    void showEvents();
    void searchEventByContent();
    void deleteEvent();
};
