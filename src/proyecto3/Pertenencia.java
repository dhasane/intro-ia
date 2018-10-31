public class Pertenencia {
	
	private String nombre;
	private float ini;
	private float iniT;
	private float fin;
	private float finT;
	
	
	Pertenencia(String nom, float i, float it, float ft,float f )
	{
	    this.nombre = nom;
	    this.ini = i;
	    this.iniT= it;
	    this.finT= ft;
	    this.fin = f;
	}
	
	// retorna un string con los valores de la Pertenencia / bordes
	String limites(){
	    String ret;
	    ret = "("+ (this.ini) +" , "+(this.iniT)+" , "+(this.finT)+" , "+(this.fin)+")";
	    return ret;
	}
	

	// evalua el porcentaje de pertenencia de un valor dado a Pertenencia
	float evaluar(float eval)
	{
	    float porc = -1;

	    if(eval < this.ini)
	    {
	        porc = 0;
	    }
	    else if(eval >= this.ini && eval < this.iniT)
	    {
	        porc = (eval-this.ini)/(this.iniT-this.ini);
	    }
	    else if (eval >= this.iniT && eval < this.finT)
	    {
	        porc = 1;
	    }
	    else if (eval >= this.finT && eval <= this.fin)
	    {
	        porc = 1 - (eval-this.finT)/(this.fin-this.finT);
	    }
	    else if(eval > this.fin)
	    {
	        porc = 0;
	    }

	    return porc;
	}

	// retorna el nombre de la Pertenencia
	String getNombre()
	{
	    return this.nombre;
	}

	// retorna el centro de la Pertenencia 
	float getCentro()
	{
	    // pensandolo, hay una forma mas facil, pero ya se quedo asi
	    return ((this.fin-this.ini)/ 2) + this.ini;
	}

}

