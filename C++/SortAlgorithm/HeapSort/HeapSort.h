#ifndef HEAPSORT
#define HEAPSORT

#include "MinHeap.h"

template<typename T>
void heap_sort(T a[], int n){
	MinHeap<T> h = MinHeap<T>(a, n-1, n-1);
	T* temp = new T[n];
	for (int i = 0; i < n; i++){
		temp[i] = h.removefirst();
	}
	for (int i = 0; i < n; i++){
		a[i] = temp[i];
	}
}

#endif