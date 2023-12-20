#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// ��������
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
    // ���캯��
    Event(const string& content, int startHour, int startMinute, int endHour, int endMinute, const string& location, const string& requirement, const string& date)
        : content(content), startHour(startHour), startMinute(startMinute), endHour(endHour), endMinute(endMinute), location(location), requirement(requirement), completed(false), date(date) {}

    // ���¼����Ϊ�����
    void markAsCompleted()
    {
        completed = true;
    }

    // ����¼��Ƿ������
    bool isCompleted() const
    {
        return completed;
    }

    // ��Ԫ���������ڽ��¼���Ϣ���������
    friend ostream& operator<<(ostream& os, const Event& event)
    {
        os << "���ڣ�" << event.date << endl;                                          // �������
        os << "���ݣ�" << event.content << endl;                                      // ����ճ�����
        os << "��ʼʱ�䣺" << event.startHour << ":" << event.startMinute << endl;     // �����ʼʱ��
        os << "����ʱ�䣺" << event.endHour << ":" << event.endMinute << endl;         // �������ʱ��
        os << "�ص㣺" << event.location << endl;                                     // ����ص�
        os << "Ҫ��" << event.requirement << endl;                                  // ���Ҫ��
        os << "״̬��" << (event.completed ? "�����" : "δ���") << endl;            // ���״̬
        return os;
    }
};

// �������ܹ���
class Schedule
{
private:
    vector<Event> events;
    // �����������ж���ʼʱ���Ƿ��ڽ���ʱ��֮ǰ
    bool isStartTimeBeforeEndTime(int startHour, int startMinute, int endHour, int endMinute) const
    {
        // �ȱȽ�Сʱ
        if (startHour < endHour)
        {
            return true;
        }
        // Сʱ��ͬʱ�ȽϷ���
        else if (startHour == endHour && startMinute < endMinute)
        {
            return true;
        }
        return false;
    }

public:
    // �������ܺ���
    void addEvent();
    void sortByEndTime();
    void markEventAsDone();
    void showEvents();
    void searchEventByContent();
    void deleteEvent();
};
