#include <vector>
#include <string>

using namespace std;

// 定义Course类
class Course
{
private:
    // 定义所需变量
    int day;
    string weekday;
    int start_time;
    int end_time;
    string name;
    string building;
    int room;
    string sname;
    string memory;

    // 定义静态数据
    static int special;
    static int remind;

public:
    // 声明各个功能所需函数
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