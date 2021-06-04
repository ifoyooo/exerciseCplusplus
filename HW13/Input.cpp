#include <iostream>
#include <string>
using namespace std;
int divide(int a,int b)
{
    if (b==0) throw "overflow";
    return a/b;
}
void f()
{
    int a,b;
    while (true)
    {
        bool flag=true;
        try
        {
            cout<<"请输入两个数：";
            cin>>a>>b;
            int r=divide(a,b);
            cout<<a<<"除以"<<b<<"的商为:"<<r<<endl;

        }
        catch(const char *)
        {
            cout<<"被除数不能为0，请重新输入\n";
            flag=false;
        }
        if (flag)
        {
            break;
        }
        
    }
}
int main()
{
    try
    {
        f();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}