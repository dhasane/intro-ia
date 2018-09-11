#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

// compara 2 char*
bool comparar(char* cc1, char* cc2){
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
	bool esVar; // guarda en caso de ser variable

//	inicializador
	Tipo(string nom)
	{
		this->nombre = new char[nom.length()+1];
		strcpy(this->nombre , nom.c_str());

		if (nombre[0] > 64 && nombre[0] < 91)
		{
			esVar = true;
		}
		else
		{
			esVar = false;
		}
	}

//	copia un valor de otro Tipo, solo en caso de este ser una variable (mayuscula)
	void copiar(Tipo t)
	{
		if(esVar && !t.esVar)
		{
			nombre = t.nombre;
		}
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
	bool comprobacion;
	vector<Axioma> causas;
	// Ej: del axioma conquistador(marco,roma)  nombre = conquistador  ,  valores = [marco,roma] con ndatos = 2 (el tamaño de la lista valores)

	// se terminaria creando como :
	// axioma(conquistador, [marco, roma] )


	public:

//	inicializador
    Axioma(){
    }

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
	void rellenarDatos(Axioma ax2 )
	{
		vector<Tipo>::iterator it;
		vector<Tipo>::iterator it2;


		it = this->valores.begin();
		it2 = ax2.valores.begin();

		bool vabien = true;

		// verifica que todos los datos que no son variables sean iguales
		for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
		{

			if ( !  ( (it->esVar)  || (it2->esVar) ) &&  !comparar( it->nombre , it2->nombre )  )
			{
				vabien = false;
				it == this->valores.end();
			}
		}



		it = this->valores.begin();
		it2 = ax2.valores.begin();



		if(vabien)
		{
			for( it,it2 ; it2 != ax2.valores.end() ,it != this->valores.end(); it++ ,it2++ )
			{
				it->copiar(*it2) ;
			}
		}

	}

	void rellenarCausas(vector<Axioma> causas){
        this->causas = causas;
	}

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
    }

};

class Predicado{
	public:
	vector<Axioma> axiomas;

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

//	esta es la funcion que debera ser con recursividad, por ahora esta con fuerza bruta, para probar funcionaiento de
//	otras funciones
	void rellenarDatos(Predicado cc2)
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
					it->rellenarDatos(*it2);
				}
			}
		}

	}
	/*
//	funcion recursiva
	void rellenarDatos()
	{
		vector<Axioma>::iterator it;// = this->valores.begin();
		vector<Axioma>::iterator it2;// = this->valores.begin();
		for(it = this->conjunto.begin(); it != this->conjunto.end(); it++ )
		{
//  		  	it->imprimir();
			for(it2 = this->conjunto.begin(); it2 != this->conjunto.end(); it2++ )
			{
//  			  	it2->imprimir();
				if(it->nombre == it2->nombre)
				{
					it->rellenarDatos(*it2);
				}
			}
		}
	}
*/

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
				predicados[a].rellenarDatos(predicados[b]);
			}
		}
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
		Predicado pred;

		cout<<"> ";
		cin>>line;
		pred = leerLinea(pred,line);
		conj.ingresar(pred);
	}



	cout<<endl<<endl<<"--------------------------------------------------------"<<endl<<endl;



	conj.imprimir();

	conj.rellenarDatos();


	cout<<endl<<endl<<"--------------------------------------------------------"<<endl<<endl;



	conj.imprimir();
	return 0;
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
