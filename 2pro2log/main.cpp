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
        if(causas.size()>0){
            while(it1 != causas.end()){
                Axioma* axiomaComprobar = &(*it1); //Asignarle el axioma

                if(comprobarSiEsta(axiomaComprobar,variable) == true){
                    cout<<"verdad"<<axiomaComprobar->nombre<<endl;
                    cantidadVerdades++;
                }
                it1++;
            }

        }
        else{
            vector<Tipo>::iterator it2 = axioma->valores.begin();
            while(it2 != axioma->valores.end()){
                cout<<"sss"<<it2->nombre<<endl;
                if(it2->nombre ==variable){
                    return true;
                }
                it2++;
            }
            return false;
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
            cout<<"tam"<<axioma->nombre<<" "<<axioma->valores.size()<<endl;
            vector<Tipo>:: iterator it1 = axioma->valores.begin();

            while(it1 != axioma->valores.end()){
                cout<<it1->nombre<<" "<<endl;
                if(buscar == it1->nombre){
                    return true;
                }
                it1++;
            }
            return false;
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
    public:
	vector<Axioma> predicados;

	public:
	Conjunto()
	{

	}
	void ingresar(Axioma pred)
	{
		predicados.push_back(pred);

	}


/*
	void imprimir()
	{
		for(int a = 0 ; a < predicados.size() ; a++)
		{
			predicados[a].imprimir();
			cout<<endl;
		}
	}


	void ingresar(Axioma pred)
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
*/
	vector<Tipo> listaDe(string nombre){
        vector<Axioma>:: iterator it = predicados.begin();
        while(it != predicados.end()){
            if(it->nombre == nombre){
                break;
            }
            it++;
        }
        return it->valores;
    }

    Axioma* buscarAxioma(char* axioma){
        vector<Axioma>:: iterator it = predicados.begin();
        Axioma* a = new Axioma();
        while(it != predicados.end()){
            a = &*it;
            if(a->nombre == axioma){
                return a;
            }
            it++;
        }

        return a;

    }

    bool existeAxioma(char* axioma){
        cout<<"entra en existe"<<predicados.size()<<endl;
        vector<Axioma>:: iterator it = predicados.begin();
        Axioma* a = new Axioma();
        while(it != predicados.end()){
            a = &*it;
            cout<<a->nombre<<" "<<axioma<<endl;
            if(a->nombre == axioma){
                return true;
            }
            it++;
        }
        cout<<"sale"<<endl;
        return false;

    }

};
Predicado leerLinea(Predicado set, string linea);
Predicado leerLineaSimple(Predicado set, string linea);
vector<char*> leer(char str[]);
vector<char*> leer2(char* str);
char* quitarParentesis(char* str);
vector<char*> separarAxioma(char* axioma);

