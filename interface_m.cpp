#include "interface.h"
//#include <iostream>
/*braucht einen bot und interface_r
 * muss diese dann kopieren und den Ausgang des Spieles bestimmen
 * dafür brauche ich eine Kopierfunktion von bot und interface_r
 * wahrscheinlich brauche ich einen extra bot wegen der Abhängigkeiten,
 * wegen der Ausgaben und wegen der initialisierung der Karten am Anfang
 * Copy-Contructoren siehe z.B. C++ für Ingeneure S. 246 kann einfach mit bot bot2(bot1); kopiert werden*/

using namespace std;

/*the interface for computer players*/


int monte::interact (int type, card * choose[STACK_SIZE], int choose_cnt){
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
	    for (int i=0; i< choose_cnt; i++){
		max=-1;
		stelle=-1;
		for (int j=i; j<choose_cnt-1; j++){
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

void monte::notify (int type, int info, int info1, int info2){
    return; 
}

void monte::init (int players_cnt){
}

monte::monte (void){

}

