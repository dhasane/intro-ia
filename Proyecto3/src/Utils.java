
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class Utils {
    
    static void darValores(List<DatoMat> matriz, List<String> catRes)
    {
        System.out.println("categorias resultado dispunibles : ");
        for (int a = 0 ; a < catRes.size() ; a++)
        {
            System.out.println(a+1+" "+catRes.get(a));
        }
        System.out.println("por favor digite el numero respectivo para la categoria deseada : ");

        int seleccion = 0;
        for(int a = 0 ; a < matriz.size() ; a++)
        {
            System.out.print(matriz.get(a)+" : ");
            
            seleccion = leerTeclado() -1; 
            
            while(seleccion >= catRes.size() || seleccion < 0)
            {
                System.out.println("por favor ingrese un numero mayor a 0 y menor o igual a "+catRes.size()+", que es la cantidad de resultados finales posibles");
                seleccion = leerTeclado() -1; 
            }
            matriz.get(a).setValor(catRes.get(seleccion));
        }
    }

    static int leerTeclado()
    {
        Scanner keyboard = new Scanner(System.in);
        //System.out.println();
        return keyboard.nextInt();
    }

    static List<DatoMat> crearMatriz(List<List<DatoMat>> listas) {
        List<DatoMat> matriz = new ArrayList<DatoMat>();

        matriz = crearMatriz(listas.get(0), listas.get(1));

        for (int a = 2; a < listas.size(); a++) {
            matriz = crearMatriz(matriz, listas.get(a));
        }
        return matriz;
    }

    static List<DatoMat> crearMatriz(List<DatoMat> V1, List<DatoMat> V2) {

        List<DatoMat> matriz = new ArrayList<DatoMat>();
        int i = (V2.size() / 2), j = (V1.size() / 2);
        for (int a = 0; a < V1.size(); a++) {

            for (int b = 0; b < V2.size(); b++) {
                DatoMat dm = new DatoMat();
                DatoMat dm2 = new DatoMat();

                dm.copyDM(V1.get(a));
                dm2.copyDM(V2.get(b));
                dm.addV(dm2);
                matriz.add(dm);
            }
        }
        return matriz;
    }

    //Buscar el mayor, en el caso de que hayan dos con el mismo nombre en la matriz escoge el valor mayor
    static List<DatoMat> unificar(List<DatoMat> Mat, List<String> res) {
        List<DatoMat> resultado = new ArrayList<>();

        DatoMat inicio = new DatoMat();
        float porcen = 0;
        /*
        System.out.println("Difusa.crearMatriz() " + res.get(0));
        System.out.println("Difusa.crearMatriz() " + res.get(1));
        System.out.println("Difusa.crearMatriz() " + res.get(2));
        */
        for (int i = 0; i < res.size(); i++) 
        {
            porcen = 0;
            for (int j = 0; j < Mat.size(); j++) 
            {
                if (Mat.get(j).getValor() == res.get(i)) 
                {
                    if (porcen < Mat.get(j).porcentaje) 
                    {
                        porcen = Mat.get(j).porcentaje;
                    }
                }
            }
            inicio = new DatoMat(res.get(i),porcen);
            inicio.valor = res.get(i);
            resultado.add(inicio);
        }
        return resultado;
    }

    //*/    // toda esta cosa era para hacer aparentemente mas de lo necesario
    /*
    static List<DatoMat> porcentajesResultado(List<List<DatoMat>> listas,  List<String> res) {
        List<DatoMat> matriz = new ArrayList<DatoMat>();
        boolean ultimo= false;
        List<DatoMat> datos = new ArrayList<DatoMat>();
        MatYDato myd;
        for (int a = 0 ; a < res.size() ; a ++)
        {
//            System.out.println("Difusa.crearMatriz() " + res.get(a));
            DatoMat dm = new DatoMat(res.get(a),0);
            datos.add(dm);
        }
        
        // aun se tiene que retornar la matriz completa, ya que se le iran sumando dimensiones
        myd = revisarDimension(listas.get(0), listas.get(1), datos,ultimo);
        matriz = myd.matriz;
        datos = myd.respuesta;
        
//        System.out.println(matriz + "\n---------------------------\n"+datos+ "\n---------------------------\n"+ "\n---------------------------\n");
//        System.out.println("\n---------------------------\n"+ "\n---------------------------\n");
        
        for (int a = 2; a < listas.size(); a++) {
            if (a == listas.size()-1) ultimo = true;
            
            myd = revisarDimension(matriz, listas.get(a), datos,ultimo);
            matriz = myd.matriz;
            datos = myd.respuesta;
            
//            System.out.println("\n---------------------------\n"+ "\n---------------------------\n");
//            System.out.println(matriz + "\n---------------------------\n"+datos+ "\n---------------------------\n"+ "\n---------------------------\n");
        }
        
        System.out.println(matriz);
        
        System.out.println("\n--------------------------------------\n");
        
        System.out.println(datos);
        return datos;
    }

    static MatYDato revisarDimension(List<DatoMat> V1, List<DatoMat> V2,  List<DatoMat> res,boolean revisarVal) {

        List<DatoMat> matriz = new ArrayList<DatoMat>();
        
        int tam = res.size();
        
        float corte1 = 10*V1.size() / tam ;
        float corte2 = 10*V2.size() / tam ;
        System.out.println(V1.size() +"    "+tam +"   el corte es : "+corte1/10+"-------------------------\n");
        System.out.println(V2.size() +"    "+tam +"   el corte es : "+corte2/10+"-------------------------\n");
        for (int a = 0; a < V1.size(); a++) {
            
            for (int b = 0; b < V2.size(); b++) {
                

                DatoMat dm = new DatoMat();

                DatoMat dm2 = new DatoMat();

                dm.copyDM(V1.get(a));
                dm2.copyDM(V2.get(b));
                
                //System.out.print(dm+"+"+dm2+"\n");
                dm.addV(dm2);
                System.out.println("---begin---");
//                System.out.println(dm);
                
                if (revisarVal) {
                    boolean enc = false;
                    int pos = 0 ;
                    float posib = 0 ;
                    
                    for (int c = 0; c < tam; c++) {
                        
                        float inf1 = corte1 * c / 10;
                        float inf2 = corte2 * c / 10;
                        
                        float sup1 = corte1 * (c + 1) / 10;
                        float sup2 = corte1 * (c + 1) / 10;
                        
                        System.out.println("------" + inf1 + "  " + a + "  " + sup1);
                        System.out.println("------" + inf2 + "  " + b + "  " + sup2);

                        if ( inf1 <= b || corte1 * c / 10 <= a) {
                            System.out.println("  hola  " + res.get(c).categorias.get(0));
                            dm.setValor(res.get(c).categorias.get(0));
//                        System.out.println("  hola 22  " + dm.getValor());
                            enc = true;
                            posib = dm.porcentaje;
                            pos = c;
                        }
                    }
                    
                    if (enc) {
                        if (dm.porcentaje > res.get(pos).porcentaje) {
                            res.get(pos).modificarProbabilidad(dm.porcentaje);
                            System.out.println("------------------" + dm + "        " + dm.porcentaje + "   " + dm.getValor() + "\n");
                        }
                    }
                }
                
                System.out.println("end =------------------------");
                //System.out.print(dm+"\n");
                matriz.add(dm);
            }
        }
        
        MatYDato myd = new MatYDato(matriz, res);
        
        return myd;
    }
    //*/
    
    
    /*
    
    //Buscar el mayor, en el caso de que hayan dos con el mismo nombre en la matriz escoge el valor mayor
    static List<DatoMat> unificar(List<DatoMat> Mat, List<String> res) {
        List<DatoMat> resultado = new ArrayList<>();
        List<DatoMat> datos = new ArrayList<>(); 
        DatoMat inicio = new DatoMat();
        float porcen = 0;
        
        int cortes = res.size() ;
        
        // se crea una lista para los vectores sobre los que se sumaran los porcentajes
        for (int a = 0 ; a < res.size() ; a ++)
        {
            System.out.println("Difusa.crearMatriz() " + res.get(a));
            DatoMat dm = new DatoMat(res.get(a),0);
            datos.add(dm);
        }

        for (int j = 0; j < Mat.size(); j++) {
            
            
        }
        return resultado;
    }
    static List<DatoMat> crearMatriz(List<List<DatoMat>> listas) {
        List<DatoMat> matriz = new ArrayList<DatoMat>();

        matriz = crearMatriz(listas.get(0), listas.get(1));

        for (int a = 2; a < listas.size(); a++) {
            matriz = crearMatriz(matriz, listas.get(a));
        }
        return matriz;
    }

    static List<DatoMat> crearMatriz(List<DatoMat> V1, List<DatoMat> V2) {

        List<DatoMat> matriz = new ArrayList<DatoMat>();
        int i = (V2.size() / 2), j = (V1.size() / 2);
        for (int a = 0; a < V1.size(); a++) {

            for (int b = 0; b < V2.size(); b++) {
                DatoMat dm = new DatoMat();

                DatoMat dm2 = new DatoMat();

                dm.copyDM(V1.get(a));
                dm2.copyDM(V2.get(b));
                
                //System.out.print(dm+"+"+dm2+"\n");
                dm.addV(dm2);

                //System.out.print(dm+"\n");
                matriz.add(dm);
            }
        }
        return matriz;
    }
*/
    static DatoMat conseguirMayor(List<DatoMat> datos) {
        DatoMat dm = null;
        for (int a = 0; a < datos.size(); a++) {
            if (a == 0) {
                dm = datos.get(a);
            } else {
                if (dm.porcentaje < datos.get(a).porcentaje) {
                    dm = datos.get(a);
                }
            }
        }
        return dm;
    }

    static List<DatoMat> conseguirMayorLista(List<DatoMat> datos) {
        List<DatoMat> dm = new ArrayList<DatoMat>();
        float porc = 0;
        for (int a = 0; a < datos.size(); a++) {
            if (a == 0) {
                porc = datos.get(a).porcentaje;
                dm.add(datos.get(a));
            } else {
                if (porc < datos.get(a).porcentaje) {
                    porc = datos.get(a).porcentaje;
                    dm = new ArrayList<DatoMat>();
                    dm.add(datos.get(a));
                } else if (porc == datos.get(a).porcentaje) {
                    dm.add(datos.get(a));
                }
            }
        }
        return dm;
    }
}
