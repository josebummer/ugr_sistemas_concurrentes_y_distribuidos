import monitor.*;

public class fumadores {

    public static void main(String[] args) {
        Estanco est = new Estanco();
        Estanquero e = new Estanquero(est);
        Fumador[] f = new Fumador[3];

        for (int i = 0; i < f.length; i++)
           f[i] = new Fumador(est,i);

        e.thr.start();
        for (int i = 0; i < f.length; i++)
           f[i].thr.start();
    }
}
