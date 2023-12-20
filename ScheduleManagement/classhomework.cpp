#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <limits>
#include <iomanip>
#include "homework.h"

using namespace std;

// �����ҵ��Ϣ
void HomeworkManager::addAssignment()
{
    // ������ҵ��Ϣ
    string name, subject, content, type, ddl;
    cout << "�������Ŀ��";
    cin >> subject;
    cout << "��������ҵ���ݣ�";
    cin >> content;
    cout << "��ѡ��ʽ��1.������ҵ/2.չʾ��ҵ����";
    int hchoice;
    cin >> hchoice;
    while(true)
    {
        if (hchoice == 1)
        {
            type = "������ҵ";
            break;
        }
        else if (hchoice == 2)
        {
            type = "չʾ��ҵ";
            break;
        }
        // �������
        else
        {
            cout << "��Ч��ѡ�����������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> hchoice;
        }
    }
    bool hvalidDate = false;
    while (!hvalidDate)
    {
        cout << "�������ֹ���ڣ�YYYY-MM-DD����";
        cin >> ddl;

        // ���ú��������ж�
        hvalidDate = validateDate(ddl);
        // �ж����ڸ�ʽ�Ƿ���ȷ�Һ���
        if (!hvalidDate)
        {
            cout << "���ڸ�ʽ����ȷ�����ڲ��������������롣" << endl;
        }
    }

    // ���������ݺ����������ҵ
    Assignment assignment(name, subject, content, type, ddl);
    assignments.push_back(assignment);
    cout << "��ҵ����ӡ�" << endl;
}

// ���������ȷ������
bool HomeworkManager::validateDate(const string& date)
{
    // ��֤���ڸ�ʽ
    stringstream ss(date);
    int year, month, day;
    char delimiter;
    ss >> year >> delimiter >> month >> delimiter >> day;

    // ��֤��ʽ��ȷ
    if (ss.fail() || delimiter != '-' || ss.peek() != EOF)
    {
        return false;
    }

    // ��֤���ں�����
    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    // ����·ݶ�Ӧ�������Ƿ���ȷ
    int daysInMonth;
    if (month == 2)
    {
        // ������жϣ��ܱ�4���������ܱ�100�����������ܱ�400����
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        daysInMonth = isLeapYear ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        daysInMonth = 30;
    }
    else
    {
        daysInMonth = 31;
    }

    if (day > daysInMonth)
    {
        return false;
    }

    // ������ں�����true
    return true;
}

// ��ʾ��ҵ�б�
void HomeworkManager::displayAssignmentList()
{
    sortAssignmentsByDdl();
    cout << "��ֹ����  - ��Ŀ    - ��ҵ" << endl;
    for (const auto& assignment : assignments)
    {
        cout << assignment.getDdl() << " - " << assignment.getSubject() << " - " << assignment.getContent() << endl;
    }
}

// �����ҵ���
void HomeworkManager::markAssignmentCompleted()
{
    // ����������ʾ
    string name;
    cout << "������Ҫ�����ɵ���ҵ���ƣ�";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    // ������ҵ��
    for (int i = 0; i < assignments.size(); i++)
    {
        // ������Ӧ����ҵ
        if (assignments[i].getName() == name)
        {
            found = true;
            // չʾ����ҵ�ı��
            if (assignments[i].getType() == "չʾ��ҵ")
            {
                // ѡ��������ʾ
                cout << "��ѡ��Ҫ��ǵ�����׼����ɻ�����̨׼����ɣ�" << endl;
                cout << "1. ����׼�����" << endl;
                cout << "2. ��̨׼�����" << endl;

                // ʵ�ֶ�Ӧѡ��
                int choice;
                cin >> choice;

                // ѡ��������
                switch (choice)
                {
                case 1:
                    assignments[i].markContentPrepared();
                    cout << "չʾ����׼����ɡ�" << endl;
                    break;
                case 2:
                    assignments[i].markPresentationPrepared();
                    cout << "չʾ��̨׼����ɡ�" << endl;
                    break;
                default:
                    cout << "��Ч��ѡ��" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            // ��������ҵ�ı��
            else
            {
                assignments[i].markCompleted();
                cout << "��ҵ����ɡ�" << endl;
                assignments.erase(assignments.begin() + i);
            }
            break;
        }
    }

    // δ���ҵ���Ӧ����ҵ
    if (!found)
    {
        cout << "δ�ҵ�����Ϊ " << name << " ����ҵ��" << endl;
    }
}

// ɾ����ҵ
void HomeworkManager::deleteAssignment()
{
    // ����������ʾ
    string name;
    cout << "������Ҫɾ������ҵ���ƣ�";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < assignments.size(); i++)
    {
        // ������Ӧ��ҵ
        if (assignments[i].getName() == name)
        {
            found = true;
            assignments.erase(assignments.begin() + i);
            cout << "��ҵ��ɾ����" << endl;
            break;
        }
    }

    // δ�ҵ���Ӧ��ҵ
    if (!found)
    {
        cout << "δ�ҵ�����Ϊ " << name << " ����ҵ��" << endl;
    }
}