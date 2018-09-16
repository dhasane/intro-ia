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

bool presenteEn(vector<string> posibles, string nval)
{
	vector<string>::iterator it;// = this->valores.begin();

	for(it = posibles.begin(); it != posibles.end(); it++ )
	{
		//cout<<*it<<"  <= "<<nval<<endl;
		if(*it == nval)
		{
			return true;
		}
	}
	
	return false;
}

class Value{

	public:

	//char * nombre;
	string nombre;
	bool esVar; // guarda en caso de ser variable
	
	vector<string> posibles;
	
	Value()
	{
	}
	
//	inicializador
	Value(string nom)
	{
		this->nombre = new char[nom.length()+1];
		//strcpy(this->nombre , nom.c_str());
		this->nombre = nom;

		if (nombre[0] > 64 && nombre[0] < 91)
		{
			esVar = true;
			//nomVar = this->nombre;
		}
		else
		{
			esVar = false;
			//nomVar = " ";
		}
	}
	
	bool compararNombre(Value v2)
	{
		//if(comparar( this->nombre , v2.nombre ) )
		if(this->nombre == (v2.nombre))
		{
			return true;
		}
		return false;
	}
	
//	copia un valor de otro Value, solo en caso de este ser una variable (mayuscula)
	void copiar(Value t)
	{
		
		//cout<<"cc "<<t.nombre<<" => "<<this->nombre<<endl;
		{
			if(esVar && !t.esVar)
			{
				if(!presenteEn(this->posibles, t.nombre))
				{
					//cout<<"copiando"<<endl;
					posibles.push_back(t.nombre);
				}
			}
			else if (esVar && t.esVar )//&& this->nombre == t.nombre)
			{
				
				//if (this->nombre!=t.nombre)
				/*{
					cout<<"c-es ----------------------"<<endl;
					cout<<"copiando dos variables : "<< this->nombre<<" de "<< t.nombre<<endl;
					
				}*/
				vector<string>::iterator it;// = this->valores.begin();

				for(it = t.posibles.begin(); it != t.posibles.end(); it++ )
				{
					cout<<*it<<":";
					if(!presenteEn(this->posibles, *it))
					{
						cout<<"copiando"<<endl;
						posibles.push_back(*it);
					}
				}
				cout<<endl;
				
			}
		}
	}

};

class Tupla{

	//private:
	public:

	string nombre;
	int ndatos;
	vector<Value> valores;
	
	// Ej: del axioma conquistador(marco,roma)  nombre = conquistador  ,  valores = [marco,roma] con ndatos = 2 (el tamaño de la lista valores)

	// se terminaria creando como :
	// axioma(conquistador, [marco, roma] )


