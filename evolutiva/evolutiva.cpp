#include <iostream>

#include "poblacion.cpp"


int main()
{
   int repeticiones = 20;  // la cantidad de veces que se va a repetir el ciclo

   int cantidad = 10;      // la cantidad de sujetos en la poblacion

   int numGenes = 8;       // la cantidad de genes que tiene cada sujeto

   // los genes de esta poblacion fueron simulados con numeros binarios, use bools para ello
   Poblacion * pob = new Poblacion(cantidad,numGenes);
   
   std::cout<<"----------- inicio "<<std::endl;
   for (int a = 0; a < repeticiones ; a ++)
   {
      pob->generacion();
   }
   
   std::cout<<"el primero se mantiene sin cambios\nel segundo hereda del primero y segundo anterior\n";
   std::cout<<"el tercero hereda del segundo anterior y tercero anterior\nel resto mutan\n";
}



