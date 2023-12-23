#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "../include/date.h"

namespace finance {
    static const int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    static const int arr2[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
    //构造函数
    Date::Date(int y, int m, int d, int h, int min) :year(y), month(m), day(d), hour(h), minute(min) {}

    int Date::code1() {
        return year * 100 + month;
    }
    int Date::code2() {
        return day * 10000 + hour * 100 + minute;
    }

    //展示详细的日期，基本只用于账目展示时使用
    void Date::date_speshow() {
        std::ostringstream oss;
        oss << year << "."
            << std::setw(2) << std::setfill('0') << month << "."
            << std::setw(2) << std::setfill('0') << day << "  "
            << std::setw(2) << std::setfill('0') << hour << ":"
            << std::setw(2) << std::setfill('0') << minute;
        std::cout << oss.str() << std::endl;
    }
    //展现大概日期，用于统计
    void Date::date_show() {
        std::cout << year << "." << std::setw(2) << std::setfill('0') << month << "." << std::setw(2) << std::setfill('0') << day << std::endl;
    }

    void Date::day_reset(int d) {
        this->day = d;
    }

    //析构函数
    Date::~Date() {}
    //判断是否是闰年，辅助判断输入日期是否非法
    bool Date::Isleapyear(int y) {                           //判断输入的年份是否是闰年
        if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) {
            return true;
        }
        else
            return false;
    }
    //年月日的获取
    int Date::getyear() {
        return year;
    }
    int Date::getmonth() {
        return month;
    }
    int Date::getday() {
        return day;
    }
    int Date::gethour() {
        return hour;
    }
    int Date::getminute() {
        return minute;
    }

    //判断输入的具体时间是否合法
    bool Date::IsTimeLegal() {
        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            return false;
        }
        return true;
    }

    //输入日期，判断日期是否合法
    bool Date::IsDateLegal() {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false; // 年、月、日必须大于等于1
        }
        int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (Isleapyear(year)) {
            daysInMonth[2] = 29; // 闰年二月有29天
        }
        if (day > daysInMonth[month]) {
            return false; // 输入的日期大于该月最大天数
        }
        return true; // 日期合法
    }

    int Date::get_days_inmonth(int year, int month) {
        static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int days = daysInMonth[month];
        if (month == 2 && Isleapyear(year)) {
            days = 29;
        }
        return days;
    }


    //计算两具体日期之间相隔的天数，主要针对信用卡负债是日利息的计算
    int Date::operator-(const Date& d) {
        // 将两个日期转换为从公元1年1月1日开始的天数
        int days1 = countDaysFromStart(year, month, day);
        int days2 = countDaysFromStart(d.year, d.month, d.day);

        // 返回两个天数之间的差值
        return days1 - days2;
    }

    int Date::countDaysFromStart(int year, int month, int day) {
        static const int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int days = 0;
        // 加上所有完整年份的天数
        for (int y = 1; y < year; ++y) {
            days += (Isleapyear(y) ? 366 : 365);
        }
        // 加上当前年份中完整月份的天数
        for (int m = 1; m < month; ++m) {
            days += daysInMonth[m];
            if (m == 2 && Isleapyear(year)) {
                days += 1; // 闰年二月多一天
            }
        }
        // 加上当前月份中的天数
        days += day;
        return days;
    }

    Date Date::operator-(int d) {
        Date result = *this;  // 创建一个新的日期对象并复制当前日期
        result.day -= d;

        while (result.day <= 0) {
            result.month--;
            if (result.month <= 0) {
                result.year--;
                result.month = 12;
            }
            int daysbefore = get_days_inmonth(result.year, result.month);
            result.day += daysbefore;
        }
        return result;
    }


    bool Date::operator ==(const Date& d1)const {
        if (d1.day == 1) {
            if (d1.year == year && d1.month == month)
                return true;                        //d1.day=1时，意味着按年与月进行比较
            else                                     //但是就算是目的是比日期，也能够实现向下兼容
                return false;
        }
        else if (d1.day == 28) {                          //d1.day=28时，意味着按年进行比较
            if (d1.month == 1) {                        //当然也兼容了日期比较
                if (d1.year == year)
                    return true;
                else
                    return false;
            }
            else {
                if (d1.year == year && d1.month == month)   //正常按照年月日进行比较
                    return true;
                else
                    return false;
            }
        }
        else {
            if (year == d1.year && month == d1.month && day == d1.day)
                return true;
            else
                return false;
        }
    }

    bool Date::operator!=(const Date& d1)const {
        return !(*this == d1);
    }

    void Date::operator =(Date& d1) {
        year = d1.year;
        month = d1.month;
        day = d1.day;
    }

    bool Date::operator <(const Date& d1)const {
        if (year < d1.year)
            return true;
        else if (year == d1.year && month < d1.month)
            return true;
        else if (year == d1.year && month == d1.month && day < d1.day)
            return true;
        else
            return false;
    }

    bool Date::operator >(const Date& d1)const {
        if (year > d1.year)
            return true;
        else if (year == d1.year && month > d1.month)
            return true;
        else if (year == d1.year && month > d1.month && day > d1.day)
            return true;
        else
            return false;
    }
}