	public:

//	inicializador
	Tupla( string nom, vector<Value> val)
	{
		this->nombre  = nom;

		this->ndatos  = val.size();

		this->valores = val;

	}

//	imprime el axioma
	void imprimir()
	{

		cout<<this->nombre<<" : ";
		vector<Value>::iterator it;// = this->valores.begin();

		for(it = this->valores.begin(); it != this->valores.end(); it++ )
		{
			if(it->esVar && it->posibles.size()>0)
			{
				Value vv = * it;
				cout<<  vv.nombre<<":(";
				
				vector<Value>::iterator itn;
				for(int a = 0 ; a < vv.posibles.size() ; a ++)
				{
					Value subVal = vv.posibles[a];
					cout<< subVal.nombre;
					
					if( a+1 == vv.posibles.size() - 1)
					{
						cout<<", ";
					}
				}
				
				
				cout << ") ";
			}
			else
			{
				cout<<  it->nombre ;
			}
			
			
			if( it + 1 != this->valores.end())cout<< ", ";
        	
		}
	}

//	compara los dos axiomas y en caso que uno de estos tenga variabes, = > copia los datos de dato a Variable
	bool rellenarDatos(Tupla ax2 , vector<Value> *variables)
	{
		//if(compararTuplas(ax2))
		if(this->nombre == ax2.nombre)
		{
		
			vector<Value>::iterator it;
			vector<Value>::iterator it2;
			
			it = this->valores.begin();
			it2 = ax2.valores.begin();
			//bool ret = false;
			int nVars = 0;
			int cantidadVariables = 0 ;
			
			
			
			for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
			{
				//cout<<"cccc "<<it2->nombre<<" => "<<it->nombre<<endl;
				it->copiar(*it2);
			}
		}
		 
	}
/*
	bool compararTuplas(Tupla ax2)
	{
		
		if(this->nombre != ax2.nombre)
		{
			return false;
		}
		vector<Value>::iterator it;
		vector<Value>::iterator it2;

		
		//bool vabien = true;
		
		it = this->valores.begin();
		it2 = ax2.valores.begin();

		

		// verifica que todos los datos que no son variables sean iguales
		for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
		{

			if ( !  ( (it->esVar)  || (it2->esVar) ) &&  !it->compararNombre(*it2)  )
			{
				return false;
			}
			
		}
		
		return true;
		
		
	}
*/
	bool tieneVariables()
	{
		cout<<this->nombre<<" : ";
		vector<Value>::iterator it;// = this->valores.begin();

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
	int nombre;
	vector<Tupla> tuplas;
	bool variables;
	bool valido; 
	
	

	
	
	void tieneVariables()
	{
		vector<Tupla>::iterator it;// = this->valores.begin();

		this->variables = false;
		
		for(it = this->tuplas.begin(); it != this->tuplas.end(); it++ )
		{
  		  	if(it->tieneVariables())
			{
				this->variables = true;
			}
		}
		
		
	}
	
//	ingresa una tupla nueva solo en caso de que o sea con un nombre nuevo
//  o tenga la misma cantidad de argumentos que la tupla con el mismo nombre

	bool ingresar(string nom, vector<Value> val)
	{
		Tupla ax(nom,val);

		vector<Tupla>::iterator it;// = this->valores.begin();

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
	
	void rellDatos(vector<Tupla>::iterator it, vector<Tupla>::iterator it2 , Linea &cc2 , vector<Value> *variables)
	{
		it->rellenarDatos(*it2 , variables);
		it2->rellenarDatos(*it , variables);
		
		int mit1 = 0;
		int mit2 = 0;
		
		if(it + 1 != this->tuplas.end())
		{
			mit1 = 1;
		}
		if(it2 + 1 != cc2.tuplas.end() )
		{
			mit2 = 1;
		}
		
		if(it +1 == this->tuplas.end() && it2 +1  == cc2.tuplas.end() )
		{
		}
		else
		{
			//completar();
			rellDatos(it+mit1,it2+mit2,cc2, variables);
		}
		
		it->rellenarDatos(*it2 , variables);
		it2->rellenarDatos(*it , variables);
		
	}
	
	void rellenarDatos( Linea &cc2 )
	{
		if(!valido)
		{
			vector<Value> variables;
			vector<Tupla>::iterator it = this->tuplas.begin();
			vector<Tupla>::iterator it2 = cc2.tuplas.begin();
			
			rellDatos(it,it2 ,cc2, &variables);
			
		}
		else{
			
			cout<<this->nombre<<" ya valido"<<endl;
		}
		
		
	}
	
	void clear()
	{
		tuplas.clear();
	}
	
	// le da los mismo valores a todas las variables que tengan el mismo nombre dentro de una linea
	void completar()
	{
		if(variables)
		{
			vector<string> yaRec;
			//Valur variable;
			
			
			string var = " ";
			string val = " ";
			
			cout<<"--------------------------"<<this->nombre<<"----------------------------tam : "<<this->tuplas.size()<<endl;
			imprimir();
			//cout<<endl;
			
			this->valido = recCompletar(false,var,val,yaRec,0,this->tuplas.size());
		}
		else 
		{
			this->valido = true ;
		}
		
		cout<<"----------------------------------------------------------------------------";
		if (this->valido == true )
		{
			cout<<this->nombre<< " es valido "<<endl;
		}
		else{
			cout<<this->nombre<< " no es valido"<<endl;
		}
		//vector<Value> variables;
		
		
	}
	
	bool recCompletar(bool enc , string var,string val,vector<string> yaRec, int vaEn,int max)
	{
		
		bool ret = false ; 
		/*cout<<"-------------------------------------"<<endl;
		if (enc)
		{
			cout<<"encontrado var :"<<var<<":"<<val;
		}
		else
		{
			cout<<"no encontrado ";
		}
		cout<<"  va en :"<<vaEn<<"  "<<max<<endl;
		*/
		
		if(vaEn < max)
		{
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
								//cout<<"nueva : "<<act->nombre<<" con valor : "<< *itpos<<endl;
								yaRec.push_back(act->nombre+":"+*itpos);
								recCompletar(true,act->nombre,*itpos,yaRec,0/*vaEn+1*/,max);
								
							}
						}
					}
					
					if(enc && act->posibles.size() == 0)
					{
						//cout<<"enc"<<endl;
						if(!presenteEn(act->posibles,val) && act->nombre == var)
						{
							
							cout<<"agregando "<<var<<" con valor : "<< val<<" a "<<act->nombre<<endl;
							act->copiar(val);
							ret = true; 
						}
					}
					else if (enc && act->posibles.size() > 0)
					{
						ret = true;
						for (int b = 0 ; b < act->posibles.size() ; b++)
						{
							//cout<<act->nombre+":"+act->posibles[b]<<endl;
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
			
			/*
			if(ret)
			{
				cout<<"se cumple "<<endl;
			}
			else
			{
				cout<<"no se cumple"<<endl;
			}*/
		
			//cout<<"final"<<endl;
		
			if(vaEn < max)
			{
				return ret && recCompletar(true,var,val,yaRec,vaEn+1,max);
			}
			else
			{
				return ret;
			}
		}
		
		
		
		
		
		
		
	}
};

class Conjunto{
	
