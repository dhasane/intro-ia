#ifndef CLASIFCPP
#define CLASIFCPP

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#include "Pertenencia.cpp"

class Clasificacion
{
    private:
        std::string nombre;
        std::vector<Pertenencia> pert;
    public:
        Clasificacion(std::string nom);
        bool insertarPertenencia(std::string nom, float i, float it, float ft,float f );
        void imprimir();
        std::string getNombre();
        float fuzzy(float val);
        float centro(std::string val);
};

// pos crea el asunto / le da nombre
Clasificacion::Clasificacion(std::string nom)
{
    this->nombre = nom;
}

// retorna el nombre de la Clasificacion
std::string Clasificacion::getNombre()
{
    return this->nombre;
}

// crea e inserta una nueva Pertenencia
// retorna true, al haber insertado la Pertenencia
bool Clasificacion::insertarPertenencia(std::string nom, float i, float it, float ft,float f )
{
    Pertenencia npert(nom, i, it, ft, f );
    this->pert.push_back(npert);
    return true;
}

// imprimir sigue imprimiendo :V
void Clasificacion::imprimir()
{
    std::cout<<this->nombre<<std::endl;

    for (int a = 0; a < this->pert.size() ; a++)
    {
        std::cout<<"   "<< this->pert[a].getNombre();
        std::cout<<" "<<this->pert[a].limites();
        std::cout<<"\n";
    }
}

// fuzzyfica los datos
// debe retornar lista de floats/ por ahora retorna el centro de masa supuesto e imprime los datos
float Clasificacion::fuzzy(float val)
{
    std::cout<<"\n"<<this->nombre<<std::endl;
    float eval = 0;
    float cm = 0; // centro de masa

    for (int a = 0; a < this->pert.size() ; a++)
    {
        eval = this->pert[a].evaluar(val);

        // centro de masa
        float cct = (this->pert[a].centro())*eval;

        //std::cout<<" :"<<cct<<"\n";
        cm += cct;

        std::cout<<"   "<< this->pert[a].getNombre();
        std::cout<<" "<<eval <<"\n";

        //std::cout<<"\n";
    }

    std::cout << "centro de masa supuesto en : "<< cm<< std::endl;

    return cm;
}

// retorna el centro de la Pertenencia
float Clasificacion::centro(std::string val)
{
    for (int a = 0; a < this->pert.size() ; a++)
    {
        if(this->pert[a].getNombre() == val)
        {
            return (this->pert[a].centro());
        }
    }
    return 0;
}


#endif
