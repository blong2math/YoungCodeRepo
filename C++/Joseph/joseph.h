#ifndef JOSEPH
#define JOSEPH

#include <iostream>
#include "list.h"

using namespace std;

struct person{
	int psw;
	int no;

	person(int p, int n){
		psw = p;
		no = n;
	}

	person(){}
};

void joseph(){
	int n;
	cout << "请输入Joseph的人数:" << endl;
	cin >> n;

	CLList<person> cycle = CLList<person>();
	for (int i = 1; i <= n; i++){
		int psw;
		cout << "请输入第" << i << "个人的密码:" << endl;
		cin >> psw;
		person p = person(psw, i);
		cycle.insert(p);
		cycle.next();
	}

	int m;
	cout << "请输入m的值：" << endl;
	cin >> m;
	cout << "依次出来的人为：";
	while (cycle.length() > 1){
		for (int i = 0; i < m; i++){
			cycle.next();
		}
		person p = cycle.remove();
		m = p.psw;
		cout << p.no << " ";
	}
	cout << cycle.remove().no << endl;

}

#endif