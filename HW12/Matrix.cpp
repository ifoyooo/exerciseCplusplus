//实现支持多种数据类型，包括自建的复数类的矩阵类
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
using namespace std;

//在Complex类中，可以直接访问其他Complex对象的private资源。
class Complex
{
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i)
    {
    }
    void print()
    {
        if (imag == 0)
        {
            cout << real << endl;
        }
        else if (imag > 0)
        {
            cout << real << "+" << imag << "j" << endl;
        }
        else
        {
            cout << real << imag << "j" << endl;
        }
    }
    double modulus() const
    {
        return real * real + imag * imag;
    }
    //默认在左边的符号，如果想要在右边，则传入一个int参数进来
    //这里因为不是一个赋值操作所以必须返回的是值，也可以是动态变量的指针或者引用
    //但是如果没有指针接受它的话则内存泄漏
    //另外一定不能用静态的临时变量，返回指针或者引用，因为函数结束以后静态变量就已经被释放了。
    //想要在左边就能用，必须写成类内的重载函数了。
    Complex operator-() const
    {
        Complex tmp;
        tmp.real = -real;
        tmp.imag = -imag;
        return tmp;
    }
    //=号的重载也必须是成员函数，与拷贝构造函数基本一致。
    Complex &operator=(const Complex &c)
    {
        real = c.real;
        imag = c.imag;
        return *this;
    }
    //但是一般这些我们都会传入const的引用，既可以避免修改原值，又可以加快速度。
    friend bool operator==(const Complex &c1, const Complex &c2);
    friend bool operator!=(const Complex &c1, const Complex &c2);
    friend bool operator>(const Complex &c1, const Complex &c2);
    friend bool operator>=(const Complex &c1, const Complex &c2);
    friend bool operator<(const Complex &c1, const Complex &c2);
    friend bool operator<=(const Complex &c1, const Complex &c2);
    friend Complex operator+(const Complex &c1, const Complex &c2);
    friend Complex operator-(const Complex &c1, const Complex &c2);
    friend Complex operator*(const Complex &c1, const Complex &c2);
    friend Complex operator/(const Complex &c1, const Complex &c2);
    friend ostream &operator<<(ostream &output, const Complex &c);
    friend istream &operator>>(istream &input, Complex &c);
};
bool operator==(const Complex &c1, const Complex &c2)
{
    return c1.real == c2.real && c1.imag == c2.imag;
}
bool operator!=(const Complex &c1, const Complex &c2)
{
    return !(c1 == c2);
}
bool operator>(const Complex &c1, const Complex &c2)
{
    return c1.modulus() > c2.modulus();
}
bool operator>=(const Complex &c1, const Complex &c2)
{
    return c1.modulus() >= c2.modulus();
}
bool operator<(const Complex &c1, const Complex &c2)
{
    return c1.modulus() < c2.modulus();
}
bool operator<=(const Complex &c1, const Complex &c2)
{
    return c1.modulus() <= c2.modulus();
}
Complex operator+(const Complex &c1, const Complex &c2)
{
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}
Complex operator-(const Complex &c1, const Complex &c2)
{
    return Complex(c1.real - c2.real, c1.imag - c2.imag);
}
Complex operator*(const Complex &c1, const Complex &c2)
{
    return Complex(c1.real * c2.real - c1.imag * c2.imag, c1.real * c2.imag + c1.imag * c2.real);
}
Complex operator/(const Complex &c1, const Complex &c2)
{
    double d = c2.modulus();
    if (d == 0)
    {
        cerr << "Error in operation / of Complex" << endl;
        exit(-1);
    }
    else
    {
        return Complex((c1.real * c2.real + c1.imag * c2.imag) / d, (c1.imag * c2.real - c1.real * c2.imag) / d);
    }
}
ostream &operator<<(ostream &output, const Complex &c)
{
    int num = c.imag;

    if (num >= 0)
    {
        output << c.real << "+" << c.imag << "i";
    }
    else
    {
        output << c.real << c.imag << "i";
    }

    return output;
}
istream &operator>>(istream &input, Complex &c)
{
    //如果后面加i，只要在后面多提取一个字符类型i就可以了。
    input >> c.real >> c.imag;
}

