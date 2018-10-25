
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

#include "especie.cpp"

class Poblacion
{
private:
   std::vector<Especie> sujetos;
   int cantidad;
public:
   Poblacion(int cant, int numeroGenes);
   void mutar(Especie *esp);
   Especie heredar(Especie H1, Especie H2);
   void imprimir();
   void imprimirDec();
   void organizar();
   void generacion();
   void imprimircmp();
};

Poblacion::Poblacion(int cant, int numeroGenes)
{
   this->cantidad = cant;
   Especie *esp;
   
   for(int a = 0 ; a < cant ; a ++ )
   {
      esp = new Especie(numeroGenes);
      mutar(esp);
      sujetos.push_back(*esp);
   }
}

// simula una generacion de esta pequeña poblacion
void Poblacion::generacion()
{
   // primero se organiza
   this->organizar();
   this->imprimircmp();
   
   // 2 y 3 heredan
   this->sujetos[2] = heredar(this->sujetos[0], this->sujetos[1]);
   this->sujetos[1] = heredar(this->sujetos[0], this->sujetos[1]);

   // el resto mutan libremente
   for(int a = 3; a < this->cantidad ; a ++)
   {
      mutar(&this->sujetos[a]);
   }
   std::cout<<"-----------"<<std::endl;
   // y se vuelve a repetir
}

// imprime todos los sujetos en binario
void Poblacion::imprimir()
{
   for(int a = 0 ; a < this->cantidad ; a ++ )
   {
      sujetos[a].imprimir();
   }
   
}

// imprime todos los sujetos en binario y decimal
void Poblacion::imprimircmp()
{
   for(int a = 0 ; a < this->cantidad ; a ++ )
   {
      sujetos[a].imprimircmp();
   }
   
}

// organiza la lista de sujetos, honestamente copie este codigo de una respuesta de stack overflow
void Poblacion::organizar()
{
   //std::sort (this->sujetos.begin() , this->sujetos.end() );
   std::sort(this->sujetos.begin(),
          this->sujetos.end(),
          [](Especie& lhs, Especie& rhs)
   {
      return lhs.evaluarEnDecimal() < rhs.evaluarEnDecimal();
   });
}

// imprime todos los sujetos en decimal
void Poblacion::imprimirDec()
{
   for(int a = 0 ; a < this->cantidad ; a ++ )
   {
      sujetos[a].imprimirDec();
   }
   
}

// muta alguno de los genes de un sujeto, le puse probabilidad de 50% de que cambie cada uno
void Poblacion::mutar(Especie *esp)
{
   for (int a = 0 ; a < esp->getNgene() ; a++)
   {
      if(rnd(0,10) > 5)
      {
         esp->setGen(a, !esp->getGen(a) );
      }
   }
}

// 50% de que herede los genes de H1 y 50% de los genes de H2
Especie Poblacion::heredar(Especie H1, Especie H2)
{
   int tam = H1.getNgene();
   Especie *esp = new Especie(tam );

   for (int a = 0 ; a < esp->getNgene() ; a++)
   {
      int ran = rnd(0,10);
      if( ran < 4)
      {
         esp->setGen(a, H1.getGen(a) );
      }
      else if ( ran < 8)
      {
         esp->setGen(a, H2.getGen(a) );
      }
      else
      {
         if(rnd(0,10)<5)
         {
             esp->setGen(a, true );
         }
         else
         {
             esp->setGen(a, false );
         }
      }
   }

   return *esp;
}