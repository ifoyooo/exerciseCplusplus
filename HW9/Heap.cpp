#include <iostream>
#include <algorithm>
using namespace std;

//实现能够有多种数据类型的最大堆。
template <class Type>
class MaxHeap
{
private:
    Type *data;
    int size;     //当前大小
    int capacity; //总容量
    int parent(int i)
    {
        //-1/2=-1；
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return i * 2 + 1;
    }
    int right(int i)
    {
        return (i + 1) * 2;
    }
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < size && data[l] > data[largest])
        {
            largest = l;
        }
        if (r < size && data[r] > data[largest])
        {
            largest = r;
        }
        if (largest != i)
        {
            swap(data[i], data[largest]);
            heapify(largest);
        }
    }

public:
    MaxHeap(int c = 10) : data(new Type[c]), size(0), capacity(c)
    {
    }
    //直接从数组进行建堆
    //则指针A指向的数组不可变。
    MaxHeap(const Type A[], int n, int c) : data(new Type[c]), size(n), capacity(c)
    {
        for (int i = 0; i < n; i++)
        {
            data[i] = A[i];
        }
        for (int i = (size - 1) / 2; i >= 0; i--)
        {
            heapify(i);
        }
    }
    //默认的析构函数不会删除掉动态变量。
    ~MaxHeap()
    {
        delete data;
    }
    bool Insert(Type element) //插入一个元素
    {
        data[size] = element;
        int i = size;
        size++;
        while (i >= 0 && data[parent(i)] < data[i])
        {
            swap(data[parent(i)], data[i]);
            i = parent(i);
        }
    }
    //让出0位置的元素，将末尾元素置于0位置，并执行heapify。
    Type DeleteMax() //找出最大的元素返回，并进行删除
    {
        Type ans = data[0];
        size--;
        data[0] = data[size];
        heapify(0);
        return ans;
    }
    bool IsFull() //是否为满
    {
        return size == capacity;
    }
    bool IsEmpty() //是否为空
    {
        return size == 0;
    }
    void Print() //打印
    {
        cout << "PRINT THE ELEMENT IN HEAP\n";
        for (int i = 0; i < size; i++)
        {
            cout << data[i] << " ";
            if (left(i) < size)
            {
                cout << data[left(i)]<<" ";
            }
            if (right(i)<size)
            {
                cout<<data[right(i)]<<" ";
            }
            cout<<endl;
        }
    }
};

int main()
{
    cout << "TEST1\n";
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    MaxHeap<int> h1(a, 10, 20);
    h1.Print();
    h1.Insert(11);
    h1.Print();
    h1.Insert(100);
    h1.Insert(1000);
    cout << h1.DeleteMax() << endl;
    h1.Print();

    cout << "TEST2\n";
    MaxHeap<int> h2(20);
    for (int i = 1; i < 11; i++)
    {
        h2.Insert(i);
    }
    h2.Print();
    h2.Insert(11);
    h2.Print();
    h2.Insert(100);
    h2.Insert(1000);
    cout << h2.DeleteMax() << endl;
    h2.Print();
}