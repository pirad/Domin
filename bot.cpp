/*bot is the referee for the game. it calls the players. it manages the turns*/

//#include <iostream>
#include "bot.h"

using namespace std;

void bot::init(card * deskgeg[25],int deskgeg_cnt){
/*init initiates the game. It gets a deck of cards that lie on the desk it initiates players*/

    //initiate desk
    desk_cnt=deskgeg_cnt;
    action_factory af;
    for (int i=0; i< desk_cnt; i++){
        desk[i]=deskgeg[i];
	desk[i]->desk_index=i;
	desk_action[i]=af.create(desk[i]->id);
    }

    for (int i=0; i<SWITCH_SIZE; i++){
	switches[i]=false;
    }
    //give the player the 10 start cards
    card * start[10];
    for (int i=0; i<7; i++){
	start[i]=desk[0];
    }
    for (int i=7; i<10; i++){
	start[i]=desk[3];
    }

    for (int i=0; i<player_cnt; i++){
        akt_player = &all_players[i];
	akt_player_ind = i;
	akt_player->init(start);
	desk[0]->stack -= 7;
    }

    empty_piles=0;
    game_end=false;
    
    return ;
}

void bot::run(void){
/*run manages the game and finds the winner*/
    notify(2,player_cnt);
    for (int i=0; i<player_cnt; i++){
	all_players[i].decision->interact(4,desk,desk_cnt);
    }
    //the turns
    while (! game_end){
	for (int j=0; j<player_cnt; j++){
	    if (! game_end){
		akt_player = &all_players[j];
	        akt_player_ind = j;
		notify(3,j);
		turn();
	    }
	}
    }
    end_game();
}

void bot::end_game(void){
    //the winner
    int end_points[player_cnt];
    for (int i=0; i< player_cnt; i++){
	akt_player = &all_players[i];
	end_points[i]=count();
    }
    int rang[player_cnt];
    for (int i=0; i<player_cnt;i++){
	rang[i]=i;
    }
    int max;
    int stelle;
    int tausch;
    for (int i=0; i< player_cnt-1; i++){
	max=-100;
	for (int j=i; j< player_cnt; j++){
	    if (end_points[j]>max){
		max=end_points[j];
		stelle=j;
	    }
	}
	tausch=rang[i];
	rang[i]=rang[stelle];
	rang[stelle]=tausch;
	tausch=end_points[i];
	end_points[i]=end_points[stelle];
	end_points[stelle]=tausch;
    }
    notify(4);
    if (end_points[0]>end_points[1]){
	notify(5,rang[0]);
    } else {
	notify(5,rang[0]);
	int i=1;
	do{
	    notify(5,rang[i]);
	} while (end_points[i] == end_points[i++] && i<player_cnt);
    }
    for (int i=0; i< player_cnt; i++){
	notify(6,rang[i],end_points[i]);
    }
}

void bot::notify(int type, int info, int info1, int info2){
    for (int i=0; i< player_cnt; i++){
	all_players[i].decision->notify(type, info, info1, info2);
    }
}

bool bot::turn(void){
/*a turn of one player, should return false when game ended*/
    bool action_card=true;
    actions=1;
    buys=1;
    money=0;

    interact(0);
    //play actions
    while (action_card){
	int action_cnt=0;
        for (int i=0; i<akt_player->hand_cnt;i++){
	    if (akt_player->hand[i]->type[1]){
		action_cnt++;
	    }
	}
	if (action_cnt>0 && actions>0){
	    interact(1);
	} else {
	    action_card=false;
	};
    }
    //buy cards
    while (buys>0){
	interact(2);
	notify(7,money);
	interact(3);
    }
    //end turn
    akt_player->end_turn();
    return true;
}

int bot::count(void){
/*counts points of akt_player*/
    int ret=0;
    int i;
    //take all cards in the hand
    do {
	i=akt_player->hand_cnt;
	akt_player->draw(1);
    } while (i != akt_player->hand_cnt);
    //count the points on the hand
    for (int i=0; i< akt_player->hand_cnt; i++){
	if (akt_player->hand[i]->type[4] || akt_player->hand[i]->type[5]){
	    ret += akt_player->hand[i]->points;
	}
    }
    return ret;
}

