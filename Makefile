main: main.o bot.o card.o player.o interface.o interface_h.o interface_c.o interface_r.o interface_e.o cardaction.o Card.db
	c++ main.o card.o cardaction.o player.o bot.o interface.o interface_h.o interface_c.o interface_r.o interface_e.o -o main -lsqlite3

card.o: card.cpp card.h
	c++ -c card.cpp -lsqlite3

Card.db: create.sql
	sqlite3 Card.db ".read create.sql"

main.o: main.cpp 
	c++ -c main.cpp 

bot.o: bot.cpp bot.h player.h card.h cardaction.h
	c++ -c bot.cpp

player.o: player.cpp player.h card.h interface.h
	c++ -c player.cpp

interface.o: interface.cpp interface.h
	c++ -c interface.cpp

interface_h.o: interface_h.cpp interface.h
	c++ -c interface_h.cpp

interface_c.o: interface_c.cpp interface.h
	c++ -c interface_c.cpp

interface_r.o: interface_r.cpp interface.h
	c++ -c interface_r.cpp

interface_e.o: interface_e.cpp interface.h
	c++ -c interface_e.cpp

cardaction.o: cardaction.h cardaction.cpp player.h card.h
	c++ -c cardaction.cpp
