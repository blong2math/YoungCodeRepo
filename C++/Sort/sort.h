#ifndef SORT
#define SORT

#include "MinHeap.h"

// Bubble Sort Algorithm
template<typename E>
void bubble_sort(E* A, int n){
	for (int i = 0; i < n; i++){
		for (int j = n - 1; j > i; j--){
			if (A[j] < A[j - 1]){
				Swap(A[j], A[j - 1]);
			}
		}
	}
}

// Insert Sort Algorithm
template<typename E>
void insert_sort(E* A, int n){
	for (int i = 1; i < n; i++){
		for (int j = i; j > 0; j--){
			if (A[j] < A[j - 1]){
				Swap(A[j], A[j - 1]);
			}
			else{
				break;
			}
		}
	}
}

// Select Sort Algorithm
template<typename E>
void select_sort(E A[], int n){
	for (int i = 0; i < n; i++){
		int lowest_index = i;
		for (int j = i + 1; j < n; j++){
			if (A[j] < A[lowest_index]){
				lowest_index = j;
			}
		}
		Swap(A[i], A[lowest_index]);
	}
}

// Heap Sort Algorithm
template<typename E>
void heap_sort(E a[], int n){
	MinHeap<E> h = MinHeap<E>(a, n - 1, n - 1);
	for (int i = 0; i < n; i++){
		h.removefirst();
	}
}

// Quick Sort Algorithm
template <typename E>
void quick_sort(E A[], int n){
	QuickSort(A, 0, n - 1);
}

// Facilitate Function for Quick Sort(Undecorated)
template <typename E>
void QuickSort(E ls[], int left, int right){
	if (left < right){
		if (ls[left] > ls[right]){
			Swap(ls[left], ls[right]);
		}
		int pivot = ls[left];
		int i = left;
		int j = right + 1;
		do{
			do{
				i++;
			} while (ls[i] < pivot);
			do{
				j--;
			} while (ls[j] > pivot && i < j);
			if (i < j){
				Swap(ls[i], ls[j]);
			}
		} while (i < j);
		Swap(ls[j], ls[left]);
		QuickSort(ls, left, j - 1);
		QuickSort(ls, j + 1, right);
	}
}

// Facilitate function to merge two right-order sequences
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

// Undecorated version of merge sort
template<typename E>
void raw_merge_sort(E* A, int b, int e, int n){
	if (b >= e){
		return;
	}
	raw_merge_sort(A, b, (e - b) / 2 + b, n);
	raw_merge_sort(A, (e - b) / 2 + 1 + b, e, n);
	merge(A, b, (e - b) / 2 + 1 + b, e);
}

// Merge Sort Algorithm
template<typename E>
void merge_sort(E* A, int n){
	//it is a decorator of merge_sort
	raw_merge_sort(A, 0, n - 1, n);
}

// Facilitate function insert sort with interval for shell sort
template<typename E>
void insert_sort_for_shell(E A[], int b, int e, int foot){
	for (int i = b; i <= e; i += foot){
		for (int j = i; j >= b; j -= foot){
			if (A[j] < A[j - foot]){
				Swap(A[j], A[j - foot]);
			}
			else{
				break;
			}
		}
	}
}

// Shell Sort Algorithm
template<typename E>
void shell_sort(E A[], int n){
	int foot = n / 2;
	while (foot > 1){
		for (int i = 0; i < foot; i++){
			int count = (n - i - 1) / foot;
			insert_sort_for_shell(A, i, i + count * foot, foot);
		}
		foot = foot / 2;
	}
	insert_sort_for_shell(A, 0, n - 1, 1);
}

#endif

#ifndef SWAP
#define SWAP

template<typename E>
void Swap(E& i, E& j){
	E temp = i;
	i = j;
	j = temp;
}

#endif

#ifndef DEBUG_TOOL
#define DEBUG_TOOL

template<typename E>
void display(E A[], int n){
	for (int i = 0; i < n; i++){
		cout << " " << A[i];
	}
	cout << endl;
}

#endif