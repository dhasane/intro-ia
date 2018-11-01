
import java.util.*;


public class finala {
        static Difusa dif;
        static Clasificacion CR;        // Categoria Resultado

	public static void main(String[] args) {
		dif = new Difusa();
                
                // ingreso categ res
                CR = new Clasificacion("velocidadObj");
                CR.insertarPertenencia("frenar",0,3,5,10);
                CR.insertarPertenencia("seguir",8,10,20,25);
                CR.insertarPertenencia("acelerar",22,25,30,80);


                // ingreso datos
                ingresarADifusa("velocidadAct");
                ingresarClasifADifusa("velocidadAct","lento",1,2,3,4);
                ingresarClasifADifusa("velocidadAct","medio",3,4,6,7);
                ingresarClasifADifusa("velocidadAct","rapido",6,8,11,12);
                ingresarClasifADifusa("velocidadAct","super_rapido",11,13,19,20);
                


                ingresarADifusa("distanciaObj");
                ingresarClasifADifusa("distanciaObj","cerca",1,5,7,10);
                ingresarClasifADifusa("distanciaObj","medio",7,15,20,25);
                ingresarClasifADifusa("distanciaObj","lejos",22,27,400,500);



                System.out.print("\n" + "------------------------------------\n");
		        
                CR.imprimir();
                
                dif.imprimir();
                
                System.out.print("\n" + "------------------------------------\n");
                
                

                List< String > catResultado = CR.getCategorias();
                
                List< List<DatoMat> > listas = new ArrayList< List<DatoMat> >();
                
                System.out.print("ingrese un valor para velocidad entre 1 y 20 : ");
                float vel  = Utils.leerFlTeclado();

                System.out.print("ingrese un valor para distancia al objeto entre 1 y 500 : ");

                float dist = Utils.leerFlTeclado();
		
                // evaluacion de las categ

                listas.add(dif.fuzzy("velocidadAct", vel));
		        listas.add(dif.fuzzy("distanciaObj", dist));


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