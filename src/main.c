/* define & typedef */
#define DEBUG
#define MAXCHAR (sizeof(char)*250)
typedef struct edge *edge;

/* include library */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "matrix.h"
#include "vector.h"
#include "heap.h"
#include "map.h"

/* global variable & struct */
char userTime[10] = "0550";
char userSrc[MAXCHAR] = "วัดสุทธิ";
char userDest[MAXCHAR] = "วัดยานนาวา";
int walkLength = 0;
struct edge{
	int weight;
	size_t vertex;
	char* busNo;
};

/* function */
void runMain();
void runTest();
int keyCmpr(const void* a, const void* b); 		// ฟังก์ชั่นเปรียบเทียบ key ใน map
int timeSift(char **a); 						// กรอง row ใน timetable
int itemCmpr(const void* a, const void* b);
edge edge_create(int weight, size_t vertex, char* busNo);

/* main function */
int main(int argc, char **argv){	
	if(argc == 1){
		runMain();
	}else if(strcmp(argv[0], "test")){
		printf("------- TEST MODE ------- \n\n");
		runTest();
	}
	printf("\n\n ------- FINISH ------- \n\n");
}

/* defined function */
void runMain(void){
	vector signMap;
	mat timetable, ntimetable;
	size_t nodeNum;

	/* input จากผู้ใช้งาน */
	printf("ตอนนี้กี่โมง? : ");scanf("%4s",userTime);
	//printf("ตอนนี้อยู่ไหน? : ");scanf("%s",userSrc);
	//printf("จะไปไหน? : ");scanf("%s",userDest);
	printf("เดินได้เยอะแค่ไหน? : ");scanf("%d",&walkLength);

	timetable = mat_readcsv("data/bus_timetable.csv");                   // อ่านไฟล์ timetable.csv
	mat_delrow(timetable, 0);// ลบ row แรกออกไป
	ntimetable = mat_siftrow(timetable, &timeSift);                      // กรองเวลา: เอาแค่สายที่สามารถขึ้นได้นะเวลานั้นผ่านฟังก์ชั่น timeSift()

	/* นำเส้นทางเดินรถใส่เข้าไปใน vector */
	signMap = vector_create(MAXCHAR);                      				// สร้าง vector
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
	nodeNum = vector_size(signMap);
	vector *G = (vector*)malloc(sizeof(vector)*nodeNum);                      // สร้าง graph มาเก็บเส้นทางเดินรถ
	for(int i=0;i<nodeNum;i++){
		G[i] = vector_create(sizeof(struct edge));
	}
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
			vector_push(G[src], edge_create(10, dest, busNo));                     // เพิ่ม edge ใน graph
			

			prevStop = busStop;															
		}
		mat_erase(route);				
	}

	/* priority queue */
	{
		heap pq;
		size_t src, dest;
		int valid, *dist;

		dist = (int*)malloc(sizeof(int)*nodeNum);
		valid = 1;
		pq = heap_create(sizeof(struct edge), &itemCmpr);
		src = vector_find(signMap, userSrc) - vector_begin(signMap);
		dest = vector_find(signMap, userDest) - vector_begin(signMap);
		
		if(src >= nodeNum){
			printf("ไม่มีป้ายต้นทางดังกล่าว\n");
			valid = 0;
		}
		if(dest >= nodeNum){
			printf("ไม่มีป้ายปลายทางดังกล่าว\n");
			valid = 0;
		}

		for(int i=0;i<nodeNum;i++){
			dist[i] = 999999;
		}
		if(!valid){
			return;	
		}
		dist[src] = 0;
		heap_push(pq, edge_create(0, src, "none"));
		while(!heap_empty(pq)){
			edge now = (edge)heap_top(pq);
			if(strcmp(vector_at(signMap, now->vertex), userDest) == 0){
				break;
			}
			heap_pop(pq);
			vector adj = G[now->vertex];
			edge next;
			while(next = (edge)vector_trav(adj)){
				if(dist[next->vertex] > dist[now->vertex] + dist[next->weight]){
					heap_push(pq, edge_create(now->weight + next->weight, next->vertex, next->busNo));
					dist[next->vertex] = now->weight + next->weight;
				}
			}
		}
	}
}

void runTest(void){
	
}

int keyCmpr(const void* a, const void* b){
	return strcmp((char*)a, (char*)b);
}

int itemCmpr(const void* a, const void* b){
	edge A = (edge)a;
	edge B = (edge)b;
	return A->weight > B->weight;
}

edge edge_create(int weight, size_t vertex, char* busNo){
	edge new_edge = (edge)malloc(sizeof(struct edge));
	new_edge->weight = weight;
	new_edge->vertex = vertex;
	new_edge->busNo = (char*)malloc(MAXCHAR);
	memcpy(new_edge->busNo, busNo, MAXCHAR);
	return new_edge;
};

/* fn เช็คว่าอยู่ในช่วงที่รถวิ่งไหม */
int timeSift(char **a){
	if(strcmp(a[2], "nan") == 0 || strcmp(a[3], "nan") == 0){
		return 0;
	}
	return minute(a[2]) <= minute(userTime) && minute(a[3]) >= minute(userTime);
}