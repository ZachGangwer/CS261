/*	CS261- HW1 - Program1.c*/

/*
*	Name: Zach Gangwer
*	Date: April 12th, 2017
*	Solution description: Basic reference passing
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int *a, int *b, int c) {
	/* Increment a */
	*a = *a + 1;

	/* Decrement  b */
	*b = *b - 1;

	/* Assign a-b to c */
	c = *a - *b;

	/* Return c */
	return c;
}

int main() {
	/* Declare three integers x,y and z and initialize them randomly to values in [0,10] */
	int *x = (int*) malloc(sizeof(int));
	int *y = (int*) malloc(sizeof(int));
	int z, ret;

	srand(time(NULL));
	*x = rand() % 11;
	*y = rand() % 11;
	z = 4;

	/* Print the values of x, y and z */
	printf("%i, %i, %i\n", *x, *y, z);

	/* Call foo() appropriately, passing x,y,z as parameters */
	ret = foo(x, y, z);

	/* Print the values of x, y and z */
	printf("%i, %i, %i\n", *x, *y, z);

	/* Print the value returned by foo */
	printf("%i\n", ret);

	/* Is the return value different than the value of z?  Why? */
	
	/***
		Yes, because z is passed by value, therefor immutable by the called function
		The value contained by z was augmented and returned, but z is untouched
	***/
	return 0;
}
