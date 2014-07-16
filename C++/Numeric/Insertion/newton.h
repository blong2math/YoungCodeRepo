//coding: cplusplus

//args: x: the pointer to x-axis values
//		y: the pointer to y-axis values
//		insert1: the first differential index
//		insert2: the second differential index
//rets:	diff: the y-axis value of insert point
double Differential(double* x, double* y, int insert1, int insert2)
{
	if((insert2 - insert1) == 1)
	{
		return (y[insert1] - y[insert2])/(x[insert1] - x[insert2]);
	}
	else
	{
		return (Differential(x, y, insert1, insert2 - 1) - Differential(x, y, insert1 + 1, insert2))/(x[insert1] - x[insert2]);
	}
}

//args: x: the pointer to x-axis values
//		y: the pointer to y-axis values
//		n: the level of differential
//		insert: the x-axis value of insert point
//rets:	func: the y-axis value of insert point
void Newton(double* x, double* y, int n, double insert)
{
	double func = sqrt(insert);
	for(int i = 1; i < n; i++)
	{
		double temp = 1;
		for(int j = 0; j < i; j++)
		{
			temp = temp * (insert - x[j]);
		}
		
		//´Ë´¦ÀûÓÃ²îÉÌµÄµü´úÐÔÖÊ¼ÆËã
		func = func + Differential(x, y, 0, i) * temp;
	}

	cout << "the function of insert is " << func<<endl;
}
