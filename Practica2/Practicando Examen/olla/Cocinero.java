import monitor.*;

class Cocinero implements Runnable{
  private Olla o;
  Thread thr;

  Cocinero(Olla po){
    o = po;
    thr = new Thread(this,"Cocinero: ");
  }

  public void run(){
    while (true){
      o.Dormir();
      o.Rellenar_Olla();
    }
  }

}
