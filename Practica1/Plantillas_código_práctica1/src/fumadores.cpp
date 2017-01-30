// *****************************************************************************
//
// Prácticas de SCD. Práctica 1.
// Plantilla de código para el ejercicio de los fumadores
//
// *****************************************************************************

#include <iostream>
#include <string>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"

using namespace std ;

const int NELE = 3;                         //Esta variable controla el numero de elementos que tiene el vector de productos
const int NFUM = 3;                         //Esta variable controla el numero de fumadores
const string elem[NELE] = {"PAPEL","TABACO","CERILLAS"};  //CUIDADO:: No cambiar el orden de los elementos.

sem_t
  sfumadores[NFUM],                //Creamos un vector de 3 semaforos para controlar a los fumadores
  estanq,                       //Otro semaforo para el estanquero
  mutex;                        //Otro semaforo para la salida de los mensajes.

// ---------------------------------------------------------------------
// introduce un retraso aleatorio de duración comprendida entre
// 'smin' y 'smax' (dados en segundos)

void retraso_aleatorio( const float smin, const float smax )
{
  static bool primera = true ;
  if ( primera )        // si es la primera vez:
  {  srand(time(NULL)); //   inicializar la semilla del generador
     primera = false ;  //   no repetir la inicialización
  }
  // calcular un número de segundos aleatorio, entre {\ttbf smin} y {\ttbf smax}
  const float tsec = smin+(smax-smin)*((float)random()/(float)RAND_MAX);
  // dormir la hebra (los segundos se pasan a microsegundos, multiplicándos por 1 millón)
  usleep( (useconds_t) (tsec*1000000.0)  );
}

// ----------------------------------------------------------------------------
// función que simula la acción de fumar, como un retardo aleatorio de la hebra.
// recibe como parámetro el numero de fumador
// el tiempo que tarda en fumar está entre dos y ocho décimas de segundo.

void fumar( int num_fumador )
{
   sem_wait( &mutex );                    //Controlamos las salidas de mensaje con el semaforo
   cout << "Fumador número " << num_fumador << ": comienza a fumar." << endl << flush ;
   sem_post( &mutex );

   retraso_aleatorio( 0.2, 0.8 );                           //Retraso aleatorio para fumar

   sem_wait( &mutex );
   cout << "Fumador número " << num_fumador << ": termina de fumar." << endl << flush ;
   sem_post( &mutex );

}
// ----------------------------------------------------------------------------

void * seleccionar( void * ){
  while(true){                        //Bucle infinito
    int num=rand()%(3);               //Creamos un numero aleatorio. FORMATO = 0 + rand() % (3)
    sem_wait( &estanq );              //El estanquero espera ha que quiten el producto de la mesa para sacar otro

    sem_wait( &mutex );               //Controlamos la salida de mensaje
    cout << "\t\t\t\t\tEl estanquero a sacado: " << elem[num] << endl;
    sem_post( &mutex );

    sem_post( &(sfumadores[num]) );       //Indicamos al fumador correspondiente que puede fumar
  }
}

void * fumador( void * id_thread){
  while(true){                                              //Bucle infinito
    unsigned long id = (unsigned long) id_thread;
    sem_wait( &mutex );
    cout << "Fumador número " << id << " espera\t" << elem[id] << endl;
    sem_post( &mutex );

    sem_wait( &(sfumadores[id]) );                           //Esperamos hasta que el estanquero nos de paso
    sem_post( &estanq );                                     //Indicamos al estanquero que puede sacar otro producto
    fumar(id);                                               //Fuma
  }
}

// ----------------------------------------------------------------------------

int main()
{
  srand( time(NULL) ); // inicializa semilla aleatoria para selección aleatoria de fumador

  pthread_t fumadores[NFUM] , estanquero;                             //Creamos las hebras

  cout << "ESTADO INICIAL:\nfumador 0 necesita:\t" << elem[0];         //Mensaje informativo
  cout << "\nfumador 1 necesita:\t" << elem[1];
  cout << "\nfumador 2 necesita:\t" << elem[2] << "\n\n\n";

  for( int i = 0 ; i < NFUM ; i++ )                                   //Inicializamos todos los semanforos
    sem_init( &sfumadores[i] , 0 , 0 );
  sem_init( &estanq , 0 , 1 );
  sem_init( &mutex , 0 , 1 );

  for( unsigned long i = 0; i < NFUM ; i++ ){                           //Ejecutamos los hilos
    void * id_thread = ( void * ) i;
    pthread_create( &fumadores[i] , NULL , fumador , id_thread );
  }
  pthread_create( &estanquero , NULL , seleccionar , NULL);

  for( int i = 0; i < NFUM ; i++ )                                      //Hacemos la espera de todos los hilos
    pthread_join( fumadores[i] , NULL );
  pthread_join( estanquero , NULL );

  for( int i = 0 ; i < NFUM ; i++ )                           //Destruimos los semaforos
    sem_destroy( &sfumadores[i] );
  sem_destroy( &estanq );


  return 0 ;
}
