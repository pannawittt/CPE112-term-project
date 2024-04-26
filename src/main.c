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

#define pair_t1 int
#define pair_t2 int
#include "pair.h"
#define heap_t pair
#include "heap.h"
#include "matrix.h"

int main(){
	map mp = map_create(&cmp);
	mat m = mat_create(16,6);
	mat_readcsv(&m,"data/example.csv");
	for(int i=0;i<16;i++){
		for(int j=0;j<6;j++){
			printf("%s ",mat_get(&m,i,j));
		}
		printf("\n");
	}
}