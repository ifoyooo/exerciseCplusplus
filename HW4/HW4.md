# Assignment 4

**Fuyun Wang**

**191300051**

## 一

### 1.1 简述Demeter法则的基本思想；过度使用Demeter法则会带 来什么问题

Demeter法则的基本思想：

- 每个单元对于其他的单元只能拥有有限的知识：只是与当前单元紧密联系的单元
- 每个单元只能和它的朋友交谈：不能和陌生单元交谈
- 只和自己直接的朋友交谈

一个类的成员函数除了能够访问自身类结构的直接子结构外，不能够以任何方式依赖于其它类的结构。

过度使用Demeter法则的问题：

过度使用迪米特法则，也会造成系统的不同模块之间的通信效率降低，使系统的不同模块之间不容易协调等缺点。同时，因为迪米特法则要求类与类之间尽量不直接通信，如果类之间需要通信就通过第三方转发的方式，这就直接导致了系统中存在大量的中介类，这些类存在的唯一原因是为了传递类与类之间的相互调用关系，这就毫无疑问的增加了系统的复杂度。

### 1.2  简述为什么要对操作符重载进行重载；操作符重载会带来什么问题。

为什么？

以负数的实现中，直接使用函数命名的方式不符合平时书写的习惯，C++允许对已有的操作符进行重载，使得他们能够对自定义类型的对象进行操作。

与函数名重载一样，操作符重载也是实现多态性的一种语言机制。

- 简单、方便，比起封装一个函数，使用operator比较形象直观
- 可以提高代码的可读性
- 为了处理自定义类型和内置类型之间的运算

会带来什么问题？

- 不合适的操作符重载会造成运算的混乱或者错误。
- 可能会对原有的定义产生覆盖或者干扰

注意点：

1. 不可臆造运算符。
2.  运算符原有操作数的个数、优先级和结合性不能改变。
3. 操作数中至少一个是自定义类型。
4.  保持重载运算符的自然含义。

### 1.3  简述操作符重载的两种形式；这两种形式有什么区别。

两种形式

- 作为一个类的非静态的成员函数
- 作为一个全局（友元函数）

区别

一般情况下操作符既可以作为全局操作符也可以当作成员函数进行重载。在有些情况下，操作符则只能作为全局函数或者只能作为类的成员函数进行重载。

以复数的加减为例（当double类型的数据与自定义类型的数据进行加减时），只能够使用全局函数重载而不能够使用类的成员函数重载。

一般情况下，对于单目运算符，我们常常都是重载为成员函数。

对于双目操作符

对于双目运算符:

a.当重载为成员函数时，会隐含一个this指针；当重载为友元函数时，将不存在隐含的this指针，需要在参数列表中显示地添加操作数。
b.当重载为成员函数时，只允许右参数的隐式转换；当重载为友元函数时，能够接受左参数和右参数的隐式转换。

## 二

```c++
//Timer.cpp
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
```

