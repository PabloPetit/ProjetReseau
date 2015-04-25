#include "main.h"

int main(int argc, char * argv[]) {
	char * intro,**args;
	int res;
    if(argc<4 || argc >12){
    	printf("Arguments incorrects\n");
    }

    intro = argv[1];
    args=(argv+2);
    initscr();
    
    res = run(intro,args,argc-2);

    printf("%d",res);

    endwin();
    return 0;
}
