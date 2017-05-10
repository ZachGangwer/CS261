/* CS261- HW1 - Program3.c*/
/* Name:
 * Date:
 * Solution description:
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


struct student {
	char initials[2];
	int score;
};


struct student *allocate() {
	/*Allocate memory for ten students*/
	struct student *class = malloc(10 * sizeof(struct student));

	/*return the pointer*/
	return class;
}

/*Generate random initials and scores for ten students.
The two initial letters must be capital and must be between A and Z.
The scores must be between 0 and 100*/
void generate(struct student *students) {
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


/*
	Output information about the ten students in the format:
		1. Initials  Score
		2. Initials  Score
		...
		10. Initials Score
*/
void output(struct student *students) {
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


/*
	*** MINIMUM ***
	* Finds the smallest value from an array of numbers
	VALUES ---(INT*)-> An integer array to search
	OUTPUT <==(INT )== The smallest value from input
*/
int minimum(int *values) {
	int output = values[0];
	int i;

	for (i = 1; i < 10; i++) {
		if (output > values[i]) {
			output = values[i];
		}
	}

	return output;
}


/*
	*** MAXIMUM ***
	* Finds the largest value from an array of numbers
	VALUES ---(INT*)-> An integer array to search
	OUTPUT <==(INT )== The largest value from input
*/
int maximum(int *values) {
	int output = values[0];
	int i;

	for (i = 1; i < 10; i++) {
		if (output < values[i]) {
			output = values[i];
		}
	}

	return output;
}

/*
	*** AVERAGE ***
	* Finds the mean of an array of numbers
	VALUES ---(INT*)-> An integer array to average
	OUTPUT <==(INT )== The average of the input
*/
int average(int *values) {
	int output, i;
	int sum = 0;

	for (i = 0; i < 10; i++) {
		sum += values[i];
	}

	output = sum/10;
	return output;
}

/*
	*** SUMMARY ***
	* Prints the initials and scores of the input array
	STUDENTS -(STUDENT*)-> An array of student objects
*/
void summary(struct student *students) {
	/*Compute and print the minimum, maximum and average scores of the ten students*/
	int scores[10];
	int min, max, mean, i;

	for (i = 0; i < 10; i++) {
		scores[i] = students[i].score;
	}

	min = minimum(scores);
	max = maximum(scores);
	mean = average(scores);

	printf("MIN: %i\nMAX: %i\nMEAN: %i\n", min, max, mean);
}


void deallocate(struct student *stud) {
	/*Deallocate memory from stud*/
	free(stud);
	stud = NULL;
}


int main()
{
	struct student *stud = NULL;

	/*call allocate*/
	stud = allocate();

	/*call generate*/
	generate(stud);

	/*call output*/
	output(stud);

	/*call summary*/
	summary(stud);

	/*call deallocate*/
	deallocate(stud);

	return 0;
}
