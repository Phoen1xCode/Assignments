#include "course.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// ��������״̬ת��
int Course::special = 0;
int Course::remind = 0;

// ���嶯̬���飬�������뼰�޸���Ϣ
vector<Course> course_table;
vector<Course> special_course;
vector<Course> remind_course;

// ¼����ͨ�γ�
void Course::inputRegularCourse()
{
    Course course;
    inputCourse(course, course_table);
}

// ¼��γ���Ϣģ��
void Course::inputCourse(Course& course, vector<Course>& courseList)
{

    cout << "�������Ͽ�����Ϊ�ܼ���1-7����";
    cin >> course.day;
    while (cin.fail() || course.day > 7 || course.day < 1)
    {
        cout << "���������������������룺";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.day;
    }
    cout << "������γ̿�ʼ�ڵڼ��ڣ�1-13����";
    cin >> course.start_time;
    while (cin.fail() || course.start_time < 1 || course.start_time > 13)
    {
        cout << "���������������������룺";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.start_time;
    }
    cout << "������γ̽����ڵڼ��ڣ�1-13����";
    cin >> course.end_time;
    while (cin.fail() || course.end_time < 1 || course.end_time > 13 || course.end_time < course.start_time)
    {
        cout << "���������������������룺";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.end_time;
    }
    cout << "������γ����ƣ�";
    cin >> course.name;
    cout << "�������ѧ¥��";
    cin >> course.building;
    cout << "��������Һţ�";
    cin >> course.room;
    while (cin.fail())
    {
        cout << "���������������������룺";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> course.room;
    }

    courseList.push_back(course);
    cout << "�γ�����ӣ�" << endl;
}

// �޸ĸ��ֿγ���Ϣ
void Course::modifyVariousCourse()
{
    while (true)
    {
        int mchoice;
        cout << endl;
        cout << "��ѡ�������" << endl;
        cout << "1.����γ�" << endl;
        cout << "2.����γ�" << endl;
        cout << "3.�γ̱�ע" << endl;
        cout << "4.�˳�����" << endl;
        cout << "���������޸Ŀγ���Ϣ�����";
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
                cout << "��δ¼���������ѿγ�" << endl;
                return modifyVariousCourse();
            }
            break;
        case 3:
            if (remind > 0)
                modifyCourse(remind_course);
            else
            {
                cout << "��δ����γ̱�ע" << endl;
                return modifyVariousCourse();
            }
            break;
        case 4:
            return;
        default:
            cout << "��������" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
}

