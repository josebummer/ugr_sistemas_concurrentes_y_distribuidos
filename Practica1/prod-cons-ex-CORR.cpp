// *****************************************************************************
//
// Prácticas de SCD. Práctica 1.
// Plantilla de código para el ejercicio del productor-consumidor con
// buffer intermedio.
//
// *****************************************************************************

#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // necesario para {\ttbf usleep()}
#include <stdlib.h> // necesario para {\ttbf random()}, {\ttbf srandom()}
#include <time.h>   // necesario para {\ttbf time()}

using namespace std ;

// ---------------------------------------------------------------------
// constantes configurables:

const unsigned
  num_items  = 40 ,    // numero total de items que se producen o consumen
  tam_vector = 10 ;    // tamaño del vector, debe ser menor que el número de items


int buffer[tam_vector] , primera_libre = 0;

sem_t
  puede_producir,
  puede_consumir,
  mutex,
  s;

// ---------------------------------------------------------------------
// introduce un retraso aleatorio de duración comprendida entre
// 'smin' y 'smax' (dados en segundos)

void retraso_aleatorio( const float smin, const float smax )
{
  static bool primera = true ;
  if ( primera )        // si es la primera vez:
  {  srand(time(NULL)); //   inicializar la semilla del generador
     primera = false ;  //   no repetir la inicialización
  }
  // calcular un número de segundos aleatorio, entre {\ttbf smin} y {\ttbf smax}
  const float tsec = smin+(smax-smin)*((float)random()/(float)RAND_MAX);
  // dormir la hebra (los segundos se pasan a microsegundos, multiplicándos por 1 millón)
  usleep( (useconds_t) (tsec*1000000.0)  );
}

// ---------------------------------------------------------------------
// función que simula la producción de un dato

unsigned producir_dato()
{
  static int contador = 0 ;
  contador = contador + 1 ;
 // retraso_aleatorio( 0.1, 0.5 );
  cout << "Productor : dato producido: " << contador << endl << flush ;
  return contador ;
}
// ---------------------------------------------------------------------
// función que simula la consumición de un dato

void consumir_dato( int dato )
{
  // retraso_aleatorio( 0.1, 1.5 );
   cout << "Consumidor: dato consumido: " << dato << endl << flush ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del productor

void * funcion_productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato = producir_dato() ;

    sem_wait(&s);

    sem_wait( &puede_producir );

    sem_wait( &mutex );
    buffer[primera_libre] = dato;
    primera_libre++;
    cout << "\t\t\t\tEl productor ha insertado --> " << dato << endl << flush ;
    sem_post( &mutex );
    sem_post(&puede_consumir);
    cout << "Productor : dato insertado: " << dato << endl << flush ;
  }
  return NULL ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del consumidor

void * funcion_consumidor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato ;

    sem_wait(&s);

    sem_wait( &puede_consumir );

    sem_wait( &mutex );
    primera_libre--;
    dato = buffer[primera_libre];
    cout << "\t\t\t\tEl consumidor ha extraido --> " << dato << endl << flush ;
    sem_post( &mutex );
    sem_post(&puede_producir);
    consumir_dato( dato ) ;
    cout << "Consumidor: dato extraído : " << dato << endl << flush ;

  }
  return NULL ;
}
//----------------------------------------------------------------------


void * funcion_reloj ( void * ){

  int iteraciones = 2*num_items;
  int i = 0;
  while( i < iteraciones ){
    sem_post(&s);
    retraso_aleatorio( 0.2 , 0.2 );
    i++;
  }
}

int main()
{

  pthread_t hebra_productor , hebra_consumidor , reloj;

  sem_init( &puede_producir , 0 , tam_vector );
  sem_init( &puede_consumir , 0 , 0 );
  sem_init( &mutex , 0 , 1 );
  sem_init( &s , 0 , 1 );

  pthread_create( &reloj , NULL , funcion_reloj , NULL );
  pthread_create( &hebra_productor , NULL , funcion_productor , NULL );
  pthread_create( &hebra_consumidor , NULL , funcion_consumidor , NULL );

  pthread_join ( hebra_consumidor , NULL );
  pthread_join ( hebra_productor , NULL );

  sem_destroy ( &puede_producir );
  sem_destroy ( &puede_consumir );
  sem_destroy ( &mutex );
  sem_destroy ( &s );


   return 0 ;
}
