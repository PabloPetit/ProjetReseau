#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char * getTime(void){

	time_t seconde;
	struct tm instant;

	char * heure = malloc(sizeof(char)*8);

	time(&seconde);
	instant=*localtime(&seconde);

	snprintf(heure, 9,"%d:%d:%d", instant.tm_hour, instant.tm_min, instant.tm_sec);
	return heure;
    //return 0;
}

int main(void){
	char * heure = getTime();
	printf("%s\n", heure);
	free(heure);
}