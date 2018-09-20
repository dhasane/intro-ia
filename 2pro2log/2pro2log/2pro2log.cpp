#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

// busca si hay un valor dentro de una lista
bool presenteEn(vector<string> posibles, string nval)
{
	vector<string>::iterator it;

	for(it = posibles.begin(); it != posibles.end(); it++ )
	{
		if(*it == nval)
		{
			return true;
		}
	}
	return false;
}

class Value{

	public:

	string nombre;
	bool esVar; // guarda en caso de ser variable
	bool rellenado;

	// guarda una lista de posibles valores a tomar, en caso de ser variable
	vector<string> posibles;

	// inicializador
	Value(string nom)
	{
		this->nombre = new char[nom.length()+1];
		this->nombre = nom;

		if (nombre[0] > 64 && nombre[0] < 91)
		{
			esVar = true;
		}
		else
		{
			esVar = false;
		}

		rellenado = false;
	}

	// compara el nombre de dos Values
	bool compararNombre(Value v2)
	{
		if(this->nombre == (v2.nombre))
		{
			return true;
		}
		return false;
	}

   //	copia un valor de otro Value, solo en caso de este ser una variable (mayuscula)
	bool copiar(Value t)
	{
		bool ret = false;

		if(esVar && !t.esVar)
		{
			if(!presenteEn(this->posibles, t.nombre))
			{
				ret = true;
				posibles.push_back(t.nombre);
			}
		}
		else if (esVar && t.posibles.size() > 0)
		{
			vector<string>::iterator it;
			for(it = t.posibles.begin(); it != t.posibles.end(); it++ )
			{
				if(!presenteEn(this->posibles, *it))
				{
					ret = true;
					posibles.push_back(*it);
				}
			}
		}
		return ret;
	}

	// impime el nombre del valor, y en caso de ser variable y tener distintas opciones, imprime todas las opciones
	void imprimir()
	{
		cout<<this->nombre ;

		if(this->esVar && this->posibles.size()>0)
		{
			cout<<":(";
			for(int a = 0 ; a < this->posibles.size() ; a ++)
			{
				Value subVal = this->posibles[a];
				cout<< subVal.nombre;

				if( a != this->posibles.size() - 1)	cout<<", ";
			}
			cout << ") ";
		}
	}
};

class Tupla{

	public:

	string nombre;
	int ndatos;
	vector<Value> valores;

	// inicializador
	Tupla( string nom, vector<Value> val)
	{
		this->nombre  = nom;

		this->ndatos  = val.size();

		this->valores = val;
	}

	// imprime los valores de la tupla
	void imprimir()
	{
		cout<<this->nombre<<" : ";
		vector<Value>::iterator it;

		for(it = this->valores.begin(); it != this->valores.end(); it++ )
		{
			it->imprimir();
			if( it + 1 != this->valores.end())cout<< ", ";
		}
	}

	// compara los dos axiomas y en caso que uno de estos tenga variabes, = > copia los datos de dato a Variable
	bool rellenarDatos(Tupla ax2)
	{
		if(this->nombre == ax2.nombre)
		{
			vector<Value>::iterator it;
			vector<Value>::iterator it2;

			it = this->valores.begin();
			it2 = ax2.valores.begin();
			int nVars = 0;
			int cantidadVariables = 0 ;

			for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
			{
				if(it->copiar(*it2))
				{
					it->rellenado = true;
				}
			}
		}
	}

	// verifica si la tupla tiene alguna variable
	bool tieneVariables()
	{
		vector<Value>::iterator it;

		for(it = this->valores.begin(); it != this->valores.end(); it++ )
		{
			if(it->esVar)
			{
				return true;
			}
		}
		return false;
	}
};

class Linea{
	public:
	int numero; // numero en la lista de conjunto
	vector<Tupla> tuplas;
	bool variables;// tiene o no variables

