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

sem_t                  //Creamos los semaforos
  puede_consumir ,
  puede_producir ,
  mutex;

int buffer[tam_vector] , primera_ocupada = 0 , primera_libre = 0;             //Creamos las variables necesarias

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
  retraso_aleatorio( 0.1, 0.5 );
  cout << "Productor : dato producido: " << contador << endl << flush ;
  return contador ;
}
// ---------------------------------------------------------------------
// función que simula la consumición de un dato

void consumir_dato( int dato )
{
   retraso_aleatorio( 0.1, 1.5 );
   cout << "Consumidor: dato consumido: " << dato << endl << flush ;
}
// ---------------------------------------------------------------------
// función que ejecuta la hebra del productor

void * funcion_productor( void * )
{
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato = producir_dato() ;        //Creamos el dato

    sem_wait( &puede_producir );        //Esperamos para poder insertar un dato

    buffer[primera_libre] = dato;       //Insertamos en el vector el dato
    //primera_libre = (primera_libre+1) % tam_vector;
    if( primera_libre == tam_vector-1 )   //Cambiamos el valor de la primera libre
      primera_libre = 0;
    else
      primera_libre++;

    sem_wait( &mutex );
    cout << "\t\t\t\tProductor produce --> " << dato << endl;
    sem_post( &mutex );
    sem_post( &puede_consumir );       //Damos paso para que se pueda extraer un dato

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

    sem_wait( &puede_consumir );                    //Esperamos para poder sacar un dato
    dato = buffer[primera_ocupada];                 //Sacamos el dato del vector
    //primera_ocupada = (primera_ocupada-1) % tam_vector;
    if( primera_ocupada == tam_vector-1 )     //Cambiamos el valor de primera ocupada
      primera_ocupada = 0;
    else
      primera_ocupada++;

    sem_wait( &mutex );
    cout << "\t\t\t\tConsumidor consume --> " << dato << endl;
    sem_post( &mutex );
    sem_post( &puede_producir );      //Damos paso para insertar otro dato

    cout << "Consumidor: dato extraído : " << dato << endl << flush ;
    consumir_dato( dato ) ;           //Mostramos el mensaje de que hemos consumido.

  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{
  pthread_t hebra_consumidor , hebra_productor;

  // falta: crear y poner en marcha las hebras, esperar que terminen
  sem_init( &puede_consumir , 0 , 0 );
  sem_init( &puede_producir , 0 , tam_vector );
  sem_init( &mutex, 0 , 1 );

  pthread_create( &hebra_productor , NULL , funcion_productor , NULL );
  pthread_create( &hebra_consumidor , NULL , funcion_consumidor , NULL );

  pthread_join( hebra_productor , NULL );
  pthread_join( hebra_consumidor , NULL );

  sem_destroy( &puede_consumir );
  sem_destroy( &puede_producir );
  sem_destroy( &mutex );

   return 0 ;
}
