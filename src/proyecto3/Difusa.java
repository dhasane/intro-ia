
import java.util.List;
import java.util.*;

public class Difusa {

    private List<Clasificacion> clasif;

    Difusa() {
        clasif = new ArrayList<Clasificacion>();
    }

    // fuzzyfica el asunto 
    // fuzzyfica una Clasificacion especifica con un valor dado
    List<DatoMat> fuzzy(String nom, float val) {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {
                return this.clasif.get(a).fuzzy(val);
            }
        }
        return null;
    }

    boolean catPresente(String nom)
    {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {
                return true;
            }
        }
        return false;
    }

    // crea una nueva Clasificacion, a la que solo le da nombre, 
    // y la ingresa a la lista
    boolean insertarClasificacion(String nom) {
        boolean found = false;
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {
                found = true;
            }
        }

        if (!found) {
            Clasificacion cl = new Clasificacion(nom);
            this.clasif.add(cl);
        }
        return !found;
    }

    // inserta una nueva Pertenencia a una clasificacion especifica
    // retorna true, en caso de poder insertar la Pertenencia
    boolean insertarAClasificacion(String nom, String nomprt, float i, float it, float ft, float f) {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {
                return this.clasif.get(a).insertarPertenencia(nomprt, i, it, ft, f);
            }
        }
        return false;
    }

    // imprime :v
    void imprimir() {
        for (int a = 0; a < this.clasif.size(); a++) {
            this.clasif.get(a).imprimir();
        }
    }

    // funcion como por jugar, el nombre ya lo describe
    float quieroAlgoEntre(String nom, String val1, String val2) {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {

                float v1 = this.clasif.get(a).getCentro(val1);
                float v2 = this.clasif.get(a).getCentro(val2);

                float prom = v1 + v2 / 2;
                System.out.println(v1 +"      "+ v2 + "     ="+prom);
                return prom;
            }
        }
        return 0;
    }
    
    float quiero(String nom, String val1) {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {

                float v1 = this.clasif.get(a).getCentro(val1);
                System.out.println(v1);
                return v1;
            }
        }
        return 0;
    }
    
    // consigue el getCentro de una Pertenencia especifica,
    // de una Clasificacion especifica
    float conseguirValor(String nom, String val) {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {
                return this.clasif.get(a).getCentro(val);
            }
        }

        return 0;
    }

    List<String> getCategorias(String nom) {
        for (int a = 0; a < this.clasif.size(); a++) {
            if (this.clasif.get(a).getNombre().equals(nom)) {
                return this.clasif.get(a).getCategorias();
            }
        }

        return null;
    }

    
}