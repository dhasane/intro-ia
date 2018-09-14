#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

// compara 2 char*
bool comparar(char* cc1, char* cc2)
{
	int tam = strlen(cc1);
	int cant = 0 ;

	for(int a = 0 ; a < tam ; a ++)
	{

		if(cc1[a] == cc2[a])
		{
			cant++;
		}
	}

	if( cant == tam)
	{
		return true;
	}
	else
	{
		return false;
	}

}

class Tipo{

	public:

	char * nombre;
	string nomVar;
	bool esVar; // guarda en caso de ser variable
	
	Tipo()
	{
	}
	
//	inicializador
	Tipo(string nom)
	{
		this->nombre = new char[nom.length()+1];
		strcpy(this->nombre , nom.c_str());
		//this->nombre = nom);

		if (nombre[0] > 64 && nombre[0] < 91)
		{
			esVar = true;
			nomVar = this->nombre;
		}
		else
		{
			esVar = false;
			nomVar = " ";
		}
	}

//	copia un valor de otro Tipo, solo en caso de este ser una variable (mayuscula)
	bool copiar(Tipo t)
	{
		if(esVar && !t.esVar)
		{
			nombre = t.nombre;
			return true;
		}
		
		return false;
	}

//	compara dos nombres
	/*bool comparar(Tipo tt)
	{
//		cout<<"-------"<<endl;
		int tam = strlen(this->nombre);
		for(int a = 0 ; a < tam ; a ++)
		{
			cout <<this->nombre[a] <<"  "<< tt.nombre[a]<<endl;
			if(this->nombre[a] != tt.nombre[a])
			{
				return false;
			}
		}

		return true;
	}*/
};

class Axioma{

	//private:
	public:

	string nombre;
	int ndatos;
	vector<Tipo> valores;
	// Ej: del axioma conquistador(marco,roma)  nombre = conquistador  ,  valores = [marco,roma] con ndatos = 2 (el tamaño de la lista valores)

	// se terminaria creando como :
	// axioma(conquistador, [marco, roma] )


	public:

//	inicializador
	Axioma( string nom, vector<Tipo> val)
	{
		this->nombre  = nom;

		this->ndatos  = val.size();

		this->valores = val;

	}

//	imprime el axioma
	void imprimir()
	{

		cout<<this->nombre<<" : ";
		vector<Tipo>::iterator it;// = this->valores.begin();

		for(it = this->valores.begin(); it != this->valores.end(); it++ )
		{
        	cout<<  it->nombre << ", ";
		}
	}

//	compara los dos axiomas y en caso que uno de estos tenga variabes, = > copia los datos de dato a Variable
	bool rellenarDatos(Axioma ax2 , vector<Tipo> *variables)
	{
		vector<Tipo>::iterator it;
		vector<Tipo>::iterator it2;

		
		it = this->valores.begin();
		it2 = ax2.valores.begin();

		//bool ret = false;
		int nVars = 0;
		int cantidadVariables = 0 ;
		
		
		if(compararAxiomas(ax2))
		{
			for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
			{
				if(it->copiar(*it2)) 
				{
					cantidadVariables++;
					
					cout<<it->nomVar<<" : "<<it2->nombre<<endl;
					Tipo nvar;
					nvar.nomVar = it->nomVar;
					nvar.nombre = it2->nombre;
					nvar.esVar = false;
					
					if(enVariables(nvar,variables))
					{
						nVars++;
					}
					
				}
			}
		}
		
		if (nVars == cantidadVariables)
		{
			return true;
		}
		else
		{
			return false;
		}	
		
		//return ret; 
	}
	
	
	//reconoce si una variable esta en la lista de variables 
	// en caso de estar, pero tener un nombre(valor) distinto, retorna false
	// si tiene nombre igual retorna true 
	// en caso de no estar presente, ingresa la variable a la lista 
	bool enVariables(Tipo &tipo , vector<Tipo> *vars)
	{
		
		vector<Tipo>::iterator it = vars->begin();
		bool presente = false;
		//bool ret = false;
		
		for(it ; it != vars->end() ; it ++)
		{
			if(it->nomVar == tipo.nomVar ) 
			{
				
				if ( it->nombre != tipo.nombre)
				{
					return false;
				}
				
				presente = true; 
			}
			
		}
		
		if(!presente)// al no ser encontrado, se agrega a la lista de variables
		{
			vars->push_back(tipo);
		}
		
		return true;
	}
	bool compararAxiomas(Axioma ax2)
	{
		
		vector<Tipo>::iterator it;
		vector<Tipo>::iterator it2;

		
		//bool vabien = true;
		
		it = this->valores.begin();
		it2 = ax2.valores.begin();

		

		// verifica que todos los datos que no son variables sean iguales
		for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
		{

			if ( !  ( (it->esVar)  || (it2->esVar) ) &&  !comparar( it->nombre , it2->nombre )  )
			{
				return false;
				//it == this->valores.end();
			}
			
		}
		
		return true;
		
		
	}
	

	
	
};

