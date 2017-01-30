import monitor.*;

class Fumador implements Runnable{
    Estanco est;
    int miIngrediente;
    public Thread thr ;

    public Fumador( Estanco p_est , int p_miIngrediente ){
        est = p_est;
        miIngrediente = p_miIngrediente;
        thr = new Thread(this, "fumador "+miIngrediente);
    }
    public void run(){
        while ( true ){
            est.obtenerIngrediente( miIngrediente );
            aux.dormir_max( 2000 );
            System.out.println("Fumador "+miIngrediente+" ha terminado de fumar");
        }
    }
}
