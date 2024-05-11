#include <stdio.h>
#include <string.h>

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

void printTime(int Time) {
    printf("%c %c %d                            %c\n", 179, 192, Time, 179);
}

void printBorder() {
    printf("%c                                   %c\n", 179, 179);
}

void printHere(int Time) {
    printf("%c %c Here                            %c\n", 179, 254, 179);
    printTime(Time);
}

void printInterchange(int Time) {
    printf("%c%c%c interchange                     %c\n", 179, 45, 95, 179);
    printTime(Time);
}

void printDestination(int Time) {
    printf("%c %c Destination                     %c\n",179, 175, 179);
    printTime(Time);
}

void printStartEndTime(int startTime, int endTime) {
    printf("%c %c start time  %c%c  end time        %c\n", 179, 232, 195, 318, 179);
    printf("%c     %d             %d         %c\n", 179,startTime,endTime,179);
}

int main() {
    printUpperBorder();
    printBorder();
    printHere(2200);
    printInterchange(2200);
    printInterchange(2200);
    printDestination(2200);
    printBorder();
    printBorder();
    printStartEndTime(2200,2200);
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printBorder();
    printUnderBorder();

    return 0;
}