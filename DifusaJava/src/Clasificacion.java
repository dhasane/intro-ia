import java.util.List;

public class Clasificacion {

	private String nombre;
	List<Pertenencia> pert;


	// pos crea el asunto / le da nombre
	Clasificacion(String nom)
	{
		this.nombre = nom;
	}

	// retorna el nombre de la Clasificacion
	String getNombre()
	{
		return this.nombre;
	}

	// crea e inserta una nueva Pertenencia
	// retorna true, al haber insertado la Pertenencia
	boolean insertarPertenencia(String nom, float i, float it, float ft,float f )
	{
		Pertenencia npert = new Pertenencia(nom, i, it, ft, f );
		this.pert.add(npert);
		return true;
	}

	// imprimir sigue imprimiendo :V
	void imprimir()
	{
		System.out.println(this.nombre + "\n");

		for (int a = 0; a < this.pert.size() ; a++)
		{
			System.out.println("   " +  this.pert.get(a).getNombre());
			System.out.println(" " + this.pert.get(a).limites());
			System.out.println("\n");
		}
	}

	// fuzzyfica los datos
	// debe retornar lista de floats/ por ahora retorna el getCentro de masa supuesto e imprime los datos
	float fuzzy(float val)
	{
		System.out.println("\n" + this.nombre + "\n");
		float eval = 0;
		float cm = 0; // getCentro de masa

		for (int a = 0; a < this.pert.size() ; a++)
		{
			eval = this.pert.get(a).evaluar(val);

			// getCentro de masa
			float cct = (this.pert.get(a).getCentro())*eval;

			//System.out.println( + " :" + cct + "\n";
			cm += cct;

			System.out.println("   " +  this.pert.get(a).getNombre());
			System.out.println(" " + eval  + "\n");

			//System.out.println( + "\n";
		}

		System.out.println("getCentro de masa supuesto en : " +  cm +  "\n");

		return cm;
	}

	// retorna el getCentro de la Pertenencia
	float getCentro(String val)
	{
		for (int a = 0; a < this.pert.size() ; a++)
		{
			if(this.pert.get(a).getNombre() == val)
			{
				return (this.pert.get(a).getCentro());
			}
		}
		return 0;
	}

}
