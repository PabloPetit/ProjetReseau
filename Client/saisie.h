#ifndef __Client__saisie__
#define __Client__saisie__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "getch.h"

#define ALPHANUMERIC 0
#define NUMERIC 1
#define IPV4 2
#define ALNU_SIZELESS 3


void print(char *);
int saisie(int,char *,const char *,int);

#endif /* defined(__Client__saisie__) */
