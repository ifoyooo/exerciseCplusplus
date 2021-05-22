#include <iostream>
using namespace std;

#define MAX_SECOND 60
#define MAX_MINUTE 60
#define MAXhour 24
#define MAXmonth 12

#define IS_LMONTH(month) (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)

class Date
{
private:
    int year, month, day;
    friend class Datetime;

public:
    Date(int year, int month, int day)
    {
        this->year = year;
        this->month = month;
        this->day = day;
    }
};
class Time
{
private:
    int hour, minute, second;
    friend class Datetime;
public:
    Time(int hour, int minute, int second)
    {
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }
};
class Datetime
{
private:
    Date date;
    Time time;
    int maxday;
    bool is_leap_yaer() const
    {
        return ((date.year % 4 == 0) && (date.year % 100 != 0)) || (date.year % 400 == 0);
    }
    void set_maxday()
    {
        if (IS_LMONTH(date.month))
        {
            maxday = 31;
        }
        else if (date.month == 2)
        {
            if (is_leap_yaer())
                maxday = 29;
            else
                maxday = 28;
        }
        else
        {
            maxday = 30;
        }
    }
    void simp()
    {
        while (time.second >= MAX_SECOND)
        {
            time.second -= MAX_SECOND;
            time.minute += 1;
        }
        while (time.second < 0)
        {
            time.second += MAX_SECOND;
            time.minute -= 1;
        }
        while (time.minute >= MAX_MINUTE)
        {
            time.minute -= MAX_MINUTE;
            time.hour += 1;
        }
        while (time.minute < 0)
        {
            time.minute += MAX_MINUTE;
            time.hour -= 1;
        }
        while (time.hour >= MAXhour)
        {
            time.hour -= MAXhour;
            date.day += 1;
        }
        while (time.hour < 0)
        {
            time.hour += MAXhour;
            date.day -= 1;
        }
        while (date.day > maxday)
        {
            date.day -= maxday;
            date.month += 1;
            set_maxday();
        }
        while (date.day <= 0)
        {
            date.day += maxday;
            date.month -= 1;
            set_maxday();
        }
        while (date.month > MAXmonth)
        {
            date.month -= MAXmonth;
            date.year += 1;
        }
        while (date.month <= 0)
        {
            date.month += MAXmonth;
            date.year -= 1;
        }
    }

public:
    std::string to_string() const
    {
        char tmp[256];
        printf("%04d-%02d-%02d|%02d:%02d:%02d\n", date.year, date.month, date.day, time.hour, time.minute, time.second);
        sscanf(tmp, "%04d-%02d-%02d|%02d:%02d:%02d\n", date.year, date.month, date.day, time.hour, time.minute, time.second);
        string ans(tmp);
        return ans;
    }
    Datetime(const Date &date, const Time &time) : date(date), time(time)
    {
        set_maxday();
        simp();
    }
    Datetime operator+(int sec)
    {

        //如果你是在函数中创建了一个临时对象，你是不能够返回它的引用或者指针的。因为它会被清理掉。一定是返回的值。
        //但是如果返回的是参数当中传进来的引用，那么可以直接返回引用。如=的操作符重载。
        Datetime temp(*this);
        temp.time.second += sec;
        temp.simp();
        return temp;
    }
    Datetime operator-(int sec)
    {
        Datetime temp(*this);
        temp.time.second-=sec;
        temp.simp();
        return temp;
    }
    bool operator<(const Datetime &dt)
    {
        if (date.year<dt.date.year) return true;
        else if (date.year>dt.date.year) return false;
        else
        {
            if (date.month<dt.date.month) return true;
            else if (date.month>dt.date.month) return false;
            else
            {
                if (date.day<dt.date.day) return true;
                else if (date.day>dt.date.day) return false;
                else
                {
                    if (time.hour<dt.time.hour) return true;
                    else if (time.hour>dt.time.hour) return false;
                    else 
                    {
                        if (time.minute<dt.time.minute) return true;
                        else if(time.minute>dt.time.minute)return false;
                        else
                        {
                            if (time.second<dt.time.second) return true;
                            else return false;
                        }
                    }
                }
            }
        }
    }
    bool operator==(const Datetime &dt)
    {
        return date.year==dt.date.year && date.month==dt.date.month && date.day==dt.date.day && time.hour==dt.time.hour && time.minute==dt.time.minute && time.second==dt.time.second;
    }
    double operator-(const Datetime& dt)
    {
        int ans=0;
        if (*this<dt)
        {
            while (((*this)==dt)==0)
            {
                (*this)++;
                ans--;
            }
            return ans;
        }
        else if (*this==dt)
        {
            return ans;
        }
        else
        {
            while (((*this)==dt)==0)
            {
                (*this)--;
                ans++;
            } 
            return ans;
        }
    }

    void operator++()
    {
        time.second++;
        simp();
    }
    void operator++(int)
    {
        time.second++;
        simp();
    }
    void operator--()
    {
        time.second--;
        simp();
    }
    void operator--(int)
    {
        time.second--;
        simp();
    }


};

int main()
{
    Date date1(2001, 1, 26);
    Time time1(0, 0, 0);
    Datetime datetime1(date1, time1);
    datetime1.to_string();
    datetime1--;
    datetime1.to_string();
    Datetime datetime2=datetime1+1;
    datetime2.to_string();
    cout<<datetime2-datetime1<<endl;
    for (int i=0;i<10000;i++)
    {
        datetime1++;
        datetime1.to_string();
    }
}