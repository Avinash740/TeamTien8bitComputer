/*
 *	qsort.c
 *
 *	Implementation of the quick sort algorithm.  This program is
 *	included to demonstrate that vcc can handle large, relatively
 *	complicated programs.  It demonstrates most of the features
 *	available in vcc-C.  It makes use of recursion, arrays, the I/O
 *	system, void functions, and more.
 *
 *	Note that since this is a recursive algorithm, if the list to sort
 *	gets large enough, it is possible to overflow the function stack,
 *	though you'd never know it.  You'd eventually start overwriting
 *	the list of numbers, so it would make for some interesting results...
 */

void quicksort(int a[], int q, int r)
{ 
	int v, i, j;
	
	if (r <= q) return;

	v=a[r]; i=q; j=r-1; 

	while (1) {

		while (a[i] < v) 
			++i;

		while (a[j] > v) 
			--j;

		if (i >= j) break;

		swap(a,i,j);

	}

	swap(a,i,r);

	quicksort(a, q, i-1);

	quicksort(a, i+1, r);
} 


void swap(int a[], int x, int y)
{
	int q;
	q = a[x];
	a[x] = a[y];
	a[y] = q;
}



int main()
{
	int i;
	int list[] = { 24, 32, 16, 17, 
			1, 3, 55, 62, 
			5, 4, 12, 63, 
			100, 25, 3, 5 };

	quicksort(list, 0, 15);
	
	for (i = 0; i < 16; ++i)
		putc(list[i]);
	
	return 0;
}
