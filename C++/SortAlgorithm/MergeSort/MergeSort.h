#ifndef MERGESORT
#define MERGESORT

#include <iostream>
using namespace std;

template<typename E>
void merge_sort(E* A, int n){
	//it is a decorator of merge_sort
	raw_merge_sort(A, 0, n - 1, n);
}


template<typename E>
void raw_merge_sort(E* A, int b, int e,int n){
	if (b >= e){
		return;
	}
	raw_merge_sort(A, b, (e - b) / 2 + b, n);
	raw_merge_sort(A, (e - b) / 2 + 1 + b, e, n);
	merge(A, b, (e - b) / 2 + 1 + b, e);
}

template<typename E>
void merge(E* A, int b, int m, int e){
	int i = b;
	int j = m;
	int count = 0;
	E* temp = new E[e - b + 1];
	while (i <= m - 1 && j <= e){
		if (A[i] < A[j]){
			temp[count] = A[i];
			i++;
		}
		else{
			temp[count] = A[j];
			j++;
		}
		count++;
	}
	if (i > m - 1){
		for (int k = j; k <= e; k++){
			temp[count] = A[k];
			count++;
		}
	}
	else{
		for (int k = i; k <= m - 1; k++){
			temp[count] = A[k];
			count++;
		}
	}
	for (int l = 0; l < e - b + 1; l++){
		A[b + l] = temp[l];
	}
}
#endif