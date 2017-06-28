/*
En un sistema distribuido, 6 procesos clientes necesitan sincronizarse de forma específica para realizar
cierta tarea, de forma que dicha tarea sólo podrá ser realizada cuando tres procesos estén preparados para
realizarla. Para ello, envían peticiones a un proceso controlador del recurso y esperan respuesta para poder
realizar la tarea específica. El proceso controlador se encarga de asegurar la sincronización adecuada. Para
ello, recibe y cuenta las peticiones que le llegan de los procesos, las dos primeras no son respondidas y
producen la suspensión del proceso que envía la petición (debido a que se bloquea esperando respuesta)
pero la tercera petición produce el desbloqueo de los tres procesos pendientes de respuesta. A continuación,
una vez desbloqueados los tres procesos que han pedido (al recibir respuesta), inicializa la cuenta y procede
cíclicamente de la misma forma sobre otras peticiones.

Creado por: Jose Antonio Ruiz Millan.

Ejercicios SCD :
Universidad de Granada
*/

#include <iostream>
#include "mpi.h"
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <vector>
#define controlador 6 //id
#define peticion 0 //etiqueta
#define permiso 1 //etiqueta

void Cliente(int id);
void Controlador();

using namespace std;

int main(int argc , char **argv){
  int rank, size;

  srand(time(0));
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if( size != 7 ){
    if( rank == 0 )
      cout << "El numero de procesos tiene que ser 7." << endl << flush;
    MPI_Finalize();
    return 0;
  }

  if( rank == controlador ){
    Controlador();
  }
  else{
    Cliente(rank);
  }

  MPI_Finalize();
  return 0;
}

void Cliente(int id){
  MPI_Status status;

  while(true){
    cout << "Cliente " << id << " envia peticion a controlador." << endl << flush;
    MPI_Ssend( NULL,0,MPI_INT,controlador,peticion,MPI_COMM_WORLD );
    MPI_Recv(NULL,0,MPI_INT,controlador,permiso,MPI_COMM_WORLD,&status);
    cout << "Cliente " << id << " puede realizar su tarea." << endl << flush;
    sleep((rand() % 3)+1);
  }
}

void Controlador(){
  int nclientes;
  vector<int> v;
  MPI_Status status;

  while(true){
    nclientes = 0;
    while( nclientes < 3 ){
      MPI_Recv(NULL,0,MPI_INT,MPI_ANY_SOURCE,peticion,MPI_COMM_WORLD,&status);
      v.push_back(status.MPI_SOURCE);
      nclientes++;
      cout << "Peticion recibida del cliente " << status.MPI_SOURCE << endl << flush;
      cout << "Hay " << nclientes << " esperando." << endl << flush;
    }
    for(int i = 0; i < v.size(); i++){
      MPI_Ssend( NULL,0,MPI_INT,v[i],permiso,MPI_COMM_WORLD );
    }
    v.clear();
  }
}
