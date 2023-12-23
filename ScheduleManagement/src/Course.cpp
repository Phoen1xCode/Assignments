#include "../include/course.h"
#include <algorithm>
#include <iostream>
#include <vector>



namespace DailylifeAssistant
{
    // ��������״̬ת��
    int Course::special = 0;
    int Course::remind = 0;

    // ¼����ͨ�γ�
    void Course::inputRegularCourse()
    {
        Course course;
        inputCourse(course, course_table);
    }

    // ¼��γ���Ϣģ��
    void Course::inputCourse(Course& course, std::vector<Course>& courseList)
    {

        std::cout << "�������Ͽ�����Ϊ�ܼ���1-7����";
        std::cin >> course.day;
        while (std::cin.fail() || course.day > 7 || course.day < 1)
        {
            std::cout << "���������������������룺";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.day;
        }
        std::cout << "������γ̿�ʼ�ڵڼ��ڣ�1-13����";
        std::cin >> course.start_time;
        while (std::cin.fail() || course.start_time < 1 || course.start_time > 13)
        {
            std::cout << "���������������������룺";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.start_time;
        }
        std::cout << "������γ̽����ڵڼ��ڣ�1-13����";
        std::cin >> course.end_time;
        while (std::cin.fail() || course.end_time < 1 || course.end_time > 13 || course.end_time < course.start_time)
        {
            std::cout << "���������������������룺";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.end_time;
        }
        std::cout << "������γ����ƣ�";
        std::cin >> course.name;
        std::cout << "�������ѧ¥��";
        std::cin >> course.building;
        std::cout << "��������Һţ�";
        std::cin >> course.room;
        while (std::cin.fail())
        {
            std::cout << "���������������������룺";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> course.room;
        }

        courseList.push_back(course);
        std::cout << "�γ�����ӣ�" << std::endl;
    }