	// caso en el que todas las variables con el mismo nombre puedan tener los mismos valores
	bool valido;

	// inicializador
	Linea()
	{
		this->variables = false;
		this->valido = false;
	}

	// verifica si la linea tiene alguna variable
	void tieneVariables()
	{
		vector<Tupla>::iterator it;

		this->variables = false;

		for(it = this->tuplas.begin(); it != this->tuplas.end(); it++ )
		{
  		  	if(it->tieneVariables())
			{
				this->variables = true;
			}
		}
	}

	// ingresa una tupla nueva solo en caso de que o sea con un nombre nuevo
	// o tenga la misma cantidad de argumentos que la tupla con el mismo nombre
	bool ingresar(string nom, vector<Value> val)
	{
		Tupla ax(nom,val);
		vector<Tupla>::iterator it;
		bool ret = true;

		for(it = this->tuplas.begin(); it != this->tuplas.end(); it++ )
		{
  		  	// en caso de que tengan el mismo nombre, pero diferente cantidad de argumentos, no se agregara a la lista
        	if( it->nombre == ax.nombre && it->ndatos != ax.ndatos)
        	{
        		ret = false;
			}
		}

		if(ret)
		{
			tuplas.push_back(ax);
		}
		return ret;
	}

   //	imprime las tuplas del predicado
	void imprimir()
	{
		vector<Tupla>::iterator it;// = this->valores.begin();

		for(it = this->tuplas.begin(); it != this->tuplas.end(); it++ )
		{
  		  	it->imprimir();
			cout<<" | ";
		}
	}

	// vacia la lista de tuplas, usado para pruebas
	void clear()
	{
		tuplas.clear();
	}

	// copia datos de otras lineas, cuando las tuplas tengan el mismo nombre
	bool rellenarDatos( Linea &cc2 )
	{
		bool ret = false;

		if(!valido)
		{
			vector<Value> variables;
			vector<Tupla>::iterator it = this->tuplas.begin();
			vector<Tupla>::iterator it2 = cc2.tuplas.begin();

			for(it; it != this->tuplas.end() ; it++)
			{
				for (it2 = cc2.tuplas.begin(); it2 != cc2.tuplas.end(); it2 ++)
				{
					if(it->nombre == it2->nombre)
					{
						ret = ret || it->rellenarDatos(*it2);
						ret = ret || it2->rellenarDatos(*it);
					}
				}
			}
		}
		return ret;
	}

	// le da los mismo valores a todas las variables que tengan el mismo nombre dentro de una linea
	// llama a recCompletar
	bool completar()
	{
		bool ret = false;
		if(variables && !this->valido)
		{
			vector<string> yaRec;
			ret = this->valido;
			this->valido = recCompletar(false," "," ",yaRec,0,this->tuplas.size());

			if (ret != this->valido)
			{

				ret = true;
			}
		}
      else
      {
         this->valido = true;
      }
		return ret;
	}

	// parte recursiva de "completar"
	bool recCompletar(bool enc , string var,string val,vector<string> yaRec, int vaEn,int max)
	{
		bool ret = true ;
		bool rret = true;

		if(vaEn < max)
		{
			ret = false;
			vector<Value>::iterator it = this->tuplas[vaEn].valores.begin();

			for (int a = 0 ; a < this->tuplas[vaEn].valores.size(); a++)
			{
				Value* act = &this->tuplas[vaEn].valores[a];

				if (act->esVar)
				{
					if(act->posibles.size() > 0)
					{
						vector<string>::iterator itpos = act->posibles.begin();
						for(itpos; itpos != act->posibles.end() ; itpos++)
						{
							if(!presenteEn(yaRec, act->nombre+":"+*itpos))
							{
								yaRec.push_back(act->nombre+":"+*itpos);
								rret = recCompletar(true,act->nombre,*itpos,yaRec,0,max);
							}
						}
					}

					if(enc && !act->rellenado)
					{
						if(!presenteEn(act->posibles,val) && act->nombre == var)
						{
							act->copiar(val);
							ret = true;
						}
					}
					else if (enc && act->posibles.size() > 0)
					{
						ret = true;
						for (int b = 0 ; b < act->posibles.size() ; b++)
						{
							if (!presenteEn(yaRec, act->nombre+":"+act->posibles[b]))
							{
								ret = false ;
							}
						}
					}
					else if (!enc)
					{
						ret = true ;
					}
				}
			}
		}
		if(vaEn < max)
		{
			return rret && ret && recCompletar(true,var,val,yaRec,vaEn+1,max);
		}
		else
		{
			return ret;
		}
	}
};

