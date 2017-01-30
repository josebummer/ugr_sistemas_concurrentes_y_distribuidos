import monitor.*;

public class ProdCons {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        if( args.length != 5 ){
          System.out.println("Sintaxis: ncons nprod tambuf niterp niterc\n");
          return;
        }
        Consumidor[] c = new Consumidor[Integer.parseInt(args[0])];
        Productor[] p = new Productor[Integer.parseInt(args[1])];
        Buffer bb = new Buffer(Integer.parseInt(args[2]));
        int iterp = Integer.parseInt(args[3]);
        int iterc = Integer.parseInt(args[4]);

        if( p.length*iterp != c.length*iterc ){
          System.out.println("No coinciden el numero de items a producir con el numero de items a consumir.\n");
          return;
        }

        for (int i = 0; i < c.length; i++)
           c[i] = new Consumidor(bb,iterc,i);
        for (int i = 0; i < p.length; i++)
           p[i] = new Productor(bb,iterp,i);

        for (int i = 0; i < p.length; i++)
           p[i].thr.start();
        for (int i = 0; i < c.length; i++)
           c[i].thr.start();
    }

}
