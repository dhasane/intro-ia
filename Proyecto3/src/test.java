
import java.util.*;


public class test {

	public static void main(String[] args) {
		Difusa dif = new Difusa();

		dif.insertarClasificacion("azucar");
		dif.insertarAClasificacion("azucar","poco dulce",2,4,7,10);
		dif.insertarAClasificacion("azucar","medio dulce",6,10,15,18);
		dif.insertarAClasificacion("azucar","muy dulce",16,20,30,30);


		dif.insertarClasificacion("leche");
		dif.insertarAClasificacion("leche","fria",3,5,7,16);
                dif.insertarAClasificacion("leche","tibia",8,17,20,22);
                dif.insertarAClasificacion("leche","caliente",16,20,26,30);
                
                dif.insertarClasificacion("precio");
		dif.insertarAClasificacion("precio","clase obrera",0,4,6,10);
		dif.insertarAClasificacion("precio","normal",7,12,15,18);
		dif.insertarAClasificacion("precio","elite superior alfas",16,20,30,30);
                
                List<String> yaNoSe = new ArrayList<>();
                yaNoSe.add("clase obrera");
                yaNoSe.add("normal");       
                yaNoSe.add("elite superior alfas");
                
		// prueba para evitar que se repitan nombres de Clasificaciones
		if(!dif.insertarClasificacion("leche"))
		{
			System.out.println("valor ya insertado" + "\n");
		}

		List<DatoMat> AZ = dif.fuzzy("azucar", 9);
		List<DatoMat> LE = dif.fuzzy("leche", 9);
		List<DatoMat> LE2 = dif.fuzzy("precio", 9);
		
		System.out.print( "evaluando 8 en azucar : "  +  (AZ) + "\n");
      System.out.print( "evaluando 8 en leche: "  +  (LE) + "\n");
		System.out.print( "evaluando 20 en leche: "  +  (LE2) + "\n");
		System.out.print("\n" + "------------------------------------\n");

		List< List<DatoMat> > listas = new ArrayList<List<DatoMat> >();

		listas.add(AZ);
		listas.add(LE);
		//listas.add(LE2);

		List<DatoMat> Mat = Difusa.crearMatriz(listas,LE2);
                System.out.println("test.main()1 + "+LE2.get(0).categorias.get(0));
                System.out.println("test.main()1 + "+LE2.get(1).categorias.get(0));
                System.out.println("test.main()1 + "+LE2.get(2).categorias.get(0));
		System.out.print(Mat);
                
                //De la lista buscar el mayor para cada categoria del resultado (Mayor para "barato",Mayor para "Normal", etc.)
                System.out.println("");
                List<DatoMat> resultado = Difusa.unificar(Mat,yaNoSe);
                
                for(int i=0; i< resultado.size();i++){
                    System.out.println(resultado.get(i).valor + " "+resultado.get(i).porcentaje);
                }
                
                
                
                
                /*
                //Esta parte no sirve 
		List<DatoMat> dms = Difusa.conseguirMayorLista(Mat);
		System.out.print("\n" + "------------------------------------\n"+dms); */
		
		//System.out.print( dif.conseguirValor("azucar","poco dulce") + "\n");
		//System.out.print("\n" + "------------------------------------\n");
		//System.out.print( dif.conseguirValor("azucar","medio dulce") + "\n");
		//System.out.print("\n" + "------------------------------------\n");

		//System.out.print("algo entre poco dulce y medio dulce : " +  dif.quieroAlgoEntre("azucar","poco dulce","medio dulce") + "\n");
		System.out.print("\n" + "------------------------------------\n");
		dif.imprimir();


	}

}

