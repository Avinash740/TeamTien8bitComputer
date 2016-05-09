/*
 *	ssort.c
 *
 *	This file is an implementation of the selection sort
 *	algorithm.  It demonstrates for loops, arrays, and function
 *	calling.
 *	It should contain no errors.
 */

int swap(int a[], int x, int y)
{
	int q;
	q = a[x];
	a[x] = a[y];
	a[y] = q;
	
	return 0;
}

int main()
{
	int a[] = { 24, 32, 16, 17, 
			1, 3, 55, 62, 
			5, 4, 12, 63, 
			100, 25, 3, 5 };
	int i, j, min;
	
	for (i = 0; i < 16; ++i)
	{
		min = i;
		for (j = i+1; j < 16; ++j)
		{
			if (a[j] < a[min])
				min = j;
		}
		swap(a, min, i);		
	}
	
	return 0;
}

