#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include "schedule.h"

using namespace std;

// ��������Ƿ�Ϸ�
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
    // ����2���ж�
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

// ����¼�
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

    cout << "���������ڣ���ʽ��YYYY-MM-DD����";
    while (cin >> date) 
    {
        // ������ڸ�ʽ�Ƿ���ȷ
        if (isDateValid(date))
        {
            break;
        }
        else
        {
            cout << "��Чѡ��������������ڣ���ʽ��YYYY-MM-DD����" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    cout << "�������ճ����ݣ�";
    cin.ignore();
    getline(cin, content);

    cout << "��������ʼСʱ��0-23����";
    while (!(cin >> startHour) || startHour < 0 || startHour > 23) 
    {
        cout << "��Чѡ�������������ʼСʱ��0-23����" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "��������ʼ���ӣ�0-59����";
    while (!(cin >> startMinute) || startMinute < 0 || startMinute > 59) 
    {
        cout << "��Чѡ�������������ʼ���ӣ�0-59����" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "���������Сʱ��0-23����";
    while (!(cin >> endHour) || endHour < 0 || endHour > 23 || !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) 
    {
        cout << "��Чѡ��������������Сʱ��0-23����" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "������������ӣ�0-59����";
    while (!(cin >> endMinute) || endMinute < 0 || endMinute > 59 || !isStartTimeBeforeEndTime(startHour, startMinute, endHour, endMinute)) 
    {
        cout << "��Чѡ�����������������ӣ�0-59����" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "������ص㣺";
    cin.ignore();
    getline(cin, location);

    cout << "������Ҫ��";
    getline(cin, requirement);

    events.push_back(Event(content, startHour, startMinute, endHour, endMinute, location, requirement, date));
    cout << "�ճ���ӳɹ���" << endl;
}

// ���ս���ʱ���������
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

// ������
void Schedule::markEventAsDone()
{
    string content;
    cout << "������Ҫ���Ϊ����ɵ��ճ����֣�";
    cin >> content;
    bool found = false;
    // ͨ�����ݽ��м���
    for (auto& event : events) 
    {
        if (event.content == content) 
        {
            found = true;
            event.completed = true;
            cout << "�ѱ������Ϊ " << content << " ���ճ�Ϊ����ɣ�" << endl;
            break;
        }
    }
    // δ�ҵ�����
    if (!found) 
    {
        cout << "û���ҵ�����Ϊ " << content << " ���ճ̣�" << endl;
    }
}

// չʾ�ճ̱�
void Schedule::showEvents()
{
    // �ȵ��ú�����������
    sortByEndTime();
    cout << "�ճ̱�" << endl;
    // ����ɱ��
    for (const auto& event : events) 
    {
        cout << (event.completed ? "[�����] " : "") << event << endl;
    }
}

// �����ճ�
void Schedule::searchEventByContent()
{
    string content;
    cout << "������Ҫ�������ճ����ݣ�";
    cin >> content;
    bool found = false;
    // ͨ�����ݽ��м���
    for (auto& event : events) 
    {
        if (event.content == content) 
        {
            found = true;
            cout << event << endl;
        }
    }
    // δ�ҵ�ʱ����
    if (!found) 
    {
        cout << "û���ҵ�����Ϊ " << content << " ���ճ̣�" << endl;
    }
}

// ɾ���ճ�
void Schedule::deleteEvent() 
{
    string content;
    cout << "������Ҫɾ�����ճ����ݣ�";
    cin >> content;
    bool found = false;
    // ͨ�����ݽ��м���
    for (auto it = events.begin(); it != events.end(); ++it) 
    {
        if (it->content == content) 
        {
            found = true;
            events.erase(it);
            cout << "��ɾ������Ϊ " << content << " ���ճ̣�" << endl;
            break;
        }
    }
    // δ�ҵ�ʱ����
    if (!found) 
    {
        cout << "û���ҵ�����Ϊ " << content << " ���ճ̣�" << endl;
    }
}
