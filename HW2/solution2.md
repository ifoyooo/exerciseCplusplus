# 高级程序设计 HW2

**STUNAME: 汪福运**

**STUID:191300051**

## T1

### 1.1构造函数的成员初始化列表的作用

一方面，对于常量和引用数据的成员，即不能够在说明他们时进行初始化，也不能够在构造函数中对他们赋值。只能够在成员初始化列表中对他们进行初始化。

另一方面，在创建包含成员对象的对象时，除了会自动调用本身类的构造函数外，还会自动调用成员对象的构造函数。而通常情况下，自动调用的是成员对象的默认构造函数。如果要调用成员对象类的非默认构造函数，需要在构造函数的成员初始化列中显示的指出。



### 1.2  C++的成员对象是什么？ 当创建包含成员对象的类的对象时，构造函数的调用顺序是什么样的？

（1）成员对象是一个类的数据成员，它是另一个类的对象。



（2）

先执行成员对象类的构造函数，在执行本对象类的构造函数。

如果含有多个成员对象，则按照它们在本类中的说明顺序执行。







## T2 代码编程题

```c++
#include <stdio.h>
#include <assert.h>

//输出宏
#define COLOR_NONE                    \033[0m
#define FONT_COLOR_RED             \033[0;31m
#define FONT_COLOR_BLUE            \033[1;34m
#define Assert(expr,type) if ((expr)==0) {printf("\033[0;31m%s!! \033[0m",Errors_string[type]);assert(0);}


//常数宏
#define Minimum 0
#define Maxsecond 60
#define Maxminite Maxsecond
#define Maxhour 24


//全局常量
const char Errors_string[3][10]={ "Herror","Merror","Serror"};
enum Errors_type {Herror,Merror,Serror};



//类的定义
class Time
{
    private:
    int t_hour,t_minite,t_second;

    void simp()
    {
        while (t_second>=Maxsecond)
        {
            t_second-=Maxsecond;
            t_minite++;
        }
        while (t_minite>=Maxminite)
        {
            t_minite-=Maxminite;
            t_hour++;
        }
        while (t_hour>=Maxhour)
        {
            t_hour-=Maxhour;

        }
    }
    public:
    Time(int h=0,int m=0,int s=0)
    {
        set(h,m,s);
    }
    void set(int h,int m,int s)
    {
        Assert(h>=Minimum&&h<Maxhour,Herror);
        Assert(m>=Minimum&&m<Maxminite,Merror);
        Assert(s>=Minimum&&s<Maxsecond,Serror);

        t_hour=h;
        t_minite=m;
        t_second=s;
    }
    void increment()
    {
        t_second++;
        simp();

    }
    void display()
    {
        printf("Time:  %02d:%02d:%02d\n",t_hour,t_minite,t_second);
    }

    bool equal(Time &other_time)
    {
        return (t_hour==other_time.t_hour&&t_minite==other_time.t_minite&&t_second==other_time.t_second);
    }

    bool less_then(Time &other_time)
    {
        return (t_hour<other_time.t_hour) || \
        (t_hour==other_time.t_hour && \
        t_minite<other_time.t_minite)||\
        (t_hour==other_time.t_hour &&\
        t_minite==other_time.t_minite&&\
        t_second<other_time.t_second);
    }
};





//正常测试
void test1()
{
    Time a;
    Time b(0,2,10);
    a.display();
    b.display();
    printf("a<=b?%d\n",a.less_then(b));
    for (int i=0;i<=(int)100000;i++)
    {
        a.display();
        a.increment();
    }
    a.display();
    b.display();
    printf("a<=b?%d\n",a.less_then(b));
}


//异常测试
void test2()
{
    Time a(-1,2,100);
    // Time b(24,0,0);
    // Time a;
    // a.set(1,61,1);
    // a.set(1,50,-1);
}
int main()
{
    // test1();
    test2();

}
```

