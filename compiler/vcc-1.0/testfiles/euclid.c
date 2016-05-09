/*
 *	euclid.c
 *
 *	vcc-C implementation of Euclids algorithm for computing the
 *	GCF of two numbers.
 */

int main()
{
	int a, b;
	
	a = 36;
	b = 54;
	
	while (a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	
	return 0;
}
