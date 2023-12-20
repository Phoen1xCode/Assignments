#include <iostream>
#include "mainSwitch.h"
#include "course.h"
#include "memo.h"
#include "homework.h"
#include "schedule.h"

using namespace std;

// 课程助手功能选择
void mainSwitch::mainCourse()
{
    extern int courseswitch;
    while (courseswitch)
    {
        // 输出选择功能界面
        cout << endl;
        cout << "——课程助手——" << endl;
        cout << "1. 录入课程" << endl;
        cout << "2. 修改课程" << endl;
        cout << "3. 删除课程" << endl;
        cout << "4. 特殊标记" << endl;
        cout << "5. 课程备注" << endl;
        cout << "6. 输出课表" << endl;
        cout << "7. 退出功能" << endl;
        cout << "请输入选项：";

        int coursechoice;
        cin >> coursechoice;

        //不同功能的选择实现
        Course c;
        switch (coursechoice)
        {
        case 1:
            c.inputRegularCourse();
            break;
        case 2:
            c.modifyVariousCourse();
            break;
        case 3:
            c.deleteCourse();
            break;
        case 4:
            c.inputSpecialCourse();
            break;
        case 5:
            c.remindCourse();
            break;
        case 6:
            c.arrangeVariousCourse();
            c.showCourse();
            break;
        case 7:
            courseswitch -= 1;
            break;
        default:
            cout << "无效选项，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

// 备忘录功能选择
void mainSwitch::mainMemos()
{   
    extern int memoswitch;
    extern MemoManager memo;
    while (memoswitch)
    {
        cout << endl;
        // 备忘录常驻展示
        cout << "——————备忘录——————" << endl;
        memo.arrangeMemos();
        memo.showMemos();

        // 输入内容提示
        cout << "——选择功能——" << endl;
        cout << "1. 输入备忘录" << endl;
        cout << "2. 置顶提醒" << endl;
        cout << "3. 修改备忘录" << endl;
        cout << "4. 删除备忘录 " << endl;
        cout << "5. 退出程序 " << endl;
        cout << "请选择操作：" ;

        int memochoice;
        cin >> memochoice;

        // 不同功能的选择实现
        switch (memochoice)
        {
        case 1:
            memo.addMemo();
            break;
        case 2:
            memo.topMemo();
            break;
        case 3:
            memo.modifyMemo();
            break;
        case 4:
            memo.deleteMemo();
            break;
        case 5:
            memoswitch -= 1;
            break;
        default:
            cout << "输入错误，请重新选择操作！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// 作业助手功能选择
void mainSwitch::mainHomework()
{
    extern int homeworkswitch;
    extern HomeworkManager manager;

    while (homeworkswitch)
    {
        // 功能选择提示
        cout << endl;
        cout << "——作业助手——" << endl;
        cout << "1. 添加作业" << endl;
        cout << "2. 显示作业清单" << endl;
        cout << "3. 标记作业完成" << endl;
        cout << "4. 删除作业" << endl;
        cout << "5. 退出" << endl;
        cout << "请选择操作：" ;

        int homeworkchoice;
        cin >> homeworkchoice;

        // 选择各个功能
        switch (homeworkchoice)
        {
        case 1:
            manager.addAssignment();
            break;
        case 2:
            manager.displayAssignmentList();
            break;
        case 3:
            manager.markAssignmentCompleted();
            break;
        case 4:
            manager.deleteAssignment();
            break;
        case 5:
            homeworkswitch -= 1;
            break;
        default:
            // 选择的纠错机制
            cout << "无效选项，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// 日程表功能选择
void mainSwitch::mainSchedule()
{
    extern int scheduleswitch;
    extern Schedule schedule;
    
    while (scheduleswitch)
    {
        // 输入内容提示
        cout << endl;
        cout << "——日程表——" << endl;
        cout << "1. 添加事件" << endl;
        cout << "2. 标记事件完成" << endl;
        cout << "3. 搜索事件" << endl;
        cout << "4. 删除事件" << endl;
        cout << "5. 输出事件" << endl;
        cout << "6. 退出功能" << endl;
        cout << "请选择要进行的操作：" ;

        int schedulechoice;
        cin >> schedulechoice;

        // 选择各个功能
        switch (schedulechoice)
        {
        case 1:
            schedule.addEvent();
            break;
        case 2:
            schedule.markEventAsDone();
            break;
        case 3:
            schedule.searchEventByContent();
            break;
        case 4:
            schedule.deleteEvent();
            break;
        case 5:
            schedule.sortByEndTime();
            schedule.showEvents();
            break;
        case 6:
            cout << "退出程序。" << endl;
            scheduleswitch -= 1;
            break;
        default:
            // 输入纠错机制
            cout << "无效的选择，请重新输入。" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}
