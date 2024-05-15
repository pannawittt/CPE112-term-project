#ifndef _UTIL_H_
#define _UTIL_H_

#define int32_t int
#define int64_t long long

#include <stddef.h>

/**
 * macro สำหรับ utility function
 * max: ส่งกลับสูงกว่า min: ส่งกลับค่าต่ำสุด
*/
#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

/**
 * macro สำหรับการ debug code
 * define DEBUG ก่อนใช้งาน
*/
#ifdef DEBUG
    #define c_version __STDC_VERSION__
    #define dbg(x) fprintf(stderr,x);printf("\n")
    #define test(x) printf("test %d passed!\n", x)
#else
    #define dbg(...)
    #define test(...)
#endif //DEBUG

/**
 * ฟังก์ชั่นไว้ใช้หาค่าใน vector
 * ใช้ vector_begin() และ vector_end()
 * _sizeOfElement คือขนาดของตัวแปรใน vector
*/
void** find(void** _begin, void** _end, const void* _value, size_t _sizeOfElement );

/**
 * ฟังก์ชั่นใช้สำหรับแปลง string ให้เป็น นาทีรวม 
 * string อยู่ในรูป "HourMinute"
 * เช่น "0320" คือ 3 ชั่วโมง 20 นาที
 * เพราะฉะนั้นฟังก์ชั่นนี้จะส่งกลับ 200 (นาที)
*/
int minute(const char* _string);

/**
 * ฟังก์ชั่นคล้ายๆ memcmp()
 * แต่มีกรณีพิเศษเกี่ยวกับ '\0'
*/
int cmp (const void *_p1, const void *_p2, size_t _sizeOfElement);

char* str(char* _string);

/**
 * ฟังก์ชั่นสำหรับแปลงค่าเป็น void pointer
 * เพื่อความสะดวกในการใช้กับ data structure ที่เป็น dynamic type
 * หรือสามารถ cast ตัวแปรที่เราต้องการให้เป็น (void*) ก็ได้
 * เช่น foo( (void*)2, (void*)'a' )
*/
void* pint(const int _value);
void* pchar(const char _value);
void* pfloat(const float _value);
void* pstr(const char* _value);

#endif // util.h
