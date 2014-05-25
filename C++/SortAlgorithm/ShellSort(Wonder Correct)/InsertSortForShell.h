#ifndef INSSORTFORSHELL
#define INSSORTFORSHELL

template<typename E>
void insert_sort_for_shell(E* A, int n, int b, int e, int foot){
	if (b < 0){
		b = 0;
	}
	if (e > n){
		e = n;
	}
	for (int i = b + foot; i <= e; i = i + foot){
		for (int j = i; j >= b + foot; j = j - foot){
			if (A[j - foot] > A[j]){
				Swap(A[j], A[j - foot]);
			}
		}
	}
}


#endif
#ifndef SWAP
#define SWAP

template<typename E>
void Swap(E& a, E& b){
	E temp = a;
	a = b;
	b = temp;

}
#endif