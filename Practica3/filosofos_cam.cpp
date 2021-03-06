/*
Creado por: Jose Antonio Ruiz Millan.

Practica 3 SCD :
Universidad de Granada
*/

#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

#define coger 0
#define soltar 1
#define sentarse 3
#define levantarse 4
#define camarero 10


using namespace std;

void Filosofo( int id, int nprocesos);
void Tenedor ( int id, int nprocesos);
void Camarero( int id, int nprocesos);

// ---------------------------------------------------------------------

int main( int argc, char** argv )
{
   int rank, size;

   srand(time(0));
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   if( size!=11)
   {
      if( rank == 0)
         cout<<"El numero de procesos debe ser 11" << endl << flush ;
      MPI_Finalize( );
      return 0;
   }

   if( rank == camarero )
     Camarero(rank,size-1);
   else if ((rank%2) == 0)
      Filosofo(rank,size-1); // Los pares son Filosofos
   else
      Tenedor(rank,size-1);  // Los impares son Tenedores

   MPI_Finalize( );
   return 0;
}
// ---------------------------------------------------------------------

void Filosofo( int id, int nprocesos )
{
   int izq = (id+1) % nprocesos;
   int der = ((id+nprocesos)-1) % nprocesos;
   MPI_Status status;

   while(1)
   {
     // Solicita silla para sentarse
     cout << "Filosofo " << id << " solicida silla... " << endl << flush ;
     MPI_Ssend( NULL, 0, MPI_INT, camarero, sentarse, MPI_COMM_WORLD );

      // Solicita tenedor izquierdo
      cout << "Filosofo "<<id<< " solicita tenedor izq ..." << izq << endl << flush;
      MPI_Ssend( NULL,0,MPI_INT,izq,coger,MPI_COMM_WORLD );
      // ...

      // Solicita tenedor derecho
      cout <<"Filosofo "<<id<< " solicita tenedor der ..." << der << endl << flush;
      MPI_Ssend( NULL,0,MPI_INT,der,coger,MPI_COMM_WORLD );
      // ...

      cout<<"Filosofo "<<id<< " COMIENDO"<<endl<<flush;
      sleep((rand() % 3)+1);  //comiendo

      // Suelta el tenedor izquierdo
      cout <<"Filosofo "<<id<< " suelta tenedor izq ..." << izq << endl << flush;
      MPI_Ssend( NULL,0,MPI_INT,izq,soltar,MPI_COMM_WORLD );
      // ...

      // Suelta el tenedor derecho
      cout <<"Filosofo "<<id<< " suelta tenedor der ..." << der << endl << flush;
      MPI_Ssend( NULL,0,MPI_INT,der,soltar,MPI_COMM_WORLD );
      // ...

      // Solicita levantarse de la silla
      cout << "Filosofo " << id << " solicida levantarse de la silla... " << endl << flush ;
      MPI_Ssend( NULL, 0, MPI_INT, camarero, levantarse, MPI_COMM_WORLD );

      // Piensa (espera bloqueada aleatorio del proceso)
      cout << "Filosofo " << id << " PENSANDO" << endl << flush;

      // espera bloqueado durante un intervalo de tiempo aleatorio
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
 }
}
// ---------------------------------------------------------------------

void Tenedor(int id, int nprocesos)
{
  int buf;
  MPI_Status status;
  int Filo;

  while( true )
  {
    // Espera un peticion desde cualquier filosofo vecino ...
    MPI_Recv(NULL,0,MPI_INT,MPI_ANY_SOURCE,coger,MPI_COMM_WORLD,&status);
    // ...

    // Recibe la peticion del filosofo ...
    Filo = status.MPI_SOURCE;
    // ...

    cout << "Ten. " << id << " recibe petic. de " << Filo << endl << flush;

    // Espera a que el filosofo suelte el tenedor...
    // ...
    MPI_Recv(NULL,0,MPI_INT,Filo,soltar,MPI_COMM_WORLD,&status);
    cout << "Ten. " << id << " recibe liberac. de " << Filo << endl << flush;
  }
}
// ---------------------------------------------------------------------

void Camarero(int id, int nprocesos)
{
  int nfilos = 0;
  MPI_Status status;
  int rama;

  while(true)
  {
    if ( nfilos==0 )      // no hay filosofos en la mesa
       rama = 0 ;
    else if (nfilos==4) // la mesa esta llena
       rama = 1 ;
    else
    {
       // leer 'status' del siguiente mensaje (esperando si no hay)
       MPI_Probe( MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );

       // calcular la rama en función del origen del mensaje
       if ( status.MPI_TAG == sentarse )
          rama = 0 ;
       else
          rama = 1 ;
    }
    switch(rama)
    {
       case 0:
          MPI_Recv( NULL, 0, MPI_INT, MPI_ANY_SOURCE, sentarse, MPI_COMM_WORLD, &status );
          cout << "Camarero sienta a Filosofo " << status.MPI_SOURCE << endl << flush;
          nfilos++;
          cout << "Hay " << nfilos << " filosofos sentados." << endl << flush;
          break;
       case 1:
          MPI_Recv( NULL, 0, MPI_INT, MPI_ANY_SOURCE, levantarse, MPI_COMM_WORLD, &status );
          cout << "Camarero levanta a Filosofo " << status.MPI_SOURCE << endl << flush;
          nfilos--;
          cout << "Hay " << nfilos << " filosofos sentados." << endl << flush;
          break;
    }
  }
}
