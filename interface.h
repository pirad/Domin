#ifndef INTERFACE_H
#define INTERFACE_H

#ifndef STACK_SIZE
#define STACK_SIZE 50
#endif

#include "card.h"

class interface{
/*the base class for player interfaces*/
    public:
	virtual ~interface() { };
	virtual int interact(int type, card * choose[STACK_SIZE], int choose_cnt)=0;
	virtual void notify(int type, int info=0, int info1=0, int info2=0)=0;
};

class interface_factory{
/*this class creates the player interfaces*/
    public:
	interface* create(const char c);
};

class human: public interface{
/*the class for the human player interface
 *implemented in interface_h.cpp*/
    public:
	int interact (int type, card * choose[STACK_SIZE], int choose_cnt);
	void notify(int type, int info=0, int info1=0, int info2=0);

};

class computer: public interface{
/*the class for the computer player interface 
 * implemented in interface_c.cpp*/
    public:
	int interact (int type, card * choose[STACK_SIZE], int choose_cnt);
	void notify(int type, int info=0, int info1=0, int info2=0);

	computer(void);

};

class random: public interface{
/*the class for the computer player interface 
 * implemented in interface_r.cpp*/
    public:
	int interact (int type, card * choose[STACK_SIZE], int choose_cnt);
	void notify(int type, int info=0, int info1=0, int info2=0);

	random(void);

};

class earl: public interface{
/*the class for the computer player interface 
 * implemented in interface_e.cpp*/
    public:
	int interact (int type, card * choose[STACK_SIZE], int choose_cnt);
	void notify(int type, int info=0, int info1=0, int info2=0);

	earl(void);

};


#endif //INTERFACE_H