int main()
{
    int cantidadAxiomas;
    Conjunto conj;
    char* linea;
    string cadena;
    vector<char*> datos;
    vector<char*> vectorCausas;
    vector<char*> sinParentesis;
    //char linea[]= "pompeyano(X),hombre(x)->romano(X)";
    //Basicos
    Axioma n;
        n.nombre = "pompeyano";
        n.ndatos = 3;
        n.valores.push_back(Tipo("lucas"));
        n.valores.push_back(Tipo("marcos"));
        n.valores.push_back(Tipo("cesar"));
        n.valores.push_back(Tipo("alguien"));

        Axioma na;
        na.nombre = "hombre";
        na.ndatos = 3;
        na.valores.push_back(Tipo("marcos"));
        na.valores.push_back(Tipo("luis"));
        na.valores.push_back(Tipo("cesar"));

        Axioma v;
        v.nombre = "nose";
        v.ndatos = 1;
        v.valores.push_back(Tipo("cesar"));

        conj.predicados.push_back(n);
        conj.predicados.push_back(na);
        conj.predicados.push_back(v);

        cout<<"cuantos axiomas va a ingresar?"<<endl;
    cin>>cantidadAxiomas;
    char* valor;
    char* pasar;
    string nombreAxioma;
    bool existe;
    for(int i=0; i<cantidadAxiomas; i++){
       Axioma* n2 = NULL;
       cout<<"Inserte nombre del axioma"<<endl;
       cin>>nombreAxioma;
       cout<<"inserte dato"<<endl;
       cin>>cadena;
        strcpy(pasar , nombreAxioma.c_str());
        existe = conj.existeAxioma(pasar);
        //n2->valores.push_back(Tipo(cadena));
        if(existe == 0){
            n2 = new Axioma();
            n2->nombre = nombreAxioma;
            n2->valores.push_back(Tipo(cadena));
            conj.predicados.push_back(*n2);

        }
        else{
            n2->valores.push_back(Tipo(cadena));
            conj.predicados.push_back(*n2);
        }
    //    n2.nombre = nombreAxioma;

        //conj.predicados.push_back(n2);
    }
    cout<<"total axiomas"<<conj.predicados.size()<<endl;
    //complejos
    cout<<"cuantos axiomas complejos va a ingresar?"<<endl;
    cin>>cantidadAxiomas;
    if(cantidadAxiomas != 0){
        for(int i =0; i<cantidadAxiomas; i++){
            vectorCausas.clear();
            sinParentesis.clear();
            datos.clear();

            cin>>cadena;
            linea = new char[cadena.length()+1];
            strcpy(linea , cadena.c_str());
            cout<<linea;

            int cantidadAxiomas;
            datos = leer(linea);
            cout<<datos[0]<<" "<<datos[1]<<"´´´´´´´´´´´´´´´"<<conj.predicados.size()<<endl;
            vectorCausas = leer2(datos[0]);

            int limite = 0;
            limite = vectorCausas.size()-1;
            for(int i=0; i<limite; i++){
                cout<<vectorCausas[i]<<endl;
                sinParentesis.push_back(quitarParentesis(vectorCausas[i]));
            }

            Axioma resultado;
            vector<Axioma> causas;
            Axioma causa;

            for(int i=0; i<limite; i++){
                //valores = conj.listaDe(sinParentesis[i]);
                cout<<"-"<<sinParentesis[i]<<endl;
                causa.nombre = sinParentesis[i];
                cout<<"--"<<causa.nombre<<endl;
                causa.valores = conj.listaDe(sinParentesis[i]);
                causas.push_back(causa);
            }
            resultado.rellenarCausas(causas);

            //Despues del entonces
            resultado.nombre = quitarParentesis(datos[1]);
            conj.ingresar(resultado);
    }
    }







    //if(cantidadAxiomas>0){
        cin.getline(linea,100);
        cout<<linea;
        string c;
    //}

    while(true){
        cout<<"buscar axioma "<<endl;
        cin.getline(linea,100);
        vector<char*> axiomaAAnalizar = separarAxioma(linea);
        Axioma* dire = new Axioma();
        cout<<axiomaAAnalizar[0]<<" "<<axiomaAAnalizar[1]<<endl;
        dire = conj.buscarAxioma(axiomaAAnalizar[0]);
        if(dire->comprobarAxiomas(dire,axiomaAAnalizar[1])){
            cout<<endl<<"True"<<endl;
        }
        else{
            cout<<endl<<"False"<<endl;
        }
   }

	return 0;
}
vector<char*> leer(char str[]){
    //char str[]= linea;
    vector<char*> datos;
    char * pch;
    //printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str,"-");
    datos.push_back(pch);// Aqui deja solo la coma
    while (pch != NULL)
    {// Aqui deberias guardar tu dato en el array!
        pch = strtok (NULL, " ,.->");
        datos.push_back(pch); // Aca tambien iria solo la coma.!!
    }
    return datos;
}

vector<char*> leer2(char* str){
    //char str[]= linea;
    vector<char*> datos;
    char * pch;
    //printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str,", ");
    datos.push_back(pch);// Aqui deja solo la coma
    while (pch != NULL)
    {// Aqui deberias guardar tu dato en el array!
        pch = strtok (NULL, " ,");
        datos.push_back(pch); // Aca tambien iria solo la coma.!!
    }

    return datos;
}

char* quitarParentesis(char* str){
    vector<char*> datos;
    char * pch;
    //printf ("Splitting string \"%s\" into tokens:\n",str);
    pch = strtok (str,"()");
    //cout<<pch<<endl;
    return pch;
}

vector<char*> separarAxioma(char* axioma){
    vector<char*> resultado;
    char * pch;

    //printf ("Splitting string \"%s\" into tokens:\n",axioma);
    pch = strtok (axioma,"( ");
    resultado.push_back(pch);// Aqui deja solo la coma
    while (pch != NULL)
    {// Aqui deberias guardar tu dato en el array!
        pch = strtok (NULL, ") ");
        resultado.push_back(pch); // Aca tambien iria solo la coma.!!
    }
    return resultado;

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
