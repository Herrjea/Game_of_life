#include <iostream>
#include <unistd.h>

#include "game.h"

using namespace std;


int main(){

	// μs of each frame.
	// Not taken into account in not possitive
	const long int usf = 20000;

	GoL board( 20, 70 );
	char exit = '\n';


	board.insert( glidergun, 0, 20 ); // (+30,+30)
	board.insert( glidergun, 30, 50, 2 ); // DDDD=

//	board.set_at_random( 170 );


	while( exit == '\n' ){
		system( "clear" );
		board.print();
		board.generation();
		if ( usf < 1 )
			cin.get( exit );
		else
			usleep( usf );
		
	}

}
