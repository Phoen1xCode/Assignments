#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

// 管理各个变量
class Assignment
{
private:
    string name;             // 作业名称
    string subject;          // 科目
    string content;          // 作业内容
    string type;             // 作业类型
    string ddl;              // 截止日期
    bool completed;          // 是否完成
    bool contentPrepared;    // 内容准备完成标志
    bool presentationPrepared;  // 展示上台准备完成标志

public:
    // 构造函数
    Assignment(const string& name, const string& subject, const string& content, const string& type, const string& ddl)
        : name(name), subject(subject), content(content), type(type), ddl(ddl), completed(false),
        contentPrepared(false), presentationPrepared(false) {}

    // 获取作业名称
    string getName() const
    {
        return name;
    }

    // 获取科目信息
    string getSubject() const
    {
        return subject;
    }

    // 获取内容信息
    string getContent() const
    {
        return content;
    }

    // 获取作业类型
    string getType() const
    {
        return type;
    }

    // 获取作业ddl
    string getDdl() const
    {
        return ddl;
    }

    // 作业完成情况
    bool isCompleted() const
    {
        return completed;
    }

    // 标记作业完成
    void markCompleted()
    {
        completed = true;
    }

    // 标记内容准备完成
    void markContentPrepared()
    {
        contentPrepared = true;
    }

    // 标记展示上台准备完成
    void markPresentationPrepared()
    {
        presentationPrepared = true;
    }
};

// 各个功能函数
class HomeworkManager
{
private:
    // 用vector存储作业列表
    vector<Assignment> assignments;
public:
    // 各个功能对应函数
    void addAssignment();
    bool validateDate(const string& date);
    void displayAssignmentList();
    void markAssignmentCompleted();
    void deleteAssignment();
    // 以下为预处理操作
private:
    // 比较作业的截止日期
    static bool compareAssignmentsByDdl(const Assignment& a1, const Assignment& a2)
    {
        tm tm1 = parseDdlString(a1.getDdl());
        tm tm2 = parseDdlString(a2.getDdl());
        return mktime(&tm1) < mktime(&tm2);
    }

    // 解析日期字符串为tm结构
    static tm parseDdlString(const string& ddlString)
    {
        tm tm = {};
        istringstream ss(ddlString);
        ss >> get_time(&tm, "%Y-%m-%d");
        return tm;
    }

    // 按截止日期排序作业列表
    void sortAssignmentsByDdl()
    {
        sort(assignments.begin(), assignments.end(), compareAssignmentsByDdl);
    }
};
