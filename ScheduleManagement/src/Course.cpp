#include "../include/course.h"
#include <algorithm>
#include <iostream>
#include <vector>



namespace DailylifeAssistant
{
    // 后续进行状态转换
    int Course::special = 0;
    int Course::remind = 0;

    // 录入普通课程
    void Course::inputRegularCourse()
    {
        Course course;
        inputCourse(course, course_table);
    }

    // 录入课程信息模块
    void Course::inputCourse(Course& course, std::vector<Course>& courseList)
    {

        std::cout << "请输入上课日期为周几（1-7）：";
        std::cin >> course.day;
        while (std::cin.fail() || course.day > 7 || course.day < 1)
        {
            std::cout << "输入数据有误，请重新输入：";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.day;
        }
        std::cout << "请输入课程开始于第几节（1-13）：";
        std::cin >> course.start_time;
        while (std::cin.fail() || course.start_time < 1 || course.start_time > 13)
        {
            std::cout << "输入数据有误，请重新输入：";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.start_time;
        }
        std::cout << "请输入课程结束于第几节（1-13）：";
        std::cin >> course.end_time;
        while (std::cin.fail() || course.end_time < 1 || course.end_time > 13 || course.end_time < course.start_time)
        {
            std::cout << "输入数据有误，请重新输入：";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.end_time;
        }
        std::cout << "请输入课程名称：";
        std::cin >> course.name;
        std::cout << "请输入教学楼：";
        std::cin >> course.building;
        std::cout << "请输入教室号：";
        std::cin >> course.room;
        while (std::cin.fail())
        {
            std::cout << "输入数据有误，请重新输入：";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.room;
        }

        courseList.push_back(course);
        std::cout << "课程已添加！" << std::endl;
    }

    // 修改各种课程信息
    void Course::modifyVariousCourse()
    {
        while (true)
        {
            int mchoice;
            std::cout << std::endl;
            std::cout << "请选择操作：" << std::endl;
            std::cout << "1.常规课程" << std::endl;
            std::cout << "2.特殊课程" << std::endl;
            std::cout << "3.课程备注" << std::endl;
            std::cout << "4.退出功能" << std::endl;
            std::cout << "请输入想修改课程信息的类别：";
            std::cin >> mchoice;
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
                        std::cout << "暂未录入特殊提醒课程" << std::endl;
                        return modifyVariousCourse();
                    }
                    break;
                case 3:
                    if (remind > 0)
                        modifyCourse(remind_course);
                    else
                    {
                        std::cout << "暂未输入课程备注" << std::endl;
                        return modifyVariousCourse();
                    }
                    break;
                case 4:
                    return;
                default:
                    std::cout << "输入有误" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }

    // 修改课程信息模块
    void Course::modifyCourse(std::vector<Course>& courseList)
    {
        // 输入课程名称
        std::string name;
        std::cout << "请输入要修改的课程名称：";
        std::cin >> name;
        std::cout << std::endl;

        // 检索对应课程
        auto it = std::find_if(courseList.begin(), courseList.end(), [&](const Course& course) {
            return course.name == name;
        });

        if (it != courseList.end())
        {
            Course& course = *it;
            while (true)
            {
                std::cout << "请选择操作：" << std::endl;
                std::cout << "1. 修改时间" << std::endl;
                std::cout << "2. 修改地点" << std::endl;
                std::cout << "3. 退出" << std::endl;
                std::cout << "请输入选项：";
                int choice;
                std::cin >> choice;

                // 选择功能
                switch (choice) {
                    case 1:
                        std::cout << "请输入更改后的日期（1-7）：";
                        std::cin >> course.day;
                        std::cout << "请输入更改后的课开始于第几节（1-13）：";
                        std::cin >> course.start_time;
                        std::cout << "请输入更改后的课结束于第几节（1-13）：";
                        std::cin >> course.end_time;
                        std::cout << "修改成功！" << std::endl;
                        break;
                    case 2:
                        std::cout << "请输入更改后的教学楼：";
                        std::cin >> course.building;
                        std::cout << "请输入更改后的教室号：";
                        std::cin >> course.room;
                        std::cout << "修改成功！" << std::endl;
                        break;
                    case 3:
                        return;
                    default:
                        std::cout << "输入有误" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                }
            }
        }
        else
        {
            std::cout << "未找到对应课程" << std::endl;
        }
    }

