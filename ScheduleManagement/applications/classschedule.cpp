#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include "schedule.h"

using namespace std;

// 检查日期是否合法
bool isDateValid(const string& date) 
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') 
    {
        return false;
    }
    int year = stoi(date.substr(0, 4));
    int month = stoi(date.substr(5, 2));
    int day = stoi(date.substr(8, 2));
    if (month < 1 || month > 12) 
    {
        return false;
    }
    if (day < 1 || day > 31) 
    {
        return false;
    }
    // 闰年2月判定
    if (month == 2) 
    {
        if (day > 29) 
        {
            return false;
        }
        if (day == 29 && (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0))) 
        {
            return false;
        }
    }
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) 
    {
        return false;
    }
    return true;
}

// 添加事件
void Schedule::addEvent() 
{
    string content;
    int startHour;
    int startMinute;
    int endHour;
    int endMinute = 59;
    string location;
    string requirement;
    string date;

    cout << "请输入日期（格式：YYYY-MM-DD）：";
    while (cin >> date) 
    {
        // 检查日期格式是否正确
        if (isDateValid(date))
        {
            break;
        }
        else
        {
            cout << "无效选项，请重新输入日期（格式：YYYY-MM-DD）：" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "请输入日程内容：";
    cin.ignore();
    getline(cin, content);

    cout << "请输入起始小时（0-23）：";
    while (!(cin >> startHour) || startHour < 0 || startHour > 23) 
    {
        cout << "无效选项，请重新输入起始小时（0-23）：" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入起始分钟（0-59）：";
    while (!(cin >> startMinute) || startMinute < 0 || startMinute > 59) 
    {
        cout << "无效选项，请重新输入起始分钟（0-59）：" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入结束小时（0-23）：";
    while (!(cin >> endHour) || endHour < 0 || endHour > 23 || !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) 
    {
        cout << "无效选项，请重新输入结束小时（0-23）：" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入结束分钟（0-59）：";
    while (!(cin >> endMinute) || endMinute < 0 || endMinute > 59 || !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) 
    {
        cout << "无效选项，请重新输入结束分钟（0-59）：" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "请输入地点：";
    cin.ignore();
    getline(cin, location);

    cout << "请输入要求：";
    getline(cin, requirement);

    events.push_back(Event(content, startHour, startMinute, endHour, endMinute, location, requirement, date));
    cout << "日程添加成功！" << endl;
}

// 按照结束时间进行排序
void Schedule::sortByEndTime()
{
    sort(events.begin(), events.end(), [](const Event& event1, const Event& event2) 
        {
        if (event1.date != event2.date) 
        {
            return event1.date < event2.date;
        }
        else if (event1.endHour != event2.endHour) 
        {
            return event1.endHour < event2.endHour;
        }
        else 
        {
            return event1.endMinute < event2.endMinute;
        }
        });
}

// 标记完成
void Schedule::markEventAsDone()
{
    string content;
    cout << "请输入要标记为已完成的日程名字：";
    cin >> content;
    bool found = false;
    // 通过内容进行检索
    for (auto& event : events) 
    {
        if (event.content == content) 
        {
            found = true;
            event.completed = true;
            cout << "已标记内容为 " << content << " 的日程为已完成！" << endl;
            break;
        }
    }
    // 未找到报错
    if (!found) 
    {
        cout << "没有找到内容为 " << content << " 的日程！" << endl;
    }
}

// 展示日程表
void Schedule::showEvents()
{
    // 先调用函数进行排序
    sortByEndTime();
    cout << "日程表：" << endl;
    // 已完成标记
    for (const auto& event : events) 
    {
        cout << (event.completed ? "[已完成] " : "") << event << endl;
    }
}

// 搜索日程
void Schedule::searchEventByContent()
{
    string content;
    cout << "请输入要搜索的日程内容：";
    cin >> content;
    bool found = false;
    // 通过内容进行检索
    for (auto& event : events) 
    {
        if (event.content == content) 
        {
            found = true;
            cout << event << endl;
        }
    }
    // 未找到时报错
    if (!found) 
    {
        cout << "没有找到内容为 " << content << " 的日程！" << endl;
    }
}

// 删除日程
void Schedule::deleteEvent() 
{
    string content;
    cout << "请输入要删除的日程内容：";
    cin >> content;
    bool found = false;
    // 通过内容进行检索
    for (auto it = events.begin(); it != events.end(); ++it) 
    {
        if (it->content == content) 
        {
            found = true;
            events.erase(it);
            cout << "已删除内容为 " << content << " 的日程！" << endl;
            break;
        }
    }
    // 未找到时报错
    if (!found) 
    {
        cout << "没有找到内容为 " << content << " 的日程！" << endl;
    }
}
