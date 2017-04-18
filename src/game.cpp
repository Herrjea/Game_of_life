#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;


GoL::GoL( int size )
	:GoL( size, size ){
}

GoL::GoL( int size_x, int size_y ){

	height = size_x;
	width = size_y;

	board = new bool*[height];

	for ( int i = 0; i < height; i++ )
		board[i] = new bool[width];

	for ( int i = 0; i < height; i++ )
		for ( int j = 0; j < width; j++ )
			board[i][j] = false;
}

GoL::GoL( const GoL & ref ){

	height = ref.get_height();
	width = ref.get_width();
	board = new bool*[height];
	for ( int i = 0; i < height; i++ )
		board[i] = new bool[width];

	for ( int i = 0; i < height; i++ )
		for ( int j = 0; j < width; j++ )
			set( i, j, ref.get(i,j) );
}

GoL::GoL( string type ){

	if ( type == "glider" ){

		height = width = 3;
		board = new bool*[height];
		for ( int i = 0; i < height; i++ )
			board[i] = new bool[width];

		set(0,0,true);
		set(1,0,true);
		set(2,0,true);
		set(2,1,true);
		set(1,2,true);

	}else if ( type == "glidergun" ){

		height = 9;
		width = 36;
		board = new bool*[height];
		for ( int i = 0; i < height; i++ )
			board[i] = new bool[width];

		set(4,0,true);
		set(5,0,true);
		set(4,1,true);
		set(5,1,true);
		set(2,34,true);
		set(3,34,true);
		set(2,35,true);
		set(3,35,true);
		set(4,10,true);
		set(5,10,true);
		set(6,10,true);
		set(3,11,true);
		set(7,11,true);
		set(2,12,true);
		set(8,12,true);
		set(2,13,true);
		set(8,13,true);
		set(5,14,true);
		set(3,15,true);
		set(7,15,true);
		set(4,16,true);
		set(5,16,true);
		set(6,16,true);
		set(5,17,true);
		set(2,20,true);
		set(3,20,true);
		set(4,20,true);
		set(2,21,true);
		set(3,21,true);
		set(4,21,true);
		set(1,22,true);
		set(5,22,true);
		set(0,24,true);
		set(1,24,true);
		set(5,24,true);
		set(6,24,true);

	}else if ( type == "switchengine" ){

		height = 6;
		width = 8;
		board = new bool*[height];
		for ( int i = 0; i < height; i++ )
			board[i] = new bool[width];

		set(2,1,true);
		set(1,2,true);
		set(3,2,true);
		set(1,4,true);
		set(4,4,true);
		set(3,5,true);
		set(4,5,true);
		set(4,6,true);

	}else{

		board = 0;
		height = width = 0;
		cout << "No known type " << type << endl;
	}
}

GoL::~GoL(){

	clear();
}

int GoL::get_height() const{

	return height;
}

int GoL::get_width() const{

	return width;
}

bool GoL::get( int x, int y ) const{

	return board[x][y];
}

void GoL::set( int x, int y, bool state ){

	if ( inside(x,y) )
		board[x][y] = state;
}

void GoL::set_at_random( int rep ){

	int x, y;
	time_t t;
	srand((int) time(&t));

	for ( int i = 0; i < rep; i++ ){

		// Try untill reaching a dead cell
		do{
			x = rand() % height;
			y = rand() % width;
		}while( board[x][y] );

		board[x][y] = true;
	}
}

void GoL::set_border( bool state ){

	// Upper and bottom borders
	for ( int i = 0; i < width; i++ ){
		set( 0, i, state );
		set( height - 1, i, state );
	}
	// Left and right borders
	for ( int i = 0; i < height; i++ ){
		set( i, 0, state );
		set( i, width - 1, state );
	}
}

bool GoL::inside( int x, int y ){

	return x >= 0 && y >= 0 && x < height && y < width;
}

int GoL::living_neighbors( int x, int y ){

	int neighbors = 0;

	for ( int i = x - 1; i <= x + 1; i++ )
		for ( int j = y - 1; j <= y + 1; j++ )
			if ( inside(i,j) && board[i][j] )
				neighbors++;
	if ( board[x][y] )
		neighbors--;

	return neighbors;
}

void GoL::generation(){

// Cambiar esto. Qué cosa tan poco eficiente D=

	int min_neighbors = 2, max_neighbors = 3;
	GoL next( height, width );

	for ( int i = 0; i < height; i++ )
		for ( int j = 0; j < width; j++ ){
			int neighbors = living_neighbors(i,j);
			if ( ( get(i,j) && neighbors >= min_neighbors && neighbors <= max_neighbors ) || ( !get(i,j) && neighbors == max_neighbors ) )
				next.set(i,j,true);
		}

	for ( int i = 0; i < height; i++ )
		for ( int j = 0; j < width; j++ )
			set(i,j,next.get(i,j));
}

void GoL::generation_alt(){

	int min_neighbors = 2, max_neighbors = 3;

	for ( int i = 0; i < height; i++ )
		for ( int j = 0; j < width; j++ ){
			int neighbors = living_neighbors(i,j);
			( ( neighbors >= min_neighbors && neighbors < max_neighbors ) || neighbors == max_neighbors ) ? set(i,j,true) : set(i,j,false);
		}
}

void GoL::rotate(){

	GoL next( width, height );

		for ( int i = 0; i < height; i++ )
			for ( int j = 0; j < width; j++ )
				next.set( j, height - i - 1, get( i, j ) );

	*this = next;
}

void GoL::insert( GoL pattern, int x, int y ){

	insert( pattern, x, y, 0 );
}

void GoL::insert( GoL pattern, int x, int y, int rotations ){

	if ( x >= 0 && y >= 0 && x + pattern.get_height() < height && y + pattern.get_width() < width ){

		for ( int i = 0; i < rotations % 4; i++ )
			pattern.rotate();

		for ( int rd_i = 0, wr_i = x; rd_i < pattern.get_height(); rd_i++, wr_i++ )
			for ( int rd_j = 0, wr_j = y; rd_j < pattern.get_width(); rd_j++, wr_j++ )
				set( wr_i, wr_j, pattern.get( rd_i, rd_j ) );
	}
}

void GoL::insert( string type, int x, int y ){

	if ( type == "glider" || type == "glidergun" || type == "switchengine" ){

		GoL pattern( type );
		insert( pattern, x, y, 0 );
	}
}

void GoL::insert( string type, int x, int y, int rotations ){

	if ( type == "glider" || type == "glidergun" || type == "switchengine" ){

		GoL pattern( type );
		insert( pattern, x, y, rotations );
	}
}

GoL & GoL::operator = ( const GoL & referencia ){

	if ( this != &referencia ){

		if ( board != 0 )
			clear();

		height = referencia.get_height();
		width = referencia.get_width();
		board = new bool*[height];
		for ( int i = 0; i < height; i++ )
			board[i] = new bool[width];

		for ( int i = 0; i < height; i++ )
			for ( int j = 0; j < width; j++ )
				set( i, j, referencia.get(i,j) );

	}

	return *this;
}

void GoL::print(){

	char live = '0', dead = ' ';

	for ( int i = 0; i < height; i++ ){
		for ( int j = 0; j < width; j++ )
			board[i][j] ? cout << live : cout << dead;
		cout << endl;
	}
}

void GoL::clear(){

	for ( int i = 0; i < height; ++i ){
		delete [] board[i];/*cout<<i<<endl;*/}
	delete [] board;

	height = width = 0;
}
