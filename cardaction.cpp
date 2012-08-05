#include "cardaction.h"
//#include <iostream>

using namespace std;

baseaction* action_factory::create(int id){
    baseaction* retval=0;
    switch (id){
	case 16: //Chapel
	    retval=new action_chapel();
	    break;
	case 17: //Scout
	    retval=new action_scout();
	    break;

	default: //rest
	    retval=new action_empty();
    }
    return retval;
}


int action_empty::do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]){
    int retval=0;

    return retval;
}

int action_chapel::do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]){
    int retval=0;
    int del=-1;
    for (int i=0; i<4; i++){
	if (akt_player->hand_cnt>0){
	    del=akt_player->decision->interact(101,akt_player->hand, akt_player->hand_cnt);
	    if (del == akt_player->hand_cnt){
		i=4;
	    } else {
		akt_player->hand[del]=akt_player->hand[akt_player->hand_cnt-1];
		akt_player->hand_cnt--;
	    }
	}
    }
    return retval;
}

int action_scout::do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]){
    int retval=-1;
    
    card * drawn[4];
    int cards_drawn=4;
    for (int i=0; i<4; i++){
	if (akt_player->deck_cnt == 0){
	    if (akt_player->discard_pile_cnt >0){
		akt_player->shuffle();
	    } else {
		cards_drawn=i;
	    }
	}
	if (cards_drawn == 4){
	    akt_player->deck_cnt--;
	    drawn[i]=akt_player->deck[akt_player->deck_cnt];
	}
    }
    card * point_cards[4];
    int point_cards_cnt=0;
    for (int i=0; i<cards_drawn; i++){
	if (drawn[i]->type[4]){
	    point_cards_cnt++;
	    point_cards[point_cards_cnt-1]=drawn[i];
	    akt_player->hand[akt_player->hand_cnt]=drawn[i];
	    akt_player->hand_cnt++;
	    cards_drawn--;
	    drawn[i]=drawn[cards_drawn];
	    i--;
	}
    }
    akt_player->decision->interact(1170,point_cards,point_cards_cnt);
    int ret_val=akt_player->decision->interact(117,drawn,cards_drawn);
    if (ret_val == cards_drawn){
	for (int i=0; i< cards_drawn; i++){
	    akt_player->deck[akt_player->deck_cnt]=drawn[cards_drawn-1-i];
	    akt_player->deck_cnt++;
	}
    } else {
	while (cards_drawn>0) {
	    akt_player->deck[akt_player->deck_cnt]=drawn[ret_val];
	    akt_player->deck_cnt++;
	    cards_drawn--;
	    drawn[ret_val]=drawn[cards_drawn];
	    if (cards_drawn <= 1){
		if (cards_drawn ==1){
		    ret_val=1;
		}
	    } else {
		ret_val = akt_player->decision->interact(1171,drawn,cards_drawn);
	    }
	}
    }
    retval=0;
    return retval;
}


/*
int action_::do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]){
    int retval=-1;

    return retval;
}
*/
