#include <iostream>
#include "mpi.h"
#define N 4

using namespace std;

void Proceso(int id, int tam);

int main(int argc , char **argv){
  int rank, size;

  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  if( size != 4 ){
    if( rank == 0 ){
      cout << "El numero de procesos debe ser 4" << endl << flush;
    }
    MPI_Finalize();
    return 0;
  }

  Proceso(rank,size);

  MPI_Finalize();
  return 0;
}

void Proceso(int id , int tam){
  int mi_valor = id;
  int suma = mi_valor;
  int sig;
  int ant;
  MPI_Status status;

  cout << "Proceso " << id << " tiene el valor " << mi_valor << endl << flush;

  for( int i = 1; i < tam; i++ ){
    sig = (id+1)%tam;
    ant = ((id+tam)-1) % tam;
    MPI_Send( &mi_valor,1,MPI_INT,sig,0,MPI_COMM_WORLD );
    cout << "Proceso " << id << " ENVIA " << mi_valor << " al proceso " << sig << endl << flush;
    MPI_Recv( &mi_valor,1,MPI_INT,ant,0,MPI_COMM_WORLD,&status);
    cout << "Proceso " << id << " RECIBE " << mi_valor << " del proceso " << ant << endl << flush;
    suma+=mi_valor;
    cout << "Proceso " << id << " tiene suma de " << suma << endl << flush;
  }
}
