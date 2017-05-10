/* CS261- HW1 - Program4.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void printArray(int *src, int len) {
	int i;

	printf("\n");

	for (i = 0; i < len; i++) {
		if (i > 0 && i % 4 == 0) {
			printf("%i,\n", src[i]);
		} else {
			printf("%i,\t", src[i]);
		}
	}

	printf("\n");

	return;
}


/*Sort the given array number, of length n*/
void sort(int *number, int n) {
	int i, j, index, temp;

	for (i = 0; i < (n - 1); i++) {
		index = i;

		for (j = (i + 1); j < n; j++) {
			if (number[index] > number[j]) {
				index = j;
			}
		}
		
		if (index != i) {
			temp = number[i];
			number[i] = number[index];
			number[index] = temp;
		}
	}

	return;
}


int main(){
	/*Declare an integer n and assign it a value of 20.*/
	int i, n = 20;
	srand(time(NULL));

	/*Allocate memory for an array of n integers using malloc.*/
	int *array = (int*) malloc(n * sizeof(int));

	/*Fill this array with random numbers, using rand().*/
	for (i = 0; i < n; i++) {
		array[i] = rand()%10000;
	}

	/*Print the contents of the array.*/
	printArray(array, n);

	/*Pass this array along with n to the sort() function of part a.*/
	printf("\n%s\n", "Sorting!");
	sort(array, n);

	/*Print the contents of the array.*/
	printArray(array, n);

	return 0;
}
