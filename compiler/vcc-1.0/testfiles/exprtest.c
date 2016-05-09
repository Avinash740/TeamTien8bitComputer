/*
 *	exprtest.c
 *
 *	This meaningless program just demonstrates the expression
 *	capabilities in vcc-C.
 */

int q;

int main(int argc, int argv)
{
	int a;
	int b;

	a = 1;
	b = 2;
	
	{
		int c;
		c = a;
		++c;
	}

	a * b + q * a;
	--q;
	
	a += 37;
	
	if (7 > 8)
		q = a;
	else
		q = b;

	a = foo(7, 8);
	
	return 0;
}


int foo(int s, int t)
{
	int a;
	
	a = s + t;
	
	if (a < 10)
		foo(a, t);
	
	return a;
}
