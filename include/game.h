#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


const string
	glider = "glider",
	glidergun = "glidergun",
	switchengine = "switchengine";

const bool
	live = true,
	dead = false;


class GoL{

	bool ** board;
	int height;
	int width;

	public:

		GoL( int );

		GoL( int, int );

		GoL( const GoL & );

		GoL( string );

		~GoL();

		int get_height() const;

		int get_width() const;

		bool get( int, int ) const;

		void set( int, int, bool );

		void set_border( bool );

		void set_at_random( int );

		int living_neighbors( int, int );

		void generation();

		void generation_alt();

		void rotate();

		void insert( GoL, int, int );

		void insert( GoL, int, int, int );

		void insert( string, int, int );

		void insert( string, int, int, int );

		GoL & operator = ( const GoL & );

		void print();

		void clear();

	private:

		bool inside( int, int );
};
