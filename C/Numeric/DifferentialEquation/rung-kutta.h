//coding: cplusplus

//args:	left: the left x-axis value of differential region
//		right: the right x-axis value of differential region
//		foot: foot length of every differential process
//		y0: original value of y-axis
//		func: equal to dy/dx
//rets:	values: the pointer to every function value
void RungKutta(double left, double right, double foot, double y0, double (*func)(double x))
{
	double temp = y0;

	int n = (int) ((right - left) / foot) + 2;
	double* values = new double[n];

	for(int i = 0; i <= (right - left)/foot; i++)
	{
		if(i == 0)
		{
			cout << "the v" << i << " is " << y0 <<endl;
			values[i] = y0;
		}
		else
		{
			double v = 0;
			
			double k1 = foot * func(temp);
			double k2 = foot * func(temp + k1 / 2);
			double k3 = foot * func(temp + k2 / 2);
			double k4 = foot * func(temp + k3);
			v = temp + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
			
			cout << "the v" << i << " is " << v <<endl;
			values[i] = y;

			temp = v;
		}
	}
}
