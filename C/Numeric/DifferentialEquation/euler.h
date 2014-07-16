//coding: cplusplus

//args:	left: the left x-axis value of differential region
//		right: the right x-axis value of differential region
//		foot: foot length of every differential process
//		y0: original value of y-axis
//		func: equal to dy/dx
//rets:	values: the pointer to every function value
void Euler(double left, double right, double foot, double y0, double (*func)(double x))
{
	double temp = y0;

	int n = (int) ((right - left) / foot) + 2;
	double* values = new double[n];

	for(int i = 0; i <= (right - left)/foot; i++)
	{
		if(i == 0)
		{
			cout << "the y" << i << " is " << y0 <<endl;
			values[i] = y0;
		}
		else
		{
			double y = 0;
			y = temp + foot * func(temp);
			cout << "the y" << i << " is " << y <<endl;
			values[i] = y;
			temp = y;
		}


	}
}