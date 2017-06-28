/*
Creado por: Jose Antonio Ruiz Millan.

Ejercicios Teoria Tema 2 SCD :
Universidad de Granada
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t
  puede_crear,
  puede_utilizar;

static int x = 0;

void * crear ( void * ){
  int d = 1;
  while ( true ){
    sem_wait ( &puede_crear );
    x = d*5;
    cout << "Creador: x=" << x << endl;
    sem_post ( &puede_utilizar );
    d++;
  }
}

void * utilizar ( void * ){
  int m;
  int i = 2;
  while ( true ){
    sem_wait ( &puede_utilizar );
    if(i%2 == 0){
      m = 2*x;
      cout << "Utilizador: m=2*x; m=" << m << endl;
    }
    sem_post ( &puede_crear );
    i++;
  }
}

int main() {

  pthread_t creadora, utilizadora;

  sem_init ( &puede_crear , 0 , 1 );
  sem_init ( &puede_utilizar , 0 , 0 );

  pthread_create ( &creadora , NULL , crear , NULL );
  pthread_create ( &utilizadora , NULL , utilizar , NULL );

  pthread_join ( creadora , NULL );
  pthread_join ( utilizadora , NULL );

  sem_destroy ( &puede_crear );
  sem_destroy ( &puede_utilizar );

  return 0;
}
