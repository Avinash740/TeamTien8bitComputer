#include "heap.h"

#define kUpperBound	64

int initList[kUpperBound];



void addInitElement(char *constant, const int idx)
{
	if (idx >= kUpperBound)
	{
		error("Initializer too long");
		return;
	}
	
	initList[idx] = atoi(constant);
}

		
