
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;


class Tipo{
	
	public:
		
	string nombre;
	Tipo *significado; // solo apunta en caso de coenzar con mayuscula nombre
	
	Tipo(string nom)
	{
		this->nombre = nom;
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
	
	Axioma( string nom, vector<Tipo> val)
	{
		this->nombre  = nom;
				
		this->ndatos  = val.size();
		
		this->valores = val;
		
		/*
        */
		
	}
	
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
