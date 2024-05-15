#include "desktop.h"

#include <stdio.h>
#include <Windows.h>
#include "vector.h"

int remainSpace(char *_str, int _space);
void intIn(int *_buffer);
void strIn(char *_buffer);
void vectIn(vector *_buffer);
void adaptiveWindowsTree(vector _buffer);
void adaptiveWindowsLastChild(vector _buffer);

void desktopIn(char* userTime, char* userSrc, char* userDest, int* walkLength, vector userBus){
    //set output code UTF-8
    SetConsoleOutputCP(65001);

    printf("╒");
    for (int i = 0; i < 35; i++) {
        printf("═");
    }
    printf("╕\n");

    printf("│                                   │\n");
    printf("│                                   │\n");
    printf("│ ┌──────────────────────────────┐  │\n");
    printf("│ │ Personalized Bus path-finding│  │\n");
    printf("│ └──────────────────────────────┘  │\n");
    printf("│                                   │\n");
    printf("│                                   │\n");
    printf("│  ■  What's the nearest bus stop?  │\n");
    strIn(userSrc);
    printf("│  »  Where're u going?             │\n");
    strIn(userDest);
    printf("│  Φ  What time is it? (hhmm)       │\n");
    strIn(userTime);
    printf("│  ¿? range ur walkable? (m)        │\n");
    intIn(walkLength);
    printf("│                                   │\n");
    printf("│                                   │\n");
    printf("│ > Recent bus stop you used        │\n");
    char buffer[250];
    adaptiveWindowsTree(userBus);
    adaptiveWindowsTree(userBus);
    adaptiveWindowsTree(userBus);
    adaptiveWindowsTree(userBus);
    adaptiveWindowsLastChild(userBus);
    printf("│                                   │\n");
    printf("│                                   │\n");
}

void desktopPrint(char* _str){
    printf("│     %s%*s│\n", _str, remainSpace(_str, 30), "");
}

void desktopEnd(){
    printf("│                                   │\n");
    printf("╘");
    for (int i = 0; i < 35; i++) {
        printf("═", 205);
    }
    printf("╛");
    printf("\n");
}

void adaptiveWindowsTree(vector _buffer) {
    printf("│   ├ ");
    fflush(stdout);
    char _str[250];
    scanf("%s", _str);
    vector_push(_buffer, (void*)_str);
    printf("\033[A\033[K│   ├ %s%*s│\n", _str, remainSpace(_str, 30), "");
}

void adaptiveWindowsLastChild(vector _buffer) {
    printf("│   └ ");
    fflush(stdout);
    char _str[250];
    scanf("%s", _str);
    vector_push(_buffer, (void*)_str);
    printf("\033[A\033[K│   └ %s%*s│\n",  _str, remainSpace(_str, 30), "");
}

void intIn(int *_buffer){
    printf("│\t");
    fflush(stdout);
    scanf("%d", _buffer);
    char charValue[250];
    sprintf(charValue, "%d", *_buffer);
    printf("\033[A\033[K");
    printf("│\t%s%*s│\n", charValue, remainSpace(charValue, 28), "");
}

void strIn(char *_buffer){
    printf("│\t");
    fflush(stdout);
    scanf("%s", _buffer);
    printf("\033[A\033[K");
    printf("│\t%s%*s│\n", _buffer, remainSpace(_buffer, 28), "");
}

int remainSpace(char *_str, int _space) {
    int len = strlen(_str);
    int remainingSpace = _space - len;

    return remainingSpace;
}