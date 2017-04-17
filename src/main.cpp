#include <iostream>
#include <unistd.h>

#include "game.h"

using namespace std;


int main(){

//	const long int VELOCIDAD = 50000; // Nanosegundos que dura cada fotograma
	Juego juego( 25, 70 );
	char salida = '\n';
	Juego gun( "glidergun" );

//	juego.Insertar( gun, 0, 20 ); // (+30,+30)
//	juego.Insertar( gun, 30, 50, 2 );

//	for ( int i = 1; i < 68; i++ ) juego.Set(10,i,true);

//	juego.SetAlAzar( 170 );

	while( salida == '\n' ){
		system( "clear" );
		juego.Mostrar();
		juego.Generacion();
		cin.get(salida);
		//usleep(VELOCIDAD);
	}

}
