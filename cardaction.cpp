#include "cardaction.h"

baseaction* action_factory::create(int id){
    baseaction* retval=0;
    switch (id){
	case 16: //Chapel
	    retval=new action_chapel();
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


/*
int action_::do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]){
    int retval=-1;

    return retval;
}
*/
