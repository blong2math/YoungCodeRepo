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