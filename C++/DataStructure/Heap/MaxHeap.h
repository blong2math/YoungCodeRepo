#ifndef HEAP
#define HEAP

#include <iostream>

using namespace std;

template<typename E>
class MaxHeap{
private:
	E* heap;
	int maxsize;
	int n;

	void siftdown(int pos){
		while (pos <= n/2){
			if (pos * 2 + 1 <= n){
				if (heap[pos * 2 + 1] > heap[pos * 2]){ //Check the max of lc and rc
					if (heap[pos * 2 + 1] > heap[pos]){ //Then swap if it more than parent
						Swap(pos, pos * 2 + 1);
						pos = pos * 2 + 1;
					}
					else{
						return;
					}
				}
				else{
					if (heap[pos * 2] > heap[pos]){
						Swap(pos, pos * 2);
						pos = pos * 2;
					}
					else{
						return;
					}
				}
			}
			else{
				if (heap[pos * 2] > heap[pos]){
					Swap(pos, pos * 2);
					pos = pos * 2;
				}
				else{
					return;
				}
			}
		}
	}

public:
	MaxHeap(E* h, int num, int max){
		heap = h;
		n = num;
		maxsize = max;
		BuildHeap();
	}

	int size(){
		return n;
	}

	bool isLeaf(int num) const{
		if (num > (n / 2) && num <= n){
			return true;
		}
		else{
			return false;
		}
	}

	int leftChild(int num) const{
		if (num * 2 <= n && num > 0){
			return num * 2;
		}
		else{
			return NULL;
		}
	}

	int rightChild(int num) const{
		if (num * 2 + 1 <= n && num > 0){
			return num * 2 + 1;
		}
		else{
			return NULL;
		}
	}

	int parent(int num) const{
		return (int)(num / 2);
	}

	void BuildHeap(){
		for (int i = n / 2; i >= 0; i--){
			siftdown(i);
		}
	}

	void print() const{
		for (int i = 0; i <= n; i++){
			cout << heap[i] << endl;
		}
	}

	void insert(const E& e){
		if (n < maxsize){
			n++;
			heap[n] = e;
		}
		else{
			cout << "out of range" << endl;
			return;
		}
		int temp = n;
		for (int i = n / 2; i >= 0; i = i / 2){
			if (heap[i] < heap[temp]){
				Swap(i, temp);
				temp = i;
			}
			else{
				break;
			}
		}
	}

	E removefirst(){
		Swap(0, n);
		n--;
		BuildHeap();
		return heap[n];
	}

	E remove(int pos){
		if (pos <= n){
			Swap(pos, n);
			BuildHeap();
		}
		else{
			cout << "out of range" << endl;
		}
	}

	//Facility functions
	void Swap(int pos1, int pos2){
		E temp = heap[pos1];
		heap[pos1] = heap[pos2];
		heap[pos2] = temp;
	}
};

#endif