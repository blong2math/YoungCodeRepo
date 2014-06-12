//coding: cplusplus

//only for 4 levels equation
//args: a: the arguments matrix
//		b: the resulting matrix
//rets:	b: the pointer to solution
void Gauss(double a[][4], double b[4])
{

	for(int i = 0; i < 4; i++)
	{
		for(int j = i + 1; j < 4; j++)
		{
			double m = a[j][i] / a[i][i];
			for(int k = 0; k < 4; k++)
			{
				a[j][k] -= a[i][k] * m;
			}
			b[j] -= m * b[i];
		}
	}

	for(i = 3; i >= 0; i--)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			b[j] -= ((a[j][i] * b[i])/ a[i][i]);
		}
	}

	for(i = 0; i < 4; i++)
	{
		b[i] /= a[i][i];
		cout << "x" << i << " is " << b[i]<<endl; 
	}
}