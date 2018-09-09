
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;


class Tipo{
	
	string nom;
	
	
	/*bool comparar(Tipo cc)
	{
		int valEquiv  = 0; // cantidad de valores iguales
		bool ret = false;
		
		if(this.nom == cc.nom && this.ndatos == cc.ndatos)
		{
			
			
			for (int a = 0 ; a < this.ndatos ; a ++)
			{
				if(this.valores[a].comparar(cc.valores[a])
				{
					valEquiv ++ ; 
				}
			}
			
		}
		
		
		
		
	}*/
	
};
class Axioma{
	
	//private:
	
	string nombre;
	int ndatos;
	vector<string> valores; 
	
	// Ej: del axioma conquistador(marco,roma)  nombre = conquistador  ,  valores = [marco,roma] con ndatos = 2 (el tamaño de la lista valores)
	
	// se terminaria creando como : 
	// axioma(conquistador, [marco, roma] )
	
	
	public:
	
	Axioma( string nom, vector<string> val)
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
		vector<string>::iterator it;// = this->valores.begin();
		
		for(it = this->valores.begin(); it != this->valores.end(); it++ )    
		{
  		  
        	cout<< *it << " ";  // prints d.
        		
		}
		cout<<endl;
	}
	/*void comparar(Axioma cc)
	{
		//int nvalEquiv = 0; // cantidad de valores no nulos 
		int valEquiv  = 0; // cantidad de valores iguales
		
		if(this.nombre == cc.nombre && this.ndatos == cc.ndatos)
		{
			
			
			for (int a = 0 ; a < this.ndatos ; a ++)
			{
				int equiv = this.valores[a].comparar(cc.valores[a])
				
				
				if( equiv == 0 ) 
				{
					valEquiv ++ ; 
				}
				else if (equiv == 2 )
				{
					
				}
			}
			
		}
		
	}
	*/
};


// axioma(tipo,tipo,tipo)
int main()
{
	
	cout<< "hola"<<endl;
	//string val[] = {"marco","roma"};
	vector<string> val;
	
	val.push_back("marco");
	val.push_back("roma");
//	cout<< sizeof(val)/sizeof(*val)<<endl<<endl;
	string nom = "conquistador";
	
	Axioma a1(nom ,val);
	
	a1.imprimir();
	
	return 0;
}
