import monitor.*;

class CocheNorte implements Runnable{
  private Puente p;
  Thread thr;
  private int numc;

  CocheNorte(Puente pp, int pnumc){
    p = pp;
    numc = pnumc;
    thr = new Thread(this,"CocheNorte "+numc+": ");
  }

  public void run(){
    while (true){
      p.EntrarCocheDelNorte(thr.getName());
      aux.dormir_max( 4000 );
      p.SalirCocheDelNorte(thr.getName());
      aux.dormir_max( 3000 );
    }
  }
}