    // �޸ĸ��ֿγ���Ϣ
    void Course::modifyVariousCourse()
    {
        while (true)
        {
            int mchoice;
            std::cout << std::endl;
            std::cout << "��ѡ�������" << std::endl;
            std::cout << "1.����γ�" << std::endl;
            std::cout << "2.����γ�" << std::endl;
            std::cout << "3.�γ̱�ע" << std::endl;
            std::cout << "4.�˳�����" << std::endl;
            std::cout << "���������޸Ŀγ���Ϣ�����";
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
                        std::cout << "��δ¼���������ѿγ�" << std::endl;
                        return modifyVariousCourse();
                    }
                    break;
                case 3:
                    if (remind > 0)
                        modifyCourse(remind_course);
                    else
                    {
                        std::cout << "��δ����γ̱�ע" << std::endl;
                        return modifyVariousCourse();
                    }
                    break;
                case 4:
                    return;
                default:
                    std::cout << "��������" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
            }
        }
    }

    // �޸Ŀγ���Ϣģ��
    void Course::modifyCourse(std::vector<Course>& courseList)
    {
        // ����γ�����
        std::string name;
        std::cout << "������Ҫ�޸ĵĿγ����ƣ�";
        std::cin >> name;
        std::cout << std::endl;

        // ������Ӧ�γ�
        auto it = std::find_if(courseList.begin(), courseList.end(), [&](const Course& course) {
            return course.name == name;
        });

        if (it != courseList.end())
        {
            Course& course = *it;
            while (true)
            {
                std::cout << "��ѡ�������" << std::endl;
                std::cout << "1. �޸�ʱ��" << std::endl;
                std::cout << "2. �޸ĵص�" << std::endl;
                std::cout << "3. �˳�" << std::endl;
                std::cout << "������ѡ�";
                int choice;
                std::cin >> choice;

                // ѡ����
                switch (choice) {
                    case 1:
                        std::cout << "��������ĺ�����ڣ�1-7����";
                        std::cin >> course.day;
                        std::cout << "��������ĺ�Ŀο�ʼ�ڵڼ��ڣ�1-13����";
                        std::cin >> course.start_time;
                        std::cout << "��������ĺ�Ŀν����ڵڼ��ڣ�1-13����";
                        std::cin >> course.end_time;
                        std::cout << "�޸ĳɹ���" << std::endl;
                        break;
                    case 2:
                        std::cout << "��������ĺ�Ľ�ѧ¥��";
                        std::cin >> course.building;
                        std::cout << "��������ĺ�Ľ��Һţ�";
                        std::cin >> course.room;
                        std::cout << "�޸ĳɹ���" << std::endl;
                        break;
                    case 3:
                        return;
                    default:
                        std::cout << "��������" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                }
            }
        }
        else
        {
            std::cout << "δ�ҵ���Ӧ�γ�" << std::endl;
        }
    }

    // ɾ���γ�
    void Course::deleteCourse()
    {
        std::string name;
        std::cout << "������Ҫɾ���Ŀγ����ƣ�";
        std::cin >> name;
        std::cout << std::endl;

        // ��course_table��ɾ����Ӧ�γ�
        auto it = std::find_if(course_table.begin(), course_table.end(), [&](const Course& course) {
            return course.name == name;
        });

        if (it != course_table.end())
        {
            course_table.erase(it);
            std::cout << "�γ���ɾ��" << std::endl;
        }
        else
        {
            std::cout << "δ�ҵ���Ӧ�γ�" << std::endl;
        }
    }

    // ¼������γ�
    void Course::inputSpecialCourse()
    {
        Course scourse;
        std::cout << "�����������������������ǵĿγ���Ϣ������������" << std::endl;
        std::cout << "������������Ϣ��";
        std::cin >> scourse.sname;

        // ��������γ���Ϣģ��
        inputCourse(scourse, special_course);
        special = 1;
    }

    // ¼��γ̱�ע
    void Course::remindCourse()
    {
        Course rcourse;
        std::cout << "���������뱸ע�ĳ���γ�����";
        std::cin >> rcourse.name;

        // ������Ӧ�γ�
        auto it = std::find_if(course_table.begin(), course_table.end(), [&](const Course& course) {
            return course.name == rcourse.name;
        });

        // �Կγ̽��б�ע
        if (it != course_table.end())
        {
            Course& course = *it;
            rcourse.day = course.day;
            *it = course;
            std::cout << "������Ըÿγ̵ı�ע��" << std::endl;
            std::cin >> rcourse.memory;
            remind_course.push_back(rcourse);
            std::cout << "��ע�����" << std::endl;
            remind = 1;
        }
        else
            std::cout << "�޷��������ÿγ�";
        std::cout << std::endl;
    }

    // ���ֿγ���Ϣ����
    void Course::arrangeVariousCourse()
    {
        if (special > 0)
            arrangeCourse(special_course);
        if (remind > 0)
            arrangeCourse(remind_course);
        arrangeCourse(course_table);
    }

    // �γ���Ϣ����ģ��
    void Course::arrangeCourse(std::vector<Course>& courseList)
    {
        // �Կγ̰�ʱ���������
        std::sort(courseList.begin(), courseList.end(), [](const Course& a, const Course& b) {
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
        std::cout << std::endl;
        if (special > 0)
            showSpecialCourse();

        // ����α����
        showRegularCourse();

        // �γ̱�ע��������ҽ�������ʱ��
        if (remind > 0)
            showRemindCourse();
    }

    // �����ǿα����
    void Course::showSpecialCourse()
    {
        // ��������Ǳ�ͷ
        std::cout << "����������������������������������������ע�⡪����������������������������������" << std::endl;
        std::cout << "ʱ��\t����\t��ѧ¥\t����\t�γ�\t��ע" << std::endl;

        // ���������Ƕ�̬���������ݣ��������
        for (const auto& scourse : special_course)
        {
            std::cout << scourse.weekday << "\t" << scourse.start_time << "-" << scourse.end_time << "\t";
            std::cout << scourse.building << "\t" << scourse.room << "\t" << scourse.name << "\t";
            std::cout << scourse.sname << std::endl;
        }
    }

    // ����α����
    void Course::showRegularCourse()
    {
        // �����ͷ
        std::cout << "���������������������������������������α�������������������������������������" << std::endl;
        std::cout << "ʱ��\t����\t��ѧ¥\t����\t�γ�" << std::endl;

        // ������̬���������ݣ��������
        for (const auto& course : course_table)
        {
            std::cout << course.weekday << "\t" << course.start_time << "-" << course.end_time << "\t";
            std::cout << course.building << "\t" << course.room << "\t" << course.name << std::endl;
        }
    }

    // �γ̱�ע���
    void Course::showRemindCourse()
    {
        // �����ͷ
        std::cout << "�������������������������������������γ̱�ע������������������������������������" << std::endl;
        std::cout << "ʱ��\t�γ�\t��ע����" << std::endl;

        // �������
        for (const auto& rcourse : remind_course)
        {
            std::cout << rcourse.day << "\t" << rcourse.name << "\t" << rcourse.memory << std::endl;
        }
    }
}
