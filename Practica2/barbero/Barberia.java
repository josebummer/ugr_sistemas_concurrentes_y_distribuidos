import monitor.*;

class Barberia extends AbstractMonitor{
  private Condition barbero;
  private Condition silla;
  private Condition sala_espera;

  public Barberia(){
    barbero = makeCondition();
    silla = makeCondition();
    sala_espera = makeCondition();
  }

  // invcado por los clientes para cortarse el pelo
  public void cortarPelo (String cliente){
      enter();
      System.out.println(cliente+" entra en la barberia.");
        if( barbero.isEmpty() ){
          System.out.println(cliente+" espera porque el barbero esta ocupado.");
          sala_espera.await();
        }
        barbero.signal();
        System.out.println(cliente+" comienza a pelarse.");
        silla.await();
        System.out.println(cliente+" termina de pelarse.");
      leave();
  }
  // invocado por el barbero para esperar (si procede) a un nuevo cliente y sentarlo para el corte
  public void siguienteCliente (){
    enter();
      if( sala_espera.isEmpty() ){
        System.out.println("Barbero:\t duerme porque la sala de espera esta vacia.");
        barbero.await();
      }
      System.out.println("Barbero:\t da paso al cliente para pelarlo");
      sala_espera.signal();
    leave();
  }
  // invocado por el barbero para indicar que ha terminado de cortar el pelo
  public void finCliente (){
    enter();
      silla.signal();
    leave();
  }
}
