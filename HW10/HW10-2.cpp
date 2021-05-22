#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;
class Point {
		int x, y;
	public:
		Point(int _x=0, int _y=0) : x(_x), y(_y) {}
		int getNormSqure() const {
			return x*x+y*y;
		}
		int getX()const {
			return x;
		}
		int getY()const {
			return y;
		}
		void display()const {
			cout <<"x:"<< x <<" y:"<<y<<endl;
		}
};
int main() {
	vector<Point> p, q;
	p.push_back(Point(-1, -1));
	p.push_back(Point(-2,-2));
	p.push_back(Point(2, 2));
	p.push_back(Point(2,100));
	p.push_back(Point(3, 3));
	p.push_back(Point(4, 4));
	p.push_back(Point(5, 5));
	p.push_back(Point(6, 6));
	q.push_back(Point(1, 1));
	q.push_back(Point(2, 2));
	q.push_back(Point(2,100));
	q.push_back(Point(3, 3));
	q.push_back(Point(4, 4));
	q.push_back(Point(5, 5));
	q.push_back(Point(6, 6));
	q.push_back(Point(-2, -2));
	q.push_back(Point(-3,-3));
// 1. 对p、q中顶点"(x, y)" 升序排序并输出(要求按照x大小，若x相等则按y的大小)
// 2. 升序输出p中满足x > 0, y > 0的所有顶点与(0, 0)的距离的平方
// 3. 根据1排序后p中顶点的顺序计算满足x > 0, y > 0相邻两个顶点的距离的平方和
// 4. 计算p中x > 0, y > 0的顶点与(0, 0)的距离的平方和
// 5. p、q在每个象限顶点数目相同，统计在1排序后p、q中满足x < 0, y < 0的顶点中按顺序所对
//应顶点距离的平方为2的数目


//1
	sort(p.begin(),p.end(),[](const Point &p1,const Point &p2)->bool {return p1.getX()<p2.getX()|| (p1.getX()==p2.getX()&& p1.getY()<p2.getY());});
	sort(q.begin(),q.end(),[](const Point &p1,const Point &p2)->bool {return p1.getX()<p2.getX()|| (p1.getX()==p2.getX()&& p1.getY()<p2.getY());});
	cout<<"task1\n";
	for_each(p.begin(),p.end(),[](const Point& p)->void {p.display();});
	for_each(q.begin(),q.end(),[](const Point& p)->void {p.display();});

//2
	cout<<"task2\n";
	vector<Point> lst;
	copy_if(p.begin(),p.end(),back_inserter(lst),[](const Point &p) {
		return p.getX()>0 && p.getY()>0;
	});
	sort(lst.begin(),lst.end(),[](const Point &p1,const Point &p2)->bool {return p1.getNormSqure()<p2.getNormSqure();});
	for_each(lst.begin(),lst.end(),[](const Point p1)->void {p1.display();});


	cout<<"task3\n";
	lst.clear();
	copy_if(p.begin(),p.end(),back_inserter(lst),[](const Point &p) {
		return p.getX()>0 && p.getY()>0;
	});
	vector<Point> lsttmp;
	transform(lst.begin()+1,lst.end(),lst.begin(),back_inserter(lsttmp),[](const Point &p1,const Point& p2)->Point {return Point(p1.getX()-p2.getX(),p1.getY()-p2.getY());});
	for_each(lst.begin(),lst.end(),[](const Point p1)->void {p1.display();});
	for_each(lsttmp.begin(),lsttmp.end(),[](const Point p1)->void {p1.display();});
	cout << accumulate(lsttmp.begin(),lsttmp.end(),0,[](int partial,const Point& p)->int {return partial + p.getNormSqure();})<<endl;

	cout <<"task4\n";
	cout << accumulate(lst.begin(),lst.end(),0,[](int partial,const Point& p)->int {return partial + p.getNormSqure();})<<endl;


	cout <<"task5\n";
	vector<Point> lst1;
	vector<Point> lst2;
	vector<Point> lst3;
	copy_if(p.begin(),p.end(),back_inserter(lst1),[](const Point &p) {
		return p.getX()<0 && p.getY()<0;
	});
	copy_if(q.begin(),q.end(),back_inserter(lst2),[](const Point &p) {
		return p.getX()<0 && p.getY()<0;
	});
	transform(lst1.begin(),lst1.end(),lst2.begin(),back_inserter(lst3),[](const Point &p1,const Point& p2)->Point {return Point(p1.getX()-p2.getX(),p1.getY()-p2.getY());});
	cout<<count_if(lst3.begin(),lst3.end(),[](const Point &p)->bool {return p.getNormSqure()==2;})<<endl;
}
