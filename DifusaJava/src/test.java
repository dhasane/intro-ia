public class test {

	public static void main(String[] args) {
		Difusa dif = new Difusa();

		dif.insertarClasificacion("azucar");
		dif.insertarAClasificacion("azucar","poco dulce",2,4,7,10);
		dif.insertarAClasificacion("azucar","medio dulce",6,10,15,18);
		dif.insertarAClasificacion("azucar","muy dulce",16,20,30,30);


		dif.insertarClasificacion("leche");
		dif.insertarAClasificacion("leche","hm",6,8,12,16);

		// prueba para evitar que se repitan nombres de Clasificaciones
		if(!dif.insertarClasificacion("leche"))
		{
			System.out.println("valor ya insertado" + "\n");
		}


		System.out.println( "evaluando 8 en azucar : "  +  (dif.fuzzy("azucar", 8)) + "\n");
		System.out.println("\n" + "------------------------------------\n");

		System.out.println( dif.conseguirValor("azucar","poco dulce") + "\n");
		System.out.println("\n" + "------------------------------------\n");
		System.out.println( dif.conseguirValor("azucar","medio dulce") + "\n");
		System.out.println("\n" + "------------------------------------\n");

		System.out.println("algo entre poco dulce y medio dulce : " +  dif.quieroAlgoEntre("azucar","poco dulce","medio dulce") + "\n");
		System.out.println("\n" + "------------------------------------\n");
		dif.imprimir();


	}

}
