#include <iostream>
#include "mainSwitch.h"
#include "course.h"
#include "memo.h"
#include "homework.h"
#include "schedule.h"

using namespace std;

// ����ȫ�ֱ����Ӷ���������
MemoManager memo;
HomeworkManager manager;
Schedule schedule;

// ����ȫ�ֱ������ƹ��ܿ���
int courseswitch = 0;
int memoswitch = 0;
int homeworkswitch = 0;
int scheduleswitch = 0;

// �����ƺ���
int main() 
{
    int mainchoice;
    while (true)
    {
        // ���������ʾ
        cout << "===������ÿһ��===" << endl;
        cout << "1. �γ�����" << endl;
        cout << "2. ����¼" << endl;
        cout << "3. ��ҵ����" << endl;
        cout << "4. �ճ�����" << endl;
        cout << "5. �˳�����" << endl;
        cout << "������ѡ�";
        cin >> mainchoice;

        // ������ĳ�Ա�Ӷ�ʹ�ó�Ա����
        mainSwitch course;
        mainSwitch memo;
        mainSwitch homework;
        mainSwitch schedule;

        // ��ͬ���ܵ�ѡ��ʵ��
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
            // ����������
            cout << "��Чѡ����������룡" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << endl;
    }
	return 0;
}