void bot::interact(int type){
/*calls the decision making instance of the akt_player, command line for human players, a programm for computer players
 * type says wich decision will be made
 * calculates the possible moves and gives the possible cards to the player*/
    card * choose[STACK_SIZE];
    int choose_cnt=0;
    int choose_int[STACK_SIZE];
    int ret_val;
    switch(type){
	case 0: //cards drawn
	    akt_player->decision->interact(type,akt_player->hand,akt_player->hand_cnt);
	    break;
	case 1://play action Card 
	    for (int i=0; i<akt_player->hand_cnt; i++){
		if (akt_player->hand[i]->type[1]){
		    choose[choose_cnt]=akt_player->hand[i];
		    choose_int[choose_cnt]=i;
		    choose_cnt++;
		}
	    }
	    ret_val=akt_player->decision->interact(type,choose,choose_cnt);
	    if (ret_val<choose_cnt){
		play(choose_int[ret_val]);
	    } else {
		actions=0;
	    }
	    break;
	case 2://play money Cards
	    for (int i=0; i<akt_player->hand_cnt; i++){
		if (akt_player->hand[i]->type[0]){
		    choose[choose_cnt]=akt_player->hand[i];
		    choose_int[choose_cnt]=i;
		    choose_cnt++;
		}
	    }
	    if (choose_cnt>0){
		    ret_val=akt_player->decision->interact(21,choose,choose_cnt);
	        if (ret_val == choose_cnt+1){
		   // play all
		    for (int i=choose_cnt-1; i>= 0; i--){
			play(choose_int[i]);
		    }
		} else {
		    if (ret_val != choose_cnt){
		    //play only one card
			do {
			    play(choose_int[ret_val]);
			    for (int i=0; i< choose_cnt; i++){
				if (choose_int[i]>choose_int[ret_val]){
				    choose_int[i]--;
				}
			    }
			    choose[ret_val]=choose[choose_cnt-1];
			    choose_int[ret_val]=choose_int[choose_cnt-1];
			    choose_cnt--;
			    ret_val=akt_player->decision->interact(22,choose,choose_cnt);
			} while ((choose_cnt != 0) && (ret_val != choose_cnt));
		    }
		}
	    }
	    break;
	case 3://buy card
	    for (int i=0; i<desk_cnt; i++){
		if (desk[i]->price <= money && desk[i]->stack>0){
		    choose[choose_cnt]=desk[i];
		    choose_int[choose_cnt]=i;
		    choose_cnt++;
		}
	    }
	    akt_player->decision->notify(1,money);
	    if (choose_cnt>0){
		ret_val=akt_player->decision->interact(type,choose,choose_cnt);
		//Achtung hier noch Stapelgröße einbauen
		if (ret_val == choose_cnt){
		    buys=0;
		} else {
		    money -= desk[choose_int[ret_val]]->price;
		    buys--;
		    akt_player->take(desk[choose_int[ret_val]]);
		    take(choose_int[ret_val]);
		}
	    } else {
		buys = 0;
	    }
	    break;
    }
}

void bot::play(int ind_hand){
/*this function plays a card it should call all things that happen if a card is played*/
    card * card_played=akt_player->hand[ind_hand];
    akt_player->play(ind_hand);
    //reduce actions if action card is played
    if (card_played->type[1]){
	actions--;
    }
    //money, buys, actions and cards
    money += card_played->plus_money;
    actions += card_played->plus_actions;
    buys += card_played->plus_buys;
    akt_player->draw(card_played->plus_cards);
    //call action
    int draw_cards=0;
    desk_action[card_played->desk_index]->do_action(akt_player, desk, desk_cnt, buys, actions, money, draw_cards, switches);
}
void bot::take(int ind_desk){
    card * ueberg[DESK_SIZE];
    
    ueberg[0]=desk[ind_desk];

    if (desk[ind_desk]->stack == 0){
	empty_piles++;
    }
    if ((desk[ind_desk]->id == 6 && desk[ind_desk]->stack==0) || empty_piles == 3){
	game_end=true;
    }	

    for (int i=0; i<player_cnt; i++){
	if (akt_player_ind != i){
	    all_players[i].decision->interact(71,ueberg,1);
	}
    }
}
void bot::trash(int ind_hand){
    card * ueberg[DESK_SIZE];
    ueberg[0]=akt_player->hand[ind_hand];

    for (int k=0; k<player_cnt; k++){
	if (akt_player_ind != k){
		all_players[k].decision->interact(72,ueberg,1);
	}
    }
}
