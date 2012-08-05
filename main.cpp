#ifndef ANZ_CARDS
#define ANZ_CARDS 17
#endif

#include <iostream>
#include "bot.h"
#include "card.h"

/*the main programm calls the bot class and says what cards are on the desk*/

using namespace std;

int main(void){
    //initiate cards on the desk
    const int anz=ANZ_CARDS;
    card st_card[anz];
    card * standard[anz];
    int standardv[anz]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
    for (int i=0; i<anz; i++){
	st_card[i].set_card(standardv[i]);
	standard[i] = & st_card [i];
    }
    //create and initiate bot class with the cards on the desk
    bot game; 
    
    interface_factory factory;
    
    game.player_cnt=3;
    game.all_players[0].decision = factory.create('h');
    game.all_players[1].decision = factory.create('c');
    game.all_players[2].decision = factory.create('e');
    game.all_players[3].decision = factory.create('c');

    game.init(standard,anz);
    //run game
    game.run();

    return 0;
}
