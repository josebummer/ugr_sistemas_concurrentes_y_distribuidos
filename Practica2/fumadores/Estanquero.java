import monitor.*;

class Estanquero implements Runnable{
    public Thread thr;
    Estanco est;

    public Estanquero( Estanco p_est ){
        est = p_est;
        thr = new Thread(this, "estanquero: ");
    }

    public void run(){
        int ingrediente;
        while (true){
            ingrediente = (int) (Math.random () * 3.0); // 0,1 o 2
            est.ponerIngrediente( ingrediente );
            est.esperarRecogidaIngrediente() ;
        }
    }
}
