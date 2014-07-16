#ifndef PERMUTATION
#define PERMUTATION

#ifndef FACTORIAL
#define FACTORIAL

int fact(int n){
	if (n == 1){
		return 1;
	}
	else{
		return fact(n - 1) * n;
	}
}
#endif

int** _gen_perm(int **p, int n, int ins){
	int **temp = new int*[fact(n + 1)];
	for (int i = 0; i < fact(n + 1); i++){
		temp[i] = new int[n + 1];
	}

	for (int l = 0; l < fact(n); l++){  // For each 
		for (int k = 0; k < n + 1; k++){
			for (int j = 0; j < k; j++){
				temp[k + l*(n + 1)][j] = p[l][j];
			}
			temp[k + l*(n + 1)][k] = ins;
			for (int j = k + 1; j < n + 1; j++){
				temp[k + l*(n + 1)][j] = p[l][j - 1];
			}
		}
	}
	for (int i = 0; i < fact(n); i++){
		delete[] p[i];
	}
	delete[] p;
	return temp;
}

int** permutation(int n){
	int** perm_list = new int*[1];
	for (int l = 1; l <= 1; l++){
		perm_list[0] = new int[1];
		perm_list[0][0] = 1;
	}
	for (int j = 1; j < n; j++){
		perm_list = _gen_perm(perm_list, j, j + 1);
	}
}
#endif