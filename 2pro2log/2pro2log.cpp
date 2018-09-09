
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;


class Tipo{
	
	public:
		
	char * nombre; // solo apunta en caso de comenzar con mayuscula nombre
	
//	inicializador
	Tipo(string nom)
	{
		this->nombre = new char[nom.length()+1];
		strcpy(this->nombre , nom.c_str());
	}
	
//	copia un valor de otro Tipo, solo en caso de este ser una variable (mayuscula)
	void copiar(Tipo t)
	{
		if(nombre[0] > 64 && nombre[0] < 91)
		{
			nombre = t.nombre;
		}
	}
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
		
		/*
        */
		
	}
	
//	imprime el axioma
	void imprimir()
	{
		
		cout<<this->nombre<<" : ";
		vector<Tipo>::iterator it;// = this->valores.begin();
		
		for(it = this->valores.begin(); it != this->valores.end(); it++ )    
		{
  		  
        	cout<<  it->nombre << " ";  // prints d.
        		
		}
		cout<<endl;
	}
	
};

class Conjunto
{
	public:
	vector<Axioma> conjunto;
	
//	ingresa un axioma nuevo solo en caso de que o sea con un nombre nuevo
//  o tenga la misma cantidad de argumentos que el axioma con el mismo nombre
//  retorna verdadero si logro ingresar el axioma
	bool ingresar(string nom, vector<Tipo> val)
	{
		Axioma ax(nom,val);
		
		vector<Axioma>::iterator it;// = this->valores.begin();
		
		bool ret = true;
		
		for(it = this->conjunto.begin(); it != this->conjunto.end(); it++ )    
		{
  		  	// en caso de que tengan el mismo nombre, pero diferente cantidad de argumentos, no se agregara a la lista
        	if( it->nombre == ax.nombre && it->ndatos != ax.ndatos)
        	{
        		ret = false;
			}
        		
		}
		
		if(ret)
		{
			conjunto.push_back(ax);
		}
		
		return ret;
	}
	
	
//	imprime el conjunto de axiomas
	void imprimir()
	{
		vector<Axioma>::iterator it;// = this->valores.begin();
		
		
		for(it = this->conjunto.begin(); it != this->conjunto.end(); it++ )    
		{
  		  	it->imprimir();        		
		}
	}
	
};

// axioma(tipo,tipo,tipo)
int main()
{
	
	cout<< "hola"<<endl;
	//string val[] = {"marco","roma"};
	vector<Tipo> val;
	
	val.push_back(Tipo("marco"));
	val.push_back(Tipo("roma"));
//	cout<< sizeof(val)/sizeof(*val)<<endl<<endl;
	//string nom = "conquistador";
	
	
	Conjunto conj;
	
	conj.ingresar("conquistador" ,val);
	
	val.clear();
	
	val.push_back(Tipo("mer"));
	val.push_back(Tipo("meree"));
	
	
	
	conj.ingresar("conquistador",val);
	
	
	
	conj.imprimir();
	
	
	
	return 0;
}
