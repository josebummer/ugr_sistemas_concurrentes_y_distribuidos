import monitor.*;

class Cliente implements Runnable{
  public Thread thr ;
  public Barberia barberia;

  public Cliente( Barberia pbar , int ncli ){
    barberia = pbar;
    thr = new Thread(this,"Cliente "+ncli+":\t");
  }

  public void run (){
    while (true) {
      barberia.cortarPelo (thr.getName()); // el cliente espera (si procede) y se corta el pelo
      aux.dormir_max( 2000 ); // el cliente está fuera de la barberia un tiempo
    }
  }
}
