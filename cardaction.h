#ifndef CARDACTION_H
#define CARDACTION_H

#ifndef DESK_SIZE
#define DESK_SIZE 25
#endif 

#ifndef SWITCH_SIZE
#define SWITCH_SIZE 1
#endif

#include "player.h"
#include "card.h"

class baseaction{
    public:
        virtual ~baseaction(){ };
	virtual int do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE])=0;
};

class action_factory{
    public:
	baseaction* create(int id);
};

class action_empty : public baseaction{
    public:
	int do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]);
};

class action_chapel: public baseaction{
    public:
	int do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]);
};


/*
class action_ : public baseaction{
    public:
	int do_action(player* akt_player, card * desk[DESK_SIZE], int &desk_cnt, int &buys, int &actions, int &money, int &draw_cards, bool switches[SWITCH_SIZE]);
};
*/

#endif //CARDACTION_H
