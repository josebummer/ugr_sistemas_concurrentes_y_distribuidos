import monitor.*;

class Estanco extends AbstractMonitor{
    private int ingredienteact;
    private Condition estanquero = makeCondition();
    private Condition[] fumadores = new Condition[3];

    public Estanco(){
        for( int i = 0; i < fumadores.length; i++ ){
            fumadores[i] = makeCondition();
        }
        ingredienteact = -1;
    }

    // invocado por cada fumador, indicando su ingrediente o numero
    public void obtenerIngrediente( int miIngrediente ){
        enter();
            if(miIngrediente != ingredienteact){
                fumadores[miIngrediente].await();
            }
            System.out.println("Fumador "+miIngrediente+": Fumando ingrediente "+miIngrediente);
            ingredienteact = -1;
            estanquero.signal();
        leave();
    }
    // invocado por el estanquero, indicando el ingrediente que pone
    public void ponerIngrediente( int ingrediente ){
        enter();
            ingredienteact = ingrediente;
            System.out.println("Estanquero: poniendo ingrediente "+ingrediente);
            fumadores[ingrediente].signal();
        leave();
    }
    // invocado por el estanquero
    public void esperarRecogidaIngrediente(){
        enter();
            if ( ingredienteact != -1 )
                estanquero.await();
        leave();
    }
}
