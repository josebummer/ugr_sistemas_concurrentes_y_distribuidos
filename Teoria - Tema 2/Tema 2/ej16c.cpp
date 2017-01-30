#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

sem_t
  ej_e,
  ej_h;

void * p1 ( void * ){
  while ( true ){
    cout << "P1: Ejecuto a." << endl;
  
    cout << "P1: Ejecuto b." << endl;
    sem_post ( &ej_e );
    sem_post ( &ej_h );
    cout << "P1: Ejecuto c." << endl;
  }
}

void * p2 ( void * ){
  while ( true ){
    cout << "P2: Ejecuto d." << endl;
    sem_wait ( &ej_e );
    cout << "P2: Ejecuto e." << endl;

    cout << "P2: Ejecuto f." << endl;
  }
}

void * p3 ( void * ){
  while ( true ){
    cout << "P3: Ejecuto g." << endl;
    sem_wait ( &ej_h );
    cout << "P3: Ejecuto h." << endl;

    cout << "P3: Ejecuto i." << endl;
  }
}

int main(){

  pthread_t P1, P2, P3;

  sem_init ( &ej_e , 0 , 0 );
  sem_init ( &ej_h , 0 , 0 );

  pthread_create ( &P1 , NULL , p1 , NULL );
  pthread_create ( &P2 , NULL , p2 , NULL );
  pthread_create ( &P3 , NULL , p3 , NULL );

  pthread_join ( P1 , NULL );
  pthread_join ( P2 , NULL );
  pthread_join ( P3 , NULL );

  sem_destroy ( &ej_e );
  sem_destroy ( &ej_h );

  return 0;
}
