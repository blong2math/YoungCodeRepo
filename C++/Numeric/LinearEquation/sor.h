//coding: cplusplus

//only for 4 levels equation
//args: a: the arguments matrix
//		b: the resulting matrix
//		w: relaxation factor
//		n: interation level
//rets:	b: the pointer to solution
void SOR(double a[][4], double b[], double w, int n)
{
	double t_x1 = 1;
	double t_x2 = 1;
	double t_x3 = 1;
	double t_x4 = 1;

	for(int i = 0; i < n; i++)
	{
		t_x1 = (1 - w) * t_x1 + (w / a[0][0]) * (b[0] - a[0][1]*t_x2 - a[0][2]*t_x3 - a[0][3]*t_x4);
		t_x2 = (1 - w) * t_x2 + (w / a[1][1]) * (b[1] - a[1][0]*t_x1 - a[1][2]*t_x3 - a[1][3]*t_x4);
		t_x3 = (1 - w) * t_x3 + (w / a[2][2]) * (b[2] - a[2][0]*t_x1 - a[2][1]*t_x2 - a[2][3]*t_x4);
		t_x4 = (1 - w) * t_x4 + (w / a[3][3]) * (b[3] - a[3][0]*t_x1 - a[3][1]*t_x2 - a[3][2]*t_x3);

	}

	cout << "the result is (" << t_x1 << ", " << t_x2 << ", " << t_x3 << ", " << t_x4 << ")" <<endl;

}