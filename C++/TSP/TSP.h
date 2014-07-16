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

// �ж��Ƿ��Ѿ��߹��ýڵ�
bool not_in(int* seq, int n, int idx){
	bool isIn = true;
	for (int i = 0; i < n; i++){
		if (seq[i] == idx){
			isIn = false;
		}
	}
	return isIn;
}

// ��������
void my_swap(int* seq, int idx1, int idx2){
	int temp = seq[idx1];
	seq[idx1] = seq[idx2];
	seq[idx2] = temp;
}

void TSP_SA(){
	// ��������
	int n = 0;
	cout << "�����������:" << endl;
	cin >> n;
	GraphM g = GraphM(n);
	int temp_dist = 0;
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			cout << "���������" << i + 1 << "������" << j + 1 << "�ľ���(Ŀǰ֧��int):" << endl;
			cin >> temp_dist;
			g.setEdge(i, j, temp_dist);
			g.setEdge(j, i, temp_dist);
		}
	}
	int source = 0;
	cout << "�������������:" << endl;
	cin >> source;
	source--;

	// ģ���˻��㷨
	float T = pow(2, n); // �¶�
	float alpha = 0.999; // ����ϵ��
	int* path = new int[n + 1];
	path[0] = path[n] = source;

	// ����̰���㷨��һ���϶�·��
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

	// ��ʱ�����·��
	int min_dist = total_distance(path, n, &g);

	while (T > 1){
		// ���ö������������������ֱ���õ�һ�����ƺ�·��
		// ��������Bolzmman���̶�·�����޸�
		for (int i = 0; i < 100; i++){
			int idx1 = (rand() % (n - 1)) + 1; // �������path�ĵڶ���ֵ�͵�n-1��ֵ
			int idx2 = (rand() % (n - 1)) + 1;
			my_swap(path, idx1, idx2);

			int temp_min = total_distance(path, n, &g);
			if (min_dist > temp_min){
				min_dist = temp_min;
			}
			else{
				if ((rand() / RAND_MAX) < exp(-(temp_min - min_dist) / T)){
					min_dist = temp_min; // ������ʺ��ʣ����޸���Сֵ
				}
				else{
					my_swap(path, idx1, idx2); // ���粻���򻻻���
				}
			}
		}
		T = T * alpha;
	}

	cout << "����Ľ������·��Ϊ:" << min_dist << endl;
	cout << "·��Ϊ:";
	for (int i = 0; i <= n; i++){
		cout << path[i] + 1 << " ";
	}
	cout << endl;
}

#endif