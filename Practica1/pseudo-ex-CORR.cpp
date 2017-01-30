#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // necesario para {\ttbf usleep()}
#include <stdlib.h> // necesario para {\ttbf random()}, {\ttbf srandom()}
#include <time.h>   // necesario para {\ttbf time()}

using namespace std;

static int x;

sem_t
  dato_par,
  dato_impar,
  seniala_par,
  seniala_impar;

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

unsigned producir_dato()
{
  static int contador = 0 ;
  contador = contador + 1 ;
  retraso_aleatorio( 0.01, 0.05 );
  cout << "Productor : dato producido: " << contador << endl << flush ;
  return contador ;
}

void consumir_dato( int dato )
{
  // retraso_aleatorio( 0.1, 1.5 );
   cout << "Consumidor: dato consumido: " << dato << endl << flush ;
}

void * producir( void * ){
  int d;
  while ( true ){
    d = producir_dato();
    x = d;
    if ( d % 2 == 0){
      sem_post( &dato_par );
      sem_wait( &seniala_par );
    }
    else{
      sem_post ( &dato_impar );
      sem_wait ( &seniala_impar );
    }
  }
}

void * consumir1 ( void * ){
  int v;
  while ( true ){
    sem_wait ( &dato_par );
    v = x;
    sem_post ( &dato_impar );
    sem_wait ( &seniala_impar);
    sem_post ( &seniala_par );
    consumir_dato(v);
  }
}

void * consumir2 ( void * ){
  int v;
  while ( true ){
    sem_wait ( &dato_impar );
    v = x;
    sem_post ( &seniala_impar);
    consumir_dato(v);
  }
}

int main(){
  pthread_t hebra_productor , hebra_consumidor1 , hebra_consumidor2;

  sem_init( &seniala_par , 0 , 0 );
  sem_init( &seniala_impar , 0 , 0 );
  sem_init( &dato_par , 0 , 0 );
  sem_init( &dato_impar , 0 , 0 );

  pthread_create( &hebra_consumidor1 , NULL , consumir1 , NULL );
  pthread_create( &hebra_consumidor2 , NULL , consumir2 , NULL );
  pthread_create( &hebra_productor , NULL , producir , NULL );

  pthread_join ( hebra_productor , NULL );
  pthread_join ( hebra_consumidor1 , NULL );
  pthread_join ( hebra_consumidor2 , NULL );

  sem_destroy ( &seniala_par );
  sem_destroy ( &seniala_impar );
  sem_destroy ( &dato_par );
  sem_destroy ( &dato_impar );

  return 0;
}
