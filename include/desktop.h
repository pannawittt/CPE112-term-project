#ifndef _DESKTOP_H_
#define _DESKTOP_H_

#include "vector.h"

void desktopIn(char* userTime, char* userSrc, char* userDest, int* walkLength, vector userBus);
void desktopEnd();
void desktopPrint(char* _str, size_t _space);

#endif