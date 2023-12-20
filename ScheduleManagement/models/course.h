#include <vector>
#include <string>

using namespace std;

// ����Course��
class Course
{
private:
    // �����������
    int day;
    string weekday;
    int start_time;
    int end_time;
    string name;
    string building;
    int room;
    string sname;
    string memory;

    // ���徲̬����
    static int special;
    static int remind;

public:
    // ���������������躯��
    void inputRegularCourse();
    void inputCourse(Course& course, vector<Course>& courseList);
    void modifyVariousCourse();
    void modifyCourse(vector<Course>& courseList);
    void deleteCourse();
    void inputSpecialCourse();
    void remindCourse();
    void arrangeVariousCourse();
    void arrangeCourse(vector<Course>& courseList);
    void showCourse();
    void showSpecialCourse();
    void showRegularCourse();
    void showRemindCourse();
};