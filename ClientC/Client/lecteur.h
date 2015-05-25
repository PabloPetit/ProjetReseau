//
//  lecteur.h
//  Client
//
//  Created by Pablo Petit on 11/05/2015.
//  Copyright (c) 2015 Pablo Petit. All rights reserved.
//

#ifndef __Client__lecteur__
#define __Client__lecteur__

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include "diffuseur.h"




void * run_lecture(void *);

#endif /* defined(__Client__lecteur__) */
