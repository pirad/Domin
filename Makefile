OUTDIR = out/
CC = c++

main: main.o bot.o card.o player.o interface.o interface_h.o interface_c.o interface_r.o interface_e.o cardaction.o Card.db
	cd $(OUTDIR) && $(CC) main.o card.o cardaction.o player.o bot.o interface.o interface_h.o interface_c.o interface_r.o interface_e.o -o ../main -lsqlite3

card.o: card.cpp card.h out
	$(CC) -c $< -o $(OUTDIR)$@ -lsqlite3

Card.db: create.sql
	sqlite3 $<.db ".read create.sql"

main.o: main.cpp out
	$(CC) -c $< -o $(OUTDIR)$@ 

bot.o: bot.cpp bot.h player.h card.h cardaction.h $(OUTDIR)
	$(CC) -c $< -o $(OUTDIR)$@ 

player.o: player.cpp player.h card.h interface.h $(OUTDIR)
	$(CC) -c $< -o $(OUTDIR)$@ 

interface.o: interface.cpp interface.h $(OUTDIR) 
	$(CC) -c $< -o $(OUTDIR)$@ 

interface_h.o: interface_h.cpp interface.h $(OUTDIR)
	$(CC) -c $< -o $(OUTDIR)$@

interface_c.o: interface_c.cpp interface.h $(OUTDIR)
	$(CC) -c $< -o $(OUTDIR)$@ 

interface_r.o: interface_r.cpp interface.h $(OUTDIR)
	$(CC) -c $< -o $(OUTDIR)$@ 

interface_e.o: interface_e.cpp interface.h $(OUTDIR) 
	$(CC) -c $< -o $(OUTDIR)$@ 

cardaction.o: cardaction.cpp cardaction.h player.h card.h $(OUTDIR)
	$(CC) -c $< -o $(OUTDIR)$@

out:
	mkdir -p $(OUTDIR)
