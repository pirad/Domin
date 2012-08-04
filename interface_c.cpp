#include "interface.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


using namespace std;

/*the interface for computer players*/


int computer::interact (int type, card * choose[STACK_SIZE], int choose_cnt){
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
	    int sort[choose_cnt];
	    for (int i=0; i< choose_cnt; i++){
		sort[i]=i;
	    }
	    int max;
	    int stelle;
	    int tausch;
	    cout << "initialisiert ";
	    for (int i=0; i< choose_cnt-1; i++){
		max=-1;
		stelle=-1;
		for (int j=i; j<choose_cnt; j++){
		    if (max<choose[sort[j]]->plus_money){
			max=choose[sort[j]]->plus_money;
			stelle=j;
		    }
		}
		tausch=sort[i];
		sort[i]=sort[stelle];
		sort[stelle]=tausch;
	    }
	    cout << "sortiert1 ";
	    for (int i=0; i< choose_cnt-1; i++){
		max=-10;
		stelle=-1;
		for (int j=i; j<choose_cnt; j++){
		    if (max<choose[sort[j]]->points){
			max=choose[sort[j]]->points;
			stelle=j;
		    }
		}
		tausch=sort[i];
		sort[i]=sort[stelle];
		sort[stelle]=tausch;
	    }
	    cout << "sortiert2 ";
	    for (int i=0; i< choose_cnt-1; i++){
		max=-1;
		stelle=-1;
		for (int j=i; j<choose_cnt; j++){
		    if (max<choose[sort[j]]->price){
			max=choose[sort[j]]->price;
			stelle=j;
		    }
		}
		tausch=sort[i];
		sort[i]=sort[stelle];
		sort[stelle]=tausch;
	    }
	    cout << "sortiert 3" << endl;

	    retval=sort[0];
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

void computer::notify (int type, int info){
    return; 
}

computer::computer (void){
    //randomize
    time_t t;
    time(&t);
    srand((unsigned int)t);
}
