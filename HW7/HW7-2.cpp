#include <iostream>
#include <queue>
#include <set>
using namespace std;

//使用STL实现。
class Queue
{
public:
    virtual bool enqueue(int num) = 0;
    virtual bool dequeue(int &num) = 0;
};
//先进先出
class Queue1 : public Queue
{
private:
    std::queue<int> lst;

public:
    bool enqueue(int num)
    {
        lst.push(num);
        return true;
    }
    bool dequeue(int &num)
    {
        if (lst.empty())
        {
            return false;
        }
        num = lst.front();
        return true;
    }
};
//最小队列
class Queue2 : public Queue
{
private:
    //std::less<int>() is a constructor call. It creates a new std::less<int> object which, yes, has overloaded operator().
    std::multiset<int> lst;

public:
    bool enqueue(int num)
    {
        lst.insert(num);
        return true;
    }
    bool dequeue(int &num)
    {
        if (lst.empty())
        {
            return false;
        }
        num = *lst.begin();
        lst.erase(lst.begin());
        return true;
    }
};
//最大队列


//通过构造一个新的类作为比较函数。
//或者重载操作符。
class CTestCmp {
public:
        bool operator() (int x, int y) {
            return x>y;
        }
};
class Queue3 : public Queue
{
private:
    std::multiset<int,CTestCmp> lst;

public:
    bool enqueue(int num)
    {
        lst.insert(num);
        return true;
    }
    bool dequeue(int &num)
    {
        if (lst.empty())
        {
            return false;
        }

        // set<int>::iterator i = lst.end();
        // i--;
        // num = *i;
        // lst.erase(i);
        num=*lst.begin();
        lst.erase(lst.begin());
        return true;
    }
};

int main()
{
    Queue3 a;
    int num = 0;
    std::cout << a.enqueue(1) << std::endl;
    std::cout << a.enqueue(1) << std::endl;
    std::cout << a.enqueue(2) << std::endl;
    std::cout << a.dequeue(num) << std::endl;
    std::cout << num << std::endl;
    std::cout << a.dequeue(num) << std::endl;
    std::cout << num << std::endl;
    std::cout << a.dequeue(num) << std::endl;
    std::cout << num << std::endl;
}