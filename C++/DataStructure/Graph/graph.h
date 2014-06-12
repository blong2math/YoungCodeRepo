#ifndef GRAPHBASE
#define GRAPHBASE

#include <iostream>
#include <string>
#include "quene.h"
#include "stack.h"
#include "list.h"

#ifndef GRAPHMARK
#define GRAPHMARK
#define UNVISITED 0
#define VISITED 1
#endif

using namespace std;

#ifndef EDGE
#define EDGE

class Edge{
	int vert;
	int wt;
public:
	Edge(){
		vert = -1;
		wt = -1;
	}

	Edge(int v, int w){
		vert = v;
		wt = w;
	}

	int vertex(){
		return vert;
	}

	int weight(){
		return wt;
	}
};

#endif

// Base class for graph
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

// Linked representation graph
class GraphL : public Graph{
private:
	LList<Edge>** vert;
	int numVertex;
	int numEdge;
	int *mark;

public:
	GraphL(int numVert){
		init(numVert);
	}

	~GraphL(){
		delete[] mark;
		for (int i = 0; i < numVertex; i++){
			delete[] vert[i];
		}
		delete vert;
	}

	void init(int n){
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n];
		for (i = 0; i < numVertex; i++){
			mark[i] = UNVISITED;
		}
		vert = (LList<Edge>**) new LList<Edge>*[numVertex];
		for (i = 0; i < numVertex; i++){
			vert[i] = new LList<Edge>();
		}
	}

	int vertex(){
		return numVertex;
	}

	int edge(){
		return numEdge;
	}

	int first(int v){
		if (vert[v]->getLength() == 0){
			return numVertex;
		}
		vert[v]->moveToStart();
		Edge it = vert[v]->getValue();
		return it.vertex();
	}

	int next(int v, int w){
		Edge it;
		if (isEdge(v, w)){
			if (vert[v]->currPos() + 1 < vert[v]->getLength()){
				vert[v]->next();
				it = vert[v]->getValue();
				return it.vertex();
			}
		}
		else{
			return numVertex;
		}
	}

	void setEdge(int v, int w, int weight){
		if (weight <= 0){
			cout << "Weight must be greater than zero!" << endl;
			return;
		}
		Edge currEdge(w, weight);
		if (isEdge(v, w)){
			vert[v]->remove();
			vert[v]->insert(currEdge);
		}
		else{
			numEdge++;
			for (vert[v]->moveToStart(); vert[v]->currPos() < vert[v]->getLength(); vert[v]->next()){
				Edge temp = vert[v]->getValue();
				if (temp.vertex() > w){
					break;
				}
			}
			vert[v]->insert(currEdge);
		}
	}

	bool isEdge(int v, int w){
		Edge it;
		for (vert[v]->moveToStart(); vert[v]->currPos() < vert[v]->getLength(); vert[v]->next()){
			Edge temp = vert[v]->getValue();
			if (temp.vertex() == w){
				return true;
			}
		}
		return false;
	}

	void delEdge(int v, int w){
		if (isEdge(v, w)){
			vert[v]->remove();
			numEdge--;
		}
	}

	int weight(int v1, int v2){
		if (isEdge(v1, v2)){
			Edge temp = vert[v1]->getValue();
			return temp.weight();
		}
		else{
			return 0;
		}
	}

	int getMark(int v){
		return mark[v];
	}

	void setMark(int v, int val){
		mark[v] = val;
	}
};

// Matrix representation graph
class GraphM : public Graph{
private:
	int numVertice;
	int numEdge;
	int **matrix;
	int *mark;
public:
	GraphM(int vertice){
		init(vertice);
	}

