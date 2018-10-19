#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include "XOR.h"

int main(int argc, char** argv)
{
	unsigned long input1 = strtoul(argv[1], NULL, 10);
	unsigned long input2 = strtoul(argv[2], NULL, 10);

	if (argc != 3)
	{
		errx(1,"Error");
		return 1;
	}
	if ((input1 != 0 && input1 != 1) || (input2 != 0 && input2 != 1))
	{
		errx(1,"Error, input must be 0 or 1");
	}

	if ((input1 == 0 || input1 == 1) && (input2 == 0 || input2 == 1))
	{
		int patt = 0;
		if (input1 == 0 && input2 == 1)
		{ patt = 1; }
		
		if (input1 == 1 && input2 == 0)
		{ patt = 2; }
		
		if (input1 == 1 && input2 == 1)
		{ patt = 3; }

		printf("Inputs are %li and %li.", input1, input2);
		XOR(patt);
		return EXIT_SUCCESS;
	}
	return 1;
}

