#include <vector>
#include <functional>
#include <cmath>
#include <algorithm>
#include <iostream>


//可以使用多个using namespace .但是如果两个之间有重名的话，那么就得写开了。
using namespace std;
using namespace std::placeholders;
/* 求导数函数，对某个函数f在点x0处求得导数
* f'(x0) = (f(x0)-f(x0-d))/d
* params:
* x: x0
* d: d
* f: f
*/

//求导函数
double derivative(double x, double d, double (*f)(double)) {
    return (f(x)-f(x-d))/d;
}



function<double(double(*)(double))> bind_derivative(double x,double d)
{
    return bind(derivative,x,d,_1);
}

// 或者直接用auto 但是要用--std=c++1y.

function<function<double(double(*)(double))>(double)> bind_derivative(double x)
{
    return [x](double d)->function<double(double(*)(double))>{return bind(derivative,x,d,_1);};
}

int main() {
 std::vector<double (*)(double)> funcs = {sin, cos, tan, exp, sqrt, log, log10};
// ⽬标函数
 //bind_derivative接受两个参数，同时返回一个接受一个参数的函数。
 auto d1 = bind_derivative(1, 0.000001); // 在x=1处求导数的函数d1
 auto d2 = bind_derivative(1)(0.000001); // 在x=1处求导数的函数d2
 std::vector<double> result1, result2;
 std::transform(funcs.begin(), funcs.end(), std::back_inserter(result1), d1);
 std::transform(funcs.begin(), funcs.end(), std::back_inserter(result2), d2);
 // result1的结果与result2的结果相同
 for_each(result1.begin(),result1.end(),[](double a)->void{cout <<a<<endl;});
 for_each(result2.begin(),result2.end(),[](double a)->void{cout <<a<<endl;});

 return 0;
}