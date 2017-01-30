import monitor.*;

class Puente extends AbstractMonitor{
  private final int MAXIMOCOCHES = 10;
  private int num_coches_norte;
  private int num_coches_sur;
  private int npueden , spueden;
  private Condition cochenorte;
  private Condition cochesur;

  Puente(){
    num_coches_norte = 0;
    num_coches_sur = 0;
    npueden = spueden = MAXIMOCOCHES;
    cochenorte = makeCondition();
    cochesur = makeCondition();
  }

  public void EntrarCocheDelNorte(String coche){
    enter();
      System.out.println(coche+"\tha llegado al puente.");
      if ( num_coches_sur > 0 || npueden == 0 ){
        System.out.println(coche+"\tespera en la cola.");
        cochenorte.await();
      }
      if( !cochesur.isEmpty() )
        npueden--;
      num_coches_norte++;
      System.out.println(coche+"\tha entrado en el puente.");
      if( npueden > 0  )
        cochenorte.signal();
    leave();
  }

  public void SalirCocheDelNorte(String coche){
    enter();
      num_coches_norte--;
      System.out.println(coche+"\tsale del puente.");
      if( num_coches_norte == 0 ){
        npueden = MAXIMOCOCHES;
        cochesur.signal();
      }
    leave();
  }
  public void EntrarCocheDelSur(String coche){
    enter();
    System.out.println(coche+"\tha llegado al puente.");
      if ( num_coches_norte > 0 || spueden == 0 ){
        System.out.println(coche+"\tespera en la cola.");
        cochesur.await();
      }
      if( !cochenorte.isEmpty() )
        spueden--;
      num_coches_sur++;
      System.out.println(coche+"\tha entrado en el puente.");
      if( spueden > 0 )
        cochesur.signal();
    leave();
  }

  public void SalirCocheDelSur(String coche){
    enter();
      num_coches_sur--;
      System.out.println(coche+"\tsale del puente.");
      if( num_coches_sur == 0 ){
        spueden = MAXIMOCOCHES;
        cochenorte.signal();;
      }
    leave();
  }
}
