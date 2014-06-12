//coding: cplusplus

//args: x: the pointer to x-axis values
//		y: the pointer to y-axis values
//		insert: the x-axis value of insert point
//rets:	func: the y-axis value of insert point
void Lagrange(double* x, double* y, double insert)
{
	double func = 0;

	for(int i = 0; i < 4; i++)
	{
		double a = 1;
		for(int j = 0; j < 4; j++){
			if(i == j){
			}
			else{
				a = a * (insert - x[j]);
				a = a / (x[i] - x[j]);
			}
		}
		
		func = func + a * y[i];
	}

	cout << "the function of insert is " << func <<endl;
}