//成功实现，
void testComplex()
{
    Complex a, b, c;
    cin >> a >> b >> c;
    cout << "a<b:" << (a < b) << endl;
    cout << (a * b) << endl;
    cout << (a / b) << endl;
    cout << (a + b) << endl;
    cout << (a * c) << endl;

    //divided by zero exit(-1);
    // (a / c).print();
}

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
        colNum = c;
        rowNum = r;
        data = new T[colNum * rowNum];
        //
        // for (int i=0;i<r*c;i++)
        // {
        // data[i]=T();
        // }
        memset(data, 0, sizeof(T) * c * r);
    }
    Matrix(int r, int c, T a[])
    {
        colNum = c;
        rowNum = r;
        data = new T[colNum * rowNum];
        for (int i = 0; i < r * c; i++)
        {
            data[i] = a[i];
        }
    }
    void print()
    {
        for (int i = 0; i < rowNum; i++)
        {
            for (int j = 0; j < colNum; j++)
            {
                cout << data[i * colNum + j] << "  ";
            }
            cout << endl;
        }
    }
    //赋值操作
    // Matrix &operator=(const Matrix &m)
    // {
    //     colNum = m.colNum;
    //     rowNum = m.rowNum;
    //     delete []data;
    //     data = new T[colNum * rowNum];
    //     memcpy(data, m.data, sizeof(T) * colNum * rowNum);
    //     return *this;
    // }
    Matrix &operator=(const Matrix<T> &m)
    {
        colNum = m.colNum;
        rowNum = m.rowNum;
        delete []data;
        data = new T[colNum * rowNum];
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
    assert(m1.colNum == m2.colNum && m1.rowNum == m2.rowNum);
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
    assert(m1.colNum == m2.colNum && m1.rowNum == m2.rowNum);
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
    assert(m1.colNum == m2.rowNum);
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
// template<class T>
// istream &operator>>(istream & input,Matrix<T> &m)
// {
//     for (int i=0;i<m.colNum*m.rowNum;i++) input>>m.data[i];
//     return input;
// }
template <class T>
istream &operator>>(istream &input, Matrix<T> &m)
{
    int a,b;
    input>>a>>b;
    Matrix<T> tmp(a,b);
    for (int i=0;i<a*b;i++) input>>tmp.data[i];
    m=tmp;
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

//成功实现
void testMatrix()
{
    // //整数类的模板实例。
    // //加减，索引，乘法
    // int a[6] = {1, 1, 1, 1, 1, 1};
    // Matrix<int> m1(2, 3, a), m2(3, 2, a);
    // m1.print();
    // m2.print();
    // (m1 + m1).print();
    // (m1 - m1).print();
    // int b[6] = {1, 2, 3, 4, 5, 6};
    // Matrix<int> m3(2, 3, b);
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         cout << m3[i][j] << endl;
    //     }
    // }
    // (m1 * m2).print();
    // (m2 * m1).print();

    // Complex c[6] = {Complex(1, 1), Complex(1, 1), Complex(1, 1), Complex(1, 1), Complex(1, 1), Complex(1, 1)};
    // Matrix<Complex> m4(2, 3, c), m5(3, 2, c);
    // m4.print();
    // m5.print();
    // (m4 + m4).print();
    // (m4 - m4).print();
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     { 
    //         cout << m4[i][j] << endl;
    //      }
    // }
    // (m4 * m5).print();
    // (m5 * m4).print();
    // return;
    Matrix<Complex> m;
    cin >> m;
    Matrix<Complex> m1;
    // m1=m;
    // cout<<m1;
    // cout << m;
}
void testMatrixFile()
{
    Matrix<Complex> m;
    ifstream minput("matrix_test.txt",ios::in);
    if (!minput) exit(-1);
    minput>>m;
    cout<<m;


}
int main()
{
    // testComplex();
    testMatrix();
    // testMatrixFile();
}
//这里有一个很重要的问题，即我们在编写类属类的方法的时候要不要给类实例化呢？
//经过测试，类内既可以实例化也可以不实例化，但是类外定义的则需要实例化。