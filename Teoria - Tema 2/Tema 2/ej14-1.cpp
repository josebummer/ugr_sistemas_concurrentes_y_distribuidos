/*
Creado por: Jose Antonio Ruiz Millan.

Ejercicios Teoria Tema 2 SCD :
Universidad de Granada
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t mutex;

static int x = 0;
static int y = 0;

void * accionp1 ( void * ){
  while ( true ){
    sem_wait( &mutex );
    x+=1;
    cout << "Soy P1: realizo x+=1;\t\t\tx=" << x << " y=" << y << endl;
    sem_post( &mutex );
  }
}

void * accionp2 ( void * ){
  while ( true ){
    sem_wait( &mutex );
    x+=1;
    y = x;
    cout << "Soy P2: realizo x+=1,y=x;\t\tx=" << x << " y=" << y << endl;
    sem_post( &mutex );
  }
}

void * accionp3 ( void * ){
  while ( true ){
    sem_wait( &mutex );
    y+=1;
    cout << "Soy P3: realizo y+=1;\t\t\tx=" << x << " y=" << y << endl;
    sem_post( &mutex );
  }
}

int main(){

  pthread_t P1,P2,P3;

  sem_init( &mutex , 0 , 1 );

  pthread_create ( &P1 , NULL , accionp1 , NULL );
  pthread_create ( &P2 , NULL , accionp2 , NULL );
  pthread_create ( &P3 , NULL , accionp3 , NULL );

  pthread_join ( P1, NULL );
  pthread_join ( P2, NULL );
  pthread_join ( P3, NULL );

  sem_destroy ( &mutex );

  return 0;
}
