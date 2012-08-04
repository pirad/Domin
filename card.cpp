#include <sqlite3.h>
#include "card.h"
#include <string>
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

/*the card object stands for each card type that is used in the game*/

card::card(void){
}

int card::set_card(int idgeg){
/*set_card reads the properties of the card (given by an id) from the database*/
    //open Database
    sqlite3* card_db;
    string Path="Card.db";
    if(sqlite3_open(Path.c_str(), &card_db) != SQLITE_OK)
    {
        cout << "Fehler beim Öffnen: " << sqlite3_errmsg(card_db) << endl;
        return 1;
    }
 
    //read Database
    int ret;
    char *statement;
    
    //the SQL statement
    statement=sqlite3_mprintf( "select id, name, descr, price, plus_actions, plus_money, plus_buys, plus_cards, points, money, action, attac, reaction, point, curse, game_base, game_intr, game_hinter, game_prosp, game_alch, game_sea, game_corn, game_misc from Card where id = %i ;",idgeg);
    sqlite3_stmt *stmt;

    ret=sqlite3_prepare_v2(card_db, statement,  500, &stmt, NULL);
    
    if (sqlite3_step(stmt) != SQLITE_DONE){
	//set the variables
        price=sqlite3_column_int(stmt,3);
	points=sqlite3_column_int(stmt,8);
	plus_actions=sqlite3_column_int(stmt,4);
	plus_money=sqlite3_column_int(stmt,5);
	plus_buys=sqlite3_column_int(stmt,6);
	plus_cards=sqlite3_column_int(stmt,7);
	for (int i=9; i<15; i++){
	    type[i-9]=(bool) sqlite3_column_int(stmt,i);
	}
	for (int i=15; i<23; i++){
	    origin[i-15]=(bool) sqlite3_column_int(stmt,i);
	}
	id=sqlite3_column_int(stmt,0);
	sprintf(name,"%s",sqlite3_column_text(stmt,1));
    } else {
	cout << "Diese id existiert nicht!" << endl;
	return 1;
    }


    //close database connection
    sqlite3_close(card_db);
 
    stack = 10;
    if (type[4]){
	stack=12;
    }
    switch (id){
	case 1: //Kupfer
	    stack=60;
	    break;
	case 2: //Silber
	    stack=40;
	    break;
	case 3: //Gold
	    stack=30;
	    break;
	case 7://Fluch
	    stack=30;
	    break;
    }

	    

    // Programm beenden
    return 0;   
 }

void card::action(void){}
void card::attac(void){}
void card::reaction(void){}
