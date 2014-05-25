#ifndef SELECTSORT
#define SELECTSORT

template<typename T>
void select_sort(T A[], int length){
	for (int i = 0; i < length; i++){
		int lowest_index = i;
		for (int j = i + 1; j < length; j++){
			if (A[j] < A[lowest_index]){
				lowest_index = j;
			}
		}
		Swap(A[i], A[lowest_index]);
	}
}
#endif

#ifndef SWAP
#define SWAP
template<typename T>
void Swap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}

#endif