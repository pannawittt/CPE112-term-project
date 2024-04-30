#define DEBUG

// user's variable
char userTime[5];

// user defined function

/**
 * นำเข้า library
*/
#include <stdio.h>
#include "util.h"
#include "matrix.h"
#include "vector.h"
#include "heap.h"

/**
 * buffer
*/
mat mat_buffer[50];

void readTimeTable();


int main(){
	
}

void readTimeTable(){
	mat timetable = mat_create(182, 7);
	mat_readcsv(timetable, "data/bus_timetable.csv");
	mat_delrow(timetable, 0);
	{// user input
		printf("ตอนนี้กี่โมง? : ");
		scanf("%s4", userTime);
	}
	mat_print(timetable);
}