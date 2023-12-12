#include "course.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 后续进行状态转换
int Course::special = 0;
int Course::remind = 0;

// 定义动态数组，便于输入及修改信息
vector<Course> course_table;
vector<Course> special_course;
vector<Course> remind_course;

// 录入普通课程
void Course::inputRegularCourse()
{
    Course course;
    inputCourse(course, course_table);
}

// 录入课程信息模块
void Course::inputCourse(Course& course, vector<Course>& courseList)
{

    cout << "请输入上课日期为周几（1-7）：";
    cin >> course.day;
    while (cin.fail() || course.day > 7 || course.day < 1)
    {
        cout << "输入数据有误，请重新输入：";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.day;
    }
    cout << "请输入课程开始于第几节（1-13）：";
    cin >> course.start_time;
    while (cin.fail() || course.start_time < 1 || course.start_time > 13)
    {
        cout << "输入数据有误，请重新输入：";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.start_time;
    }
    cout << "请输入课程结束于第几节（1-13）：";
    cin >> course.end_time;
    while (cin.fail() || course.end_time < 1 || course.end_time > 13 || course.end_time < course.start_time)
    {
        cout << "输入数据有误，请重新输入：";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.end_time;
    }
    cout << "请输入课程名称：";
    cin >> course.name;
    cout << "请输入教学楼：";
    cin >> course.building;
    cout << "请输入教室号：";
    cin >> course.room;
    while (cin.fail())
    {
        cout << "输入数据有误，请重新输入：";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.room;
    }

    courseList.push_back(course);
    cout << "课程已添加！" << endl;
}

