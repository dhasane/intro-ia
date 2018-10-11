

#ifndef PERTNCPP
#define PERTCPP

#include <iostream>
#include <string>

class Pertenencia
{
    private:
        std::string nombre;
        float ini;  // soft start 
        float iniT; // hard start
        float finT; // hard end
        float fin;  // soft end

    public:
        Pertenencia(std::string nom, float i, float it, float ft,float f );
        float evaluar(float eval);
        std::string getNombre();
        std::string limites();
        float centro();
};

// constructor :v
Pertenencia::Pertenencia(std::string nom, float i, float it, float ft,float f )
{
    this->nombre = nom;
    this->ini = i;
    this->iniT= it;
    this->finT= ft;
    this->fin = f;
}

// retorna un string con los valores de la Pertenencia / bordes
std::string Pertenencia::limites()
{
    std::string ret;
    ret = "("+std::to_string(this->ini)+" , "+std::to_string(this->iniT)+" , "+std::to_string(this->finT)+" , "+std::to_string(this->fin)+")";
    return ret;
}

// evalua el porcentaje de pertenencia de un valor dado a Pertenencia
float Pertenencia::evaluar(float eval)
{
    float porc;

    if(eval < this->ini)
    {
        porc = 0;
    }
    else if(eval >= this->ini && eval < this->iniT)
    {
        porc = (eval-this->ini)/(this->iniT-this->ini);
    }
    else if (eval >= this->iniT && eval < this->finT)
    {
        porc = 1;
    }
    else if (eval >= this->finT && eval <= this->fin)
    {
        porc = 1 - (eval-this->finT)/(this->fin-this->finT);
    }
    else if(eval > this->fin)
    {
        porc = 0;
    }

    return porc;
}

// retorna el nombre de la Pertenencia
std::string Pertenencia::getNombre()
{
    return this->nombre;
}

// retorna el centro de la Pertenencia 
float Pertenencia::centro()
{
    // pensandolo, hay una forma mas facil, pero ya se quedo asi
    return ((this->fin-this->ini)/ 2) + this->ini;
}


#endif