	~GraphM(){
		delete[] mark;
		for (int i = 0; i < numVertice; i++){
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void init(int n){
		numVertice = n;
		numEdge = 0;
		mark = new int[n];
		for (int i = 0; i < numVertice; i++){
			mark[i] = UNVISITED;
		}
		matrix = (int**) new int*[numVertice];
		for (int i = 0; i < numVertice; i++){
			matrix[i] = new int[numVertice];
		}
		for (int i = 0; i < numVertice; i++){
			for (int j = 0; j < numVertice; j++){
				matrix[i][j] = -1;
			}
		}
	}

	int vertex(){
		return numVertice;
	}

	int edge(){
		return numEdge;
	}

	int first(int v){
		for (int i = 0; i < numVertice; i++){
			if (matrix[v][i] != 0){
				return i;
			}
		}
		return numVertice;
	}

	int next(int v, int w){
		for (int i = w + 1; i < numVertice; i++){
			if (matrix[v][i] != 0){
				return i;
			}
		}
		return numVertice;
	}

	void setEdge(int v1, int v2, int weight){
		if (v1 < numVertice && v2 < numVertice){
			if (weight > 0){
				matrix[v1][v2] = weight;
				numEdge++;
			}
			else{
				cout << "the weight must be more than zero!" << endl;
				return;
			}
		}
		else{
			cout << "out of index, not exist this vertice!" << endl;
			return;
		}
	}

	void delEdge(int v1, int v2){
		if (v1 < numVertice && v2 < numVertice){
			matrix[v1][v2] = 0;
			numEdge--;
		}
		else{
			cout << "out of index, not exist this vertice!" << endl;
			return;
		}
	}

	bool isEdge(int v1, int v2){
		if (v1 < numVertice && v2 < numVertice){
			return (matrix[v1][v2] != 0);
		}
		else{
			return false;
		}
	}

	int weight(int v1, int v2){
		if (v1 < numVertice && v2 < numVertice){
			return matrix[v1][v2];
		}
		else{
			cout << "out of index, not exist this vertice!" << endl;
			return 0;
		}
	}

	int getMark(int v){
		if (v < numVertice){
			return mark[v];
		}
		else{
			cout << "out of index, not exist this vertice!" << endl;
			return -1;
		}
	}
	void setMark(int v, int m){
		if (m == 0 || m == 1){
			if (v < numVertice){
				mark[v] = m;
			}
			else{
				cout << "out of index, not exist this vertice!" << endl;
				return;
			}
		}
		else{
			cout << "wrong mark" << endl;
			return;
		}
	}
};

// Depth-first search
void dfs(Graph* G, int v1){
	cout << "Now visit vertex " << v1 << endl;
	G->setMark(v1, VISITED);
	for (int v2 = G->first(v1); v2 < G->vertex(); v2 = G->next(v1, v2)){
		if (G->getMark(v2) == UNVISITED){
			dfs(G, v2);
		}
	}
}

// Breadth-first search
void bfs(Graph* G, int v1){
	G->setMark(v1, VISITED);
	LQueue<int> search = LQueue<int>();
	while (search.length() != 0){
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

// Topology Sort
void topology_sort(Graph* G){
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

// Dijkstra algorithm for single-source distance calc
void dijkstra(Graph* G, int* D, int s, int max){
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

// floyd-warshall algorithm for multi-distance calc
void floyd_warshall(Graph* G, int max, int** dist, string** path){
	// Initialize Distance Matrix
	int n = G->vertex();
	dist = new int*[n];
	//path = new string*[n];
	for (int i = 0; i < n; i++){
		dist[i] = new int[n];
		//path[i] = new string[n];
	}
	for (int v1 = 0; v1 < n; v1++){
		for (int v2 = 0; v2 < n; v2++){
			if (v1 == v2){
				dist[v1][v2] = 0;
				//path[v1][v2] = "";
			}
			else{
				int wt = G->weight(v1, v2);
				if (wt != -1){
					dist[v1][v2] = G->weight(v1, v2);
					// int to string
					/*
					char buf[10];
					itoa(v1, buf, 10);
					string sv1(buf);
					itoa(v2, buf, 10);
					string sv2(buf);
					path[v1][v2] = sv1 + " " + sv2;
					*/
				}
				else{
					dist[v1][v2] = max * n + 1;
					/*
					path[v1][v2] = "no direct path";
					*/
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

// prim algorithm to find a minimal tree for a graph
void prim(Graph* G, int* D, int s, int max){
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

// kruskal algorithm to find a minimal tree for a graph
void kruskal(Graph* G){

}

#endif