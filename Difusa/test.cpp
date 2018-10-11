
#include <iostream>
#include <string>

#include "difusa.cpp"

using namespace std;
main()
{
    Difusa dif;

    dif.insertarClasificacion("azucar");
    dif.insertarAClasificacion("azucar","poco dulce",2,4,7,10);
    dif.insertarAClasificacion("azucar","medio dulce",6,10,15,18);
    dif.insertarAClasificacion("azucar","muy dulce",16,20,30,30);


    dif.insertarClasificacion("leche");
    dif.insertarAClasificacion("leche","hm",6,8,12,16);

    // prueba para evitar que se repitan nombres de Clasificaciones
    if(!dif.insertarClasificacion("leche"))
    {
        cout<<"valor ya insertado"<<endl;
    }


    cout<< "evaluando 8 en azucar : " << dif.fuzzy("azucar", 8)<<endl;
    cout<<endl<<"------------------------------------\n";
    
    cout<< dif.conseguirValor("azucar","poco dulce")<<endl;
    cout<<endl<<"------------------------------------\n";
    cout<< dif.conseguirValor("azucar","medio dulce")<<endl;
    cout<<endl<<"------------------------------------\n";
    
    cout<<"algo entre poco dulce y medio dulce : "<< dif.quieroAlgoEntre("azucar","poco dulce","medio dulce")<<endl;
    cout<<endl<<"------------------------------------\n";
    dif.imprimir();
}