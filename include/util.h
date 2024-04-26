#ifndef _UTIL_H_
#define _UTIL_H_

#define int32_t int
#define int64_t long long

#ifndef util_t
#define util_t int
#endif // util_t

#ifndef MOD
#define MOD 1000000007
#endif

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)
#define _C_VER_ printf("%d",__STDC_VERSION__)
#define swap(x,y) do{ unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; memcpy(swap_temp,&y,sizeof(x)); memcpy(&y,&x,sizeof(x));  memcpy(&x,swap_temp,sizeof(x));}while(0)
#ifdef DEBUG
    #define dbg(x) fprintf(stderr,x);printf("\n");
#else
    #define dbg(...) 
#endif //DEBUG

int greater(const util_t first, const util_t second);
int greater_equal(const util_t first, const util_t second);
int less(const util_t first, const util_t second);
int less_equal(const util_t first, const util_t second);
int mmod(int first, int second);
int mod(int value);

#endif // util.h
