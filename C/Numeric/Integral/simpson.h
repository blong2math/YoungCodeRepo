//coding: cplusplus


//args:	left: the left x-axis value of integral region
//		right: the right x-axis value of integral region
//		n: the integral level
//		func: the pointer of be-integral function
//rets: integral: the approximate integral value
void Simpson(double left, double right, int n, double (*func)(double x))
{
	double integral = 0;

	double foot = (right - left) / n;

	for(int i = 0; i < n; i++)
	{
		integral = integral + (foot / 6)*(func(left + i * foot) + 4 * func(left + (i + 1/2) * foot) + func(left + (i + 1) * foot));
	}

	return integral;
}