class Predicado
{
	public:
	vector<Axioma> axiomas;
	//vector<Tipo> variables;

//	ingresa un axioma nuevo solo en caso de que o sea con un nombre nuevo
//  o tenga la misma cantidad de argumentos que el axioma con el mismo nombre
//  retorna verdadero si logro ingresar el axioma

	bool ingresar(string nom, vector<Tipo> val)
	{
		Axioma ax(nom,val);

		vector<Axioma>::iterator it;// = this->valores.begin();

		bool ret = true;

		for(it = this->axiomas.begin(); it != this->axiomas.end(); it++ )
		{
  		  	// en caso de que tengan el mismo nombre, pero diferente cantidad de argumentos, no se agregara a la lista
        	if( it->nombre == ax.nombre && it->ndatos != ax.ndatos)
        	{
        		ret = false;
			}

		}

		if(ret)
		{
			axiomas.push_back(ax);
		}

		return ret;
	}

//	imprime los axiomas del predicado
	void imprimir()
	{
		vector<Axioma>::iterator it;// = this->valores.begin();


		for(it = this->axiomas.begin(); it != this->axiomas.end(); it++ )
		{
  		  	it->imprimir();
			cout<<" | ";
		}
		
	}

	/*
//	esta es la funcion que debera ser con recursividad, por ahora esta con fuerza bruta, para probar funcionaiento de
//	otras funciones
	void rellenarDatosFB(Predicado cc2)
	{
		vector<Axioma>::iterator it;// = this->valores.begin();


		vector<Axioma>::iterator it2;// = this->valores.begin();


		for(it = this->axiomas.begin(); it != this->axiomas.end(); it++ )
		{
//  		  	it->imprimir();
			for(it2 = cc2.axiomas.begin(); it2 != cc2.axiomas.end(); it2++ )
			{
//  			  	it2->imprimir();

				if(it->nombre == it2->nombre && it->ndatos == it2->ndatos)
				{
					//it->rellenarDatos(*it2);
				}
			}
		}

	}
*/
	
	void buscDatos(vector<Axioma>::iterator it, vector<Axioma>::iterator it2 , Predicado &cc2 , vector<Tipo> *variables)
	{
		

		
		
		if (it->rellenarDatos(*it2 , variables))
		{
			
			// falta
			
		}
		else
		{
			
		}
		
		if(it + 1 != this->axiomas.end())
		{
			it++;
		}
		if(it2 + 1 != cc2.axiomas.end() )
		{
			it2++;
			
		}
		
		if(it +1 == this->axiomas.end() && it2 +1  == cc2.axiomas.end() )
		{
			cout<<endl<<"fin"<<endl;
		}
		else
		{
			cout<<endl<<it->nombre<<" "<< it2->nombre<<endl;
			buscDatos(it,it2,cc2, variables);
		}
		
		
		
		
		

	}
	
	void buscarDatos( Predicado &cc2 )
	{
		vector<Tipo> variables;
		vector<Axioma>::iterator it = this->axiomas.begin();
		vector<Axioma>::iterator it2 = cc2.axiomas.begin();
		
		buscDatos(it,it2 ,cc2, &variables);
	}
	
	
	/*
//Sirve con solo un parametro pompeyano(a) -> romano(a)     -romano tiene A, por lo que fucionaria
//Falta con dos o mas parametros: gobernante(Y)^hombre(X)->odia(x,Y)       -Odia tiene X y Y
	bool comprobarAxiomas(Axioma* axioma, string variable){
	    //Al principio se pasaria el que se quiere mirar ej: romano(a)
		
        vector<Axioma>::iterator it1 = axioma->causas.begin();

        int cantidadAxiomas = causas.size();
        int cantidadVerdades = 0;
        while(it1 != causas.end()){
            Axioma* axiomaComprobar = &(*it1); //Asignarle el axioma

            if(comprobarSiEsta(axiomaComprobar,variable) == true){
                cantidadVerdades++;
            }
            it1++;
        }

        if(cantidadAxiomas == cantidadVerdades){
            comprobacion = true;
        }
        else{
            comprobacion = false;
        }

        return comprobacion;
	}

    bool comprobarSiEsta(Axioma* axioma, string buscar){
        if(axioma->causas.size() == 0){
            vector<Tipo>:: iterator it1 = axioma->valores.begin();

            while(it1 != valores.end()){
                if(buscar == it1->nombre){
                    return true;
                }
                it1++;
            }
        }
        else{
            return comprobarAxiomas(axioma,buscar);
        }


        return false;
    }*/

};


