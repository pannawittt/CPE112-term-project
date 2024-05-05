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

void printMenu() {
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c\n", 179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191, 179);
    printf("%c %c Personalized Bus path-finding %c %c\n", 179,179,179,179);
    printf("%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c %c\n", 179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c  %c  What's the nearest bus stop?  %c\n",179, 254, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c  %c  Where're u going?             %c\n", 179, 175,179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c  %c  What time is it?              %c\n", 179, 232, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c  %c%c How long ur walkable range?   %c\n", 179, 168, 63, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    
}

int main() {
    printUpperBorder();
    printMenu();
    printUnderBorder();

    return 0;
}