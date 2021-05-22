#include <iostream>
using namespace std;
class Object
{
    public:
    Object()
    {
        cout<<"obj";
    }
    ~Object()
    {
        cout<<"disobj ";
    }
};
class Base : public Object
{
    public:
    Base()
    {
        cout<<"base";
    }
    ~Base()
    {
        cout<<"disbase ";
    }
};
class Derived1 : virtual public Base
{
    public:
    Derived1()
    {
        cout<<"d1";
    }
    ~Derived1()
    {
        cout<<"disd1 ";
    }
};
class Derived2 : virtual public Base
{
private:
    Object o;
    public :
    Derived2()
    {
        cout<<"d2";
    }
    ~Derived2()
    {
        cout<<"disd2 ";
    }
};
class Mid : public Derived1, public Derived2
{
    public:
    Mid()
    {
        cout<<"mid";
    }
    ~Mid()
    {
        cout<<"dismid ";
    }
};
class Final : public Mid, public Object, public Derived1
{
private:
    Derived2 d2;
public:
    Final()
    {
        cout<<"final\n";
    }
    ~Final()
    {
        cout<<"disfinal ";
    }
};
//为什么是这样构造顺序？
//obj base d1 obj d2 mid obj d1 obj base obj d2 final

int main()
{
    {
        Final f;
    }
    return 0;
}