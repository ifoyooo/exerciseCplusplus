#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>
using namespace std;
enum Sex
{
    MALE,
    FEMALE
};
enum Major
{
    MATHEMATICS,
    PHYSICS,
    CHEMISTRY,
    COMPUTER,
    GEOGRAPHY,
    ASTRONOMY,
    ENGLISH,
    CHINESE,
    PHILOSOPHY
};
class Date
{
    int year;
    int month;
    int day;

public:
    Date(int y, int m, int d)
    {
        year = y;
        month = m;
        day = d;
    }
    int get_year() const { return year; }
    int get_month() const { return month; }
    int get_day() const { return day; }
    void display()
    {
        cout << year << '/' << month << '/' << day;
    }
};
class Student
{
    int no;
    string name;
    Sex sex;
    Date birth_date;
    string birth_place;
    Major major;

public:
    Student(int no1, char *name1, Sex sex1,
            Date birth_date1, char *birth_place1, Major major1) : name(name1), birth_date(birth_date1), birth_place(birth_place1)
    {
        no = no1;
        sex = sex1;
        major = major1;
    }
    int get_no() const { return no; }
    string get_name() const { return name; }
    Sex get_sex() const { return sex; }
    Major get_major() const { return major; }
    string get_birth_place() const { return birth_place; }
    int get_age(const Date &dt) const //const 会约束不能够改变对象的数据成员！
    {
        int age = dt.get_year() - birth_date.get_year();
        if (dt.get_month() < birth_date.get_month())
        {
            age -= 1;
        }
        else if (dt.get_month() == birth_date.get_month() && dt.get_day() < birth_date.get_day())
        {
            age -= 1;
        }
        return age;
    }
    void display()
    {
        cout << no << ", " << name << ", "
             << (sex == MALE ? "male" : "female") << ", ";
        birth_date.display();
        cout << ", " << birth_place << ", ";
        switch (major)
        {
        case MATHEMATICS:
            cout << "Mathematics";
            break;
        case PHYSICS:
            cout << "Physics";
            break;
        case CHEMISTRY:
            cout << "Chemistry ";
            break;
        case COMPUTER:
            cout << "Computer";
            break;
        case GEOGRAPHY:
            cout << "Geography";
            break;
        case ASTRONOMY:
            cout << "Astronomy";
            break;
        case ENGLISH:
            cout << "English";
            break;
        case CHINESE:
            cout << "Chinese";
            break;
        case PHILOSOPHY:
            cout << "Philosophy";
            break;
        }
    }
};
bool match_major_and_sex(Student &st) //判断st是否为计算机专业的女生?
{
    return st.get_major() == COMPUTER && st.get_sex() == FEMALE;
}
bool match_birth_place(Student &st) //判断st的出生地是否为"南京"
{
    return (st.get_birth_place()).find("南京") != string::npos;
}
bool compare_no(Student &st1, Student &st2) //比较st1和st2的的学号
{
    return st1.get_no() < st2.get_no();
}
void display_student_info(Student &st) //显示st的信息?
{
    st.display();
    cout << endl;
}