class Conjunto{
	
	vector<Predicado> predicados;
	
	public:
	
	Conjunto()
	{
	}
	
	void imprimir()
	{
		for(int a = 0 ; a < predicados.size() ; a++)
		{
			predicados[a].imprimir();
			cout<<endl;
		}
	}
	
	void ingresar(Predicado pred)
	{
		predicados.push_back(pred);
	}
	
	void rellenarDatos()
	{
		for(int a = 0 ; a < predicados.size() ; a++)
		{
			for(int b = 0 ; b < predicados.size() ; b++)
			{
				predicados[a].buscarDatos(predicados[b]);
				//rellenarDatosFB(predicados[b]);
			}
		}
	}
	
	
	
	Predicado leerLineaSimple(Predicado set, string linea){

		int a = 0, b = 0, end = linea.size();

		while(linea[b] != '(' && b < end )
			b++;

		string name = linea.substr(a,b);
		b++;

		vector<Tipo> fields;

		while(a+b < end){
			a = a+b;
			b = 0;
			while(linea[a+b] != ',' && linea[a+b] != ')' && a+b < end)
				b++;
	
			fields.push_back(Tipo(linea.substr(a,b)));
			b++;
		}
		set.ingresar(name,fields);
		return set;
	}

	Predicado leerLinea(Predicado set, string linea){

		int a = 0, b = 0, end = linea.size();

		while(a+b < end){
			a = b;
			while(linea[b] != ')' && b < end)
				b++;

			//cout<<linea.substr(a,b+1)<<endl;
			if(linea[b] == ')'){
				b++;
				set = leerLineaSimple(set,linea.substr(a,b));
				b++;
				while(linea[b] == ' ')
					b++;
			}
		}

		return set;
	}
	
	void ingresarLinea(string linea)
	{
		Predicado pred;
		pred = leerLinea(pred,linea);
		ingresar(pred);
	}
	
};


// axioma(tipo,tipo,tipo)


//void insertarAList

Predicado leerLinea(Predicado set, string linea);
Predicado leerLineaSimple(Predicado set, string linea);

int main()
{

	//cout<< "hola"<<endl;
	//string val[] = {"marco","roma"};
	//vector<Tipo> val;


//	cout<< sizeof(val)/sizeof(*val)<<endl<<endl;
	//string nom = "conquistador";


	Conjunto conj;

	/*val.clear();
	val.push_back(Tipo("marco"));
	val.push_back(Tipo("rusia"));
	val.push_back(Tipo("hola"));
	conj.ingresar("conquistador" ,val);

	val.clear();
	val.push_back(Tipo("marco"));
	val.push_back(Tipo("M"));
	val.push_back(Tipo("hola"));
	conj.ingresar("conquistador",val);

	val.clear();
	val.push_back(Tipo("marco"));
	val.push_back(Tipo("roma"));
	val.push_back(Tipo("hola"));
	conj.ingresar("conquistador" ,val);

	val.clear();
	val.push_back(Tipo("mao"));
	val.push_back(Tipo("M"));
	conj.ingresar("conq",val);
*/
	
	int numpred = 0 ;
	cout<<"cantidad de predicados a ingresar :";
	cin>>numpred;
	
	
	string line;
	cout<<"ingrese algo: \n";
	for(int a = 0 ; a < numpred ; a ++)
	{
		
		
		cout<<"> ";
		cin>>line;
		
		conj.ingresarLinea(line);
		
	}
	
	
	
	cout<<endl<<endl<<"antes --------------------------------------------------------"<<endl<<endl;
	
	
	
	conj.imprimir();

	conj.rellenarDatos();



	cout<<endl<<endl<<"despues --------------------------------------------------------"<<endl<<endl;
	
	
	
	conj.imprimir();
	return 0;
}


