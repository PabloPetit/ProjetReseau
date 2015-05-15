#ifndef __Menu__getch__
#define __Menu__getch__

#include <stdio.h>
#include <termios.h>

void initTermios(int);
void resetTermios();
char getch_(int);
char getchr();
char getche();

#endif
