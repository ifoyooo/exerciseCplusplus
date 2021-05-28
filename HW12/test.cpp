#include <iostream>
#include <fstream>
using namespace std;
//常常对于某种结构化数据，我们可以使用二进制的方式进行存储和读取。
void testread()
{
    int x=658763,y;
    ofstream out_file("myfile.dat",ios::out|ios::binary);
    out_file.write((char *)&x,sizeof(x)); 
    out_file.close();
    // ifstream in_file("myfile.dat",ios::in);//以文本方式读入就会按照文本去分析。
    ifstream in_file("myfile.dat",ios::in|ios::binary);//以二进制方式去读取。//两种不能够混用。
    in_file.read((char *)&y,sizeof(y)); //y=658763
    in_file.close();
    cout<<y;
}
void testinput()
{
    int a;
    int b;
    char c;
    cin>>a>>b;
    cout<<a<<endl<<b<<endl;
    // cin>>a>>c>>b;
    // cout<<a<<endl;
    // if (c=='-') cout<<-b; else cout<<b; cout <<endl;
}
int main()
{
    testread();
}