
import java.util.List;
import java.util.*;

public class Clasificacion {

    private String nombre;
    List<Pertenencia> pert;

    // pos crea el asunto / le da nombre
    Clasificacion(String nom) {
        this.nombre = nom;
        pert = new ArrayList<Pertenencia>();
    }

    // retorna el nombre de la Clasificacion
    String getNombre() {
        return this.nombre;
    }

    // crea e inserta una nueva Pertenencia
    // retorna true, al haber insertado la Pertenencia
    boolean insertarPertenencia(String nom, float i, float it, float ft, float f) {
        Pertenencia npert = new Pertenencia(nom, i, it, ft, f);
        this.pert.add(npert);
        return true;
    }

    // imprimir imprime :V
    void imprimir() {
        System.out.println(this.nombre + "\n");

        for (int a = 0; a < this.pert.size(); a++) {
            System.out.println("   " + this.pert.get(a).getNombre());
            System.out.println("    " + this.pert.get(a).limites());
            System.out.println("\n");
        }
    }

    // fuzzyfica los datos
    // retorna lista de floats
    List<DatoMat> fuzzy(float val) {
        List<DatoMat> resultados = new ArrayList<DatoMat>();
        float eval = 0;
        DatoMat dm;
        for (int a = 0; a < this.pert.size(); a++) {
            eval = this.pert.get(a).evaluar(val);

            dm = new DatoMat(this.pert.get(a).getNombre(), eval);

            resultados.add(dm);
        }
        return resultados;
    }

    // retorna el Centro de la Pertenencia
    float getCentro(String val) {
        for (int a = 0; a < this.pert.size(); a++) {
            if (this.pert.get(a).getNombre() == val) {
                return (this.pert.get(a).getCentro());
            }
        }
        return 0;
    }

    List<String> getCategorias() {
        List<String> cat = new ArrayList<String>();

        for (int a = 0; a < this.pert.size(); a++) {
            cat.add(this.pert.get(a).getNombre());
        }

        return cat;
    }

    // consigue el centro de masa
    String getResultado(List<DatoMat> resultado) {
        float cm = 0;
        System.out.println(resultado+"\n");
        for(int a = 0 ; a < resultado.size() ; a++)
        {
            float centro = getCentro(resultado.get(a).categorias.get(0) );
            float porcent = resultado.get(a).porcentaje;
            System.out.println("centro figura : "+centro+" * "+porcent);
            // multiplica el centro de la figura por su porcentaje
            cm += centro*porcent;
        }

        System.out.println("centro de masa final : "+cm);
        return Utils.conseguirMayor(fuzzy(cm)).categorias.get(0);
    }

}
