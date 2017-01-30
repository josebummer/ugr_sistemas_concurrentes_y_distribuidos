#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t mutex , mutex2;

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
    sem_wait( &mutex2 );
    y = x;
    cout << "Soy P2: realizo x+=1,y=x;\t\tx=" << x << " y=" << y << endl;
    sem_post( &mutex2 );
    sem_post( &mutex );
  }
}

void * accionp3 ( void * ){
  while ( true ){
    sem_wait ( &mutex2 );
    y+=1;
    cout << "Soy P3: realizo y+=1;\t\t\tx=" << x << " y=" << y << endl;
    sem_post( &mutex2 );
  }
}

int main(){

  pthread_t P1,P2,P3;

  sem_init( &mutex , 0 , 1 );
  sem_init( &mutex2 , 0 , 1 );

  pthread_create ( &P1 , NULL , accionp1 , NULL );
  pthread_create ( &P2 , NULL , accionp2 , NULL );
  pthread_create ( &P3 , NULL , accionp3 , NULL );

  pthread_join ( P1, NULL );
  pthread_join ( P2, NULL );
  pthread_join ( P3, NULL );

  sem_destroy ( &mutex );
  sem_destroy ( &mutex2 );

  return 0;
}
