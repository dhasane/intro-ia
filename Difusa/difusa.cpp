
#ifndef DIFUSACPP
#define DIFUSACPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Clasificacion.cpp"

class Difusa
{
    private:
        std::vector<Clasificacion> clasif;
    public:
        Difusa();
        bool insertarClasificacion(std::string nom);
        bool insertarAClasificacion(std::string nom, std::string nomprt, float i, float it, float ft,float f );
        void imprimir();
        float fuzzy(std::string nom , float val);
        float conseguirValor(std::string nom, std::string val);
        float quieroAlgoEntre(std::string nom, std::string val1, std::string val2);
};

Difusa::Difusa(){}

// fuzzyfica el asunto 
// fuzzyfica una Clasificacion especifica con un valor dado
float Difusa::fuzzy(std::string nom , float val)
{
    for (int a = 0; a < this->clasif.size() ; a++)
    {
        if(this->clasif[a].getNombre() == nom)
        {
            this->clasif[a].fuzzy(val);
        }
    }
}

// crea una nueva Clasificacion, a la que solo le da nombre, 
// y la ingresa a la lista
bool Difusa::insertarClasificacion(std::string nom)
{
    bool found = false;
    for (int a = 0; a < this->clasif.size() ; a++)
    {
        if(this->clasif[a].getNombre() == nom)
        {
            found = true;
        }
    }

    if(!found)
    {
        Clasificacion cl(nom);
        this->clasif.push_back(cl);
    }

    return !found;
    
}

// inserta una nueva Pertenencia a una clasificacion especifica
// retorna true, en caso de poder insertar la Pertenencia
bool Difusa::insertarAClasificacion(std::string nom, std::string nomprt, float i, float it, float ft,float f )
{
    for (int a = 0; a < this->clasif.size() ; a++)
    {
        if(this->clasif[a].getNombre() == nom)
        {
            return this->clasif[a].insertarPertenencia(nomprt,i,it,ft,f);
        }
    }
    return false;
}

// imprime :v
void Difusa::imprimir()
{
    for (int a = 0; a < this->clasif.size() ; a++)
    {
        this->clasif[a].imprimir();
    }
}

// funcion como por jugar, el nombre ya lo describe
float Difusa::quieroAlgoEntre(std::string nom, std::string val1, std::string val2)
{
    for (int a = 0; a < this->clasif.size() ; a++)
    {
        if(this->clasif[a].getNombre() == nom)
        {
            return (this->clasif[a].centro(val1) + this->clasif[a].centro(val2))/2;
        }
    }
    return 0;
}

// consigue el centro de una Pertenencia especifica,
// de una Clasificacion especifica
float Difusa::conseguirValor(std::string nom, std::string val)
{
    for (int a = 0; a < this->clasif.size() ; a++)
    {
        if(this->clasif[a].getNombre() == nom)
        {
            return this->clasif[a].centro(val);
        }
    }

    return 0;
}

#endif
