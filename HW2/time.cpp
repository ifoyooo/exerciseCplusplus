#include <stdio.h>
#include <assert.h>


#define COLOR_NONE                    \033[0m
#define FONT_COLOR_RED             \033[0;31m
#define FONT_COLOR_BLUE            \033[1;34m
#define Assert(expr,type) if ((expr)==0) {printf("\033[0;31m%s!! \033[0m",Errors_string[type]);assert(0);}
#define Minimum 0
#define Maxsecond 60
#define Maxminite Maxsecond
#define Maxhour 24
const char Errors_string[3][10]={ "Herror","Merror","Serror"};
enum Errors_type {Herror,Merror,Serror};

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