class Conjunto{

	vector<Linea> lineas;
	bool verif;

	public:

	//inicializador
	Conjunto()
	{
		this->verif = false;
	}

	// imprime todo el conjunto
	void imprimir()
	{
		for(int a = 0 ; a < lineas.size() ; a++)
		{
         /*if(lineas[a].valido) cout<< " linea valida\t: ";
         else cout<< " linea no valida: ";*/
			lineas[a].imprimir();
			cout<<endl;
		}
	}

	// ingresa lineas
	void ingresar(Linea pred)
	{
		pred.numero = this->lineas.size();

		pred.tieneVariables();

		lineas.push_back(pred);
	}

	// rellena los datos buscando en las demas lineas
	bool rellenarDatos()
	{
		bool ret = false;
      //cout<<"-------------------------------------------"<<endl;
		for(int a = 0 ; a < lineas.size() ; a++)
		{
			/*
			cout<<endl<<endl<<"---linea "<<a<<" : ";
			lineas[a].imprimir();
			cout<<endl;//*/

			if ( !lineas[a].valido )
			{
				for(int b = 0 ; b < lineas.size() ; b++)
				{
					if(a!=b)
					{
						/*
						cout<<"linea "<<b<<" : ";
						lineas[b].imprimir();
						cout<<endl;//*/

						ret = ret || lineas[a].rellenarDatos(lineas[b]);
					}
				}
			}
		}

		return ret;
	}

	// rellena los datos buscando las variables dentro de la misma linea. Recursiva en linea
	bool completar()
	{
		bool ret = false;

		this->verif = true;
		for(int a = 0 ; a < lineas.size() ; a++)
		{
			ret = ret || lineas[a].completar();
			// en caso de que la linea no sea valida, el conjunto tampoco lo sera
			this->verif = this->verif && lineas[a].valido;
		}

		return ret;
	}

	// lee una tupla
	Linea leerLineaSimple(Linea set, string linea)
	{
		int a = 0, b = 0, end = linea.size();
		vector<Value> fields;

		while(linea[b] != '(' && b < end ) b++;
		string name = linea.substr(a,b);

		b++;

		while( a+b < end && linea[ a + b  -1 ] != ')' )
		{
			a = a+b;
			b = 0;

			while(linea[a+b] != ',' && linea[ a+b ] != ')' && a+b < end) b++;
			fields.push_back(Value(linea.substr(a,b)));
			b++;
		}

		set.ingresar(name,fields);
		return set;
	}

	// lee una linea
	Linea leerLinea(Linea set, string linea)
	{
		int a = 0, b = 0, end = linea.size();
		bool ing = false;

		while( b < end )
		{
			if( !ing && (linea[b] > 64 && linea[b] < 91 || linea[b] > 96 && linea[b] < 123  )&& b < end )
			{
				a = b;
				ing = true ;
			}

			if(linea[b] == ')')
			{
				set = leerLineaSimple(set,linea.substr(a,b));
				ing = false;
			}
			b++;
		}
		return set;
	}

	// ingresa una linea
	void ingresarLinea(string linea)
	{
		Linea pred;
		pred = leerLinea(pred,linea);
		ingresar(pred);
	}

