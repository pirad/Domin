#include "interface.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


using namespace std;

/*the interface for earl players*/


int earl::interact (int type, card * choose[STACK_SIZE], int choose_cnt){
    int retval=-1;
    switch (type){
	case 1:
	    for (int i=0; i<choose_cnt; i++){
		if (choose[i]->plus_actions>0){
		    return i;
		}
	    }
	    retval=0;
	    break;
	case 21:
	    retval=choose_cnt+1;
	    break;
	case 3:
	    retval=choose_cnt;
	    for (int i=0; i< choose_cnt; i++){
		if (choose[i]->id == 6){
		    return i;
		}
		if (choose[i]->id == 3){
		    retval=i;
		}
		if (choose[i]->id == 5 && (retval == choose_cnt || choose[retval]->id != 3)){
		    retval=i;
		}
		if (choose[i]->id == 2 && retval == choose_cnt){
		    retval=i;
		}
	    }
	    break;
	default:
	    if (choose_cnt>1){
		retval=rand() % (choose_cnt-1) ; 
	    } else {
		retval = choose_cnt;
	    }
    }


    return retval;
}

void earl::notify (int type, int info, int info1, int info2){
    return; 
}

earl::earl (void){
    //randomize
    time_t t;
    time(&t);
    srand((unsigned int)t);
}