	vector<Linea> lineas;
	
	public:
	
	Conjunto()
	{
	}
	
	void imprimir()
	{
		for(int a = 0 ; a < lineas.size() ; a++)
		{
			lineas[a].imprimir();
			cout<<endl;
		}
	}
	
	void ingresar(Linea pred)
	{
		pred.nombre = this->lineas.size();
		
		pred.tieneVariables();
		
		lineas.push_back(pred);
		//rellenarDatos();
	}
	
	void rellenarDatos()
	{
		for(int a = 0 ; a < lineas.size() ; a++)
		{
			cout<<"---linea "<<a<<" : ";
			lineas[a].imprimir();
			cout<<endl;
			
			if ( !lineas[a].valido )
			{
				
				for(int b = 0 ; b < lineas.size() ; b++)
				{
					if(a!=b)
					{
						cout<<"linea "<<b<<" : ";
						lineas[b].imprimir();
						cout<<endl;
						
						lineas[a].rellenarDatos(lineas[b]);
					}
				}
				
			}
			else{
					
				cout<<lineas[a].nombre<<" ya es valido"<<endl;
					
			}
			
			cout<<endl<<endl;
		}
		//rellDatos(0,0,lineas.size());
	}
	
	void completar()
	{
		for(int a = 0 ; a < lineas.size() ; a++)
		{
			
			lineas[a].completar();
				
		}
		//rellDatos(0,0,lineas.size());
	}
	
	void rellDatos(int vaEn,int comp, int max)
	{
		cout<<"linea "<<vaEn<<" : ";
		lineas[vaEn].imprimir();
		lineas[vaEn].rellenarDatos(lineas[comp]);
		
		if(vaEn +1 != max && comp +1 != max)
		{
			rellDatos(vaEn+1,comp+1,lineas.size());
		}
		else if(vaEn +1 != max)
		{
			rellDatos(vaEn+1,comp,lineas.size());
		}
		else if(comp +1 != max)
		{
			rellDatos(vaEn,comp+1,lineas.size());
		}
		
		
		
	}
	
	
	
