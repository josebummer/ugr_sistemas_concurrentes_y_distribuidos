/*
Creado por: Jose Antonio Ruiz Millan.

Ejercicios SCD :
Universidad de Granada
*/

#include <iostream>
#include "mpi.h"
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#define controlador 0
#define solicitud 0
#define liberar 1

using namespace std;

void Controlador();
void Proceso(int id);

int main(int argc, char **argv ){
  int rank, size;

  srand(time(0));
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if( size < 15 ){
    if( rank == 0 ){
      cout << "El numero de procesos debe ser mayor 14." << endl << flush;
    }
    MPI_Finalize();
    return 0;
  }

  if( rank == controlador ){
    Controlador();
  }
  else{
    Proceso(rank);
  }

  MPI_Finalize();
  return 0;
}

void Proceso(int id){
  while(true){
    cout << "Proceso " << id << " envia peticion." << endl << flush;
    MPI_Ssend( NULL,0,MPI_INT,controlador,solicitud,MPI_COMM_WORLD );
    cout << "Proceso " << id << " utiliza recurso." << endl << flush;
    sleep((rand() % 3)+1);
    cout << "Proceso " << id << " termina de utilizar recurso y envia para liberar." << endl << flush;
    MPI_Ssend( NULL,0,MPI_INT,controlador,liberar,MPI_COMM_WORLD );
    usleep( 1000U * (100U+(rand()%900U)) );
  }
}

void Controlador(){
  MPI_Status status;
  int nprocesos = 0;

  while(true){
    if( nprocesos == 12 ){ // llegamos al maximo
      cout << "Controlador espera para liberar porque se ha llegado al tope" << endl << flush;
      MPI_Recv(NULL,0,MPI_INT,MPI_ANY_SOURCE,liberar,MPI_COMM_WORLD,&status);
      cout << "Controlador libera recurso al proceso " << status.MPI_SOURCE << endl << flush;
      nprocesos--;
    }
    else if( nprocesos > 0 ){ // estamos en un valor normal
      MPI_Probe(MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD, &status );
      if( status.MPI_TAG == solicitud ){
        cout << "Controlador espera peticion del proceso " << status.MPI_SOURCE << endl << flush;
        MPI_Recv(NULL,0,MPI_INT,status.MPI_SOURCE,solicitud,MPI_COMM_WORLD,&status);
        cout << "Controlador da recurso al proceso " << status.MPI_SOURCE << endl << flush;
        nprocesos++;
      }
      else{
        cout << "Controlador espera liberacion del proceso " << status.MPI_SOURCE << endl << flush;
        MPI_Recv(NULL,0,MPI_INT,status.MPI_SOURCE,liberar,MPI_COMM_WORLD,&status);
        nprocesos--;
      }
    }
    else{ // tenemos 0 procesos
      cout << "Controlador espera peticion." << endl << flush;
      MPI_Recv(NULL,0,MPI_INT,MPI_ANY_SOURCE,solicitud,MPI_COMM_WORLD,&status);
      cout << "Controlador da recurso al proceso " << status.MPI_SOURCE << endl << flush;
      nprocesos++;
    }
    cout << "Hay " << nprocesos << " procesos utilizando recursos." << endl << flush;
  }
}
