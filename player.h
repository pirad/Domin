#ifndef PLAYER_H
#define PLAYER_H

#ifndef STACK_SIZE
#define STACK_SIZE 50
#endif

#include "card.h"
#include "interface.h"

class player{
    public:
	void init(card * start[10]);

	card * discard_pile[2*STACK_SIZE];
	int discard_pile_cnt;
	card * deck[2*STACK_SIZE];
	int deck_cnt;
	card * hand[STACK_SIZE];
	int hand_cnt;
	card * played[STACK_SIZE];
	int played_cnt;
 
	void shuffle(void);
	void draw(int nmb);
	void play(int ind_hand);
	void take(card * card_taken);
	void end_turn(void);

	interface* decision;
};
#endif //PLAYER_H
