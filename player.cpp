#include "player.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

/*player manages the card stacks and hase a player interface*/

using namespace std;

void player::play(int ind_hand){
/*puts card from hand to played cards*/
    card * card_played = hand[ind_hand];
    played[played_cnt]=hand[ind_hand];
    played_cnt++;
    for (int i=ind_hand; i<hand_cnt-1; i++){
	hand[i]=hand[i+1];
    }
    hand_cnt--;
}

void player::take(card * card_taken){
/*puts a card card_taken to the discard_pile*/
    if (card_taken->stack>0){
	card_taken->stack --;
	discard_pile[discard_pile_cnt]=card_taken;
	discard_pile_cnt++;
    }
}

void player::shuffle(void){
/*shuffles the discard_pile and puts the cards on the deck pile*/
    //put all cards on the deck
    for (int i=0; i< discard_pile_cnt; i++){
	deck[i]=discard_pile[i];
    }
    deck_cnt=discard_pile_cnt;
    discard_pile_cnt=0;
    //shuffle the deck
    card * swap;
    int j;
    for (int i=0; i<deck_cnt-1; i++){
	swap=deck[i];
	j=rand() % (deck_cnt-i-1) +i+1;
	deck[i]=deck[j];
	deck[j]=swap;
    }
}

void player::draw(int nmb){
/*drwas nmb cards from the deck to the hand, shuffles if deck is empty*/
    for (int i=0; i<nmb; i++){
	if (deck_cnt==0){
	    //shuffle
	    if (discard_pile_cnt>0){
		shuffle();
	    } else {
		return ;
	    }
	}
	//draw
	deck_cnt--;
	hand[hand_cnt]=deck[deck_cnt];
	hand_cnt++;
    }
}



void player::init(card * start[10]){
/*initiates player, takes the cards given, shuffles and draws*/
    for (int i=0; i<10; i++){
	discard_pile[i]=start[i];
    };
    discard_pile_cnt=10;
    deck_cnt=0;
    hand_cnt=0;
    played_cnt=0;
    //randomize
    time_t t;
    time(&t);
    srand((unsigned int)t);
    
    //shuffle and draw
    shuffle();
    draw(5);
}

void player::end_turn(void){
/*discards all cards in game nd draws 5 new cards*/
    //discard the played cards
    while (played_cnt > 0){ 
	played_cnt--;
        discard_pile[discard_pile_cnt]=played[played_cnt];
	discard_pile_cnt++;
    }
    //discard the cards on the hand
    while (hand_cnt > 0){ 
	hand_cnt--;
	discard_pile[discard_pile_cnt]=hand[hand_cnt];
	discard_pile_cnt++;
    }
    //draw
    draw(5);
}
