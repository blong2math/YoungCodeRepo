#ifndef QUICKSORT
#define QUICKSORT

// Use for interface
template <typename T>
void quick_sort(T* A, int n){
	QuickSort(A, 0, n-1);
}

template <typename T>
void QuickSort(T* ls, int left, int right){
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
			} while (ls[j] > pivot);
			if (i < j){
				Swap(ls[i], ls[j]);
			}
		} while (i < j);
		Swap(ls[j], ls[left]);
		QuickSort(ls, left, j - 1);
		QuickSort(ls, j + 1, right);
	}
}

#endif

#ifndef SWAP
#define SWAP

template <typename T>
void Swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

#endif