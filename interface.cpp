#include "interface.h"

interface* interface_factory::create(const char c){
/*creates the instance of the player interface*/
    interface* retval=0;
    switch (c){
	case 'h':
	    retval= new human();
	    break;
	case 'c':
	    retval= new computer();
	    break;
	case 'r':
	    retval= new random();
	    break;
	case 'e':
	    retval= new earl();
	    break;
    }
    return retval;
}