class MatchMajorAndSex
{
    Major major;
    Sex sex;

public:
    MatchMajorAndSex(Major m, Sex s)
    {
        major = m;
        sex = s;
    }
    bool operator()(Student &st)
    {
        return st.get_major() == major && st.get_sex() == sex;
    }
};
class MatchBirthPlace
{
    string birth_place;

public:
    MatchBirthPlace(char *bp) { birth_place = bp; }
    bool operator()(Student &st) //判断st的出生地是否"南京"
    {
        return (st.get_birth_place()).find(birth_place) != string::npos;
    }
};
int main()
{
    vector<Student> students; //创建存放学生信息的容器students

    //获得所有学生的数据，存储在容器students中，
    students.push_back(Student(2, "zhang", FEMALE, Date(1991, 10, 1),
                               "江苏南京", COMPUTER));
    students.push_back(Student(5, "li", MALE, Date(1992, 10, 1),
                               "北京", PHILOSOPHY));
    students.push_back(Student(1, "wang", FEMALE, Date(1993, 10, 1),
                               "南京", COMPUTER));
    students.push_back(Student(6, "sun1", MALE, Date(1994, 12, 30), "江苏省南京市", PHILOSOPHY));
    students.push_back(Student(7, "sun2", MALE, Date(1995, 12, 30), "江苏省南京市", MATHEMATICS));
    students.push_back(Student(4, "qian", MALE, Date(1996, 10, 1),
                               "上海", PHILOSOPHY));
    students.push_back(Student(3, "zhao", MALE, Date(1997, 10, 1),
                               "江苏南京", COMPUTER));
    students.push_back(Student(3, "zhao", MALE, Date(2010, 10, 1),
                               "江苏南京",PHYSICS));

    //......

    //统计计算机专业女生的人数
    cout << "计算机专业女生的人数是："
         << count_if(students.begin(), students.end(), match_major_and_sex)
         << endl;

    //统计出生地为"南京"的学生人数?
    cout << "出生地为\"南京\"的学生人数是:"
         << count_if(students.begin(), students.end(), match_birth_place)
         << endl;

    //按照学号进行排序了！！
    //按学号由小到大对students的元素进行排序?
    sort(students.begin(), students.end(), compare_no);

    //按学号由小到大输出所有学生的信息
    cout << "按学号排序后的学生信息：\n";
    for_each(students.begin(), students.end(), display_student_info);

    //完成如下的练习题！！！！
    //还有为什么要非要-std=c++11 or -std=gnu++11?
    //升序输出计算机专业男生的姓名
    vector<Student> s1;
    //这里必须要用inserter！
    copy_if(students.begin(), students.end(), inserter(s1, s1.begin()), MatchMajorAndSex(COMPUTER, MALE));
    // copy_if(students.begin(),students.end(),back_inserter(s1),[](const Student &st)->bool{return st.get_sex()==MALE && st.get_major()==COMPUTER;});
    for_each(s1.begin(), s1.end(), [](const Student &st) -> void { cout << st.get_name() << endl; });
    //升序输出出生地是“南京”、专业为哲学或数学的学生的年龄(年龄计算可以以代码实现时的日期为准)
    for_each(students.begin(), students.end(), [](const Student &st) -> void {if ((st.get_birth_place()).find("南京") != string::npos  && (st.get_major()==PHILOSOPHY || st.get_major()==MATHEMATICS)){cout<<st.get_no()<<":"<<st.get_name()<<":"<<"age:"<<st.get_age(Date(2021,5,15))<<endl; } });
    //统计全部女生的平均年龄
    s1.clear();
    copy_if(students.begin(), students.end(), inserter(s1, s1.begin()), [](const Student &st) -> bool { return st.get_sex() == FEMALE; });
    cout << accumulate(s1.begin(), s1.end(), 0, [](double partial, const Student &st) -> double { return partial + st.get_age(Date(2021, 5, 15)); }) / s1.size() << endl;
    //统计出生地是“南京”的计算机专业学生的平均年龄
    s1.clear();
    copy_if(students.begin(), students.end(), inserter(s1, s1.begin()), [](const Student &st) -> bool { return (st.get_birth_place()).find("南京") != string::npos && st.get_major() == COMPUTER; });
    cout << (double)accumulate(s1.begin(), s1.end(), 0, [](double partial, const Student &st) -> double { return partial + st.get_age(Date(2021, 5, 15)); }) / s1.size() << endl;
    //统计非计算机专业年龄小于20岁的学生的平均年龄
    s1.clear();
    copy_if(students.begin(), students.end(), inserter(s1, s1.begin()), [](const Student &st) -> bool { return st.get_age(Date(2021, 5, 15)) <= 20 && st.get_major() != COMPUTER; });
    cout << (double)accumulate(s1.begin(), s1.end(), 0, [](double partial, const Student &st) -> double { return partial + st.get_age(Date(2021, 5, 15)); }) / s1.size() << endl;
    return 0;
}
