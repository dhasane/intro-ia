
import java.util.*;


public class testt {
        static Difusa dif;
        static Clasificacion CR;        // Categoria Resultado

	public static void main(String[] args) {

		dif = new Difusa();
                
                // ingreso categ res
                // prefiero tener una buena diferenciacion entre las categ res y los datos
                String nombreClasificacion = " ";
                String nombreCategoria = " ";
                int respuesta1, respuesta2;
                boolean otraCategoria = true, otraClasificacion = true;
                float valorInicio, valorFin, valorTinicio, valorTfin;
                List< List<DatoMat> > listas = new ArrayList< List<DatoMat> >();
                
                
                do{
                    System.out.println("Ingresar nombre nueva categoria");
                    nombreClasificacion = Utils.leerTecladoString();
                    //Buscar si ya existe
                    ingresarADifusa(nombreClasificacion);
		    
                    do{
                        System.out.println(" Ingresar nueva clasificación para "+nombreClasificacion);
                        nombreCategoria = Utils.leerTecladoString();
                        System.out.println(" Inicio de "+nombreCategoria);
                        valorInicio = Utils.leerTeclado();
                        System.out.println(" Inicio arriba de "+nombreCategoria);
                        valorTinicio = Utils.leerTeclado();
                        System.out.println(" Fin arriba de "+nombreCategoria);
                        valorTfin = Utils.leerTeclado();
                        System.out.println(" Fin de "+nombreCategoria);
                        valorFin = Utils.leerTeclado();
                        
                        ingresarClasifADifusa(nombreClasificacion,nombreCategoria,valorInicio,valorTinicio,valorTfin,valorFin);

                        System.out.println("¿Otra categoria ?(1| 0)");
                        respuesta1 = Utils.leerTeclado();
                        if(respuesta1 == 1 ){
                            otraClasificacion = true;
                        }
                        else{
                            otraClasificacion = false;
                        }

                    }while(otraClasificacion);
                    
                    System.out.println("¿Otra clasificación ?(1| 0)");
                    respuesta2 = Utils.leerTeclado();
                    if(respuesta2 == 1 ){
                        otraCategoria = true;
                    }
                    else{
                        otraCategoria = false;
                    }
                }while(otraCategoria);
                    
                    
                
                
                
                CR = new Clasificacion("precio");
                CR.insertarPertenencia("clase obrera",1,4,6,10);
                CR.insertarPertenencia("normal",7,12,15,18);
                CR.insertarPertenencia("elite superior alfas",16,20,30,30);

/*
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
                
                System.out.println("Ingrese lo que desea\n");
                String cadena = Utils.leerTecladoString();
                System.out.println(">"+cadena);
                    
                System.out.print("\n" + "------------------------------------\n");
		dif.imprimir();
                
                System.out.print("\n" + "------------------------------------\n");
                
                // evaluacion de las categ
		List<DatoMat> AZ = dif.fuzzy("azucar", 9);
		List<DatoMat> LE = dif.fuzzy("leche", 15);
                List<DatoMat> CA = dif.fuzzy("cafe", 20);
                
		List< String > catResultado = CR.getCategorias();
		
		System.out.print( "evaluando 9 en azucar : "  +  (AZ) + "\n");
                System.out.print( "evaluando 15 en leche: "  +  (LE) + "\n");
                System.out.print( "evaluando 20 en cafe: "  +  (CA) + "\n");
		System.out.print( "\n\ncategorias resultado "  +  (catResultado) + "\n");
		System.out.print("\n" + "------------------------------------\n");

		

		listas.add(AZ);
		listas.add(LE);
                listas.add(CA);
                
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
            System.out.println("clasificacion ya existente \n");
        } else {
            System.out.println("clasificacion insertado exitosamente \n");
        }
    }

    static void ingresarClasifADifusa(String nom, String nomprt, float i, float it, float ft, float f) 
    {
        if (!dif.insertarAClasificacion(nom,nomprt,i,it,ft,f)) {
            System.out.println("categoria ya existente \n");
        } else {
            System.out.println("categoria insertada exitosamente \n");
        }
    }

}