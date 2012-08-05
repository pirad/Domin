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

void cards_drawn_output(card * choose[STACK_SIZE], int choose_cnt){
/*Sorts the Cards and counts the different types writes them on standard output*/
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
	    if (max<choose[sorted_choose[j]]->price){
		max=choose[sorted_choose[j]]->price;
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
    cout << endl;
}

int human::interact (int type, card * choose[STACK_SIZE], int choose_cnt){
    int ret_val=-1;
    char inp;
    switch(type){
	case 0: //Cards drawn
	    cout << "Sie haben folgende Karten auf der Hand: " << endl;
	    cards_drawn_output(choose, choose_cnt);
	    break;
	case 1: //Karte ausspielen
	    cout << "Welche Karte wollen Sie spielen? Sie haben:" << endl;
	    ret_val=card_choose(choose,choose_cnt,true);
	    break;
	case 21: //Geld ausspielen
	    cout << "Spielen Sie Geld aus!" << endl;
	    cout << "Sie haben: " << endl;
	    cards_drawn_output(choose,choose_cnt);
	    cout << "Wollen Sie alle Karten ausspielen? (j/n) " ;
	    inp='x';
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

	case 3: // buy card
	    cout << "Welche Karte wollen Sie kaufen? " << endl;
	    cout << "Sie haben zur Auswahl: " << endl;
	    ret_val=card_choose(choose,choose_cnt,true);
	    if (ret_val == choose_cnt){
		cout << "Sie wollen keine Karte kaufen." << endl;
	    } else {
		cout << "Sie haben " << choose[ret_val]->name << " gekauft. Es sind noch " << choose[ret_val]->stack-1 << " Karten übrig." << endl;
	    }
	    break;

	case 4: //cards played with
	    cout << "Es wird gespielt mit: " << endl;;
	    for (int i=0; i< choose_cnt; i++){
		cout << choose[i]->name << ", ";
		switch (i){
		    case 2:
		    case 6:cout << endl;
		}
	    }
	    cout << endl;
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

	case 117: //Scout  
	    cout << "Folgende Karten müssen Sie zurück auf den Nachziehstapel legen: ";
	    cards_drawn_output(choose,choose_cnt);
	    cout << "Wollen Sie alle Karten so zurück legen, wie Sie sie genommen haben? (j/n) ";
	    inp = 'x';
	    do {
		cin >> inp;
	    } while (inp != 'j' && inp != 'n');
	    if (inp == 'n'){
		cout << "Welche Karte wollen Sie zuerst zurück legen? " << endl;
		ret_val=card_choose(choose,choose_cnt,false);
	    } else {
		ret_val=choose_cnt;
	    }
	    break;
	case 1171: //Scout next Card
	    cout << "Welche Karte soll nun zurück auf den Ablagestapel?" << endl;
	    ret_val=card_choose(choose,choose_cnt,false);
	    break;
	case 1170: //Scout point cards taken
	    cout << "Sie haben folgende Punktekarten auf die Hand genommen: ";
	    cards_drawn_output(choose,choose_cnt);
	    break;
	      }
    return ret_val;
}

void human::notify(int type, int info, int info1, int info2){
    switch (type){
	case 1: //money amount
	    cout << "Sie haben " << info << " Geld." << endl;
	    break;
	case 2: //number Player
	    cout << "Es spielen " << info << " Spieler." << endl;
	    break;
	case 3: //turn Player
	    cout << endl << endl <<"Spieler " << info << " ist an der Reihe." << endl;
	    break;
	case 4: //end
	    cout << endl << endl;
	    for (int i=0; i< 20; i++){
		cout << "===" ;
	    }
	    cout << endl << "Das Spiel ist zu ende." << endl << endl;
	    break;
	case 5: //winner
	    cout << "Spieler " << info << " hat gewonnen!" << endl;
	    break;
	case 6: //points
	    cout << endl << "Spieler " << info << " hat " << info1 << " Punkte." << endl;
	    break;
	case 7: //money other player
	    cout << "Der Spieler hat " << info << " Geld." << endl;
	    break;
    }
}

