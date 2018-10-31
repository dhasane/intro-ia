



import java.util.*;


public class test {
    
    static Difusa dif;
    static Clasificacion CR;        // Categoria Resultado
    static List< List<DatoMat> > listas;

    static int pos;

    static boolean catresing;       // categoria res ingresada

	public static void main(String[] args) {
        catresing = false;
		dif = new Difusa();
        listas = new ArrayList< List<DatoMat> >();
        CR = null;

        menu();

                // evaluacion de las categ
                //ingresarFuzzy("azucar", 9);
                //ingresarFuzzy("leche", 15);
                //ingresarFuzzy("cafe", 20);
                
		        
		        
               
	}

    


    static void menu()
    {
        String[] opcion;
        boolean salir = false;
        
        int tam = 0;
        float val =0;
        while(!salir)
        {
            System.out.print("\n" + "------------------------------------\n");
            pos = 0;
            System.out.print("> ");
            opcion = Utils.leerTecladoString().split(" ");
            
            if(opcion[pos].equals("help"))
            {
                System.out.println("imprimir");
                System.out.println("salir");
                System.out.println("ingresar catres (nombre cat)");
                System.out.println("ingresar subcatres");
                System.out.println("ingresar categoria (nombre cat)");
                System.out.println("ingresar subcat");
                System.out.println("resultado");
                System.out.println("(categoria) entre (subcat) (subcat2)");
                System.out.println("quiero (categoria)(subcat)");
            }
            else if(opcion[pos].equals("imprimir"))
            {
                System.out.println("categoria resultado : ");
                if (CR != null) CR.imprimir();

                System.out.println("categorias : ");
                dif.imprimir();

                System.out.println("preferencias : ");
                System.out.println(listas+"---------");
                
            }
            else if(opcion[pos].equals("salir"))
            {
                salir = true;
            }
            else if(opcion[pos].equals("resultado"))
            {
                if(listas.size()>0){
                    catresing = true;
                }
                if(catresing && listas.size() > 0 && CR != null)
                {
                    encontrarResultado(listas,CR);
                }
                else
                {
                    System.out.println("es necesario tener categorias y sub categorias resultado y por lo menos una preferencia");
                }
            }
            else if(opcion[pos].equals("ingresar"))
            {
                pos ++;
                opcion = comprobar(opcion);
                
                if(opcion[pos].equals("categoria"))
                {
                    pos++;
                    opcion = comprobar(opcion);
                    ingresarADifusa(opcion[pos]);
                }
                else if(opcion[pos].equals("subcat"))
                {
                    
                    boolean ing = false;
                    do
                    {
                        System.out.println("ingresar: \n(categoria)(nueva subcat)(borde bajo inferior)(punto alto inferior)(punto alto superior)(borde bajo superior)");
                        opcion = Utils.leerTecladoString().split(" ");
                        System.out.println(opcion.length);
                        if(opcion.length != 5 )
                        {
                            ingresarClasifADifusa(opcion[0],opcion[1],Float.parseFloat(opcion[2]),Float.parseFloat(opcion[3]),Float.parseFloat(opcion[4]),Float.parseFloat(opcion[5]));
                            ing = true;
                        }
                        else 
                        {
                            System.out.println("cantidad equivocada de argumentos");
                        }

                    }while(!ing);
                    
                }
                else if(opcion[pos].equals("catres"))
                {
                    pos++;
                    opcion = comprobar(opcion);
                    CR = new Clasificacion(opcion[pos]);
                }
                else if(opcion[pos].equals("subcatres"))
                {
                    
                    boolean ing = false;
                    do
                    {
                        System.out.println("ingresar: \n(nueva subcat res)(borde bajo inferior)(punto alto inferior)(punto alto superior)(borde bajo superior)");
                        opcion = Utils.leerTecladoString().split(" ");
                        System.out.println(opcion.length);
                        if(opcion.length != 4 )
                        {
                            CR.insertarPertenencia(opcion[0],Float.parseFloat(opcion[1]),Float.parseFloat(opcion[2]),Float.parseFloat(opcion[3]),Float.parseFloat(opcion[4]));
                            ing = true;
                            catresing = true;
                        }
                        else 
                        {
                            System.out.println("cantidad equivocada de argumentos");
                        }

                    }while(!ing);
                    
                }
                else
                {
                    System.out.println("opcion no valida ");
                }
                
            }
            else if(opcion.length == 4 && opcion[1].equals("entre"))
            {
                if(dif.catPresente(opcion[0]))
                {
                    System.out.println(dif.getCategorias(opcion[0]));

                    val = dif.quieroAlgoEntre(opcion[0], opcion[2], opcion[3]);
                    System.out.println("valor es : "+val);
                    ingresarFuzzy(opcion[0],val);
                }
                
            }
            else if(opcion.length == 3 && opcion[0].equals("quiero"))
            {
                if(dif.catPresente(opcion[1]))
                {
                    System.out.println(dif.getCategorias(opcion[1]));

                    val = dif.quiero(opcion[1],opcion[2]);
                    System.out.println("valor es : "+val);
                    ingresarFuzzy(opcion[1],val);
                }
                
            }
            /*
            else if(opcion.length == 2 && opcion[0].equals("mas"))
            {
                if(dif.catPresente(opcion[1]))
                {
                    System.out.println(dif.getCategorias(opcion[1]));

                    val = val + (1/2);
                    System.out.println("valor es : "+val);
                    ingresarFuzzyYaIngresado(opcion[1],val);
                }
                
            }
            else if(opcion.length == 2 && opcion[0].equals("menos"))
            {
                if(dif.catPresente(opcion[1]))
                {
                    System.out.println(dif.getCategorias(opcion[1]));

                    val = val - (1/2);
                    System.out.println("valor es : "+val);
                    ingresarFuzzyYaIngresado(opcion[1],val);
                }
                
            } */
        }
    }

    static String[] comprobar(String[] opcion)
    {
        if(opcion.length < pos+1)
        {
            System.out.println("que quiere ingresar ?");
            opcion = Utils.leerTecladoString().split(" ");
            pos = 0;
        }
        return opcion;
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
    
    static void ingresarFuzzyYaIngresado(String cat, float val)
    {
       /* System.out.println("cat"+cat);
        for(int i=0; i<listas.size(); i++){
            System.out.println("test.ingresarFuzzyYaIngresado()<<<<"+ listas.get(i).get(i).getValor());
            System.out.println("test.ingresarFuzzyYaIngresado()<<<<"+ listas.get(i).get(i).categorias+listas.size());
            if(listas.get(i).get(i).categorias.get(i).equals(cat)){
                listas.remove(i);
                System.out.println("test.ingresarFuzzyYaIngresado() yyy"+ listas.size());
            }
        } */
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

