#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;


Juego::Juego( int tamanyo )
	:Juego( tamanyo, tamanyo ){
}

Juego::Juego( int tamanyo_x, int tamanyo_y ){

	alto = tamanyo_x;
	ancho = tamanyo_y;

	mapa = new bool*[alto];

	for ( int i = 0; i < alto; i++ )
		mapa[i] = new bool[ancho];

	for ( int i = 0; i < alto; i++ )
		for ( int j = 0; j < ancho; j++ )
			mapa[i][j] = false;
}

Juego::Juego( const Juego & referencia ){

	alto = referencia.GetAlto();
	ancho = referencia.GetAncho();
	mapa = new bool*[alto];
	for ( int i = 0; i < alto; i++ )
		mapa[i] = new bool[ancho];

	for ( int i = 0; i < alto; i++ )
		for ( int j = 0; j < ancho; j++ )
			Set( i, j, referencia.Get(i,j) );
}

Juego::Juego( string tipo ){

	if ( tipo == "glider" ){

		alto = ancho = 3;
		mapa = new bool*[alto];
		for ( int i = 0; i < alto; i++ )
			mapa[i] = new bool[ancho];

		Set(0,0,true);
		Set(1,0,true);
		Set(2,0,true);
		Set(2,1,true);
		Set(1,2,true);

	}else if ( tipo == "glidergun" ){

		alto = 9;
		ancho = 36;
		mapa = new bool*[alto];
		for ( int i = 0; i < alto; i++ )
			mapa[i] = new bool[ancho];

		Set(4,0,true);
		Set(5,0,true);
		Set(4,1,true);
		Set(5,1,true);
		Set(2,34,true);
		Set(3,34,true);
		Set(2,35,true);
		Set(3,35,true);
		Set(4,10,true);
		Set(5,10,true);
		Set(6,10,true);
		Set(3,11,true);
		Set(7,11,true);
		Set(2,12,true);
		Set(8,12,true);
		Set(2,13,true);
		Set(8,13,true);
		Set(5,14,true);
		Set(3,15,true);
		Set(7,15,true);
		Set(4,16,true);
		Set(5,16,true);
		Set(6,16,true);
		Set(5,17,true);
		Set(2,20,true);
		Set(3,20,true);
		Set(4,20,true);
		Set(2,21,true);
		Set(3,21,true);
		Set(4,21,true);
		Set(1,22,true);
		Set(5,22,true);
		Set(0,24,true);
		Set(1,24,true);
		Set(5,24,true);
		Set(6,24,true);

	}else if ( tipo == "switchengine" ){

		alto = 6;
		ancho = 8;
		mapa = new bool*[alto];
		for ( int i = 0; i < alto; i++ )
			mapa[i] = new bool[ancho];

		Set(2,1,true);
		Set(1,2,true);
		Set(3,2,true);
		Set(1,4,true);
		Set(4,4,true);
		Set(3,5,true);
		Set(4,5,true);
		Set(4,6,true);

	}else{

		mapa = 0;
		alto = ancho = 0;
	}
}

Juego::~Juego(){

	Destruir();
}

int Juego::GetAlto() const{

	return alto;
}

int Juego::GetAncho() const{

	return ancho;
}

bool Juego::Get( int x, int y ) const{

	return mapa[x][y];
}

void Juego::Set( int x, int y, bool valor ){

	if ( x >= 0 && y >= 0 && x < alto && y < ancho )
		mapa[x][y] = valor;
}

void Juego::SetAlAzar( int iteraciones ){

	int x, y;
	time_t t;
	srand((int) time(&t));

	for ( int i = 0; i < iteraciones; i++ ){

		// Repite hasta dar con una célula muerta
		do{
			x = rand() % alto;
			y = rand() % ancho;
		}while( mapa[x][y] );

		mapa[x][y] = true;
	}
}

void Juego::SetLimite( bool valor ){

	for ( int i = 0; i < ancho; i++ )
		Set( 0, i, valor );
	for ( int i = 0; i < ancho; i++ )
		Set( alto - 1, i, valor );
	for ( int i = 0; i < alto; i++ )
		Set( i, 0, valor );
	for ( int i = 0; i < alto; i++ )
		Set( i, ancho - 1, valor );
}

