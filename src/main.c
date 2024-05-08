// define & macro
#define DEBUG
#define MAXCHAR 250

// นำเข้า library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "matrix.h"
#include "vector.h"
#include "heap.h"
#include "map.h"
#include "graph.h"

/* global variable */
char userTime[10] = "0550";

/* declared function */
void runMain();
void runTest();
int keyCmpr(const void* a, const void* b); 		// ฟังก์ชั่นเปรียบเทียบ key ใน map
int timeSift(char **a); 							  // กรอง row ใน timetable

void bi(void *c, size_t soe){
	unsigned char *p = c;
	while(soe--){
		for( int i = 7; i >= 0; i-- ) {
    		printf( "%d", ( *p++ >> i ) & 1 ? 1 : 0 );
		}
		printf("\n");
	}
}

/* main function */
int main(){
	runMain();
	//runTest();
	printf("\n\n ---- FINISH ---- \n\n");
}

/* defined function */
void runMain(void){
	vector signMap;
	mat timetable, ntimetable;

	/* input จากผู้ใช้งาน */
	printf("ตอนนี้กี่โมง? : ");scanf("%4s",userTime);

	timetable = mat_readcsv("data/bus_timetable.csv");                      // อ่านไฟล์ timetable.csv
	mat_delrow(timetable, 0);// ลบ row แรกออกไป
	ntimetable = mat_siftrow(timetable, &timeSift);                      // กรองเวลา: เอาแค่สายที่สามารถขึ้นได้นะเวลานั้นผ่านฟังก์ชั่น timeSift()

	/* นำเส้นทางเดินรถใส่เข้าไปใน vector */
	signMap = vector_create(MAXCHAR);                      // สร้าง vector
	for(size_t i=0;i<mat_lenrow(ntimetable);i++){
		char *busNo, *busStop;
		int direction;
		char fileName[MAXCHAR];
		mat route;
		
		
		busNo = mat_get(ntimetable, i, 0);                      							// เอาเลขรถบัสจาก matrix
		direction = (strcmp(mat_get(ntimetable, i, 5), "ไป") ? 1 : 0);                      // ดูว่าเป็นขาไปหรือขากลับ

		snprintf(fileName, MAXCHAR, "data/routes/route_%s.csv", busNo);                      // สร้างชื่อไฟล์จากตัวแปร
		route = mat_readcsv(fileName); 
		mat_delrow(route, 0);

		for(size_t sign=0;sign<mat_lencol(route);sign++){
			busStop = mat_get(route, direction, sign);

			if(!strcmp(busStop,"blankjaa"))break;                      // ไม่มีป้ายต่อละ
			if(vector_find(signMap, busStop) != vector_end(signMap)){		 // เจอชื่อซ้ำ
				continue;
			}

			vector_push(signMap, busStop);                      // ใส่ชื่อป้ายเข้าไปใน vector
		}

		mat_erase(route);        // ลบ matrix (ประหยัดพื้นที่)
	}
	
	/* plot graph */
	graph G = graph_create(vector_size(signMap));                      // สร้าง graph มาเก็บเส้นทางเดินรถ
	for(size_t i=0;i<mat_lenrow(ntimetable);i++){
		size_t src, dest;
		char *busNo, *busStop, *prevStop;
		int direction;
		char fileName[MAXCHAR];
		mat route;
		
		busNo = mat_get(ntimetable, i, 0);
		direction = (strcmp(mat_get(ntimetable, i, 5), "ไป") ? 1 : 0);

		snprintf(fileName, MAXCHAR, "data/routes/route_%s.csv", busNo);
		route = mat_readcsv(fileName); 
		mat_delrow(route, 0);

		prevStop = mat_get(route, direction, 0);
		for(size_t sign=1;sign<mat_lencol(route);sign++){
			busStop = mat_get(route, direction, sign);
			if(!strcmp(busStop,"blankjaa"))break;

			src = vector_find(signMap, prevStop) - vector_begin(signMap);                      // หา ID ของป้ายก่อนหน้า
			dest = vector_find(signMap, busStop) - vector_begin(signMap);                      // หา ID ของป้ายปัจจุบัน
			assert(src < vector_size(signMap) && dest < vector_size(signMap));
			graph_addedge(G, src, dest, 10, busNo);                      // เพิ่ม edge ใน graph

			prevStop = busStop;															
		}

		mat_erase(route);				
	}


}

void runTest(void){

}

/* global variable */
int keyCmpr(const void* a, const void* b){
	return strcmp((char*)a, (char*)b);
}

/* fn เช็คว่าอยู่ในช่วงที่รถวิ่งไหม */
int timeSift(char **a){
	if(strcmp(a[2], "nan") == 0 || strcmp(a[3], "nan") == 0){
		return 0;
	}
	return minute(a[2]) <= minute(userTime) && minute(a[3]) >= minute(userTime);
}
