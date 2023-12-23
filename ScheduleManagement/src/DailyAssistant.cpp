#include <iostream>
#include "../include/DailyAssistant.h"

namespace DailylifeAssistant {
    // 清除输入缓冲区
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // 清屏函数，跨平台兼容
    void clearScreen() {
        system("cls");
    }


    // 主控制函数
    void DailyAssistant::mainDailylifeAssistant() {
        Course c;
        MemoManager memo;
        Schedule schedule;
        HomeworkManager homework;

        // 选择各个功能
        int mainChoice;

        while (true) {
            // 输出功能提示
            std::cout << "===陪伴你的每一天===" << std::endl;
            std::cout << "1. 课程助手" << std::endl;
            std::cout << "2. 备忘录" << std::endl;
            std::cout << "3. 作业助手" << std::endl;
            std::cout << "4. 日程助手" << std::endl;
            std::cout << "5. 退出程序" << std::endl;
            std::cout << "请输入选项：";
            std::cin >> mainChoice;
            clearScreen();

            // 不同功能的选择实现
            switch (mainChoice) {
                case 1:
                    MainCourse();
                    break;
                case 2:
                    MainMemos();
                    break;
                case 3:
                    MainHomework();
                    break;
                case 4:
                    MainSchedule();
                    break;
                case 5:
                    return; // 退出程序
                default:
                    // 输入纠错机制
                    std::cout << "无效选项，请重新输入！" << std::endl;
                    clearInputBuffer();
                    break;
            }
            std::cout << std::endl;
        }
    }

    // 课程助手功能选择
    void DailyAssistant::MainCourse() {
        int courseswitch = 1;
        Course c;

//        c.loadCourseTable("coursetable.json");
//        c.loadSpecialCourses("specialcourse.json");
//        c.loadRemindCourses("remindcourse.json");

        while (courseswitch) {
            // 输出选择功能界面
            std::cout << std::endl;
            std::cout << "——课程助手——" << std::endl;
            std::cout << "1. 录入课程" << std::endl;
            std::cout << "2. 修改课程" << std::endl;
            std::cout << "3. 删除课程" << std::endl;
            std::cout << "4. 特殊标记" << std::endl;
            std::cout << "5. 课程备注" << std::endl;
            std::cout << "6. 输出课表" << std::endl;
            std::cout << "7. 退出功能" << std::endl;
            std::cout << "请输入选项：";

            int coursechoice;
            std::cin >> coursechoice;
            system("cls");

            //不同功能的选择实现
            switch (coursechoice) {
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
//                    c.saveCourseTable("coursetable.json", c.course_table);
//                    c.saveSpecialCourses("specialcourse.json", c.special_course);
//                    c.saveRemindCourses("remindcourse.json", c.remind_course);
                    courseswitch = 0;
                    break;
                default:
                    std::cout << "无效选项，请重新输入！" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }

    // 备忘录功能选择
    void DailyAssistant::MainMemos() {
        int memoswitch = 1;
        MemoManager memo;

        // 从json文件中读取备忘录信息
//        memo.loadMemosFromFile("memos.json");

        while (memoswitch) {
            std::cout << std::endl;
            // 备忘录常驻展示
            std::cout << "——————备忘录——————" << std::endl;
            memo.arrangeMemos();
            memo.showMemos();

            // 输入内容提示
            std::cout << "——选择功能——" << std::endl;
            std::cout << "1. 输入备忘录" << std::endl;
            std::cout << "2. 置顶提醒" << std::endl;
            std::cout << "3. 修改备忘录" << std::endl;
            std::cout << "4. 删除备忘录 " << std::endl;
            std::cout << "5. 退出程序 " << std::endl;
            std::cout << "请选择操作：";

            int memochoice;
            std::cin >> memochoice;
            system("cls");
            // 不同功能的选择实现
            switch (memochoice) {
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
                    // 将备忘录信息存入json文件
//                    memo.saveMemosToFile("memos.json");
                    memoswitch = 0;
                    break;
                default:
                    std::cout << "输入错误，请重新选择操作！" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }

    // 作业助手功能选择
    void DailyAssistant::MainHomework() {
        int homeworkswitch = 1;
        HomeworkManager homework;

        while (homeworkswitch) {
            // 功能选择提示
            std::cout << std::endl;
            std::cout << "——作业助手——" << std::endl;
            std::cout << "1. 添加作业" << std::endl;
            std::cout << "2. 显示作业清单" << std::endl;
            std::cout << "3. 标记作业完成" << std::endl;
            std::cout << "4. 删除作业" << std::endl;
            std::cout << "5. 退出" << std::endl;
            std::cout << "请选择操作：";

            int homeworkchoice;
            std::cin >> homeworkchoice;
            system("cls");
            // 选择各个功能
            switch (homeworkchoice) {
                case 1:
                    homework.addAssignment();
                    break;
                case 2:
                    homework.displayAssignmentList();
                    break;
                case 3:
                    homework.markAssignmentCompleted();
                    break;
                case 4:
                    homework.deleteAssignment();
                    break;
                case 5:
                    homeworkswitch = 0;
                    break;
                default:
                    // 选择的纠错机制
                    std::cout << "无效选项，请重新输入！" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }

    }

    // 日程表功能选择
    void DailyAssistant::MainSchedule() {
        int scheduleswitch = 1;
        Schedule schedule;

        //从json文件中读取日程表功能
//        schedule.loadEventsFromJson("schedule.json");

        while (scheduleswitch) {
            // 输入内容提示
            std::cout << std::endl;
            std::cout << "——日程表——" << std::endl;
            std::cout << "1. 添加事件" << std::endl;
            std::cout << "2. 标记事件完成" << std::endl;
            std::cout << "3. 搜索事件" << std::endl;
            std::cout << "4. 删除事件" << std::endl;
            std::cout << "5. 输出事件" << std::endl;
            std::cout << "6. 退出功能" << std::endl;
            std::cout << "请选择要进行的操作：";

            int schedulechoice;
            std::cin >> schedulechoice;
            system("cls");
            // 选择各个功能
            switch (schedulechoice) {
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
                    // 将日程信息存入json文件
//                    schedule.saveEventsToJson("schedule.json");
                    scheduleswitch = 0;
                    break;
                default:
                    // 输入纠错机制
                    std::cout << "无效的选择，请重新输入。" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }




}
