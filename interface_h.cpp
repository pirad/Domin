#include "interface.h"
#include <iostream>

/*the interface for human players*/

using namespace std;

int card_choose(card * choose[STACK_SIZE], int choose_cnt, bool none){
    int retval=-1; 
    if (none){
	cout << 0 << " - keine, ";
    }
    for (int i=0; i< choose_cnt; i++){
	cout << i+1 << " - " << choose[i]->name << " (" << choose[i]->price << "/" << choose[i]->stack << "), ";
    }
    cout << " ";
    do {
	cin >> retval;
    } while (retval < 0 || retval > choose_cnt-1+none);
    if (retval == 0){
	return choose_cnt;
    } else {
	return retval-1;
    }
    return retval;
}

int human::interact (int type, card * choose[STACK_SIZE], int choose_cnt){
    int ret_val=-1;
    switch(type){
	case 1: //Karte ausspielen
	    cout << "Welche Karte wollen Sie spielen? Sie haben:" << endl;
	    ret_val=card_choose(choose,choose_cnt,true);
	    break;
	case 21: //Geld ausspielen
	    cout << "Spielen Sie Geld aus!" << endl;
	    cout << "Sie haben: " << endl;
	    int sorted_choose[choose_cnt];
	    for (int i=0; i< choose_cnt; i++){
		sorted_choose[i]=i;
	    }
	    int max;
	    int stelle;
	    int tausch;
	    for (int i=0; i< choose_cnt-1; i++){
		max=1000;
		stelle=-1;
		for (int j=i; j<choose_cnt; j++){
		    if (max>choose[sorted_choose[j]]->id){
			max=choose[sorted_choose[j]]->id;
			stelle=j;
		    }
		}
		tausch=sorted_choose[i];
		sorted_choose[i]=sorted_choose[stelle];
		sorted_choose[stelle]=tausch;
	    }
	    for (int i=0; i< choose_cnt-1; i++){
		max=-1;
		stelle=-1;
		for (int j=i; j<choose_cnt; j++){
		    if (max<choose[sorted_choose[j]]->plus_money){
			max=choose[sorted_choose[j]]->plus_money;
			stelle=j;
		    }
		}
		tausch=sorted_choose[i];
		sorted_choose[i]=sorted_choose[stelle];
		sorted_choose[stelle]=tausch;
	    }
	    int cnt;
	    for (int i=0; i<choose_cnt; i++){
		cnt=1;
		while (i<choose_cnt-1 && choose[sorted_choose[i]]->id == choose[sorted_choose[i+1]]->id){
		    cnt++;
		    i++;
		}
		cout << cnt << " " << choose[sorted_choose[i]]->name <<", ";
	    }
	    cout << endl << "Wollen Sie alle Karten ausspielen? (j/n) " ;
	    char inp;
	    do {
		cin >> inp;
	    } while (inp != 'j' && inp != 'n');
	    if (inp == 'j'){
		// play all
	       ret_val = choose_cnt+1;
	    } else {
		//ask for first card
		cout << "Welche wollen Sie ausspielen? Sie haben: " << endl;
		ret_val=card_choose(choose,choose_cnt,true);
	    }
	    break;
	case 22: //play more money
	    cout << "Welche Geldkarte wollen Sie noch ausspielen? Sie haben: " << endl;
	    ret_val=card_choose(choose,choose_cnt,true);
	    break;

	case 3:
	    cout << "Welche Karte wollen Sie kaufen? " << endl;
	    cout << "Sie haben zur Auswahl: " << endl;
	    ret_val=card_choose(choose,choose_cnt,true);
	    if (ret_val == choose_cnt){
		cout << "Sie wollen keine Karte kaufen." << endl;
	    } else {
		cout << "Sie haben " << choose[ret_val]->name << " gekauft. Es sind noch " << choose[ret_val]->stack-1 << " Karten übrig." << endl;
	    }
	    break;

	case 71: //enemy taken card
	    cout << "Ihr Gegner hat " << choose[0]->name << " genommen. Es sind noch " << choose[0]->stack << " Karten übrig." << endl;
	    break;
	case 72: //enemy trashed card
	    cout << "Ihr Gegner hat " << choose[0]->name << " entsorgt." << endl;
	    break;

	case 101: //chapel
	    cout << "Welche Karte wollen Sie entsorgen? Sie haben: " << endl;
	    ret_val=card_choose(choose,choose_cnt,true); 
	    break;
    }
    return ret_val;
}

void human::notify(int type, int info){
    switch (type){
	case 1: //money amount
	    cout << "Sie haben " << info << " Geld." << endl;
	    break;
    }
}