// 修改各种课程信息
void Course::modifyVariousCourse()
{
    while (true)
    {
        int mchoice;
        cout << endl;
        cout << "请选择操作：" << endl;
        cout << "1.常规课程" << endl;
        cout << "2.特殊课程" << endl;
        cout << "3.课程备注" << endl;
        cout << "4.退出功能" << endl;
        cout << "请输入想修改课程信息的类别：";
        cin >> mchoice;
        switch (mchoice)
        {
        case 1:
            modifyCourse(course_table);
            break;
        case 2:
            if (special > 0)
                modifyCourse(special_course);
            else
            {
                cout << "暂未录入特殊提醒课程" << endl;
                return modifyVariousCourse();
            }
            break;
        case 3:
            if (remind > 0)
                modifyCourse(remind_course);
            else
            {
                cout << "暂未输入课程备注" << endl;
                return modifyVariousCourse();
            }
            break;
        case 4:
            return;
        default:
            cout << "输入有误" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

// 修改课程信息模块
void Course::modifyCourse(vector<Course>& courseList) 
{
    // 输入课程名称
    string name;
    cout << "请输入要修改的课程名称：";
    cin >> name;
    cout << endl;

    // 检索对应课程
    auto it = find_if(courseList.begin(), courseList.end(), [&](const Course& course) {
        return course.name == name;
        });

    if (it != courseList.end())
    {
        Course& course = *it;
        while (true)
        {
            cout << "请选择操作：" << endl;
            cout << "1. 修改时间" << endl;
            cout << "2. 修改地点" << endl;
            cout << "3. 退出" << endl;
            cout << "请输入选项：";
            int choice;
            cin >> choice;

            // 选择功能
            switch (choice) {
            case 1:
                cout << "请输入更改后的日期（1-7）：";
                cin >> course.day;
                cout << "请输入更改后的课开始于第几节（1-13）：";
                cin >> course.start_time;
                cout << "请输入更改后的课结束于第几节（1-13）：";
                cin >> course.end_time;
                cout << "修改成功！" << endl;
                break;
            case 2:
                cout << "请输入更改后的教学楼：";
                cin >> course.building;
                cout << "请输入更改后的教室号：";
                cin >> course.room;
                cout << "修改成功！" << endl;
                break;
            case 3:
                return;
            default:
                cout << "输入有误" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

            course.name = name;
            *it = course;
            cout << endl;
        }
    }
    else {
        cout << "该课程不存在" << endl;
    }
}

// 删除课程
void Course::deleteCourse()
{
    string dname;
    cout << "请输入要删除的课程名称：";
    cin >> dname;

    bool found = false;

    // 检索要删除的课程
    auto removeCourse = [&](vector<Course>& courseList) 
        {
        auto it = remove_if(courseList.begin(), courseList.end(), [&](const Course& course) {
            return course.name == dname;
            });
        if (it != courseList.end())
        {
            courseList.erase(it, courseList.end());
            found = true;
        }
        };

    removeCourse(course_table);
    removeCourse(special_course);
    removeCourse(remind_course);

    // 删除是否成功信息提示
    if (found)
        cout << "课程已删除！" << endl;
    else
        cout << "未找到该课程！" << endl;
}

// 录入特殊课程
void Course::inputSpecialCourse()
{
    Course scourse;
    cout << "——————请输入特殊标记的课程信息——————" << endl;
    cout << "输入特殊标记信息：";
    cin >> scourse.sname;

    // 调用输入课程信息模块
    inputCourse(scourse, special_course);
    special = 1;
}

// 录入课程备注
void Course::remindCourse()
{
    Course rcourse;
    cout << "请输入你想备注的常规课程名：";
    cin >> rcourse.name;

    // 检索对应课程
    auto it = find_if(course_table.begin(), course_table.end(), [&](const Course& course) {
        return course.name == rcourse.name;
        });

    // 对课程进行备注
    if (it != course_table.end())
    {
        Course& course = *it;
        rcourse.day = course.day;
        *it = course;
        cout << "请输入对该课程的备注：" << endl;
        cin >> rcourse.memory;
        remind_course.push_back(rcourse);
        cout << "备注已添加" << endl;
        remind = 1;
    }
    else
        cout << "无法检索到该课程";
    cout << endl;
}

// 各种课程信息整理
void Course::arrangeVariousCourse()
{
    if (special > 0)
        arrangeCourse(special_course);
    if (remind > 0)
        arrangeCourse(remind_course);
    arrangeCourse(course_table);
};

// 课程信息整理模块
void Course::arrangeCourse(vector<Course>& courseList)
{
    // 对课程按时间进行排序
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        if (a.day == b.day)
            return a.start_time < b.start_time;
        return a.day < b.day;
        });

    // 将数字转化为周号
    for (auto& course : courseList)
    {
        switch (course.day)
        {
        case 1:
            course.weekday = "Mon";
            break;
        case 2:
            course.weekday = "Tue";
            break;
        case 3:
            course.weekday = "Wed";
            break;
        case 4:
            course.weekday = "Thu";
            break;
        case 5:
            course.weekday = "Fri";
            break;
        case 6:
            course.weekday = "Sat";
            break;
        case 7:
            course.weekday = "Sun";
            break;
        }
    }
}

// 课表输出
void Course::showCourse()
{
    // 特殊标记课表输出（当且仅当存在时）
    cout << endl;
    if (special > 0)
        showSpecialCourse();

    // 常规课表输出
    showRegularCourse();

    // 课程备注输出（当且仅当存在时）
    if (remind > 0)
        showRemindCourse();
};

// 特殊标记课表输出
void Course::showSpecialCourse()
{
    // 输出特殊标记表头
    cout << "——————————————————特殊注意——————————————————" << endl;
    cout << "时间\t节数\t教学楼\t教室\t课程\t备注" << endl;

    // 遍历特殊标记动态数组中内容，进行输出
    for (const auto& scourse : special_course)
    {
        cout << scourse.weekday << "\t" << scourse.start_time << "-" << scourse.end_time << "\t";
        cout << scourse.building << "\t" << scourse.room << "\t" << scourse.name << "\t";
        cout << scourse.sname << endl;
    }
}

// 常规课表输出
void Course::showRegularCourse()
{
    // 输出表头
    cout << "———————————————————课表———————————————————" << endl;
    cout << "时间\t节数\t教学楼\t教室\t课程" << endl;

    // 遍历动态数组中内容，进行输出
    for (const auto& course : course_table)
    {
        cout << course.weekday << "\t" << course.start_time << "-" << course.end_time << "\t";
        cout << course.building << "\t" << course.room << "\t" << course.name << endl;
    }
}

// 课程备注输出
void Course::showRemindCourse()
{
    // 输出表头
    cout << "——————————————————课程备注——————————————————" << endl;
    cout << "时间\t课程\t备注内容" << endl;

    // 输出内容
    for (const auto& rcourse : remind_course)
    {
        cout << rcourse.day << "\t" << rcourse.name << "\t" << rcourse.memory << endl;
    }
}
