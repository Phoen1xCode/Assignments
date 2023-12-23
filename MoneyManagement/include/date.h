#pragma once
namespace finance {
    class Date {
    private:
        int year;
        int month;
        int day;
        int hour;
        int minute;
    public:
        Date(int y, int m, int d, int h = 0, int min = 0);
        ~Date();
        int code1();
        int code2();
        void date_speshow();    //具体时间展示
        void date_show();       //日期展示
        void day_reset(int d);
        int getyear();
        int getmonth();
        int getday();
        int gethour();
        int getminute();
        bool Isleapyear(int y);
        bool IsDateLegal();
        bool IsTimeLegal();
        int get_days_inmonth(int year, int month);
        int countDaysFromStart(int year, int month, int day);
        int operator-(const Date& d1);     //某日前多少天的日期
        Date operator-(int d);        //两日期间有多少天
        void operator=(Date& d1);    //复制
        bool operator ==(const Date& d1)const;   //比较
        bool operator !=(const Date& d1)const;
        bool operator <(const Date& d1)const;    //后大前小
        bool operator >(const Date& d1)const;
    };
}