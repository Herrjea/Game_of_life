#include <iostream>
#include <unistd.h>

#include "game.h"

using namespace std;


int main(){

	// ns of each frame.
	// Not taken into account in not possitive
	const long int nsf = 20000;
	GoL board( 20, 70 );
	char exit = '\n';

	board.insert( glidergun, 0, 20 ); // (+30,+30)
	board.insert( glidergun, 30, 50, 2 ); // DDDD=

//	for ( int i = 1; i < 68; i++ ) board.set( 10, i, true );

//	board.set_at_random( 170 );

	while( exit == '\n' ){
		system( "clear" );
		board.print();
		board.generation();
		if ( nsf < 1 )
			cin.get( exit );
		else
			usleep( nsf );
		
	}

}
