import monitor.*;

class Salvaje implements Runnable{
  private Olla o;
  Thread thr;
  private int nsalvajes;

  Salvaje(Olla po, int pnsalvajes){
    o = po;
    nsalvajes = pnsalvajes;
    thr = new Thread(this,"Salvaje "+nsalvajes+":");
  }

  public void run(){
    while (true){
      o.Servirse_1_Misionero(thr.getName());
      aux.dormir_max(2000);
      System.out.println(thr.getName()+"\ttermina a comer.");
    }
  }

}
