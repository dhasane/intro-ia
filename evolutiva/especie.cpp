
#include <random>

// funcion de aleatoriedad, use una un poco mas rebuscada porque srand no es muy confiable/ demasiado predesible
int rnd(int min, int max)
{
   std::random_device r;
 
   // Choose a random mean between 1 and 6
   std::default_random_engine e1(r());
   std::uniform_int_distribution<int> uniform_dist(min, max);
   return  uniform_dist(e1);
}

class Especie
{
private:
   int ngene;     // cantidad de genes
   bool* genes;   // genes del ente
   int tsup;      // tiempo de supervivencia
public:
   Especie(int gen);
   bool getGen(int p);
   void setGen(int p, bool val);
   int getNgene();
   void imprimir();
   void imprimirDec();
   int evaluarEnDecimal();
   void imprimircmp();
};

Especie::Especie(int gen)
{
   this->ngene = gen;
   this->genes = new bool[gen];
   this->tsup = 0;

   for (int a = 0 ; a < gen ; a ++)
   {
      this->genes[a] = true;
   }
}

// retorna el gen p
bool Especie::getGen(int p)
{
   return this->genes[p];
}

// retorna la cantidad de genes
int Especie::getNgene()
{
   return this->ngene;
}

// al gen en la posicion p le da el valor val 
void Especie::setGen(int p, bool val)
{
   this->genes[p] = val;
}

// imprime en binario
void Especie::imprimir()
{
   for (int a = 0 ; a < this->ngene ; a ++)
   {
      if(this->genes[a]) std::cout<<1;
      else std::cout<<0;
   }
   
   std::cout<<std::endl;
}

// imprime en binario y decimal
void Especie::imprimircmp()
{
   for (int a = 0 ; a < this->ngene ; a ++)
   {
      if(this->genes[a]) std::cout<<1;
      else std::cout<<0;
   }
   
   std::cout<<" : "<<evaluarEnDecimal()<<std::endl;
}

// imprime de decimal
void Especie::imprimirDec()
{
   std::cout<<evaluarEnDecimal()<<std::endl;
}

// convierte el binario a decimal 
int Especie::evaluarEnDecimal()
{
   int dec = 0;
   int mult = 1;
   for (int a = 1 ; a <= this->ngene ; a ++)
   {
      dec += this->genes[this->ngene-a] * mult;

      mult*=2;
   }
   return dec;
}