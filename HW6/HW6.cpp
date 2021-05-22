#include <stdio.h>
#include <assert.h>
#include <iostream>
using namespace std;

#define COLOR_NONE                    \033[0m
#define FONT_COLOR_RED             \033[0;31m
#define FONT_COLOR_BLUE            \033[1;34m
#define Assert(expr, type)                                     \
    if ((expr) == 0)                                           \
    {                                                          \
        printf("\033[0;31m%s!! \033[0m", Errors_string[type]); \
        assert(0);                                             \
    }
#define Minimum 0
#define Maxsecond 60
#define Maxminite Maxsecond
#define Maxhour 24
const char Errors_string[3][10] = {"Herror", "Merror", "Serror"};
enum Errors_type
{
    Herror,
    Merror,
    Serror
};

class Time
{
protected:
    int t_hour, t_minite, t_second;

    void simp()
    {
        while (t_second >= Maxsecond)
        {
            t_second -= Maxsecond;
            t_minite++;
        }
        while (t_minite >= Maxminite)
        {
            t_minite -= Maxminite;
            t_hour++;
        }
        while (t_hour >= Maxhour)
        {
            t_hour -= Maxhour;
        }
    }

public:
    Time(int h = 0, int m = 0, int s = 0)
    {
        set(h, m, s);
    }
    void set(int h, int m, int s)
    {
        Assert(h >= Minimum && h < Maxhour, Herror);
        Assert(m >= Minimum && m < Maxminite, Merror);
        Assert(s >= Minimum && s < Maxsecond, Serror);

        t_hour = h;
        t_minite = m;
        t_second = s;
    }
    void increment()
    {
        t_second++;
        simp();
    }
    void display() const 
    {
        printf("Time:  %02d:%02d:%02d\n", t_hour, t_minite, t_second);
    }

    bool equal(const Time &other_time) const 
    {
        return (t_hour == other_time.t_hour && t_minite == other_time.t_minite && t_second == other_time.t_second);
    }

    bool less_then(const Time &other_time) const 
    {
        return (t_hour < other_time.t_hour) ||
               (t_hour == other_time.t_hour &&
                t_minite < other_time.t_minite) ||
               (t_hour == other_time.t_hour &&
                t_minite == other_time.t_minite &&
                t_second < other_time.t_second);
    }
};
enum TimeZone
{
    W12 = -12,
    W11,
    W10,
    W9,
    W8,
    W7,
    W6,
    W5,
    W4,
    W3,
    W2,
    W1,
    GMT,
    E1,
    E2,
    E3,
    E4,
    E5,
    E6,
    E7,
    E8,
    E9,
    E10,
    E11,
    E12
};
class ExtTime : public Time
{
public:
    ExtTime() { tz = GMT; }
    ExtTime(int h, int m, int s, TimeZone t) : Time(h, m, s) { tz = t; }
    void set(int h, int m, int s, TimeZone t)
    {
        Time::set(h, m, s);
        tz = t;
    }
    void display() const
    {
        if (tz < 0)
        {
            cout << "西" << -int(tz) << "区\t";
        }
        else if (tz == 0)
        {
            cout<<"格林威治标准时间 (GMT) \t";
        }
        else 
        {
            cout <<"东"<<int(tz)<<"区\t";
        }
        Time::display();
    }
    bool equal(const ExtTime &other_time)const 
    {
        Time t((t_hour+other_time.tz-tz+24)%24,t_minite,t_second);
        return t.equal(other_time);
    }
    bool less_than(const ExtTime &other_time) const 
    {
        Time t((t_hour+other_time.tz-tz+24)%24,t_minite,t_second);
        return t.less_then(other_time);
    }
private:
    TimeZone tz;
};

int main()
{
    ExtTime t(1,1,1,W1);
    ExtTime q(2,2,2,W1);
    if (t.less_than(q))
    {
        cout << "YEs!"<<endl;
    }
    else 
    {
        cout <<"fault"<<endl;
    }
}
