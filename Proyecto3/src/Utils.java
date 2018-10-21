
import java.util.ArrayList;
import java.util.List;



public class Utils {
    
    
    /*static List<DatoMat> crearMatriz(List<List<DatoMat>> listas, List<String> res) {
        List<DatoMat> matriz = new ArrayList<DatoMat>();

        matriz = crearMatriz(listas.get(0), listas.get(1), res);

        for (int a = 2; a < listas.size(); a++) {
            matriz = crearMatriz(matriz, listas.get(a), res);
        }
        return matriz;
    }

    static List<DatoMat> crearMatriz(List<DatoMat> V1, List<DatoMat> V2, List<String> res) {

        List<DatoMat> matriz = new ArrayList<DatoMat>();
        int i = (V2.size() / 2), j = (V1.size() / 2);
        for (int a = 0; a < V1.size(); a++) {

            for (int b = 0; b < V2.size(); b++) {
                DatoMat dm = new DatoMat();

                DatoMat dm2 = new DatoMat();

                dm.copyDM(V1.get(a));
                dm2.copyDM(V2.get(b));

                int aa = (V2.size() / 2) + i;
                int bb = (V1.size() / 2) - j;
                if (bb < 0) {
                    bb = bb * -1;
                }
//                                System.out.println("Difusa.crearMatriz()"+bb+" "+aa);
                if (b == aa && a == bb) {
                    //0.2
//                                    System.out.println("Normal "+bb+" "+aa);
                    dm.setValor(res.get(res.size() / 2));
                    i--;
                    j++;
                } else if (b > V1.size() / 2 && a > V2.size() / 2 || b == V1.size() / 2 && a > V2.size() / 2 || b > V1.size() / 2 && a == V2.size() / 2) {
                    dm.setValor(res.get(res.size() - 1));
                } else if (b < V1.size() / 2 && a < V2.size() / 2 || b == V1.size() / 2 && a < V2.size() / 2 || b < V1.size() / 2 && a == V2.size() / 2) {
                    dm.setValor(res.get(0));
                }

                //System.out.print(dm+"+"+dm2+"\n");
                dm.addV(dm2);

                //System.out.print(dm+"\n");
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

        System.out.println("Difusa.crearMatriz() " + res.get(0));
        System.out.println("Difusa.crearMatriz() " + res.get(1));
        System.out.println("Difusa.crearMatriz() " + res.get(2));

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
    */
    
    //Buscar el mayor, en el caso de que hayan dos con el mismo nombre en la matriz escoge el valor mayor
    static List<DatoMat> unificar(List<DatoMat> Mat, List<String> res) {
        List<DatoMat> resultado = new ArrayList<>();

        DatoMat inicio = new DatoMat();
        float porcen = 0;

        System.out.println("Difusa.crearMatriz() " + res.get(0));
        System.out.println("Difusa.crearMatriz() " + res.get(1));
        System.out.println("Difusa.crearMatriz() " + res.get(2));

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
