/* CS261- HW1 - Program5.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct student {
	char initials[2];
	int score;
};

/*Sort the given array number, of length n*/
void sort(struct student *class, int n) {
	int i, j, index;
	struct student temp;

	for ( i = 0; i < (n - 1); i++ ) {
		index = i;

		for (j = (i + 1); j < n; j++ ) {
			if ( class[index].score > class[j].score ) {
				index = j;
			}
		}

		if ( index != i ) {
			temp = class[i];
			class[i] = class[index];
			class[index] = temp;
		}
	}

	return;
}

void generate(struct student *students) {
	/*Generate random initials and scores for ten students.
	The two initial letters must be capital and must be between A and Z.
	The scores must be between 0 and 100*/

	int asciiF, asciiL, i;
	struct student *current;
	srand(time(NULL));

	for (i = 0; i < 10; i++) {
		current = &students[i];
		asciiF = 65 + (rand() % 25);
		asciiL = 65 + (rand() % 25);

		current->score = rand() % 1001;
		current->initials[0] = asciiF;
		current->initials[1] = asciiL;
	}
}


void output(struct student *students) {
	/*
		Output information about the ten students in the format:
			1. Initials  Score
			2. Initials  Score
			...
			10. Initials Score
	*/
	char first, last;
	int currScore, i;
	struct student *currStudent;

	for (i = 0; i < 10; i++) {
		currStudent = &students[i];
		first = currStudent->initials[0];
		last = currStudent->initials[1];
		currScore = currStudent->score;

		printf("%i.\t%c%c\t%i\n", (i + 1), first, last, currScore);
	}
}


int main(){
	/*Declare an integer n and assign it a value.*/
	int n = 10;

	/*Allocate memory for n students using malloc.*/
	struct student *students = malloc(n * sizeof(struct student));

	/*Generate random IDs and scores for the n students, using rand().*/
	generate(students);

	/*Print the contents of the array of n students.*/
	printf("%s\n", "Unsorted:");
	output(students);

	/*Pass this array along with n to the sort() function*/
	sort(students, n);

	/*Print the contents of the array of n students.*/
	printf("\n%s\n", "Sorted:");
	output(students);

	return 0;
}
