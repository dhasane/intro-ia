
import java.util.*;


public class test {
        static Difusa dif;
	public static void main(String[] args) {
		dif = new Difusa();
                
                ingresarADifusa("azucar");
		dif.insertarClasificacion("azucar");
		dif.insertarAClasificacion("azucar","poco dulce",2,4,7,10);
		dif.insertarAClasificacion("azucar","medio dulce",6,10,15,18);
		dif.insertarAClasificacion("azucar","muy dulce",16,20,30,30);


		dif.insertarClasificacion("leche");
		dif.insertarAClasificacion("leche","fria",3,5,7,16);
                dif.insertarAClasificacion("leche","tibia",8,17,20,22);
                dif.insertarAClasificacion("leche","caliente",16,20,26,30);
                
                
                dif.insertarClasificacion("cafe");
		dif.insertarAClasificacion("cafe","claro",1,7,10,20);
                dif.insertarAClasificacion("cafe","oscuro",12,18,24,30);
                
                dif.insertarClasificacion("precio");
		dif.insertarAClasificacion("precio","clase obrera",1,4,6,10);
		dif.insertarAClasificacion("precio","normal",7,12,15,18);
		dif.insertarAClasificacion("precio","elite superior alfas",16,20,30,30);
                       
                
                System.out.print("\n" + "------------------------------------\n");
		dif.imprimir();
                
                System.out.print("\n" + "------------------------------------\n");
                
                
		List<DatoMat> AZ = dif.fuzzy("azucar", 9);
		List<DatoMat> LE = dif.fuzzy("leche", 15);
                List<DatoMat> CA = dif.fuzzy("cafe", 20);
                
		List< String > catResultado = dif.getCategorias("precio");
		
		System.out.print( "evaluando 9 en azucar : "  +  (AZ) + "\n");
                System.out.print( "evaluando 15 en leche: "  +  (LE) + "\n");
                System.out.print( "evaluando 20 en cafe: "  +  (CA) + "\n");
		System.out.print( "\n\ncategorias resultado "  +  (catResultado) + "\n");
		System.out.print("\n" + "------------------------------------\n");

		List< List<DatoMat> > listas = new ArrayList< List<DatoMat> >();

		listas.add(AZ);
		listas.add(LE);
                listas.add(CA);
                
		List<DatoMat> Mat = Utils.crearMatriz(listas);
                
                Utils.darValores(Mat,catResultado);
                
                System.out.print("\n" + "------------------------------------\n");
                System.out.print("\n" + "------------------------------------\n");
                
                //System.out.print(Mat);

                List<DatoMat> resultado = Utils.unificar(Mat,catResultado);
                System.out.println("\nresultado : \n");
                System.out.println("categoria | porcentaje | \"categoria\" (realmente esta porque se esta usando datomat/ sobra) ");
                System.out.println(resultado);
                
                System.out.println();
                
                System.out.println("\n\n\nresultado final : "+dif.encontrarResultado("precio",resultado));

                
	}
        
    static void ingresarADifusa(String nom) 
    {
        if (!dif.insertarClasificacion(nom)) {
            System.out.println("valor ya insertado \n");
        } else {
            System.out.println("valor insertado \n");
        }
    }

}