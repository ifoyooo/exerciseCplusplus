#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//直接以int型保存
void testint()
{
    //写入//将1到100的二进制都存在seek.data当中。
    ofstream out_file("seek.dat",ios::out|ios::binary);
    if (!out_file) 
    {
        cerr<<"out_fail!"<<endl;
        exit(-1);
    }
    for (int i=1;i<101;i++)
    {
        out_file.write((char*)&i,sizeof(int));
    }
    out_file.close();//如果这里不close的话，后面读的就是空文件，因为数据还没有从缓冲区传入到文件当中。
    //读出//将seek.data中的每个数字输出。
    int num;
    ifstream in_file("seek.dat",ios::in|ios::binary);
    if (!in_file) 
    {
        cerr<<"is_fail!"<<endl;
        exit(-1);
    }
    // for (int i=0;i<10;i++)
    // {
    //     in_file.seekg((9+i*10)*sizeof(int),ios::beg);
    //     in_file.read((char *)&num,sizeof(int));
    //     cout<<num<<endl;
    // }
    // in_file.close();
    for (int i=0;i<10;i++)
    {
        in_file.seekg(9*sizeof(int),ios::cur);
        in_file.read((char*)&num,sizeof(int));
        cout<<num<<endl;
    }
    in_file.close();
}
void testchar()
{
    string data;
    for (int i=1;i<101;i++)
        data+=std::to_string(i);
    ofstream out_file("seek.dat",ios::out|ios::binary);
    if (!out_file) 
    {
        cerr<<"out_fail!"<<endl;
        exit(-1);
    }
    out_file.write(data.c_str(),data.length());
    out_file.close();

    ifstream in_file("seek.dat",ios::in|ios::binary);
    char num[20]="\0";
    for (int i=0;i<9;i++)
    {
        in_file.seekg(9+i*20,ios::beg);
        in_file.read(num,2);
        cout<<num<<endl;
    }
    in_file.seekg(18,ios::cur);
    in_file.read(num,3);
    cout<<num<<endl;


    return ;
}
int main()
{
    testint();
    testchar();
}