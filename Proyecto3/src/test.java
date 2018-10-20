
import java.util.*;


public class test {

	public static void main(String[] args) {
		Difusa dif = new Difusa();

		dif.insertarClasificacion("azucar");
		dif.insertarAClasificacion("azucar","poco dulce",2,4,7,10);
		dif.insertarAClasificacion("azucar","medio dulce",6,10,15,18);
		dif.insertarAClasificacion("azucar","muy dulce",16,20,30,30);


		dif.insertarClasificacion("leche");
		dif.insertarAClasificacion("leche","fria",6,8,12,16);
   	dif.insertarAClasificacion("leche","tibia",14,17,20,22);
   	dif.insertarAClasificacion("leche","caliente",16,20,26,30);

		// prueba para evitar que se repitan nombres de Clasificaciones
		if(!dif.insertarClasificacion("leche"))
		{
			System.out.println("valor ya insertado" + "\n");
		}

		List<DatoMat> AZ = dif.fuzzy("azucar", 8);
		List<DatoMat> LE = dif.fuzzy("leche", 7);
		List<DatoMat> LE2 = dif.fuzzy("leche", 20);
		
		System.out.print( "evaluando 8 en azucar : "  +  (AZ) + "\n");
      System.out.print( "evaluando 7 en leche: "  +  (LE) + "\n");
		System.out.print( "evaluando 20 en leche: "  +  (LE2) + "\n");
		System.out.print("\n" + "------------------------------------\n");

		List< List<DatoMat> > listas = new ArrayList<List<DatoMat> >();

		listas.add(AZ);
		listas.add(LE);
		listas.add(LE2);

		List<DatoMat> Mat = Difusa.crearMatriz(listas);
		System.out.print(Mat);



		List<DatoMat> dms = Difusa.conseguirMayorLista(Mat);
		System.out.print("\n" + "------------------------------------\n"+dms);
		
		//System.out.print( dif.conseguirValor("azucar","poco dulce") + "\n");
		//System.out.print("\n" + "------------------------------------\n");
		//System.out.print( dif.conseguirValor("azucar","medio dulce") + "\n");
		//System.out.print("\n" + "------------------------------------\n");

		//System.out.print("algo entre poco dulce y medio dulce : " +  dif.quieroAlgoEntre("azucar","poco dulce","medio dulce") + "\n");
		System.out.print("\n" + "------------------------------------\n");
		dif.imprimir();


	}

}

