import monitor.*;

public class prueba {

    public static void main(String[] args) {
        if( args.length != 2 ){
          System.out.println("Sintaxis: ncochesnorte ncochessur\n");
          return;
        }
        Puente p = new Puente();
        CocheNorte[] cn = new CocheNorte[Integer.parseInt(args[0])];
        CocheSur[] cs = new CocheSur[Integer.parseInt(args[1])];
        for( int i = 0 ; i < Integer.parseInt(args[0]); i++ ){
          cn[i] = new CocheNorte(p,i);
        }
        for( int i = 0 ; i < Integer.parseInt(args[1]); i++ ){
          cs[i] = new CocheSur(p,i);
        }

        for( int i = 0 ; i < Integer.parseInt(args[0]); i++ ){
          cn[i].thr.start();
        }
        for( int i = 0 ; i < Integer.parseInt(args[1]); i++ ){
          cs[i].thr.start();
        }

    }
}
