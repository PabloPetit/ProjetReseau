//
//  menu.h
//  Client
//
//  Created by Pablo Petit on 20/04/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#ifndef __Client__menu__
#define __Client__menu__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.h"
#include "diffuseur.h"

int menu_simple(char *, char * args[],int);
int capture_select_simple(int);
liste_dif ** menu_diffuseurs(liste_dif *,int);



#endif /* defined(__Client__menu__) */
