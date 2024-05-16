/* define & typedef */
#define DEBUG
#define MAXCHAR (sizeof(char)*250)
typedef struct edge *edge;
typedef struct item *item;

/* include library */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "util.h"
#include "matrix.h"
#include "vector.h"
#include "heap.h"
#include "desktop.h"

/* global variable & struct */
char userTime[10];
char userSrc[MAXCHAR];
char userDest[MAXCHAR];
char userCo[MAXCHAR];
char strBuffer[MAXCHAR];
int walkLength = 0;
vector busPrior;
FILE *DBG;
struct edge{
	int weight;
	size_t vertex;
	char* busNo;
};
struct item{
	int distance;
	int fromVertex;
	int toVertex;
	char* busNo;
};

/* function */
void runMain();
void runTest();
int strCmpr(const void* a, const void* b);
int strCaseCmpr(const void* a, const void* b);
int timeSift(char **a); 						// กรอง row ใน timetable
int itemCmpr(const void* a, const void* b);
edge edge_create(int weight, size_t vertex, char* busNo);
item item_create(int distance, int fromVertex, int toVertex, char* busNo);

/* main function */
int main(int argc, char **argv){
	DBG = fopen("debug.txt","w");
	busPrior = vector_create(MAXCHAR);
	if(argc == 1){
		desktopIn(userTime, userSrc, userDest, &walkLength, busPrior, userCo);
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
	
	if(strCaseCmpr(userCo, "BMTA")==0){
		strcpy(userCo, "TSB");
	}else if(strCaseCmpr(userCo, "TSB")==0){
		strcpy(userCo, "BMTA");
	}
	timetable = mat_readcsv("data/bus_timetable.csv");                   // อ่านไฟล์ timetable.csv
	mat_delrow(timetable, 0);// ลบ row แรกออกไป
	ntimetable = mat_siftrow(timetable, &timeSift);                     // กรองเวลา: เอาแค่สายที่สามารถขึ้นได้นะเวลานั้นผ่านฟังก์ชั่น timeSift()

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
	for(size_t i=0;i<nodeNum;i++){
		G[i] = vector_create(sizeof(struct edge));
	}
	for(size_t i=0;i<mat_lenrow(ntimetable);i++){
		size_t src, dest;
		char *busNo, *busStop, *prevStop, *temp;
		int direction, time;
		char fileName[MAXCHAR], buffer[MAXCHAR];
		mat route, weight;
		
		busNo = mat_get(ntimetable, i, 0);
		direction = (strcmp(mat_get(ntimetable, i, 5), "ไป") ? 1 : 0);
		snprintf(fileName, MAXCHAR, "data/routes/route_%s.csv", busNo);
		route = mat_readcsv(fileName);
		mat_delrow(route, 0);

		snprintf(buffer, MAXCHAR,"data/weights/%s_%s.csv", busNo, (direction ? "out" : "in"));
		weight = mat_readcsv(buffer);
		prevStop = mat_get(route, direction, 0);
		for(size_t sign=1;sign<mat_lencol(route);sign++){
			busStop = mat_get(route, direction, sign);
			if(!strcmp(busStop,"blankjaa"))break;
	
			time = atoi(mat_get(weight, sign, 2));
			src = vector_find(signMap, prevStop, &strCmpr) - vector_begin(signMap);                      // หา ID ของป้ายก่อนหน้า
			dest = vector_find(signMap, busStop, &strCmpr) - vector_begin(signMap);                      // หา ID ของป้ายปัจจุบัน
			vector_push(G[src], edge_create(time, dest, busNo));
			prevStop = busStop;															
		}
		mat_erase(route);
		mat_erase(weight);		
	}
	mat walkRoute = mat_readcsv("data/weights/walk.csv");
	for(size_t i=1;i<mat_lenrow(walkRoute);i++){
		char *from, *to;
		int time;
		size_t idxFrom, idxTo;

		from = mat_get(walkRoute, i, 0);
		to = mat_get(walkRoute, i, 1);
		time = atoi(mat_get(walkRoute, i, 2));
		idxFrom = vector_find(signMap, from, &strCmpr) - vector_begin(signMap);
		idxTo = vector_find(signMap, to, &strCmpr) - vector_begin(signMap);

		vector_push(G[idxFrom], edge_create(time, idxTo, str("Walk")));
	}
	mat_erase(walkRoute);

	/* priority queue */
	{
		heap pq;
		size_t src, dest;
		int *dist, *idTrack, *visited;
		char** busTrack;
		item now, top;
		edge next;

		dist = (int*)malloc(sizeof(int)*nodeNum);
		idTrack = (int*)malloc(sizeof(int)*nodeNum);
		visited = (int*)malloc(sizeof(int)*nodeNum);
		busTrack = (char**)malloc(sizeof(char*)*nodeNum);
		pq = heap_create(sizeof(struct item), &itemCmpr);
		src = vector_find(signMap, userSrc, &strCaseCmpr) - vector_begin(signMap);
		dest = vector_find(signMap, userDest, &strCaseCmpr) - vector_begin(signMap);
		
		if(src >= nodeNum || dest >= nodeNum){
			desktopPrint("try again, the bus stop", 32);
			desktopPrint("may use another name", 32);
			return;
		}

		for(int i=0;i<nodeNum;i++){
			dist[i] = 999999;
			idTrack[i] = -1;
			busTrack[i] = (char*)malloc(MAXCHAR);
			visited[i] = 0;
		}
		dist[src] = 0;
		heap_push(pq, item_create(0, -1, src, str("Walk")));
		while(!heap_empty(pq)){
			top = (item)heap_top(pq);
			now = item_create(top->distance, top->fromVertex, top->toVertex, top->busNo);
			
			heap_pop(pq);
			if(visited[now->toVertex]){
				continue;
			}

			visited[now->toVertex] = 1;
			dist[now->toVertex] = now->distance;
			strncpy(busTrack[now->toVertex], now->busNo, MAXCHAR);
			idTrack[now->toVertex] = now->fromVertex;

			if(now->toVertex == dest){
				break;
			}
			while(next = (edge)vector_trav(G[now->toVertex])){
				if(!visited[next->vertex]){
					size_t newDist = next->weight + dist[now->toVertex];
					heap_push(pq, item_create(newDist, now->toVertex, next->vertex, next->busNo));
				}
			}

		}

		/* สรุปผล */
		vector result = vector_create(MAXCHAR);
		snprintf(strBuffer, MAXCHAR, "time : %d", dist[dest]);
		desktopPrint(strBuffer, 32);
		size_t iter = dest, nextIter;
		char* prev = NULL;
		int firstTime = 1;
		while(iter != -1){ //busTrack[iter]
			nextIter = idTrack[iter];
			if(!prev || strcmp(prev, busTrack[iter])){
				if(firstTime){
					snprintf(strBuffer, MAXCHAR, "└ %s → %s",  busTrack[iter], vector_at(signMap, iter));
					firstTime ^= 1;
				}else{
					snprintf(strBuffer, MAXCHAR, "├ %s → %s",  busTrack[iter], vector_at(signMap, iter));
				}
				vector_push(result, strBuffer);
			}
			prev = busTrack[iter];
			iter = nextIter;
		}

		char* path;
		vector_reverse(result);
		while(path = vector_trav(result)){
			desktopPrint(path, 36);
		}
	}

}

void runTest(void){
}

int strCmpr(const void* a, const void* b){
	return strcmp((char*)a, (char*)b);
}

int strCaseCmpr(const void* a, const void* b){
	char A[250], B[250];
	strcpy(A, (char*)a);
	strcpy(B, (char*)b);

	return strcmp(toLower(A), toLower(B));
}

int itemCmpr(const void* a, const void* b){
	item A = (item)a;
	item B = (item)b;
	if(A->distance == B->distance){
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
	return A->distance > B->distance;
}

edge edge_create(int weight, size_t vertex, char* busNo){
	edge new_edge = (edge)malloc(sizeof(struct edge));
	new_edge->weight = weight;
	new_edge->vertex = vertex;
	new_edge->busNo = (char*)malloc(MAXCHAR);
	if(busNo){
		memcpy(new_edge->busNo, busNo, MAXCHAR);
	}
	return new_edge;
}

item item_create(int distance, int fromVertex, int toVertex, char* busNo){
	item new_item = (item)malloc(sizeof(struct item));
	new_item->distance = distance;
	new_item->fromVertex = fromVertex;
	new_item->toVertex = toVertex;
	new_item->busNo = (char*)malloc(MAXCHAR);
	if(busNo){
		memcpy(new_item->busNo, busNo, MAXCHAR);
	}
	return new_item;
}

/* fn เช็คว่าอยู่ในช่วงที่รถวิ่งไหม */
int timeSift(char **a){
	if(strcmp(a[2], "nan") == 0 || strcmp(a[3], "nan") == 0){
		return strCaseCmpr(a[1], userCo)!=0;
	}
	return minute(a[2]) <= minute(userTime) && minute(a[3]) >= minute(userTime) && (strCaseCmpr(a[1], userCo)!=0);
}