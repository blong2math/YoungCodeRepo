#ifndef SHELLSORT
#define SHELLSORT

#include "InsertSortForShell.h"

template<typename E>
void shell_sort(E* A, int n){
	int gap = n - 1;
	int foot = 1;
	while (gap > 1){
		gap = gap / 2;
		foot = foot * 2;
		for (int i = 0; i <= gap; i++){
			insert_sort_for_shell(A, n - 1, i, i + gap, foot);
		}
	}
	insert_sort_for_shell(A, n, 0, n - 1, 1);
}

#endif