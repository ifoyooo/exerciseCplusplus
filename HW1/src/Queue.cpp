#include <iostream>
#include "Queue.h"
#include <string.h>
#include <assert.h>
using namespace std;

// static const int SIZES[SIZENUM] = {10, 20, 30, 50, 100};
static const int SIZES[SIZENUM] = {1, 2, 3, 5, 10};

#define MULTISTACK
// #define CYCLEARRAY
// #define PTR

#if defined MULTISTACK
class Queue
{
private:
    int *stack = (int *)malloc(sizeof(int) * SIZES[0]);
    int cnt;
    int isize;

public:
    Queue();
    void enQueue(int i);
    void deQueue(int &i);
    void printAll();
};

Queue::Queue()
{
    cnt = 0;
    isize = 0;
}

void Queue::enQueue(int data)
{
    if (cnt >= SIZES[isize])
    {
        if (isize + 1 >= SIZENUM)
        {
            cout << BOLDRED << "WRONG:--- queue --- overflow\n";
            exit(-1);
            return;
        }
        else
        {
            cout << BOLDYELLOW << "WARNING:---queue---expanding\n";
            int *tmp = (int *)malloc(sizeof(int) * SIZES[isize + 1]);
            memcpy((void *)tmp, (void *)stack, SIZES[isize] * sizeof(int));
            free(stack);
            stack = tmp;
            stack[cnt] = data;
            cnt++;
            isize++;
        }
    }
    else
    {
        stack[cnt] = data;
        cnt++;
    }
    // cout << BOLDGREEN << "ADD SUCCESSFULLY\n";
}

void Queue::deQueue(int &data)
{
    if (cnt == 0)
    {
        cout << BOLDRED << "WRONG:---queue---empty\n";
        return;
    }
    cnt--;
    data = stack[0];

    for (int i=0;i<cnt;i++)
    {
        stack[i]=stack[i+1];
    }

    if (cnt <= SIZES[isize - 1])
    {
        cout << BOLDYELLOW << "WARNING:---queue---shrinking\n";
        int *tmp = (int *)malloc(sizeof(int) * SIZES[isize - 1]);
        memcpy((void *)tmp, (void *)stack, SIZES[isize - 1] * sizeof(int));
        free(stack);
        stack = tmp;
        isize--;
    }
}

void Queue::printAll()
{
    cout << BOLDBLUE << "PRINT ALL ELEMENTS\n";
    for (int i = 0; i < cnt; i++)
    {
        cout << "stack[" << i << "]=" << stack[i] << "\n";
    }
}

#elif defined CYCLEARRAY
class Queue
{
private:
    int head;
    int tail;
    int array[MAXSIZE];

public:
    Queue();
    void enQueue(int i);
    void deQueue(int *i);
    void printAll();
} void Queue::enQueue(int i)
{
    return;
}

void Queue::deQueue(int *i)
{
    return;
}

void Queue::printAll()
{
    return;
}
#elif defined PTR

class Queue
{
private:
    struct Node
    {
        int content;
        Node *next;
    } * head, *tail;
    int cnt;
public:
    Queue();
    void enQueue(int i);
    void deQueue(int &i);
    void printAll();

};

Queue::Queue()
{
    head=tail=NULL;
    cnt=0;
}

void Queue::enQueue(int i)
{
    if (cnt==0)
    {
        assert(head==NULL);
        assert(tail==NULL);
        cnt++;
        tail=head=new Node;
        tail->content=head->content=i;
        tail->next=head->next=NULL;
        // cout<<BOLDGREEN<<"PUSH SUCCESSFULLY\n";
    }
    else if (cnt>=MAXSIZE)
    {
        cout<<BOLDRED<<"WRONG:---queue---overflow\n";
        exit(-1);
    }

    else if (cnt==1)
    {
        tail=new Node;
        tail->content=i;
        tail->next=NULL;
        head->next=tail;
        cnt++;

        // cout<<BOLDGREEN<<"PUSH SUCCESSFULLY\n";

    }
    else
    {
        Node *p=new Node;
        p->content=i;
        p->next=NULL;
        tail->next=p;
        tail=p;
        cnt++;

        // cout<<BOLDGREEN<<"PUSH SUCCESSFULLY\n";
    }
}

void Queue::deQueue(int &i)
{
    if (cnt==0)
    {
        assert(head==nullptr&&tail==nullptr);
        cout<<BOLDRED<<"WORNG:---queue-empty\n";
    }
    else
    {
        cnt--;
        Node *p=head;
        i=p->content;
        head=head->next;
        if (head==NULL)
        {
            tail=NULL;
        }
        free(p);

        // cout<<BOLDGREEN<<"POP SUCCESSFULLY\n";

    }
    return;
}

void Queue::printAll()
{
    if (cnt==0)
    {
        cout<<BOLDYELLOW<<"Nothing to display\n";
    }
    else
    {
        for (Node *p=head;p!=nullptr;p=p->next)
        {
            cout<<BLUE<<p->content<<"\n";
        }
    }
    return;
}

#endif

void test()
{
    Queue queue;
    while (1)
    {
        int a;
        cin >> a;
        if (a == 0)
        {
            int b;
            cin >> b;
            queue.enQueue(b);
            queue.printAll();
        }
        else
        {
            int b;
            cin >> b;
            queue.deQueue(b);
            queue.printAll();
        }
    }
}

int main()
{
    // Queue queue;
    // int i = 0;
    // printf("i=%d\n", i);
    // queue.enQueue(1);
    // queue.enQueue(2);
    // queue.deQueue(i);
    // queue.enQueue(3);
    // printf("i=%d\n", i);
    // queue.printAll();
    // return 0;
    test();
}