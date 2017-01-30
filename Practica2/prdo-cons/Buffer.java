import monitor.*;

public class Buffer extends AbstractMonitor{
    private int numSlots , cont;
    private double[] buffer;
    private Condition extraer = makeCondition();
    private Condition depositar = makeCondition();

    public Buffer( int num ){
        numSlots = num;
        cont = 0;
        buffer = new double[numSlots];
    }
    public void puede_depositar( double valor ) throws InterruptedException{
        enter();
            if( cont == numSlots ){
                depositar.await();
            }
            buffer[cont] = valor;
            cont++;
            extraer.signal();
        leave();
    }
    public double puede_extraer(){
        double valor;
        enter();
            if( cont == 0 ){
                extraer.await();
            }
            cont--;
            valor = buffer[cont];
            depositar.signal();
        leave();
        return valor;
    }

}
