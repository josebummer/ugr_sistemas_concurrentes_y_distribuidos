import monitor.*;

public class prueba {

    public static void main(String[] args) {
        if( args.length != 1 ){
          System.out.println("Sintaxis: nclientes\n");
          return;
        }
        Barberia bar = new Barberia();
        Barbero b = new Barbero(bar);
        Cliente[] c = new Cliente[Integer.parseInt(args[0])];
        for( int i = 0 ; i < Integer.parseInt(args[0]); i++ ){
          c[i] = new Cliente(bar,i);
        }

        b.thr.start();
        for( int i = 0 ; i < Integer.parseInt(args[0]); i++ ){
          c[i].thr.start();
        }

    }
}
