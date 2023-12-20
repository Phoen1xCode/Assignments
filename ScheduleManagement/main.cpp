#include <iostream>
#include "mainSwitch.h"
#include "course.h"
#include "memo.h"
#include "homework.h"
#include "schedule.h"

using namespace std;

// 定义全局变量从而保留内容
MemoManager memo;
HomeworkManager manager;
Schedule schedule;

// 定义全局变量控制功能开关
int courseswitch = 0;
int memoswitch = 0;
int homeworkswitch = 0;
int scheduleswitch = 0;

// 主控制函数
int main() 
{
    int mainchoice;
    while (true)
    {
        // 输出功能提示
        cout << "===陪伴你的每一天===" << endl;
        cout << "1. 课程助手" << endl;
        cout << "2. 备忘录" << endl;
        cout << "3. 作业助手" << endl;
        cout << "4. 日程助手" << endl;
        cout << "5. 退出程序" << endl;
        cout << "请输入选项：";
        cin >> mainchoice;

        // 定义类的成员从而使用成员函数
        mainSwitch course;
        mainSwitch memo;
        mainSwitch homework;
        mainSwitch schedule;

        // 不同功能的选择实现
        switch (mainchoice)
        {
        case 1:
            courseswitch += 1;
            course.mainCourse();
            break;
        case 2:
            memoswitch += 1;
            memo.mainMemos();
            break;
        case 3:
            homeworkswitch += 1;
            homework.mainHomework();
            break;
        case 4:
            scheduleswitch += 1;
            schedule.mainSchedule();
            break;
        case 5:
            return 0;        
        default:
            // 输入纠错机制
            cout << "无效选项，请重新输入！" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << endl;
    }
	return 0;
}