	Linea leerLineaSimple(Linea set, string linea){

		int a = 0, b = 0, end = linea.size();

		while(linea[b] != '(' && b < end )
			b++;

		string name = linea.substr(a,b);
		b++;

		vector<Value> fields;

		while(a+b < end){
			a = a+b;
			b = 0;
			while(linea[a+b] != ',' && linea[a+b] != ')' && a+b < end)
				b++;
	
			fields.push_back(Value(linea.substr(a,b)));
			b++;
		}
		set.ingresar(name,fields);
		return set;
	}

	Linea leerLinea(Linea set, string linea){

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
		Linea pred;
		pred = leerLinea(pred,linea);
		ingresar(pred);
	}
	
};


// axioma(tipo,tipo,tipo)


//void insertarAList

Linea leerLinea(Linea set, string linea);
Linea leerLineaSimple(Linea set, string linea);

int main()
{

	//cout<< "hola"<<endl;
	//string val[] = {"marco","roma"};
	vector<Value> val;


	Conjunto conj;
	
	//*
	Linea linea; 
	
	
	val.clear();
	val.push_back(Value("marco"));
	linea.ingresar("hombre" ,val);
	conj.ingresar(linea);
	
	linea.clear();
	val.clear();
	val.push_back(Value("marco"));
	linea.ingresar("pompeyano",val);
	conj.ingresar(linea);
	
	linea.clear();
	val.clear();
	val.push_back(Value("X3"));
	linea.ingresar("pompeyano",val);
	val.clear();
	val.push_back(Value("X3"));
	linea.ingresar("romano",val);
	conj.ingresar(linea);
	
	
	linea.clear();
	val.clear();
	val.push_back(Value("cesar"));
	linea.ingresar("gobernante",val);
	conj.ingresar(linea);
	
	
	linea.clear();
	
	val.clear();
	val.push_back(Value("X5"));
	linea.ingresar("romano",val);
	val.clear();
	val.push_back(Value("X5"));
	val.push_back(Value("cesar"));
	linea.ingresar("leal",val);
	val.clear();
	val.push_back(Value("X5"));
	val.push_back(Value("cesar"));
	linea.ingresar("odia",val);	
	conj.ingresar(linea);
	
	
	linea.clear();
	val.clear();
	val.push_back(Value("X7"));
	linea.ingresar("hombre",val);
	val.clear();
	val.push_back(Value("Y7"));
	linea.ingresar("gobernante",val);
	val.clear();
	val.push_back(Value("X5"));
	val.push_back(Value("Y7"));
	linea.ingresar("intenta_asesinar",val);
	val.clear();
	val.push_back(Value("X5"));
	val.push_back(Value("Y7"));
	linea.ingresar("leal",val);
	conj.ingresar(linea);
	
	
	linea.clear();
	val.clear();
	val.push_back(Value("marco"));
	val.push_back(Value("cesar"));
	linea.ingresar("intenta_asesinar",val);
	conj.ingresar(linea);
	
	
	
	
	/*/
	int numpred = 0 ;
	cout<<"cantidad de lineas a ingresar :";
	cin>>numpred;
	
	
	string line;
	cout<<"ingrese algo: \n";
	for(int a = 0 ; a < numpred ; a ++)
	{
		
		cout<<"> ";
		cin>>line;
		
		conj.ingresarLinea(line);
		
	}
	//*/
	
	
	cout<<endl<<endl<<"antes --------------------------------------------------------"<<endl<<endl;
	
	
	
	conj.imprimir();
	
	cout<<endl<<endl;
	conj.rellenarDatos();
	conj.completar();
	conj.rellenarDatos();



	cout<<endl<<endl<<"despues --------------------------------------------------------"<<endl<<endl;
	
	
	
	conj.imprimir();
	return 0;
}


