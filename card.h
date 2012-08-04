#ifndef CARD_H
#define CARD_H

class card{
    public:
	int price;
	int points;
	int plus_actions;
	int plus_money;
	int plus_buys;
	int plus_cards;
	bool type[6];
	bool origin[8];
	int id;
	char name[40];
	
	int stack;
	int desk_index;
	
	int set_card(int id);
	void action(void);
	void attac(void);
	void reaction(void);

	card(void);
};
#endif //CARD_H
