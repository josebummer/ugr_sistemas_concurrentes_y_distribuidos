/*
En un sistema distribuido, 3 procesos productores producen continuamente valores enteros y los envían a un
proceso buffer que los almacena temporalmente en un array local de 4 celdas enteras para ir enviándoselos
a un proceso consumidor. A su vez, el proceso buffer realiza lo siguiente, sirviendo de forma equitativa al
resto de procesos:
a) Envía enteros al proceso consumidor siempre que su array local tenga al menos dos elementos
disponibles.
b) Acepta envíos de los productores mientras el array no esté lleno, pero no acepta que cualquier productor
pueda escribir dos veces consecutivas en el búfer.

Creado por: Jose Antonio Ruiz Millan.

Ejercicios SCD :
Universidad de Granada
*/

#include <iostream>
#include "mpi.h"
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#define consumidor 3 //id
#define buffer 4 //id
#define producir 0 //etiqueta
#define consumir 1 //etiqueta

using namespace std;

void Productor(int id);
void Consumidor();
void Buffer();

int main(int argc, char **argv){
  int rank, size;

  srand(time(0));
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );

  if( size != 5 ){
    if( rank == 0 ){
      cout << "El numero de procesos tiene que ser 7." << endl << flush;
    }
    MPI_Finalize();
    return 0;
  }

  if( rank == consumidor ){
    Consumidor();
  }
  else if( rank == buffer ){
    Buffer();
  }
  else{
    Productor(rank);
  }

  MPI_Finalize();
  return 0;
}

void Productor(int id){
  int dato = id;

  while(true){
    cout << "Productor " << id << " produce el dato " << dato << endl << flush;
    MPI_Ssend( &dato,1,MPI_INT,buffer,producir,MPI_COMM_WORLD );
    dato++;
  }
}

void Consumidor(){
  MPI_Status status;
  int dato;

  while(true){
    MPI_Recv(&dato,1,MPI_INT,buffer,consumir,MPI_COMM_WORLD,&status);
    cout << "Consumidor consume el dato " << dato << endl << flush;
  }
}

void Buffer(){
  MPI_Status status;
  int prodant = -1,dato;
  int datos[4],pos = 0;

  while(true){
    //MPI_Probe( MPI_ANY_SOURCE, producir, MPI_COMM_WORLD, &status );
    MPI_Recv(&dato,1,MPI_INT,MPI_ANY_SOURCE,producir,MPI_COMM_WORLD,&status);
    if( pos < 4 && prodant != status.MPI_SOURCE ){
      cout << "Buffer recibe " << dato << " del productor " << status.MPI_SOURCE << endl << flush;
      prodant = status.MPI_SOURCE;
      datos[pos] = dato;
      pos++;
      cout << "Buffer ahora contiene " << pos << " datos." << endl << flush;
    }
    else if( pos >= 2 ){
      MPI_Ssend( &datos[pos-1],1,MPI_INT,consumidor,consumir,MPI_COMM_WORLD );
      cout << "Buffer envia " << datos[pos-1] << " al consumidor " << endl << flush;
      pos--;
      cout << "Buffer ahora contiene " << pos << " datos." << endl << flush;
    }
  }
}
