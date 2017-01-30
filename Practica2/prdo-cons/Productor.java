import monitor.*;

public class Productor implements Runnable {
    private Buffer bb;
    private int veces, numP;
    Thread thr;

    public Productor( Buffer pbb , int pveces , int pnumP ){
        bb = pbb;
        veces = pveces;
        numP = pnumP;
        thr = new Thread( this, "produtor "+numP );
    }
    public void run(){
        try{
            for ( int i = 0; i < veces; i++){
                double item = (double)(i+1);
                System.out.println(thr.getName() + " produciendo: " +item);
                bb.puede_depositar(item);
            }
        }
        catch(Exception e)
        {
            System.err.println("Excepcion en main: " + e);
        }
    }
}
