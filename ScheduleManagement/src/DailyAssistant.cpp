#include <iostream>
#include "../include/DailyAssistant.h"

namespace DailylifeAssistant {
    // ������뻺����
    void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // ������������ƽ̨����
    void clearScreen() {
        system("cls");
    }


    // �����ƺ���
    void DailyAssistant::mainDailylifeAssistant() {
        Course c;
        MemoManager memo;
        Schedule schedule;
        HomeworkManager homework;

        // ѡ���������
        int mainChoice;

        while (true) {
            // ���������ʾ
            std::cout << "===������ÿһ��===" << std::endl;
            std::cout << "1. �γ�����" << std::endl;
            std::cout << "2. ����¼" << std::endl;
            std::cout << "3. ��ҵ����" << std::endl;
            std::cout << "4. �ճ�����" << std::endl;
            std::cout << "5. �˳�����" << std::endl;
            std::cout << "������ѡ�";
            std::cin >> mainChoice;
            clearScreen();

            // ��ͬ���ܵ�ѡ��ʵ��
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
                    return; // �˳�����
                default:
                    // ����������
                    std::cout << "��Чѡ����������룡" << std::endl;
                    clearInputBuffer();
                    break;
            }
            std::cout << std::endl;
        }
    }

    // �γ����ֹ���ѡ��
    void DailyAssistant::MainCourse() {
        int courseswitch = 1;
        Course c;

//        c.loadCourseTable("coursetable.json");
//        c.loadSpecialCourses("specialcourse.json");
//        c.loadRemindCourses("remindcourse.json");

        while (courseswitch) {
            // ���ѡ���ܽ���
            std::cout << std::endl;
            std::cout << "�����γ����֡���" << std::endl;
            std::cout << "1. ¼��γ�" << std::endl;
            std::cout << "2. �޸Ŀγ�" << std::endl;
            std::cout << "3. ɾ���γ�" << std::endl;
            std::cout << "4. ������" << std::endl;
            std::cout << "5. �γ̱�ע" << std::endl;
            std::cout << "6. ����α�" << std::endl;
            std::cout << "7. �˳�����" << std::endl;
            std::cout << "������ѡ�";

            int coursechoice;
            std::cin >> coursechoice;
            system("cls");

            //��ͬ���ܵ�ѡ��ʵ��
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
                    std::cout << "��Чѡ����������룡" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }

    // ����¼����ѡ��
    void DailyAssistant::MainMemos() {
        int memoswitch = 1;
        MemoManager memo;

        // ��json�ļ��ж�ȡ����¼��Ϣ
//        memo.loadMemosFromFile("memos.json");

        while (memoswitch) {
            std::cout << std::endl;
            // ����¼��פչʾ
            std::cout << "����������������¼������������" << std::endl;
            memo.arrangeMemos();
            memo.showMemos();

            // ����������ʾ
            std::cout << "����ѡ���ܡ���" << std::endl;
            std::cout << "1. ���뱸��¼" << std::endl;
            std::cout << "2. �ö�����" << std::endl;
            std::cout << "3. �޸ı���¼" << std::endl;
            std::cout << "4. ɾ������¼ " << std::endl;
            std::cout << "5. �˳����� " << std::endl;
            std::cout << "��ѡ�������";

            int memochoice;
            std::cin >> memochoice;
            system("cls");
            // ��ͬ���ܵ�ѡ��ʵ��
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
                    // ������¼��Ϣ����json�ļ�
//                    memo.saveMemosToFile("memos.json");
                    memoswitch = 0;
                    break;
                default:
                    std::cout << "�������������ѡ�������" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }

    // ��ҵ���ֹ���ѡ��
    void DailyAssistant::MainHomework() {
        int homeworkswitch = 1;
        HomeworkManager homework;

        while (homeworkswitch) {
            // ����ѡ����ʾ
            std::cout << std::endl;
            std::cout << "������ҵ���֡���" << std::endl;
            std::cout << "1. �����ҵ" << std::endl;
            std::cout << "2. ��ʾ��ҵ�嵥" << std::endl;
            std::cout << "3. �����ҵ���" << std::endl;
            std::cout << "4. ɾ����ҵ" << std::endl;
            std::cout << "5. �˳�" << std::endl;
            std::cout << "��ѡ�������";

            int homeworkchoice;
            std::cin >> homeworkchoice;
            system("cls");
            // ѡ���������
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
                    // ѡ��ľ������
                    std::cout << "��Чѡ����������룡" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }

    }

    // �ճ̱���ѡ��
    void DailyAssistant::MainSchedule() {
        int scheduleswitch = 1;
        Schedule schedule;

        //��json�ļ��ж�ȡ�ճ̱���
//        schedule.loadEventsFromJson("schedule.json");

        while (scheduleswitch) {
            // ����������ʾ
            std::cout << std::endl;
            std::cout << "�����ճ̱���" << std::endl;
            std::cout << "1. ����¼�" << std::endl;
            std::cout << "2. ����¼����" << std::endl;
            std::cout << "3. �����¼�" << std::endl;
            std::cout << "4. ɾ���¼�" << std::endl;
            std::cout << "5. ����¼�" << std::endl;
            std::cout << "6. �˳�����" << std::endl;
            std::cout << "��ѡ��Ҫ���еĲ�����";

            int schedulechoice;
            std::cin >> schedulechoice;
            system("cls");
            // ѡ���������
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
                    // ���ճ���Ϣ����json�ļ�
//                    schedule.saveEventsToJson("schedule.json");
                    scheduleswitch = 0;
                    break;
                default:
                    // ����������
                    std::cout << "��Ч��ѡ�����������롣" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }




}
