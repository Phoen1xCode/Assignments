#include <iostream>
#include "mainSwitch.h"
#include "course.h"
#include "memo.h"
#include "homework.h"
#include "schedule.h"

using namespace std;

// �γ����ֹ���ѡ��
void mainSwitch::mainCourse()
{
    extern int courseswitch;
    while (courseswitch)
    {
        // ���ѡ���ܽ���
        cout << endl;
        cout << "�����γ����֡���" << endl;
        cout << "1. ¼��γ�" << endl;
        cout << "2. �޸Ŀγ�" << endl;
        cout << "3. ɾ���γ�" << endl;
        cout << "4. ������" << endl;
        cout << "5. �γ̱�ע" << endl;
        cout << "6. ����α�" << endl;
        cout << "7. �˳�����" << endl;
        cout << "������ѡ�";

        int coursechoice;
        cin >> coursechoice;

        //��ͬ���ܵ�ѡ��ʵ��
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
            cout << "��Чѡ����������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

// ����¼����ѡ��
void mainSwitch::mainMemos()
{   
    extern int memoswitch;
    extern MemoManager memo;
    while (memoswitch)
    {
        cout << endl;
        // ����¼��פչʾ
        cout << "����������������¼������������" << endl;
        memo.arrangeMemos();
        memo.showMemos();

        // ����������ʾ
        cout << "����ѡ���ܡ���" << endl;
        cout << "1. ���뱸��¼" << endl;
        cout << "2. �ö�����" << endl;
        cout << "3. �޸ı���¼" << endl;
        cout << "4. ɾ������¼ " << endl;
        cout << "5. �˳����� " << endl;
        cout << "��ѡ�������" ;

        int memochoice;
        cin >> memochoice;

        // ��ͬ���ܵ�ѡ��ʵ��
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
            cout << "�������������ѡ�������" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ��ҵ���ֹ���ѡ��
void mainSwitch::mainHomework()
{
    extern int homeworkswitch;
    extern HomeworkManager manager;

    while (homeworkswitch)
    {
        // ����ѡ����ʾ
        cout << endl;
        cout << "������ҵ���֡���" << endl;
        cout << "1. �����ҵ" << endl;
        cout << "2. ��ʾ��ҵ�嵥" << endl;
        cout << "3. �����ҵ���" << endl;
        cout << "4. ɾ����ҵ" << endl;
        cout << "5. �˳�" << endl;
        cout << "��ѡ�������" ;

        int homeworkchoice;
        cin >> homeworkchoice;

        // ѡ���������
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
            // ѡ��ľ������
            cout << "��Чѡ����������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// �ճ̱���ѡ��
void mainSwitch::mainSchedule()
{
    extern int scheduleswitch;
    extern Schedule schedule;
    
    while (scheduleswitch)
    {
        // ����������ʾ
        cout << endl;
        cout << "�����ճ̱���" << endl;
        cout << "1. ����¼�" << endl;
        cout << "2. ����¼����" << endl;
        cout << "3. �����¼�" << endl;
        cout << "4. ɾ���¼�" << endl;
        cout << "5. ����¼�" << endl;
        cout << "6. �˳�����" << endl;
        cout << "��ѡ��Ҫ���еĲ�����" ;

        int schedulechoice;
        cin >> schedulechoice;

        // ѡ���������
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
            cout << "�˳�����" << endl;
            scheduleswitch -= 1;
            break;
        default:
            // ����������
            cout << "��Ч��ѡ�����������롣" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}
