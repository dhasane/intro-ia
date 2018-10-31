
import java.util.*;


public class tesv2 {
    static Difusa dif;
    static Clasificacion CR;        // Categoria Resultado
    static List< List<DatoMat> > listas;

    static int pos;
	public static void main(String[] args) {
		dif = new Difusa();
        listas = new ArrayList< List<DatoMat> >();
                
                // ingreso categ res
                // prefiero tener una buena diferenciacion entre las categ res y los datos
                CR = new Clasificacion("velocidadObj");
                CR.insertarPertenencia("frenar",0,10,20,30);
                CR.insertarPertenencia("seguir",20,30,40,50);
                CR.insertarPertenencia("acelerar",40,50,60,70);


                // ingreso datos
                ingresarADifusa("velocidadAct");
                ingresarClasifADifusa("velocidad","lento",1,20,30,40);
                ingresarClasifADifusa("velocidad","medio",30,48,60,70);
                ingresarClasifADifusa("velocidad","rapido",60,80,110,120);
                ingresarClasifADifusa("velocidad","super_rapido",110,130,190,200);
                


                ingresarADifusa("distanciaObj");
                ingresarClasifADifusa("distanciaObj","cerca",5,5,7,10);
                ingresarClasifADifusa("distanciaObj","medio",7,15,20,25);
                ingresarClasifADifusa("distanciaObj","lejos",3,5,7,16);
                
                
                
                System.out.print("\n" + "------------------------------------\n");
		        dif.imprimir();
                
                System.out.print("\n" + "------------------------------------\n");

                ingresarFuzzy("velocidadAct", 9);
                ingresarFuzzy("distanciaObj", 15);
                
                encontrarResultado(listas,CR); 
	}



    static void encontrarResultado(List< List<DatoMat> > listas,Clasificacion CR)
    {

        List<DatoMat> Mat = Utils.crearMatriz(listas);
        
        System.out.println(Mat+"---------");
        List< String > catResultado = CR.getCategorias();

        System.out.println(catResultado+"---------");


        // se le da valores a cada situacion, o como se quiera llamar
        Utils.darValores(Mat,catResultado);
                
        System.out.print("\n" + "------------------------------------\n");
        System.out.print("\n" + "------------------------------------\n");

        List<DatoMat> resultado = Utils.unificar(Mat,catResultado);
        System.out.println("\nresultado : \n");
        System.out.println("categoria | porcentaje ");
        System.out.println(resultado);
                
        System.out.println();

        // se consigue el resultado final
        System.out.println("\n\n\nresultado final : "+CR.getResultado(resultado) );
    }

    static void ingresarFuzzy(String cat, float val)
    {
        listas.add(dif.fuzzy(cat, val));
        
    }

        // se preguntaran "Hamilton, pero para que hiciste estas funciones si es basicamente
        // la misma cosa", pero no, ahi estan las verificaciones, entonces es mas facil para despues
    static void ingresarADifusa(String nom) 
    {
        if (!dif.insertarClasificacion(nom)) {
            System.out.println("clasificacion no ingresada \n");
        } else {
            System.out.println("clasificacion ingresada exitosamente \n");
        }
    }

    static void ingresarClasifADifusa(String nom, String nomprt, float i, float it, float ft, float f) 
    {
        System.out.println(nom);
        if (!dif.insertarAClasificacion(nom,nomprt,i,it,ft,f)) {
            System.out.println("categoria no ingresada \n");
        } else {
            System.out.println("categoria ingresada exitosamente \n");
        }
    }

}
