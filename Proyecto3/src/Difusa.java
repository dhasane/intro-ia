import java.util.List;
import java.util.*;

public class Difusa {

	private List<Clasificacion> clasif;

	Difusa(){
		clasif = new ArrayList<Clasificacion>();
	}


	static List<DatoMat> crearMatriz(List<DatoMat> V1, List<DatoMat> V2)
	{
		List<DatoMat> matriz = new ArrayList<DatoMat>();
		for (int a = 0 ; a < V1.size() ; a ++)
		{
			
			for(int b = 0 ; b < V2.size() ; b++)
			{
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


	// fuzzyfica el asunto 
	// fuzzyfica una Clasificacion especifica con un valor dado
	List<DatoMat> fuzzy(String nom , float val)
	{
      //List<DatoMat> resultados = new List<DatoMat>(20,1);

		for (int a = 0; a < this.clasif.size() ; a++)
		{
			if(this.clasif.get(a).getNombre() == nom)
			{
				return this.clasif.get(a).fuzzy(val);
			}
		}
      return null; //resultados;
	}

	// crea una nueva Clasificacion, a la que solo le da nombre, 
	// y la ingresa a la lista
	boolean insertarClasificacion(String nom)
	{
		boolean found = false;
		for (int a = 0; a < this.clasif.size() ; a++)
		{
			if(this.clasif.get(a).getNombre() == nom)
			{
				found = true;
			}
		}

		if(!found)
		{
			Clasificacion cl = new Clasificacion(nom);
			this.clasif.add(cl);
		}

		return !found;

	}

	// inserta una nueva Pertenencia a una clasificacion especifica
	// retorna true, en caso de poder insertar la Pertenencia
	boolean insertarAClasificacion(String nom, String nomprt, float i, float it, float ft,float f )
	{
		for (int a = 0; a < this.clasif.size() ; a++)
		{
			if(this.clasif.get(a).getNombre() == nom)
			{
				return this.clasif.get(a).insertarPertenencia(nomprt,i,it,ft,f);
			}
		}
		return false;
	}

	// imprime :v
	void imprimir()
	{
		for (int a = 0; a < this.clasif.size() ; a++)
		{
			this.clasif.get(a).imprimir();
		}
	}

	// funcion como por jugar, el nombre ya lo describe
	float quieroAlgoEntre(String nom, String val1, String val2)
	{
		for (int a = 0; a < this.clasif.size() ; a++)
		{
			if(this.clasif.get(a).getNombre() == nom)
			{
				return (this.clasif.get(a).getCentro(val1) + this.clasif.get(a).getCentro(val2))/2;
			}
		}
		return 0;
	}

	// consigue el getCentro de una Pertenencia especifica,
	// de una Clasificacion especifica
	float conseguirValor(String nom, String val)
	{
		for (int a = 0; a < this.clasif.size() ; a++)
		{
			if(this.clasif.get(a).getNombre() == nom)
			{
				return this.clasif.get(a).getCentro(val);
			}
		}

		return 0;
	}
}
