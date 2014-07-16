//coding: cplusplus

//args:	left: the left x-axis value of integral region
//		right: the right x-axis value of integral region
//		n: the integral level
//		func: the pointer of be-integral function
//rets: integral: the approximate integral value
double Ladder(double left, double right, int n, double (*func)(double x))
{
	double integral = 0;
	
	double foot = (right - left) / n;

	for(int i = 0; i < n; i++){
		integral = integral + (foot / 2)*(func(left + i * foot) + func(left + (i + 1) * foot));
	}

	cout << "using the ladder integral, the result is " << integral <<endl;
	return integral;
}