#ifndef BOT_H
#define BOT_H

#define DESK_SIZE 25

#ifndef SWITCH_SIZE
#define SWITCH_SIZE 1
#endif


#include "player.h"
#include "card.h"
#include "cardaction.h"

class bot{
    public:
	void interact(int type);
	void init(card * deskgeg[DESK_SIZE], int deskgeg_cnt);
	bool turn(void);
	void run(void);
	int count(void);
	void end_game(void);
	void play(int ind_hand);
	void take(int ind_desk);
	void trash(int ind_hand);


	card * desk[DESK_SIZE];
	int desk_cnt;
	baseaction* desk_action[DESK_SIZE];
	int empty_piles;
	bool game_end;
	int buys;
    	int actions;
	int money;
	bool switches[SWITCH_SIZE];

	player* akt_player;
	int akt_player_ind;
	player all_players[4];
	int player_cnt;


    private:
	void notify(int type, int info=0, int info1=0, int info2=0);
};

#endif //BOT_H