    // 删除课程
    void Course::deleteCourse()
    {
        std::string name;
        std::cout << "请输入要删除的课程名称：";
        std::cin >> name;
        std::cout << std::endl;

        // 从course_table中删除对应课程
        auto it = std::find_if(course_table.begin(), course_table.end(), [&](const Course& course) {
            return course.name == name;
        });

        if (it != course_table.end())
        {
            course_table.erase(it);
            std::cout << "课程已删除" << std::endl;
        }
        else
        {
            std::cout << "未找到对应课程" << std::endl;
        }
    }

    // 录入特殊课程
    void Course::inputSpecialCourse()
    {
        Course scourse;
        std::cout << "——————请输入特殊标记的课程信息——————" << std::endl;
        std::cout << "输入特殊标记信息：";
        std::cin >> scourse.sname;

        // 调用输入课程信息模块
        inputCourse(scourse, special_course);
        special = 1;
    }

    // 录入课程备注
    void Course::remindCourse()
    {
        Course rcourse;
        std::cout << "请输入你想备注的常规课程名：";
        std::cin >> rcourse.name;

        // 检索对应课程
        auto it = std::find_if(course_table.begin(), course_table.end(), [&](const Course& course) {
            return course.name == rcourse.name;
        });

        // 对课程进行备注
        if (it != course_table.end())
        {
            Course& course = *it;
            rcourse.day = course.day;
            *it = course;
            std::cout << "请输入对该课程的备注：" << std::endl;
            std::cin >> rcourse.memory;
            remind_course.push_back(rcourse);
            std::cout << "备注已添加" << std::endl;
            remind = 1;
        }
        else
            std::cout << "无法检索到该课程";
        std::cout << std::endl;
    }

    // 各种课程信息整理
    void Course::arrangeVariousCourse()
    {
        if (special > 0)
            arrangeCourse(special_course);
        if (remind > 0)
            arrangeCourse(remind_course);
        arrangeCourse(course_table);
    }

    // 课程信息整理模块
    void Course::arrangeCourse(std::vector<Course>& courseList)
    {
        // 对课程按时间进行排序
        std::sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
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
        std::cout << std::endl;
        if (special > 0)
            showSpecialCourse();

        // 常规课表输出
        showRegularCourse();

        // 课程备注输出（当且仅当存在时）
        if (remind > 0)
            showRemindCourse();
    }

    // 特殊标记课表输出
    void Course::showSpecialCourse()
    {
        // 输出特殊标记表头
        std::cout << "——————————————————特殊注意——————————————————" << std::endl;
        std::cout << "时间\t节数\t教学楼\t教室\t课程\t备注" << std::endl;

        // 遍历特殊标记动态数组中内容，进行输出
        for (const auto& scourse : special_course)
        {
            std::cout << scourse.weekday << "\t" << scourse.start_time << "-" << scourse.end_time << "\t";
            std::cout << scourse.building << "\t" << scourse.room << "\t" << scourse.name << "\t";
            std::cout << scourse.sname << std::endl;
        }
    }

    // 常规课表输出
    void Course::showRegularCourse()
    {
        // 输出表头
        std::cout << "———————————————————课表———————————————————" << std::endl;
        std::cout << "时间\t节数\t教学楼\t教室\t课程" << std::endl;

        // 遍历动态数组中内容，进行输出
        for (const auto& course : course_table)
        {
            std::cout << course.weekday << "\t" << course.start_time << "-" << course.end_time << "\t";
            std::cout << course.building << "\t" << course.room << "\t" << course.name << std::endl;
        }
    }

    // 课程备注输出
    void Course::showRemindCourse()
    {
        // 输出表头
        std::cout << "——————————————————课程备注——————————————————" << std::endl;
        std::cout << "时间\t课程\t备注内容" << std::endl;

        // 输出内容
        for (const auto& rcourse : remind_course)
        {
            std::cout << rcourse.day << "\t" << rcourse.name << "\t" << rcourse.memory << std::endl;
        }
    }
}
