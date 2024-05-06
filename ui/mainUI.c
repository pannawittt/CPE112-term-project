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

int RemainingSpace(char *str, int space) {
    int len = strlen(str);
    int remainingSpace = space - len;

    return remainingSpace;
}

void inputCHAR(char *CHAR) {
    printf("%c\t", 179);
    fflush(stdout);
    scanf("%s", CHAR);
    printf("\033[A\033[K%c\t %s%*s%c\n", 179, CHAR, RemainingSpace(CHAR, 27), "", 179);
}

void inputINT(int *INT) {
    printf("%c\t", 179);
    fflush(stdout);
    scanf("%d", INT);
    // Convert integer to character
    char charValue[1000];
    sprintf(charValue, "%d", *INT);
    printf("\033[A\033[K%c\t %s%*s%c\n", 179, charValue, RemainingSpace(charValue, 27), "", 179);
}

void adaptiveWindowsTree(char *CHAR) {
    printf("%c   %c", 179, 195);
    fflush(stdout);
    scanf("%s", CHAR);
    printf("\033[A\033[K%c   %c%s%*s%c\n", 179, 195,  CHAR, RemainingSpace(CHAR, 31), "", 179);
}


void adaptiveWindowsLastChild(char *CHAR) {
    printf("%c   %c", 179, 192);
    fflush(stdout);
    scanf("%s", CHAR);
    printf("\033[A\033[K%c   %c%s%*s%c\n", 179, 192,  CHAR, RemainingSpace(CHAR, 31), "", 179);

}



char src[1000], dest[1000], recentBusStop[1000][1000];
int time, range;

void printBody() {
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c\n", 179,218,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,191, 179);
    printf("%c %c Personalized Bus path-finding%c  %c\n", 179,179,179,179);
    printf("%c %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c\n", 179,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c  %c  What's the nearest bus stop?  %c\n",179, 254, 179);
    inputCHAR(src);
    printf("%c  %c  Where're u going?             %c\n", 179, 175,179);
    inputCHAR(dest);
    printf("%c  %c  What time is it? (hhmm)       %c\n", 179, 232, 179);
    inputINT(&time);
    printf("%c  %c%c range ur walkable? (m)        %c\n", 179, 168, 63, 179);
    inputINT(&range);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c > Recent bus stop you used        %c\n", 179, 179);
    adaptiveWindowsTree(recentBusStop[0]);
    adaptiveWindowsTree(recentBusStop[1]);
    adaptiveWindowsTree(recentBusStop[2]);
    adaptiveWindowsTree(recentBusStop[3]);
    adaptiveWindowsLastChild(recentBusStop[4]);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
    printf("%c                                   %c\n", 179, 179);
}

int main() {
    printUpperBorder();
    printBody();
    printUnderBorder();

    return 0;
}