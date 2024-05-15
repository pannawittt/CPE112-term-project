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
#include "desktop.h"

/* global variable & struct */
char userTime[10];
char userSrc[MAXCHAR] = "WatTuk";
char userDest[MAXCHAR] = "ChaloemKrung";
char strBuffer[MAXCHAR];
int walkLength = 0;
vector busPrior;
FILE *DBG;
struct edge{
	int weight;
	size_t vertex;
	char* busNo;
};

/* function */
void runMain();
void runTest();
int strCmpr(const void* a, const void* b); 		// ฟังก์ชั่นเปรียบเทียบ key ใน map
int timeSift(char **a); 						// กรอง row ใน timetable
int itemCmpr(const void* a, const void* b);
edge edge_create(int weight, size_t vertex, char* busNo);

/* main function */
int main(int argc, char **argv){
	DBG = fopen("debug.txt","w");
	if(argc == 1){
		busPrior = vector_create(MAXCHAR);
		desktopIn(userTime, userSrc, userDest, &walkLength, busPrior);
		runMain();
		desktopEnd();
	}else if(strcmp(argv[0], "test")){
		printf("------- TEST MODE ------- \n\n");
		runTest();
	}
	fclose(DBG);
}

/* defined function */
void runMain(void){
	vector signMap;
	mat timetable, ntimetable;
	size_t nodeNum;
	
	timetable = mat_readcsv("data/bus_timetable.csv");                   // อ่านไฟล์ timetable.csv
	mat_delrow(timetable, 0);// ลบ row แรกออกไป
	ntimetable = mat_siftrow(timetable, &timeSift);                      // กรองเวลา: เอาแค่สายที่สามารถขึ้นได้นะเวลานั้นผ่านฟังก์ชั่น timeSift()

	/* นำเส้นทางเดินรถใส่เข้าไปใน vector */
	signMap = vector_create(MAXCHAR);                    				// สร้าง vector
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
			if(vector_find(signMap, busStop, &strCmpr) != vector_end(signMap)){		 // เจอชื่อซ้ำ
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

			src = vector_find(signMap, prevStop, &strCmpr) - vector_begin(signMap);                      // หา ID ของป้ายก่อนหน้า
			dest = vector_find(signMap, busStop, &strCmpr) - vector_begin(signMap);                      // หา ID ของป้ายปัจจุบัน
			vector_push(G[src], edge_create(1, dest, busNo));
			prevStop = busStop;															
		}
		mat_erase(route);				
	}

	/* priority queue */
	{
		heap pq;
		size_t src, dest;
		int valid, *dist, *idTrack;
		char** busTrack;
		edge now, next, top;

		dist = (int*)malloc(sizeof(int)*nodeNum);
		idTrack = (int*)malloc(sizeof(int)*nodeNum);
		busTrack = (char**)malloc(sizeof(char*)*nodeNum);
		for(int i=0;i<nodeNum;i++){
			busTrack[i] = (char*)malloc(MAXCHAR);
		}
		valid = 1;
		pq = heap_create(sizeof(struct edge), &itemCmpr);
		src = vector_find(signMap, userSrc, &strCmpr) - vector_begin(signMap);
		dest = vector_find(signMap, userDest, &strCmpr) - vector_begin(signMap);
		
		if(src >= nodeNum){
			desktopPrint("not found source");
			valid = 0;
		}
		if(dest >= nodeNum){
			desktopPrint("not found destination");
			valid = 0;
		}

		for(int i=0;i<nodeNum;i++){
			dist[i] = 999999;
			idTrack[i] = -1;
		}
		if(!valid){
			return;	
		}

		dist[src] = 0;
		heap_push(pq, edge_create(0, src, "none"));
		//printf("src: %d dest: %d\n", src, dest);
		while(!heap_empty(pq)){

			edge top = (edge)heap_top(pq);
			now = edge_create(top->weight, top->vertex, top->busNo);
			strncpy(busTrack[now->vertex], now->busNo, MAXCHAR);
	
			if(strcmp(vector_at(signMap, now->vertex), userDest) == 0){
				break;
			}
			heap_pop(pq);

			while(next = (edge)vector_trav(G[now->vertex])){
				if(dist[next->vertex] > dist[now->vertex] + next->weight){	
					dist[next->vertex] = dist[now->vertex] + next->weight;
					idTrack[next->vertex] = now->vertex;
					heap_push(pq, edge_create(dist[next->vertex], next->vertex, next->busNo));
					edge e;
					while(e = heap_trav(pq)){
						fprintf(DBG, "%s ", e->busNo);
					}
					fprintf(DBG, "\n");
				}
			}

		}

		//output: dist[dest]
		snprintf(strBuffer, MAXCHAR, "distance : %d", dist[dest]);
		desktopPrint(strBuffer);
		size_t iter = dest;
		while(idTrack[iter] != -1){
			snprintf(strBuffer, MAXCHAR, "bus : %s", busTrack[iter]);
			desktopPrint(strBuffer);
			iter = idTrack[iter];
		}
	}
}

void runTest(void){
	heap h = heap_create(sizeof(edge), &itemCmpr);
	
}

int strCmpr(const void* a, const void* b){
	return strcmp((char*)a, (char*)b);
}

int itemCmpr(const void* a, const void* b){
	edge A = (edge)a;
	edge B = (edge)b;
	if(A->weight == B->weight){
		size_t idxA = vector_find(busPrior, A->busNo, &strCmpr) - vector_begin(busPrior);
		size_t idxB = vector_find(busPrior, B->busNo, &strCmpr) - vector_begin(busPrior);
		size_t end = vector_end(busPrior) - vector_begin(busPrior);
		if(idxA == end){
			vector_push(busPrior,A->busNo);
		}
		if(idxB == end){
			vector_push(busPrior,B->busNo);
		}
		return idxA > idxB;
	}
	return A->weight > B->weight;
}

edge edge_create(int weight, size_t vertex, char* busNo){
	edge new_edge = (edge)malloc(sizeof(struct edge));
	new_edge->weight = weight;
	new_edge->vertex = vertex;
	new_edge->busNo = (char*)malloc(MAXCHAR);
	if(busNo){	
		memcpy(new_edge->busNo, busNo, MAXCHAR);
	}else{
		//strcpy(new_edge->busNo, "NULL");
	}
	return new_edge;
};

/* fn เช็คว่าอยู่ในช่วงที่รถวิ่งไหม */
int timeSift(char **a){
	if(strcmp(a[2], "nan") == 0 || strcmp(a[3], "nan") == 0){
		return 0;
	}
	return minute(a[2]) <= minute(userTime) && minute(a[3]) >= minute(userTime);
}