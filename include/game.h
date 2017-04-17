#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


class Juego{

	bool ** mapa;
	int alto;
	int ancho;

	public:

		Juego( int );

		Juego( int, int );

		Juego( const Juego & );

		Juego( string );

		~Juego();

		int GetAlto() const;

		int GetAncho() const;

		bool Get( int, int ) const;

		void Set( int, int, bool );

		void SetLimite( bool );

		void SetAlAzar( int );

		bool Dentro( int, int );

		int Vecinos( int, int );

		void Generacion();

		void GeneracionB();

		void Rotar();

		void Insertar( Juego, int, int );

		void Insertar( Juego, int, int, int );

		void Insertar( string, int, int );

		void Insertar( string, int, int, int );

		Juego & operator = ( const Juego & );

		void Mostrar();

		void Destruir();
};
