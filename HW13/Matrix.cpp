#include <iostream>
#include <string>
#include <cstring>
using namespace std;
template <class T>
class Matrix
{
private:
    int colNum;
    int rowNum;
    T *data;

public:
    Matrix(int r = 0, int c = 0)
    {
        if (c < 0 || r < 0)
        {
            string WaringInformation = "initialize matrix size error";
            throw WaringInformation;
        }
        colNum = c;
        rowNum = r;
        try
        {
            data = new T[colNum * rowNum];
        }
        catch (const bad_alloc &e)
        {
            string WarningInformation = "alloc error";
            throw WarningInformation;
        }
        //
        // for (int i=0;i<r*c;i++)
        // {
        // data[i]=T();
        // }
        memset(data, 0, sizeof(T) * c * r);
    }
    Matrix(int r, int c, T a[])
    {
        if (c < 0 || r < 0)
        {
            string WaringInformation = "initialize matrix size error";
            throw WaringInformation;
        }
        colNum = c;
        rowNum = r;
        try
        {
            data = new T[colNum * rowNum];
        }
        catch (const bad_alloc &e)
        {
            string WarningInformation = "alloc error";
            throw WarningInformation;
        }
        for (int i = 0; i < r * c; i++)
        {
            data[i] = a[i];
        }
    }
    Matrix<T> &operator=(const Matrix<T> &m)
    {
        colNum = m.colNum;
        rowNum = m.rowNum;
        delete[] data;
        try
        {
            data = new T[colNum * rowNum];
        }
        catch (const bad_alloc &e)
        {
            string WarningInformation = "alloc error";
            throw WarningInformation;
        }
        memcpy(data, m.data, sizeof(T) * colNum * rowNum);
        return *this;
    }

    //实现矩阵类
    Matrix operator-()
    {
        Matrix m(rowNum, colNum);
        for (int i = 0; i < colNum * rowNum; i++)
        {
            m[i] = -data[i];
        }
    }
    T *operator[](int index)
    {
        if (index >= rowNum)
        {
            string WarningInformation = "Index out of range";
            throw WarningInformation;
        }
        return &data[index * colNum];
    }
    //函数模板的声明上面也要加！
    //友元函数的class和模板类的class还不能一样？
    template <class Ty>
    friend Matrix<Ty> operator+(const Matrix<Ty> &m1, const Matrix<Ty> &m2);
    template <class Ty>
    friend Matrix<Ty> operator-(const Matrix<Ty> &m1, const Matrix<Ty> &m2);
    template <class Ty>
    friend Matrix<Ty> operator*(const Matrix<Ty> &m1, const Matrix<Ty> &m2);
    template <class Ty>
    friend istream &operator>>(istream &input, Matrix<Ty> &m);
    template <class Ty>
    friend ostream &operator<<(ostream &output, const Matrix<Ty> &m);
};
template <class T>
Matrix<T> operator+(const Matrix<T> &m1, const Matrix<T> &m2)
{
    // assert(m1.colNum == m2.colNum && m1.rowNum == m2.rowNum);
    if (m1.colNum != m2.colNum || m1.rowNum != m2.rowNum)
    {
        string WarningInformation = "No matching Matrixs";
        throw WarningInformation;
    }
    Matrix<T> tmp(m1.rowNum, m1.colNum);
    for (int i = 0; i < tmp.colNum * tmp.rowNum; i++)
    {
        tmp.data[i] = m1.data[i] + m2.data[i];
    }
    return tmp;
}
template <class T>
Matrix<T> operator-(const Matrix<T> &m1, const Matrix<T> &m2)
{
    // assert(m1.colNum == m2.colNum && m1.rowNum == m2.rowNum);
    if (m1.colNum != m2.colNum || m1.rowNum != m2.rowNum)
    {
        string WarningInformation = "No matching Matrixs";
        throw WarningInformation;
    }
    Matrix<T> tmp(m1.rowNum, m1.colNum);
    for (int i = 0; i < tmp.colNum * tmp.rowNum; i++)
    {
        tmp.data[i] = m1.data[i] - m2.data[i];
    }
    return tmp;
}
template <class T>
Matrix<T> operator*(const Matrix<T> &m1, const Matrix<T> &m2)
{
    // assert(m1.colNum == m2.rowNum);
    if (m1.colNum != m2.rowNum)
    {
        string WarningInformation = "No matching Matrixs";
        throw WarningInformation;
    }
    Matrix<T> tmp(m1.rowNum, m2.colNum);
    for (int i = 0; i < tmp.rowNum * tmp.colNum; i++)
    {
        int r = i / tmp.colNum;
        int c = i % tmp.colNum;
        for (int j = 0; j < m1.colNum; j++)
        {
            tmp.data[i] = tmp.data[i] + m1.data[r * m1.colNum + j] * m2.data[j * m2.colNum + c];
        }
    }
    return tmp;
}
template <class T>
istream &operator>>(istream &input, Matrix<T> &m)
{
    int a, b;
    input>>a>>b;
    if (input.fail())
    {
        input.clear(); //将失效位清除
		input.sync();//清空输入流
        string WarningInformation="wrong type";
        throw WarningInformation;
    }
    Matrix<T> tmp(a, b);
    for (int i = 0; i < a * b; i++)
        input >> tmp.data[i];
    if (input.fail())
    {
        input.clear(); //将失效位清除
		input.sync();//清空输入流
        string WarningInformation="wrong type";
        throw WarningInformation;
    }
    m = tmp;
    return input;
}
template <class T>
ostream &operator<<(ostream &output, const Matrix<T> &m)
{
    for (int i = 0; i < m.rowNum; i++)
    {
        for (int j = 0; j < m.colNum; j++)
            output << m.data[i * m.colNum + j] << " ";
        output << endl;
    }
    return output;
}

// //成功实现
// void testMatrix()
// {
//     Matrix<int> m;
//     cin >> m;
//     cout << m;
// }
void f()
{
    Matrix<int> a, b;
    while (true)
    {
        bool flag=true;
        try
        {
            char oper;
            cout<<"请输入操作符+/*"<<endl;
            cin >> oper;
            if (oper!='+' && oper!='*')
            {
                string WarningInformation="No matching operator!";
                throw WarningInformation;
            }
            cout<<"请输入矩阵A"<<endl;
            cin>>a;
            cout<<"请输入矩阵B"<<endl;
            cin>>b;
            if (oper=='*')
            {
                cout<<a*b;
            }
            else 
            {
                cout<<a+b;
            }
        
        }
        catch(const string &s)
        {
            flag=false;
            cerr<<s<<endl;
            cout<<"请重新输入"<<endl;
        }
        if (flag) 
        {
            break;
        }
    }
}
int main()
{
    try{
        f();
    }
    catch(...)
    {
        cout<<"请重新运行本程序"<<endl;
        exit(0);
    }
}
/* 有两点需要记录一下
 * 首先当istream接收到了错误的类型就会失败，可以调用input.fail来判断。且在此处不能直接重新循环，因为input当中仍然保留着值，要先对流进行清空。
 * 在模板类当中定义方法时，如果用到了同类型的数据，可以实例化也可以不是实例化，会默认属于相同的类型，但是在类外定义就必须要实例化。
 */