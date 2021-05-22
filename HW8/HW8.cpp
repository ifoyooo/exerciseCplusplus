#include <iostream>
#include <cstring>
using namespace std;

bool doubleCmp(const void *a, const void *b)
{
    return *(double *)a < *(double *)b;
}
void Merge(void *base, unsigned l, unsigned imid, unsigned r, unsigned element_size, bool (*cmp)(const void *, const void *))
{
    int n1 = imid - l;
    int n2 = r - imid;
    char lbase[(n1 +1) * element_size];
    char rbase[(n2 +1) * element_size];
    memcpy((char *)lbase, (char *)base + l * element_size, n1 * element_size);
    memcpy((char *)rbase, (char *)base + imid * element_size, n2 * element_size);
    // *(double *)(lbase+(n1)*element_size)=1000000000;
    // *(double *)(rbase+(n2)*element_size)=1000000000;
    for (int i = 0; i < n1; i++)
    {
        cout << "a1:" << *(double *)(lbase + i * element_size) << "\t";
    }
    for (int i = 0; i < n2; i++)
    {
        cout << "b1:" << *(double *)(rbase + i * element_size) << "\t";
    }
    cout << endl;
    int i = 0, j = 0;
    for (int k = l; k < r; k++)
    {
        if ((j>=n2||cmp((char *)lbase + i * element_size, (char *)rbase + j * element_size))&&i<n1)
        {
            memcpy((char *)base + k * element_size, (char *)lbase + i * element_size, element_size);
            i++;
        }
        else 
        {
            memcpy((char *)base + k * element_size, (char *)rbase + j * element_size, element_size);
            j++;
        }
    }
    for (int i = 0; i < n1; i++)
    {
        cout << "a2:" << *(double *)(lbase + i * element_size) << "\t";
    }
    for (int i = 0; i < n2; i++)
    {
        cout << "b2:" << *(double *)(rbase + i * element_size) << "\t";
    }
    cout << endl;
}
void SplitSort(void *base, unsigned l, unsigned r, unsigned element_size, bool (*cmp)(const void *, const void *))
{
    for (int i = l; i < r; i++)
    {
        cout << *(double *)((char *)base + i * element_size) << "\t";
    }
    cout << endl;
    if (l >= r - 1)
        return;
    int imid = (l + r) / 2;
    SplitSort(base, l, imid, element_size, cmp);
    SplitSort(base, imid, r, element_size, cmp);
    Merge(base, l, imid, r, element_size, cmp);
}

void MergeSort(void *base, unsigned count, unsigned element_size, bool (*cmp)(const void *, const void *))
{
    SplitSort(base, 0, count, element_size, cmp);
}
int main()
{
    double a[10] = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
    MergeSort(a, 10, sizeof(double), doubleCmp);
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
}