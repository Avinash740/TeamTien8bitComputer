/*
 *	errors.c
 *
 *	This program is laden with errors, and its purpose is to
 *	demonstrate the compiler's error reporting system.
 */


int f1() { }

char x;
char y;

int f2() { }

int f3(int a, int, int c) { }

int f4(int) { }

int f5(int a, while, int b)
{
}

int a, while, b;

int f6() {
	break
	break;
	return;
}

int f7() {
	a,
	int, b;
}

int f8() {
	f7(a,
	int,
	b);
}
