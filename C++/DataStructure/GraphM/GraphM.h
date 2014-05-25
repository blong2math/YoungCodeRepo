#ifndef GRAPHMATRIX
#define GRAPHMATRIX

#include <iostream>
#include "Graph.h"


using namespace std;

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
		delete [] mark;
		for (int i = 0; i < numVertice; i++){
			delete [] matrix[i];
		}
		delete [] matrix;
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

#endif