bool Juego::Dentro( int x, int y ){

	bool dentro = ( x >= 0 && y >= 0 && x < alto && y < ancho ) ? true : false;
	return dentro;
}

int Juego::Vecinos( int x, int y ){

	int vecinos = 0;

	for ( int i = x - 1; i <= x + 1; i++ )
		for ( int j = y - 1; j <= y + 1; j++ )
			if ( Dentro(i,j) && mapa[i][j] )
				vecinos++;
	if ( mapa[x][y] )
		vecinos--;

	return vecinos;
}

void Juego::Generacion(){

	int vecinos_minimos = 2, vecinos_maximos = 3;
	Juego siguiente( alto, ancho );

	for ( int i = 0; i < alto; i++ )
		for ( int j = 0; j < ancho; j++ ){
			int vecinos = Vecinos(i,j);
			if ( ( Get(i,j) && vecinos >= vecinos_minimos && vecinos <= vecinos_maximos ) || ( !Get(i,j) && vecinos == vecinos_maximos ) )
				siguiente.Set(i,j,true);
		}

	for ( int i = 0; i < alto; i++ )
		for ( int j = 0; j < ancho; j++ )
			Set(i,j,siguiente.Get(i,j));
}

void Juego::GeneracionB(){

	int vecinos_minimos = 2, vecinos_maximos = 3;

	for ( int i = 0; i < alto; i++ )
		for ( int j = 0; j < ancho; j++ ){
			int vecinos = Vecinos(i,j);
			( ( vecinos >= vecinos_minimos && vecinos < vecinos_maximos ) || vecinos == vecinos_maximos ) ? Set(i,j,true) : Set(i,j,false);
		}
}

void Juego::Rotar(){

	Juego nuevo( ancho, alto );

		for ( int i = 0; i < alto; i++ )
			for ( int j = 0; j < ancho; j++ )
				nuevo.Set( j, alto - i - 1, Get( i, j ) );

	*this = nuevo;
}

void Juego::Insertar( Juego patron, int pos_x, int pos_y ){

	Insertar( patron, pos_x, pos_y, 0 );
}

void Juego::Insertar( Juego patron, int pos_x, int pos_y, int rotaciones ){

	if ( pos_x >= 0 && pos_y >= 0 && pos_x + patron.GetAlto() < alto && pos_y + patron.GetAncho() < ancho ){

		for ( int i = 0; i < rotaciones % 4; i++ )
			patron.Rotar();

		for ( int lec_i = 0, esc_i = pos_x; lec_i < patron.GetAlto(); lec_i++, esc_i++ )
			for ( int lec_j = 0, esc_j = pos_y; lec_j < patron.GetAncho(); lec_j++, esc_j++ )
				Set( esc_i, esc_j, patron.Get( lec_i, lec_j ) );
	}
}

void Juego::Insertar( string tipo, int pos_x, int pos_y ){

	if ( tipo == "glider" || tipo == "glidergun" || tipo == "switchengine" ){

		Juego patron(tipo);
		Insertar( patron, pos_x, pos_y, 0 );
	}
}

void Juego::Insertar( string tipo, int pos_x, int pos_y, int rotaciones ){

	if ( tipo == "glider" || tipo == "glidergun" ){

		Juego patron(tipo);
		Insertar( patron, pos_x, pos_y, rotaciones );
	}
}

Juego & Juego::operator = ( const Juego & referencia ){

	if ( this != &referencia ){

		if ( mapa != 0 )
			Destruir();

		alto = referencia.GetAlto();
		ancho = referencia.GetAncho();
		mapa = new bool*[alto];
		for ( int i = 0; i < alto; i++ )
			mapa[i] = new bool[ancho];

		for ( int i = 0; i < alto; i++ )
			for ( int j = 0; j < ancho; j++ )
				Set( i, j, referencia.Get(i,j) );

	}

	return *this;
}

void Juego::Mostrar(){

	char vivo = '0', muerto = ' ';

	for ( int i = 0; i < alto; i++ ){
		for ( int j = 0; j < ancho; j++ )
			mapa[i][j] ? cout << vivo : cout << muerto;
		cout << endl;
	}
}

void Juego::Destruir(){

	for ( int i = 0; i < alto; ++i ){
		delete [] mapa[i];/*cout<<i<<endl;*/}
	delete [] mapa;

	alto = ancho = 0;
}
