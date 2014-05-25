#ifndef BUBBLESORT
#define BUBBLESORT

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