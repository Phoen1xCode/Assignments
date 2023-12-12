#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

// �����������
class Assignment
{
private:
    string name;             // ��ҵ����
    string subject;          // ��Ŀ
    string content;          // ��ҵ����
    string type;             // ��ҵ����
    string ddl;              // ��ֹ����
    bool completed;          // �Ƿ����
    bool contentPrepared;    // ����׼����ɱ�־
    bool presentationPrepared;  // չʾ��̨׼����ɱ�־

public:
    // ���캯��
    Assignment(const string& name, const string& subject, const string& content, const string& type, const string& ddl)
        : name(name), subject(subject), content(content), type(type), ddl(ddl), completed(false),
        contentPrepared(false), presentationPrepared(false) {}

    // ��ȡ��ҵ����
    string getName() const
    {
        return name;
    }

    // ��ȡ��Ŀ��Ϣ
    string getSubject() const
    {
        return subject;
    }

    // ��ȡ������Ϣ
    string getContent() const
    {
        return content;
    }

    // ��ȡ��ҵ����
    string getType() const
    {
        return type;
    }

    // ��ȡ��ҵddl
    string getDdl() const
    {
        return ddl;
    }

    // ��ҵ������
    bool isCompleted() const
    {
        return completed;
    }

    // �����ҵ���
    void markCompleted()
    {
        completed = true;
    }

    // �������׼�����
    void markContentPrepared()
    {
        contentPrepared = true;
    }

    // ���չʾ��̨׼�����
    void markPresentationPrepared()
    {
        presentationPrepared = true;
    }
};

// �������ܺ���
class HomeworkManager
{
private:
    // ��vector�洢��ҵ�б�
    vector<Assignment> assignments;
public:
    // �������ܶ�Ӧ����
    void addAssignment();
    bool validateDate(const string& date);
    void displayAssignmentList();
    void markAssignmentCompleted();
    void deleteAssignment();
    // ����ΪԤ�������
private:
    // �Ƚ���ҵ�Ľ�ֹ����
    static bool compareAssignmentsByDdl(const Assignment& a1, const Assignment& a2)
    {
        tm tm1 = parseDdlString(a1.getDdl());
        tm tm2 = parseDdlString(a2.getDdl());
        return mktime(&tm1) < mktime(&tm2);
    }

    // ���������ַ���Ϊtm�ṹ
    static tm parseDdlString(const string& ddlString)
    {
        tm tm = {};
        istringstream ss(ddlString);
        ss >> get_time(&tm, "%Y-%m-%d");
        return tm;
    }

    // ����ֹ����������ҵ�б�
    void sortAssignmentsByDdl()
    {
        sort(assignments.begin(), assignments.end(), compareAssignmentsByDdl);
    }
};
