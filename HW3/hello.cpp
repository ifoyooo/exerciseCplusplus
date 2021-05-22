#include <iostream>
#include <cstring>
using namespace std;
class Merchandise
{
    static int MerchandiseCnt;
    char *name;

public:
    Merchandise(const char *_name);
    ~Merchandise();
    char *get_name() const;
    void set_name(const char *_name); //set_name const 去掉！
};
Merchandise::Merchandise(const char *_name)
{
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
    MerchandiseCnt++;
}
Merchandise::~Merchandise()
{
    delete name;
    name = nullptr;
}
char *Merchandise::get_name() const
{
    return name;
}
void Merchandise::set_name(const char *_name)
{
    delete name;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}
int main()
{
    Merchandise m1("phone");
    Merchandise m2(m1);
    return 0;
}