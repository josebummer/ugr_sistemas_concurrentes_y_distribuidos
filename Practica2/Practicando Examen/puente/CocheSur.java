import monitor.*;

class CocheSur implements Runnable{
  private Puente p;
  Thread thr;
  private int numc;

  CocheSur(Puente pp, int pnumc){
    p = pp;
    numc = pnumc;
    thr = new Thread(this,"CocheSur "+numc+": ");
  }

  public void run(){
    while( true ){
      p.EntrarCocheDelSur(thr.getName());
      aux.dormir_max( 4000 );
      p.SalirCocheDelSur(thr.getName());
      aux.dormir_max( 3000 );
    }
  }
}
