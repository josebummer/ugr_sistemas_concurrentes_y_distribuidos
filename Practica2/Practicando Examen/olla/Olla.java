import monitor.*;

class Olla extends AbstractMonitor{
  private final int TAMANIOOLLA = 50;
  private int elem;
  private Condition cocinero;
  private Condition salvaje;

  Olla(){
    elem = TAMANIOOLLA;
    cocinero = makeCondition();
    salvaje = makeCondition();
  }

  public void Servirse_1_Misionero(String nsalvaje){
    enter();
    System.out.println(nsalvaje+"\tva ha la olla.");
      if( elem == 0 ){
        System.out.println(nsalvaje+"\tla olla esta vacia, llamamos al cocinero y esperamos.");
        cocinero.signal();
        salvaje.await();
      }
      elem--;
      System.out.println(nsalvaje+"\tempieza a comer.");
      if( elem == 0 ){
        cocinero.signal();
      }
      else{
        salvaje.signal();
      }
    leave();
  }

  public void Rellenar_Olla(){
    enter();
      System.out.println("Cocinero:\tvoy ha rellenar la olla.");
      elem = TAMANIOOLLA;
      System.out.println("Cocinero:\tolla rellenada.");
      salvaje.signal();
    leave();
  }

  public void Dormir(){
    enter();
      if( elem > 0 ){
        System.out.println("Cocinero:\tduerme.");
        cocinero.await();
        System.out.println("Cocinero:\tdespierta.");
      }
    leave();
  }
}
