#include "set.h"

FloatSet::FloatSet()
{
    cnt=0;
    numbers=new float[SIZE_ONCE];
    capbility=SIZE_ONCE;
}
FloatSet::FloatSet(const FloatSet &s)
{
    cnt=s.cnt;
    capbility=s.capbility;
    assert(capbility%SIZE_ONCE==0);
    numbers=new float[capbility];
    memcpy(numbers,s.numbers,sizeof(float)*capbility);
}
FloatSet::~FloatSet()
{
    delete []numbers;
}
bool FloatSet::is_empty() const
{
    return cnt==0;   
}
int  FloatSet::size() const
{
    return cnt;
}
bool FloatSet::is_element(float e) const
{
    for (int i=0;i<cnt;i++)
    {
        if (numbers[i]==e)
        {
            return true;
        }
    }
    return false;
}
bool FloatSet::is_subset(const FloatSet &s) const
{
    for (int i=0;i<s.cnt;i++)
    {
        if (!is_element(s.numbers[i]))
        {
            return false;
        }
    }
    return true;
}
bool FloatSet::is_equal(const FloatSet &s) const
{
    if (s.cnt!=cnt) return false;
    //大小相同并且是子集。
    return is_subset(s);
}
bool FloatSet::insert(float e)
{
    if (is_element(e))
    {
        return false;
    }
    if (cnt==capbility)
    {
        capbility+=SIZE_ONCE;
        float *tmp=new float[capbility];
        memcpy(tmp,numbers,(capbility-SIZE_ONCE)*sizeof(float));
        delete []numbers;
        numbers=tmp;        
    }
    numbers[cnt]=e;
    cnt++;
    return true;
}
bool FloatSet::remove(float e)
{
    for (int i=0;i<cnt;i++)
    {
        if (numbers[i]==e)
        {
            for (int j=i;j<cnt-1;j++)
            {
                numbers[j]=numbers[j+1];
            }
            cnt--;
            if (cnt==capbility-SIZE_ONCE)
            {
                capbility-=SIZE_ONCE;
                float *tmp=new float[capbility];
                memcpy(tmp,numbers,capbility*sizeof(float));
                delete []numbers;
                numbers=tmp;
            }
            return true;
        }
    }

    return false;
}
void FloatSet::display() const
{
    for (int i=0;i<cnt;i++)
    {
        printf("%f , ",numbers[i]);
    }
    printf("\n");
}

FloatSet FloatSet::union2(const FloatSet &s) const
{
    FloatSet ans(*this);
    for (int i=0;i<s.cnt;i++)
    {
        if (!is_element(s.numbers[i]))
        {
            ans.insert(s.numbers[i]);
        }
    }
    return ans;


}
FloatSet FloatSet::intersection2(const FloatSet &s) const
{
    FloatSet ans(*this);
    for (int i=0;i<cnt;i++)
    {
        if (!s.is_element(numbers[i]))
        {
            ans.remove(numbers[i]);
        }
    }
    return ans;
}
FloatSet FloatSet::difference2(const FloatSet &s) const
{
    FloatSet ans;
    for (int i=0;i<cnt;i++)
    {
        if (!s.is_element(numbers[i]))
        {
            ans.insert(numbers[i]);
        }
    }
    return ans;
}
FloatSet FloatSet::operator+(const FloatSet &s) const
{
    return union2(s);
}
FloatSet FloatSet::operator*(const FloatSet &s) const
{
    return intersection2(s);
}
FloatSet FloatSet::operator-(const FloatSet &s) const
{
    return difference2(s);
}