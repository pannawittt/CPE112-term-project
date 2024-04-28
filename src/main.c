#define DEBUG
#include "util.h"
#define map_t1 char*
#define map_t2 int
#include "map.h"

int cmp(const char *s1, const char *s2){
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}

int cmpr(const char *s1, const char *s2){
	return minute(s1) <= minute(s2);
}


#define pair_t1 int
#define pair_t2 int
#include "pair.h"
#define heap_t pair
#include "heap.h"
#include "matrix.h"

int main(){
	mat timetable = mat_create(182, 7);
	mat_readcsv(&timetable, "data/bus_timetable.csv");
}