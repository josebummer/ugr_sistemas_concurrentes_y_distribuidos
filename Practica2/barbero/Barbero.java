import monitor.*;

class Barbero implements Runnable{
  public Thread thr ;
  public Barberia barberia;

  public Barbero( Barberia pbar ){
    barberia = pbar;
    thr = new Thread(this,"Barbero: ");
  }

  public void run (){
    while (true) {
      barberia.siguienteCliente ();
      aux.dormir_max( 2500 ); // el barbero está cortando el pelo
      barberia.finCliente ();
    }
  }
}
