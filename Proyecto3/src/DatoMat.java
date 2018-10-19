



import java.util.List;
import java.util.*;

public class DatoMat {

   List<String> categorias;
   int cantidad;

   float porcentaje;

   DatoMat()
   {
      this.cantidad = 0;
      this.categorias = new ArrayList<>();
   }

   DatoMat(String primerValor, float porc)
   {
      this.cantidad = 0;
      this.categorias = new ArrayList<>();
      this.categorias.add(primerValor);
      this.porcentaje = porc;
   }

   void addV(String valor, float porc)
   {
      this.cantidad ++;
      this.categorias.add(valor);

      if(porc < this.porcentaje)
      {
         this.porcentaje = porc;
      }
   }

   void addV(DatoMat v2)
   {
      this.cantidad += v2.cantidad;

      for (int a = 0 ; a < v2.categorias.size() ; a++)
      {
         this.categorias.add(v2.categorias.get(a));
      }
      

      if(v2.porcentaje < this.porcentaje)
      {
         this.porcentaje = v2.porcentaje;
      }
   }

   void copyDM(DatoMat dm2)
   {
      this.cantidad = dm2.cantidad;

      for (int a = 0 ; a < dm2.categorias.size() ; a++)
      {
         this.categorias.add(dm2.categorias.get(a));
      }
      
      this.porcentaje = dm2.porcentaje;
   }

   public String toString() 
   {
      String ret = "| ";
      for (int a = 0 ; a < categorias.size() ; a ++ )
      {
         ret += categorias.get(a) + " | ";
      }
      
      return  ret +": "+ porcentaje + "\n";
      //return getClass().getName() + "@" + Integer.toHexString(hashCode());
   }
}
