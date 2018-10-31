
import java.util.*;


public class finala {
        static Difusa dif;
        static Clasificacion CR;        // Categoria Resultado

	public static void main(String[] args) {
		dif = new Difusa();
                
                // ingreso categ res
                // prefiero tener una buena diferenciacion entre las categ res y los datos
                /*CR = new Clasificacion("precio");
                CR.insertarPertenencia("clase obrera",1,4,6,10);
                CR.insertarPertenencia("normal",7,12,15,18);
                CR.insertarPertenencia("elite superior alfas",16,20,30,30);


                // ingreso datos
                ingresarADifusa("azucar");
		ingresarClasifADifusa("azucar","poco dulce",2,4,7,10);
		ingresarClasifADifusa("azucar","medio dulce",6,10,15,18);
		ingresarClasifADifusa("azucar","muy dulce",16,20,30,30);


		ingresarADifusa("leche");
		ingresarClasifADifusa("leche","fria",3,5,7,16);
                ingresarClasifADifusa("leche","tibia",8,17,20,22);
                ingresarClasifADifusa("leche","caliente",16,20,26,30);
                
                
                ingresarADifusa("cafe");
		ingresarClasifADifusa("cafe","claro",1,7,10,20);
                ingresarClasifADifusa("cafe","oscuro",12,18,24,30);
                       
                */
                CR = new Clasificacion("velocidadObj");
                CR.insertarPertenencia("frenar",0,10,20,30);
                CR.insertarPertenencia("seguir",20,30,40,50);
                CR.insertarPertenencia("acelerar",40,50,60,70);


                // ingreso datos
                ingresarADifusa("velocidadAct");
                ingresarClasifADifusa("velocidadAct","lento",1,2,3,4);
                ingresarClasifADifusa("velocidadAct","medio",3,4,6,7);
                ingresarClasifADifusa("velocidadAct","rapido",6,8,11,12);
                ingresarClasifADifusa("velocidadAct","super_rapido",11,13,19,20);
                


                ingresarADifusa("distanciaObj");
                ingresarClasifADifusa("distanciaObj","cerca",5,5,7,10);
                ingresarClasifADifusa("distanciaObj","medio",7,15,20,25);
                ingresarClasifADifusa("distanciaObj","lejos",22,27,400,500);


                System.out.print("\n" + "------------------------------------\n");
		dif.imprimir();
                
                System.out.print("\n" + "------------------------------------\n");
                
                

		List< String > catResultado = CR.getCategorias();
		
		List< List<DatoMat> > listas = new ArrayList< List<DatoMat> >();
                
                float dist = 15;
                float vel  = 100;
		
                // evaluacion de las categ
                listas.add(dif.fuzzy("velocidadAct", 10));
		listas.add(dif.fuzzy("distanciaObj", 15));


		List<DatoMat> Mat = Utils.crearMatriz(listas);
                
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
        

        // se preguntaran "Hamilton, pero para que hiciste estas funciones si es basicamente
        // la misma cosa", pero no, ahi estan las verificaciones, entonces es mas facil para despues
    static void ingresarADifusa(String nom) 
    {
        if (!dif.insertarClasificacion(nom)) {
            System.out.println("valor ya insertado \n");
        } else {
            System.out.println("valor insertado \n");
        }
    }

    static void ingresarClasifADifusa(String nom, String nomprt, float i, float it, float ft, float f) 
    {
        if (!dif.insertarAClasificacion(nom,nomprt,i,it,ft,f)) {
            System.out.println("valor ya insertado \n");
        } else {
            System.out.println("valor insertado \n");
        }
    }

}