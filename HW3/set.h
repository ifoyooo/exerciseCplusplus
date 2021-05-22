#include <iostream>
#include <assert.h>
#include <cstring>
#define SIZE_ONCE 10
class FloatSet
{
    private:
    float *numbers;
    int cnt;    
    int capbility;

    public:
    FloatSet();
    FloatSet(const FloatSet& s);
    ~FloatSet();
    bool is_empty() const;
    int size() const;
    bool is_element(float e)const;
    bool is_subset(const FloatSet& s) const; 
    bool is_equal(const FloatSet& s) const;
    bool insert(float e);
    bool remove(float e);
    void display() const;
    FloatSet union2(const FloatSet &s) const;
    FloatSet intersection2(const FloatSet &s) const;
    FloatSet difference2(const FloatSet& s) const; 
    FloatSet operator+(const FloatSet &s) const ;
    FloatSet operator-(const FloatSet&s) const;
    FloatSet operator*(const FloatSet &s) const;
 

};