	// llama las funciones rellenarDatos y completar hasta que todas las lineas esten verificadas o que hayan 10 ciclos
	// debe haber una manera mas eficiente, pero esto funciona por el momento
	void pro2log()
	{
		cout<<endl<<endl<<"inicial --------------------------------------------------------"<<endl<<endl;

		imprimir();

      cout<<endl<<endl<<"cambios --------------------------------------------------------"<<endl<<endl;

		bool cambios = true;

		int cc = 0 ;
		while(!this->verif && cambios)
		{

			cambios = false;

			cambios = cambios || rellenarDatos() || completar();
         cout<<endl;
         imprimir();
			cc++;
		}
		cout<<cc<<endl;
		cout<<endl<<endl<<"final --------------------------------------------------------"<<endl<<endl;
		imprimir();

      /*
		if(this->verif)
		{
			cout<<"datos completados"<<endl;
		}
		else
		{
			cout<<"datos no completados"<<endl;
		}*/
	}
};

// para conseguir los datos dados en el ejercicio. Quema de datos de las sabrosas
Conjunto prueba()
{
	Conjunto conj;

	Linea linea;
	vector<Value> val;

	string hombre = "hombre";
	string romano = "romano";
	string marco = "marco";
	string pompeyano = "pompeyano";
	string cesar = "cesar";
	string gobernante = "gobernante";
	string leal = "leal";
	string odia = "odia";
	string intenta_asesinar = "intenta_asesinar";


	linea.clear();
	val.clear();
	val.push_back(Value(marco));
	linea.ingresar(hombre ,val);
	conj.ingresar(linea);

	linea.clear();
	val.clear();
	val.push_back(Value(marco));
	linea.ingresar(pompeyano,val);
	conj.ingresar(linea);

	linea.clear();
	val.clear();
	val.push_back(Value("X3"));
	linea.ingresar(pompeyano,val);
	val.clear();
	val.push_back(Value("X3"));
	linea.ingresar(romano,val);
	conj.ingresar(linea);

	linea.clear();
	val.clear();
	val.push_back(Value(cesar));
	linea.ingresar(gobernante,val);
	conj.ingresar(linea);

	linea.clear();
	val.clear();
	val.push_back(Value("X5"));
	linea.ingresar(romano,val);
	val.clear();
	val.push_back(Value("X5"));
	val.push_back(Value(cesar));
	linea.ingresar(leal,val);
	val.clear();
	val.push_back(Value("X5"));
	val.push_back(Value(cesar));
	linea.ingresar(odia,val);
	conj.ingresar(linea);

	linea.clear();
	val.clear();
	val.push_back(Value("X7"));
	linea.ingresar(hombre,val);
	val.clear();
	val.push_back(Value("Y7"));
	linea.ingresar(gobernante,val);
	val.clear();
	val.push_back(Value("X7"));
	val.push_back(Value("Y7"));
	linea.ingresar(intenta_asesinar,val);
	val.clear();
	val.push_back(Value("X7"));
	val.push_back(Value("Y7"));
	linea.ingresar(leal,val);
	conj.ingresar(linea);

	linea.clear();
	val.clear();
	val.push_back(Value(marco));
	val.push_back(Value(cesar));
	linea.ingresar(intenta_asesinar,val);
	conj.ingresar(linea);

	return conj;

}

int main()
{
	Conjunto conj;

	int numpred = 0 ;
	cout<<"cantidad de lineas a ingresar :";
	cin>>numpred;

	if(numpred == 0)
	{
		conj = prueba();
		numpred = 8;
	}
	else
	{
		string line;
		cout<<"ingrese algo: \n";
		for(int a = 0 ; a < numpred ; a ++)
		{
			cout<<"> ";
			cin>>line;

			conj.ingresarLinea(line);
		}
	}

	if(numpred != 0 )
	{
		conj.pro2log();
	}


	return 0;
}
