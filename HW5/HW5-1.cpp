#include <iostream>
#include <cstring>
#include <assert.h>
using namespace std;
//一个类本身就是自己的友元.
class Matrix
{
    int *p_data;  //表示矩阵数据
    int row, col; //表示矩阵的行数和列数
public:
    Matrix(int r, int c, const int a[]);
    void display();
    Matrix(int r, int c);                    //构造函数
    ~Matrix();                               //析构函数
    int &operator[](int i);                  //重载[], 对于Matrix对象m, 能够通过m[i][j]访问第i+1行、第j+1列元素
    Matrix &operator=(const Matrix &m);      //重载=, 实现矩阵整体赋值, 若行/列不等, 归还空间并重新分配
    bool operator==(const Matrix &m) const;  //重载==, 判断矩阵是否相等
    Matrix operator+(const Matrix &m) const; //重载+, 完成矩阵加法, 可假设两矩阵满足加法条件(两矩阵行、列分别相等)
    Matrix operator*(const Matrix &m) const; //重载*, 完成矩阵乘法, 可假设两矩阵满足乘法条件(this.col = m.row)
};
Matrix::Matrix(int r, int c)
{
    p_data = new int[r * c];
    row = r;
    col = c;
}
Matrix::Matrix(int r, int c, const int a[])
{
    row = r;
    col = c;
    p_data = new int[r * c];
    for (int i = 0; i < r * c; i++)
    {
        p_data[i] = a[i];
    }
}
void Matrix::display()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << p_data[i * col + j] << " ";
        }
        cout << endl;
    }
}
Matrix::~Matrix()
{
    delete p_data;
}
int &Matrix::operator[](int i)
{
    return p_data[i * row];
}
Matrix &Matrix::operator=(const Matrix &m)
{
    if (m.col != col || m.row != row)
    {
        col = m.col;
        row = m.row;
    }
    memcpy(p_data, m.p_data, col * row * sizeof(int));
}
bool Matrix::operator==(const Matrix &m) const
{
    if (col != m.col || row != m.row)
    {
        return false;
    }
    for (int i = 0; i < row * col; i++)
    {
        if (p_data[i] != m.p_data[i])
        {
            return false;
        }
    }
    return true;
}
Matrix Matrix::operator+(const Matrix &m) const
{
    assert(m.col == col && m.row == row);
    Matrix tmp(row, col);
    for (int i = 0; i < col * row; i++)
    {
        tmp.p_data[i] = p_data[i] + m.p_data[i];
    }
    return tmp;
}
Matrix Matrix::operator*(const Matrix &m) const
{
    Matrix tmp(row, m.col);
    memset(tmp.p_data, 0, row * m.col * sizeof(int));
    for (int i = 0; i < row * m.col; i++)
    {
        int r = i / m.col;
        int c = i % m.col;
        for (int j = 0; j < col; j++)
        {
            tmp.p_data[i] += p_data[r * col + j] * m.p_data[j * m.col + c];
        }
    }
    return tmp;
}
int main()
{
    const int a[6] = {1, 1, 1, 1, 1, 1};
    Matrix A(2, 3, a);
    Matrix B(3, 2, a);
    A.display();
    B.display();
    cout << (A == B) << endl;
    Matrix C(1, 1);
    C = A * B;
    C.display();
}
