#ifndef TSP
#define TSP

#include "graph.h"
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

// n is len(seq)-1
int total_distance(int* seq, int n, Graph* g){
	int sum = 0;
	for (int i = 0; i < n; i++){
		sum += g->weight(seq[i], seq[i + 1]);
	}
	return sum;
}

// 判断是否已经走过该节点
bool not_in(int* seq, int n, int idx){
	bool isIn = true;
	for (int i = 0; i < n; i++){
		if (seq[i] == idx){
			isIn = false;
		}
	}
	return isIn;
}

// 交换函数
void my_swap(int* seq, int idx1, int idx2){
	int temp = seq[idx1];
	seq[idx1] = seq[idx2];
	seq[idx2] = temp;
}

void TSP_SA(){
	// 输入数据
	int n = 0;
	cout << "请输入城市数:" << endl;
	cin >> n;
	GraphM g = GraphM(n);
	int temp_dist = 0;
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			cout << "请输入城市" << i + 1 << "到城市" << j + 1 << "的距离(目前支持int):" << endl;
			cin >> temp_dist;
			g.setEdge(i, j, temp_dist);
			g.setEdge(j, i, temp_dist);
		}
	}
	int source = 0;
	cout << "请输入出发城市:" << endl;
	cin >> source;
	source--;

	// 模拟退火算法
	float T = pow(2, n); // 温度
	float alpha = 0.999; // 降温系数
	int* path = new int[n + 1];
	path[0] = path[n] = source;

	// 先用贪心算法求一条较短路径
	for (int i = 0; i < n; i++){
		int min_index = 0;
		int min_dist = 65000;
		for (int j = 0; j < n; j++){
			if (j != path[i] && g.weight(path[i], j) < min_dist && not_in(path, i + 1, j)){
				min_dist = g.weight(path[i], j);
				min_index = j;
			}
		}
		path[i + 1] = min_index;
	}

	// 暂时的最好路径
	int min_dist = total_distance(path, n, &g);

	while (T > 1){
		// 利用二交换法不断随机更改直到得到一个近似好路径
		// 这里利用Bolzmman过程对路径做修改
		for (int i = 0; i < 100; i++){
			int idx1 = (rand() % (n - 1)) + 1; // 随机交换path的第二个值和第n-1个值
			int idx2 = (rand() % (n - 1)) + 1;
			my_swap(path, idx1, idx2);

			int temp_min = total_distance(path, n, &g);
			if (min_dist > temp_min){
				min_dist = temp_min;
			}
			else{
				if ((rand() / RAND_MAX) < exp(-(temp_min - min_dist) / T)){
					min_dist = temp_min; // 假如概率合适，就修改最小值
				}
				else{
					my_swap(path, idx1, idx2); // 假如不对则换回来
				}
			}
		}
		T = T * alpha;
	}

	cout << "求出的近似最短路程为:" << min_dist << endl;
	cout << "路径为:";
	for (int i = 0; i <= n; i++){
		cout << path[i] + 1 << " ";
	}
	cout << endl;
}

#endif