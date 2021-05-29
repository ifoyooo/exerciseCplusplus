#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

enum Gender {Male,Female};
class Grade
{
    private:
    int id;
    char name[10];
    Gender sex;
    int grade;
    public:
    Grade(int i=0,char n[]=NULL,Gender s=Male,int g=0):
    id(i),sex(s),grade(g)
    {
        // strcpy(name,n);
        if (n==NULL)
        {
            name[0]='\0';
        }
        else 
        {
            strcpy(name,n);
        }
    }
    int getGrade() const 
    {
        return grade;
    }
    Gender getGender() const 
    {
        return sex;
    }
    friend istream &operator>>(istream &input,Grade &gd)
    {
        input>>gd.id;
        input>>gd.name;
        int tmp;
        input>>tmp;
        gd.sex=(Gender)tmp;
        input>>gd.grade;
        return input;
    }
    friend ostream &operator<<(ostream &output,const Grade& gd)
    {
        output<<gd.id<<" "<<gd.name<<" "<<gd.sex<<" "<<gd.grade<<"\n";
        return output;
    }

};
size_t getFileSize(const std::string& file_name){
	std::ifstream in(file_name.c_str(),ios::in|ios::binary);
	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	in.close();
	return size; //单位是：byte
}
void init()
{
/*输入测试样例
1 lilei 0 90
2 feifei 1 60
3 gugu 0 70
4 hanhan 1 59
5 haha 1 80
*/
    Grade grades[5];
    for (int i=0;i<5;i++)
    {
        cin>>grades[i];
    }
    for (int i=0;i<5;i++)
    {
        cout<<grades[i];
    }
    ofstream out("a.dat",ios::out|ios::binary);
    for (int i=0;i<5;i++)
    {
        //栈中存储结构体。
        out.write((char*)&grades[i],sizeof(Grade));
    }

}
void saveTop3(vector<Grade*>);
void saveLowerAverage(const vector<Grade *> & grades);
void change()
{
    vector<Grade*> grades;
    int num=getFileSize("a.dat")/sizeof(Grade);
    ifstream in("a.dat",ios::in|ios::binary);
    for (int i=0;i<num;i++)
    {
        Grade *newgrade=new Grade;
        in.read((char *)newgrade,sizeof(Grade));
        grades.push_back(newgrade);
    }
    in.close();    
    //不改变原来的vector。
    saveTop3(grades);
}
void saveTop3(vector<Grade*> grades)
{
    sort(grades.begin(),grades.end(),[](Grade *gd1,Grade *gd2)->bool {if (gd1->getGrade()>gd2->getGrade())return true;return false; });
    ofstream out("b.dat",ios::binary|ios::out);
    for_each(grades.begin(),grades.begin()+3,[&out](Grade *gd)->void {out.write((char*)gd,sizeof(Grade));});
    for_each(grades.begin(),grades.begin()+3,[](Grade *gd)->void{cout<<*gd;});
}
void saveLowerAverage(const vector<Grade *> & grades)
{
    vector<Grade *>mg,fg;
    copy_if(grades.begin(),grades.end(),back_inserter(mg),[](Grade *gd)->bool{return gd->getGender()==Male;});
    copy_if(grades.begin(),grades.end(),back_inserter(fg),[](Grade *gd)->bool{return gd->getGender()==Female;});
    int mgave=accumulate(mg.begin(),mg.end(),0,)
}
void addMakeUp()
{

}

//想要STL不报错，就要重写c_cpp_properties
//想要默认用vscode的编辑选项，就要编写task，ctrl+shift+b.
//lauch.json用于调试等等。
int main()
{
    init();
    change();
}