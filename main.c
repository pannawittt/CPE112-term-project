#define DEBUG
#include "util.h"
#define pair_t1 char*
#define pair_t2 int
#include "map.h"

int cmp(const char *s1, const char *s2){
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}


int main(){
	map mp = map_create(&cmp);
	char* k = "test";
	*map_get(&mp,"jhin") += 1;
	*map_get(&mp,"lulu") = 5;
	printf("%d",*map_get(&mp, "lulu"));
}