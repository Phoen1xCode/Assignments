#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <limits>
#include <iomanip>
#include "homework.h"

using namespace std;

// 添加作业信息
void HomeworkManager::addAssignment()
{
    // 输入作业信息
    string name, subject, content, type, ddl;
    cout << "请输入科目：";
    cin >> subject;
    cout << "请输入作业内容：";
    cin >> content;
    cout << "请选择方式（1.常规作业/2.展示作业）：";
    int hchoice;
    cin >> hchoice;
    while(true)
    {
        if (hchoice == 1)
        {
            type = "常规作业";
            break;
        }
        else if (hchoice == 2)
        {
            type = "展示作业";
            break;
        }
        // 纠错机制
        else
        {
            cout << "无效的选择，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> hchoice;
        }
    }
    bool hvalidDate = false;
    while (!hvalidDate)
    {
        cout << "请输入截止日期（YYYY-MM-DD）：";
        cin >> ddl;

        // 调用函数进行判断
        hvalidDate = validateDate(ddl);
        // 判断日期格式是否正确且合理
        if (!hvalidDate)
        {
            cout << "日期格式不正确或日期不合理，请重新输入。" << endl;
        }
    }

    // 若各项内容合理，则添加作业
    Assignment assignment(name, subject, content, type, ddl);
    assignments.push_back(assignment);
    cout << "作业已添加。" << endl;
}

// 检测日期正确合理性
bool HomeworkManager::validateDate(const string& date)
{
    // 验证日期格式
    stringstream ss(date);
    int year, month, day;
    char delimiter;
    ss >> year >> delimiter >> month >> delimiter >> day;

    // 验证格式正确
    if (ss.fail() || delimiter != '-' || ss.peek() != EOF)
    {
        return false;
    }

    // 验证日期合理性
    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    // 检查月份对应的天数是否正确
    int daysInMonth;
    if (month == 2)
    {
        // 闰年的判断：能被4整除但不能被100整除，或者能被400整除
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

    // 如果日期合理返回true
    return true;
}

// 显示作业列表
void HomeworkManager::displayAssignmentList()
{
    sortAssignmentsByDdl();
    cout << "截止日期  - 科目    - 作业" << endl;
    for (const auto& assignment : assignments)
    {
        cout << assignment.getDdl() << " - " << assignment.getSubject() << " - " << assignment.getContent() << endl;
    }
}

// 标记作业完成
void HomeworkManager::markAssignmentCompleted()
{
    // 输入内容提示
    string name;
    cout << "请输入要标记完成的作业名称：";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    // 遍历作业本
    for (int i = 0; i < assignments.size(); i++)
    {
        // 检索对应的作业
        if (assignments[i].getName() == name)
        {
            found = true;
            // 展示类作业的标记
            if (assignments[i].getType() == "展示作业")
            {
                // 选择各项功能提示
                cout << "请选择要标记的内容准备完成还是上台准备完成：" << endl;
                cout << "1. 内容准备完成" << endl;
                cout << "2. 上台准备完成" << endl;

                // 实现对应选择
                int choice;
                cin >> choice;

                // 选择标记内容
                switch (choice)
                {
                case 1:
                    assignments[i].markContentPrepared();
                    cout << "展示内容准备完成。" << endl;
                    break;
                case 2:
                    assignments[i].markPresentationPrepared();
                    cout << "展示上台准备完成。" << endl;
                    break;
                default:
                    cout << "无效的选择。" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            // 常规类作业的标记
            else
            {
                assignments[i].markCompleted();
                cout << "作业已完成。" << endl;
                assignments.erase(assignments.begin() + i);
            }
            break;
        }
    }

    // 未查找到对应的作业
    if (!found)
    {
        cout << "未找到名称为 " << name << " 的作业。" << endl;
    }
}

// 删除作业
void HomeworkManager::deleteAssignment()
{
    // 输入内容提示
    string name;
    cout << "请输入要删除的作业名称：";
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (int i = 0; i < assignments.size(); i++)
    {
        // 检索对应作业
        if (assignments[i].getName() == name)
        {
            found = true;
            assignments.erase(assignments.begin() + i);
            cout << "作业已删除。" << endl;
            break;
        }
    }

    // 未找到对应作业
    if (!found)
    {
        cout << "未找到名称为 " << name << " 的作业。" << endl;
    }
}