import java.util.List;
import java.util.*;

public class Difusa {

	private List<Clasificacion> clasif;

	Difusa(){
		clasif = new ArrayList<Clasificacion>();
	}


	static List<DatoMat> crearMatriz(List<List<DatoMat> > listas, List<DatoMat> res)
	{
		List<DatoMat> matriz = new ArrayList<DatoMat>();

		matriz = Difusa.crearMatriz(listas.get(0),listas.get(1),res);

		for (int a = 2 ; a < listas.size() ; a ++)
		{
			matriz = Difusa.crearMatriz(matriz,listas.get(a),res);
		}

		return matriz;
	}

	static List<DatoMat> crearMatriz(List<DatoMat> V1, List<DatoMat> V2,List<DatoMat> res)
	{   

		List<DatoMat> matriz = new ArrayList<DatoMat>();
                int i = (V2.size()/2) , j = (V1.size()/2);
		for (int a = 0 ; a < V1.size() ; a ++)
		{
			
			for(int b = 0 ; b < V2.size() ; b++)
			{
				DatoMat dm = new DatoMat();
				
				DatoMat dm2 = new DatoMat();

				dm.copyDM(V1.get(a));
				dm2.copyDM(V2.get(b));
                                
                                int aa= (V2.size()/2)+i;
                                int bb= (V1.size()/2)-j;
                                if(bb<0){
                                    bb= bb*-1;
                                }
                                System.out.println("Difusa.crearMatriz()"+bb+" "+aa);
                                if(b==aa && a==bb ){
                                    //0.2
                                    System.out.println("Normal "+bb+" "+aa);
                                    dm.setValor(res.get(res.size()/2).categorias.get(0));
                                    i--;
                                    j++;
                                } 
                                else if(b> V1.size()/2 && a>V2.size()/2 || b== V1.size()/2 && a>V2.size()/2 || b> V1.size()/2 && a==V2.size()/2){
                                    dm.setValor(res.get(res.size()-1).categorias.get(0));
                                }
                                else if(b< V1.size()/2 && a<V2.size()/2 || b== V1.size()/2 && a<V2.size()/2 || b< V1.size()/2 && a==V2.size()/2 ){
                                    dm.setValor(res.get(0).categorias.get(0));
                                }
                                
				//System.out.print(dm+"+"+dm2+"\n");

				dm.addV(dm2);

				//System.out.print(dm+"\n");
				matriz.add(dm);
			}
		}

		return matriz;
	}

	static DatoMat conseguirMayor(List<DatoMat> datos)
	{
		DatoMat dm = null;
		for (int a = 0 ; a < datos.size() ; a ++)
		{
			if(a == 0)
			{
				dm = datos.get(a);
			}
			else
			{
				if(dm.porcentaje < datos.get(a).porcentaje)
				{
					dm = datos.get(a);
				}
			}
		}

		return dm;
	}

	static List<DatoMat> conseguirMayorLista(List<DatoMat> datos)
	{
		List<DatoMat> dm = new ArrayList<DatoMat>();
		float porc = 0;
		for (int a = 0 ; a < datos.size() ; a ++)
		{
			if(a == 0)
			{
				porc = datos.get(a).porcentaje;
				dm.add(datos.get(a));
			}
			else
			{
				if(porc < datos.get(a).porcentaje)
				{
					porc = datos.get(a).porcentaje;
					dm = new ArrayList<DatoMat>();
					dm.add(datos.get(a));
				}
				else if(porc == datos.get(a).porcentaje)
				{
					dm.add(datos.get(a));
				}
			}
		}

		return dm;
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
        
        //Buscar el mayor, en el caso de que hayan dos con el mismo nombre en la matriz escoge el valor mayor
        static List<DatoMat> unificar(List<DatoMat> Mat, List<String> res){
            List<DatoMat> resultado = new ArrayList<>();
            
            DatoMat inicio = new DatoMat();
            float porcen =0;
            
            
            System.out.println("Difusa.crearMatriz() "+res.get(0));
            System.out.println("Difusa.crearMatriz() "+res.get(1));
            System.out.println("Difusa.crearMatriz() "+res.get(2));
            
            
            
            for(int i=0; i<res.size(); i++){
                inicio = new DatoMat();
                porcen =0;
                inicio.valor = res.get(i);

                for(int j=0; j<Mat.size();j++){
                    if(Mat.get(j).getValor()==res.get(i)){
                       if(porcen< Mat.get(j).porcentaje){
                           
                           porcen = Mat.get(j).porcentaje;
                       }
                    }
                }
                inicio.porcentaje = porcen;
                resultado.add(inicio);
            }
            
            return resultado;
        }
}
