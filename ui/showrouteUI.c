#include <stdio.h> 

void printUpperBorder() {
    printf("%c", 213);
    for (int i = 0; i < 35; i++) {
        printf("%c", 205);
    }
    printf("%c", 184);
    printf("\n");
}

void printUnderBorder() {
    printf("%c", 212);
    for (int i = 0; i < 35; i++) {
        printf("%c", 205);
    }
    printf("%c", 190);
    printf("\n");
}

void printBorder() {
    printf("%c                                   %c\n", 179, 179);
}

void printRouteNo(int routeNo) {
    printf("%c Route No.: %d                     %c\n", 179, routeNo, 179);
}

int main() {
    printUpperBorder();
    printBorder();
    printRouteNo(21);
    printBorder();
    printUnderBorder();

    return 0;
}