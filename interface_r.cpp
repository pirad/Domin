#include "interface.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/*the interface for random players*/


int random::interact (int type, card * choose[STACK_SIZE], int choose_cnt){
    int retval=-1;
    switch (type){
	case 1: 
	    retval=rand() % choose_cnt + 1; 
	    break;
	case 3:
	    if (! (choose_cnt==1 && choose[0]->id == 7)){
		do {
		    retval=rand() % choose_cnt + 1; 
		} while (retval < choose_cnt && choose[retval]->id == 7);
	    }
	    cout << retval << endl;
	    break;
	case 21:
	    retval=choose_cnt+1;
	    break;
	case 101:
	    retval=choose_cnt;
	default:
	    if (choose_cnt>1){
		retval=rand() % (choose_cnt-1) ; 
	    } else {
		retval = choose_cnt;
	    }
    }

    return retval;
}

void random::notify (int type, int info, int info1, int info2){
    return; 
}

random::random (void){
    //randomize
    time_t t;
    time(&t);
    srand((unsigned int)t);
}
