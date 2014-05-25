#ifndef GRAPHBASE
#define GRAPHBASE

#include <iostream>
#include <string>
#include "lquene.h"
#include "lstack.h"

#ifndef GRAPHMARK
#define GRAPHMARK
#define UNVISITED 0
#define VISITED 1
#endif

using namespace std;

class Graph{
private:
	void operator =(const Graph&){};

	Graph(const Graph&){};
public:
	Graph(){};

	virtual ~Graph(){};

	// Initialization
	virtual void init(int n) = 0;

	// Number of vertices and edges;
	virtual int vertex() = 0;
	virtual int edge() = 0;

	// Neighbor Vertice
	virtual int first(int v) = 0;
	virtual int next(int v, int w) = 0;

	// Edge operating
	virtual void setEdge(int v1, int v2, int weight) = 0;
	virtual void delEdge(int v1, int v2) = 0;
	virtual bool isEdge(int v1, int v2) = 0;

	// Weight operating
	virtual int weight(int v1, int v2) = 0;

	// Mark operating
	virtual int getMark(int v) = 0;
	virtual void setMark(int v, int mark) = 0;


};

void DFS(Graph* G, int v1){
	cout << "Now visit vertex " << v1 << endl;
	G->setMark(v1, VISITED);
	for (int v2 = G->first(v1); v2 < G->vertex(); v2 = G->next(v1, v2)){
		if (G->getMark(v2) == UNVISITED){
			DFS(G, v2);
		}
	}
}

void BFS(Graph* G, int v1){
	G->setMark(v1, VISITED);
	LQueue<int> search = LQueue<int>();
	while (search.getLength() != 0){
		int now = search.dequeue();
		cout << "Now visit vertex " << now << endl;
		for (int v2 = G->first(now); v2 < G->vertex(); v2 = G->next(now, v2)){
			if (G->getMark(v2) == UNVISITED){
				search.enqueue(v2);
			}
		}
		G->setMark(now, VISITED);
	}
}

void TopologySort(Graph* G){
	int* indeg = new int[G->vertex()];
	for (int v = 0; v < G->vertex(); v++){
		indeg[v] = 0;
	}
	for (int v1 = 0; v1 < G->vertex(); v1++){
		for (int v2 = G->first(v1); v2 < G->vertex(); v2 = G->next(v1, v2)){
			indeg[v2]++;
		}
	}
	LStack<int> seq = LStack<int>();
	for (int v = 0; v < G->vertex(); v++){
		if (indeg[v] == 0){
			seq.push(v);
		}
	}
	while (seq.length() != 0){
		int v1 = seq.pop();
		cout << "do vertex " << v1 << endl;
		G->setMark(v1, VISITED);
		for (int v2 = G->first(v1); v2 < G->vertex(); v2 = G->next(v1, v2)){
			indeg[v2]--;
		}
		for (int v = 0; v < G->vertex(); v++){
			if (indeg[v] == 0 && G->getMark(v1) != VISITED){
				seq.push(v);
			}
		}
	}
}

void Dijkstra(Graph* G, int* D, int s, int max){
	void Dijkstra(Graph* G, int* D, int s, int max){
	for (int i = 0; i < G->vertex(); i++){
		D[i] = max * G->vertex();
	}
	D[s] = 0;
	int now = s;
	G->setMark(s, VISITED);
	for (int i = 0; i < G->vertex() - 1; i++){
		int min_point = -1;
		int min_wt = max * G->vertex();
		for (int v2 = G->first(now); v2 < G->vertex(); v2 = G->next(now, v2)){
			if (v2 != now){
				int temp_wt = G->weight(now, v2);
				if (D[v2] > D[now] + temp_wt && temp_wt != -1){
					D[v2] = D[now] + temp_wt;
				}
				if (G->getMark(v2) == UNVISITED && D[v2] < min_wt){
					min_point = v2;
					min_wt = D[v2];
				}
			}
		}
		if (min_point == -1){
			cout << "Wrong happend!" << endl;
			break;
		}
		else{
			now = min_point;
		}
	}
}
}

void FloydWarshall(Graph* G, int max, int** dist, string** path){
	// Initialize Distance Matrix
	int n = G->vertex();
	dist = new int*[n];
	path = new string*[n];
	for (int i = 0; i < n; i++){
		dist[i] = new int[n];
		path[i] = new string[n];
	}
	for (int v1 = 0; v1 < n; v1++){
		for (int v2 = 0; v2 < n; v2++){
			if (v1 == v2){
				dist[v1][v2] = 0;
				path[v1][v2] = "";
			}
			else{
				int wt = G->weight(v1, v2);
				if (wt != -1){
					dist[v1][v2] = G->weight(v1, v2);
					// int to string
					char buf[10];
					itoa(v1, buf, 10);
					string sv1(buf);
					itoa(v2, buf, 10);
					string sv2(buf);
					path[v1][v2] = sv1 + " " + sv2;
				}
				else{
					dist[v1][v2] = max * n + 1;
					path[v1][v2] = "no direct path";
				}
			}
		}
	}

	// Floyd-Warshall
	for (int k = 0; k < n; k++){
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					path[i][j] = path[i][k] + " " + path[k][j];
				}
			}
		}
	}
}

void Prim(Graph* G, int* D, int s, int max){
	for (int v = 0; v < G->vertex(); v++){
		D[v] = max;
	}
	D[s] = 0;
	for (int v = G->first(s); v < G->vertex(); v = G->next(s, v)){
		D[v] = G->weight(s, v);
	}
	int v1 = s;
	for (int i = 0; i < G->vertex() - 1; i++){
		int min_wt = max;
		int min_point = -1;
		for (int v2 = G->first(v1); v2 < G->vertex(); v2 = G->next(v1, v2)){
			if (D[v2] != 0){
				if (G->weight(v1, v2) < min_wt){
					min_point = v2;
				}
			}
		}
		cout << "MST insert edge (" << v1 << ", " << min_point << ")!" << endl;
		int v1 = min_point;
		for (int v3 = G->first(min_point); v3 < G->vertex(); v3 = G->next(min_point, v3)){
			if (D[v3] > G->weight(min_point, v3)){
				D[v3] = G->weight(min_point, v3);
			}
		}
	}
}

void Kruskal(Graph* G){

}

#endif