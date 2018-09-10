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
	bool comprobacion;
	vector<Tipo> valores;
	vector<Axioma*> causas;
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
	Axioma (){

	}

//	imprime el axioma
	void imprimir()
	{

		cout<<this->nombre<<" : ";
		vector<Tipo>::iterator it;// = this->valores.begin();

		for(it = this->valores.begin(); it != this->valores.end(); it++ )
		{
        	cout<<  it->nombre << " ";
		}
		cout<<endl;
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

};

class Conjunto{
	public:
	vector<Axioma> conjunto;
    bool comprobacion;
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


//	esta es la funcion que debera ser con backtracking, por ahora esta con fuerza bruta, para probar funcionaiento de
//	otras funciones
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

    vector<Tipo> listaDe(string nombre, int &cantidadValores){
        vector<Axioma>:: iterator it = conjunto.begin();
        while(it != conjunto.end()){
            cout<<it->nombre<<endl;
            if(it->nombre == nombre){
                cout<<"Si"<<endl;
                break;
            }
            it++;
        }

        cantidadValores = it->ndatos;
        return it->valores;
    }


    bool axiomaPerro(string axioma, vector<Axioma*> condiciones){
        Axioma axiomaNuevo;

        axiomaNuevo.nombre = axioma;
        axiomaNuevo.causas = condiciones;

        conjunto.push_back(axiomaNuevo);
        return true;
    }



    bool comprobarAxioma(string axioma){

        int tamanoAxioma = 0;
        int tamanoVariable = 0;
        string nombreAxioma;
        for(int i=0; i<axioma.length() ; i++ ){
           if(axioma[i] != '(' ){
                tamanoAxioma++;
           }
           else{
                break;
           }



        }

        cout<<"Tamaño Axioma : "<<tamanoAxioma<<endl;
        cout<<"Tamaño variable : "<<axioma.length()-tamanoAxioma-2<<endl;
        for(int i=0; i<tamanoAxioma; i++){
            nombreAxioma[i]=axioma[i];
            cout<<axioma[i]<<" "<<nombreAxioma[i]<<endl;
        }


        cout<<endl<<nombreAxioma<<endl;

        string nombreVariable;
        for(int i=tamanoAxioma; i<axioma.length()-tamanoAxioma-2;i++){
            nombreVariable[i]=axioma[i];
        }
        cout<<nombreVariable<<endl;
        vector<Axioma>::iterator it1 = conjunto.begin();

        while(it1!= conjunto.end()){
            if(nombreAxioma == it1->nombre){
                cout<<"existe"<<endl;
                vector<Axioma*> causas= it1->causas;

            }

            it1++;
        }

    }
};

// axioma(tipo,tipo,tipo)
int main()
{
	vector<Tipo> val;
	Conjunto conj;

	val.push_back(Tipo("marco"));
	val.push_back(Tipo("roma"));
	conj.ingresar("hombre" ,val);

	val.clear();
	val.push_back(Tipo("marco"));
	val.push_back(Tipo("M"));
	conj.ingresar("pompeyano",val);

	val.clear();
	val.push_back(Tipo("cesar"));
	conj.ingresar("gobernante",val);

	conj.imprimir();
	//conj.rellenarDatos();
	cout<<endl<<endl<<"--------------------------------------------------------"<<endl<<endl;
	conj.imprimir();

    vector<Tipo> resultado;
    int cantidad =0 ;
    resultado = conj.listaDe("gobernante",cantidad);

    vector<Tipo>::iterator it1 = resultado.begin();
    for(int i=0; i<cantidad; i++){
        cout<<it1->nombre<<endl;
        it1++;
    }

    vector<Axioma*> condiciones;
    Axioma* nuevo = new Axioma("pompeyano",conj.listaDe("pompeyano",cantidad));

    condiciones.push_back(nuevo);
    conj.axiomaPerro("romano",condiciones);
    //int array_enteros[]={'9','8','7','6','5','4','3','2'};
    //int longitud=sizeof(array_enteros)/sizeof(*array_enteros);
    //cout<<longitud<<endl;


    conj.imprimir();

    cout<<endl;
    conj.comprobarAxioma("romano(Marcos)");
	return 0;
}
