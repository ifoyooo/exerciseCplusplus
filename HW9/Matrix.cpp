//实现支持多种数据类型，包括自建的复数类的矩阵类
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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

void testComplex()
{
    Complex a(1, 1), b(2, 2), c(0, 0);
    a.print();
    b.print();
    c.print();
    cout << "a<b:" << (a < b) << endl;
    (a * b).print();
    (a / b).print();
    (a + b).print();
    (a * c).print();

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
    Matrix &operator=(const Matrix &m)
    {
        colNum = m.colNum;
        rowNum = m.rowNum;
        delete data;
        data = new T[colNum * rowNum];
        memset(data, m.data, sizeof(T) * colNum * rowNum);
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

void testMatrix()
{
    //整数类的模板实例。
    //加减，索引，乘法
    int a[6] = {1, 1, 1, 1, 1, 1};
    Matrix<int> m1(2, 3, a), m2(3, 2, a);
    m1.print();
    m2.print();
    (m1 + m1).print();
    (m1 - m1).print();
    int b[6] = {1, 2, 3, 4, 5, 6};
    Matrix<int> m3(2, 3, b);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << m3[i][j] << endl;
        }
    }
    (m1 * m2).print();
    (m2 * m1).print();

    Complex c[6] = {Complex(1, 1), Complex(1, 1), Complex(1, 1), Complex(1, 1), Complex(1, 1), Complex(1, 1)};
    Matrix<Complex> m4(2, 3, c), m5(3, 2, c);
    m4.print();
    m5.print();
    (m4 + m4).print();
    (m4 - m4).print();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << m4[i][j] << endl;
        }
    }
    (m4 * m5).print();
    (m5 * m4).print();

    return;
}
int main()
{
    testComplex();
    testMatrix();
}