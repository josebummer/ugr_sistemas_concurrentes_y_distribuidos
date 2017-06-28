/*
Una tribu de antropófagos comparte una olla en la que caben M misioneros. Cuando algún salvaje quiere
comer, se sirve directamente de la olla, a no ser que ésta esté vacı́a. Si la olla está vacı́a, el salvaje despertará
al cocinero y esperará a que éste haya rellenado la olla con otros M misioneros.
Implementar los procesos salvajes y cocinero usando paso de mensajes, usando un proceso olla que
incluye una construcción de espera selectiva que sirve peticiones de los salvajes y el cocinero para mantener
la sincronización requerida, teniendo en cuenta que:
• La solución no debe producir interbloqueo.
• Los salvajes podrán comer siempre que haya comida en la olla,
• Solamente se despertará al cocinero cuando la olla esté vacı́a.
• Los procesos usan operaciones de comunicación sı́ncronas.

Creado por: Jose Antonio Ruiz Millan.

Ejercicios SCD :
Universidad de Granada
*/

#include <iostream>
#include "mpi.h"
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#define M 5
#define proc 5
#define cocinero 4
#define olla 3
#define peticion 0
#define rellenar 1
#define esta_llena 2

using namespace std;

void Salvaje(int id);
void Cocinero();
void Olla();

int main(int argc , char **argv){
  int rank, size;

  srand(time(0));
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if( size != proc ){
    if( rank == 0 ){
      cout << "El numero de procesos tiene que ser " << M << endl << flush;
    }
    MPI_Finalize();
    return 0;
  }

  if( rank == olla ){
    Olla();
  }
  else if( rank == cocinero ){
    Cocinero();
  }
  else{
    Salvaje(rank);
  }

  MPI_Finalize();
  return 0;
}

void Salvaje(int id){
  while(true){
    cout << "Salvaje " << id << " se acerca a la olla." << endl << flush;
    MPI_Ssend( NULL,0,MPI_INT,olla,peticion,MPI_COMM_WORLD );
    cout << "Salvaje " << id << " COMIENDO." << endl << flush;
    sleep((rand() % 3)+1);
  }
}

void Cocinero(){
  MPI_Status status;

  while(true){
    MPI_Recv(NULL,0,MPI_INT,olla,rellenar,MPI_COMM_WORLD,&status);
    cout << "Cocinero rellena la Olla." << endl << flush;
    sleep(rand() % 2);
    MPI_Ssend( NULL,0,MPI_INT,olla,esta_llena,MPI_COMM_WORLD );
  }
}

void Olla(){
  int rama,contador = M;
  MPI_Status status;

  while(true){
    rama = (contador == 0)?0:1;

    switch(rama){
      case 0:
        cout << "Olla vacia, llamamos a cocinero." << endl << flush;
        MPI_Ssend( NULL,0,MPI_INT,cocinero,rellenar,MPI_COMM_WORLD );
        MPI_Recv(NULL,0,MPI_INT,cocinero,esta_llena,MPI_COMM_WORLD,&status);
        contador = M;
        cout << "Olla rellenada." << endl << flush;
      break;
      case 1:
        MPI_Recv(NULL,0,MPI_INT,MPI_ANY_SOURCE,peticion,MPI_COMM_WORLD,&status);
        cout << "Salvaje " << status.MPI_SOURCE << " coge un misionero." << endl << flush;
        contador--;
        cout << "Olla tiene " << contador << " misioneros." << endl << flush;
      break;
    }
  }
}
