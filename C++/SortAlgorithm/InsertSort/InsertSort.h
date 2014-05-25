#ifndef INSERTSORT
#define INSERTSORT

template<typename E>
void insert_sort(E* A, int n){
	for(int i = 1; i < n; i++){
		for(int j = i; j > 0; j--){
			if(A[j] < A[j-1]){
				Swap(A[j], A[j-1]);
			}else{
				break;
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