import monitor.*;

public class prueba {

    public static void main(String[] args) {
        if( args.length != 1 ){
          System.out.println("Sintaxis: nsalvajes\n");
          return;
        }
        Olla o = new Olla();
        Cocinero c = new Cocinero(o);
        Salvaje[] s = new Salvaje[Integer.parseInt(args[0])];
        for( int i = 0 ; i < Integer.parseInt(args[0]); i++ ){
          s[i] = new Salvaje(o,i);
        }

        c.thr.start();
        for( int i = 0 ; i < Integer.parseInt(args[0]); i++ ){
          s[i].thr.start();
        }

    }
}
