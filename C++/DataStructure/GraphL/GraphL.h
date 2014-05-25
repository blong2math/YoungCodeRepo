#ifndef GRAPHLINK
#define GRAPHLINK

#include "Edge.h"
#include "Graph.h"
#include "llist.h"
#include <iostream>

using namespace std;

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
			delete [] vert[i];
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
			if (vert[v]->getCurrPos() + 1 < vert[v]->getLength()){
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
			for (vert[v]->moveToStart(); vert[v]->getCurrPos() < vert[v]->getLength(); vert[v]->next()){
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
		for (vert[v]->moveToStart(); vert[v]->getCurrPos() < vert[v]->getLength(); vert[v]->next()){
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

#endif