// �޸Ŀγ���Ϣģ��
void Course::modifyCourse(vector<Course>& courseList) 
{
    // ����γ�����
    string name;
    cout << "������Ҫ�޸ĵĿγ����ƣ�";
    cin >> name;
    cout << endl;

    // ������Ӧ�γ�
    auto it = find_if(courseList.begin(), courseList.end(), [&](const Course& course) {
        return course.name == name;
        });

    if (it != courseList.end())
    {
        Course& course = *it;
        while (true)
        {
            cout << "��ѡ�������" << endl;
            cout << "1. �޸�ʱ��" << endl;
            cout << "2. �޸ĵص�" << endl;
            cout << "3. �˳�" << endl;
            cout << "������ѡ�";
            int choice;
            cin >> choice;

            // ѡ����
            switch (choice) {
            case 1:
                cout << "��������ĺ�����ڣ�1-7����";
                cin >> course.day;
                cout << "��������ĺ�Ŀο�ʼ�ڵڼ��ڣ�1-13����";
                cin >> course.start_time;
                cout << "��������ĺ�Ŀν����ڵڼ��ڣ�1-13����";
                cin >> course.end_time;
                cout << "�޸ĳɹ���" << endl;
                break;
            case 2:
                cout << "��������ĺ�Ľ�ѧ¥��";
                cin >> course.building;
                cout << "��������ĺ�Ľ��Һţ�";
                cin >> course.room;
                cout << "�޸ĳɹ���" << endl;
                break;
            case 3:
                return;
            default:
                cout << "��������" << endl;
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
        cout << "�ÿγ̲�����" << endl;
    }
}

// ɾ���γ�
void Course::deleteCourse()
{
    string dname;
    cout << "������Ҫɾ���Ŀγ����ƣ�";
    cin >> dname;

    bool found = false;

    // ����Ҫɾ���Ŀγ�
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

    // ɾ���Ƿ�ɹ���Ϣ��ʾ
    if (found)
        cout << "�γ���ɾ����" << endl;
    else
        cout << "δ�ҵ��ÿγ̣�" << endl;
}

// ¼������γ�
void Course::inputSpecialCourse()
{
    Course scourse;
    cout << "�����������������������ǵĿγ���Ϣ������������" << endl;
    cout << "������������Ϣ��";
    cin >> scourse.sname;

    // ��������γ���Ϣģ��
    inputCourse(scourse, special_course);
    special = 1;
}

// ¼��γ̱�ע
void Course::remindCourse()
{
    Course rcourse;
    cout << "���������뱸ע�ĳ���γ�����";
    cin >> rcourse.name;

    // ������Ӧ�γ�
    auto it = find_if(course_table.begin(), course_table.end(), [&](const Course& course) {
        return course.name == rcourse.name;
        });

    // �Կγ̽��б�ע
    if (it != course_table.end())
    {
        Course& course = *it;
        rcourse.day = course.day;
        *it = course;
        cout << "������Ըÿγ̵ı�ע��" << endl;
        cin >> rcourse.memory;
        remind_course.push_back(rcourse);
        cout << "��ע�����" << endl;
        remind = 1;
    }
    else
        cout << "�޷��������ÿγ�";
    cout << endl;
}

// ���ֿγ���Ϣ����
void Course::arrangeVariousCourse()
{
    if (special > 0)
        arrangeCourse(special_course);
    if (remind > 0)
        arrangeCourse(remind_course);
    arrangeCourse(course_table);
};

// �γ���Ϣ����ģ��
void Course::arrangeCourse(vector<Course>& courseList)
{
    // �Կγ̰�ʱ���������
    sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
        if (a.day == b.day)
            return a.start_time < b.start_time;
        return a.day < b.day;
        });

    // ������ת��Ϊ�ܺ�
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

// �α����
void Course::showCourse()
{
    // �����ǿα���������ҽ�������ʱ��
    cout << endl;
    if (special > 0)
        showSpecialCourse();

    // ����α����
    showRegularCourse();

    // �γ̱�ע��������ҽ�������ʱ��
    if (remind > 0)
        showRemindCourse();
};

// �����ǿα����
void Course::showSpecialCourse()
{
    // ��������Ǳ�ͷ
    cout << "����������������������������������������ע�⡪����������������������������������" << endl;
    cout << "ʱ��\t����\t��ѧ¥\t����\t�γ�\t��ע" << endl;

    // ���������Ƕ�̬���������ݣ��������
    for (const auto& scourse : special_course)
    {
        cout << scourse.weekday << "\t" << scourse.start_time << "-" << scourse.end_time << "\t";
        cout << scourse.building << "\t" << scourse.room << "\t" << scourse.name << "\t";
        cout << scourse.sname << endl;
    }
}

// ����α����
void Course::showRegularCourse()
{
    // �����ͷ
    cout << "���������������������������������������α�������������������������������������" << endl;
    cout << "ʱ��\t����\t��ѧ¥\t����\t�γ�" << endl;

    // ������̬���������ݣ��������
    for (const auto& course : course_table)
    {
        cout << course.weekday << "\t" << course.start_time << "-" << course.end_time << "\t";
        cout << course.building << "\t" << course.room << "\t" << course.name << endl;
    }
}

// �γ̱�ע���
void Course::showRemindCourse()
{
    // �����ͷ
    cout << "�������������������������������������γ̱�ע������������������������������������" << endl;
    cout << "ʱ��\t�γ�\t��ע����" << endl;

    // �������
    for (const auto& rcourse : remind_course)
    {
        cout << rcourse.day << "\t" << rcourse.name << "\t" << rcourse.memory << endl;
    }
}
