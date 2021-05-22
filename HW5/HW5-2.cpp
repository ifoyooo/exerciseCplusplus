#include <cstring>
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
const int NUM = 32;
class A
{
    //对于静态的成员函数与变量，只在声明的时候加入static，在定义的时候不加。
    //同时，必须将其声明预定义分开写。
public:
    static void *operator new(size_t size);
    static void operator delete(void *p);
    static void give_back();

private:
    A *next;          //用于组织A类对象自由空间结点的链表。
    static A *p_free; //用于指向A类对象的自由空间链表头。
    static vector<A *> blocks;
};
A *A::p_free = NULL;
vector<A*> A::blocks;
void *A::operator new(size_t size)
{
    if (p_free == NULL)
    {                                     //申请NUM个A类对象的大空间。
        p_free = (A *)malloc(size * NUM); //一个动态数组
        blocks.push_back(p_free);
        //在大空间上建立自由结点链表。
        for (int i = 0; i < NUM - 1; i++)
            p_free[i].next = &p_free[i + 1];
        p_free[NUM - 1].next = NULL;
    }
    //从链表中给当前对象分配空间
    A *p = p_free;
    p_free = p_free->next;
    memset(p, 0, size);
    return p;
}
void A::operator delete(void *p)
{
    ((A *)p)->next = p_free;
    p_free = (A *)p;
}
void A::give_back()
{
    printf("give back!.blocksize=%d",blocks.size());
    for (int i = 0; i < blocks.size(); i++)
    {
        free(blocks[i]);
    }
    blocks.erase(blocks.begin(), blocks.end());
}

int main()
{
    A *q1 = new A;
    A *q2 = new A;
    delete q1;
    A::give_back();
}