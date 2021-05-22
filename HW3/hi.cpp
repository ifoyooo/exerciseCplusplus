#include <iostream>
#include <string.h>
using namespace std;
class Merchandise
{
    static int MerchandiseCnt;
    char *name;

    public:
    Merchandise(const char *_name);
    Merchandise(const Merchandise& m);
    ~Merchandise();
    char *get_name()const;
    void set_name(const char *_name);
    //删除 const.
    //静态成员没有初始化的定义，这个取值的时候要使用数据类型 类名的具体定义。
    //没有自定依靠构造函数。
};
int Merchandise::MerchandiseCnt=0;
Merchandise::Merchandise(const char *_name)
{
    name=new char[strlen(_name)+1];
    strcpy(name,_name);
    MerchandiseCnt++;

}
Merchandise::Merchandise(const Merchandise& m)
{
    name=new char[strlen(m.get_name())+1];
    strcpy(name,m.get_name());
    MerchandiseCnt++;
}
Merchandise::~Merchandise()
{
    delete name;
    name=nullptr;
}
char *Merchandise::get_name() const
{
    return name;
}
void Merchandise::set_name(const char *_name)
{
    delete name;
    name =new char [strlen(_name)+1];
    strcpy(name,_name);
}
int main()
{
    Merchandise m1("phone");
    Merchandise m2(m1);
    return 0;
}