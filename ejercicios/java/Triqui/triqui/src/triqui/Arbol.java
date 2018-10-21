package triqui;

import java.util.Random;

public class Arbol {

	Tablero tab;
	Arbol hijos[];
	int nHijos;
	int nivelesBajar = 2;

	// Crea la raiz, el tablero antes del movimiento
	public Arbol(Tablero actual) {
		// Turno X = 1, O = 2, el turno actual es el del oponente
		int turnoActual = 2;
		this.tab = new Tablero(actual);
		nHijos = this.tab.espVac();
		this.hijos = new Arbol[nHijos];

		for (int a = 0 ; a < nHijos ; a++)
		{
			hijos[a] = new Arbol(this.tab , turnoActual, nivelesBajar, a);
		}
	}

	// Creación de los siguientes nodos
	private Arbol(Tablero anterior, int turn, int nivelesBajar, int numTableroHijo) {
		this.nHijos = anterior.espVac() - 1;
		int turnoActual = (turn%2)+1;
		if(nHijos < 0) {
			int i = -1;
			while(numTableroHijo >= 0 && i<8) {
				i++;
				if(this.tab.modificarTablero(i, turnoActual)) {
					return;
				}
			}
		}
		else {
			this.tab = new Tablero(anterior);

			int i = -1;
			while(numTableroHijo >= 0 && i<8) {
				i++;
				if(this.tab.modificarTableroPos(i, turnoActual)) {
					numTableroHijo--;
				}
			}
			this.tab.modificarTablero(i, turnoActual);
			if(nivelesBajar > 0){
				hijos = new Arbol[nHijos];
				for (int a =0 ; a<nHijos ; a++){
					if(this.tab.espVac() - nivelesBajar>0)
					hijos[a] = new Arbol(this.tab, turnoActual, nivelesBajar-1,a);
				}
			}
		}
	}

	public void podarArbol() {
		this.podarArbol(nivelesBajar, -500, true);
	}

	// True - Buscar los maximos, False - Buscar los minimos
	public int podarArbol(int nivel, int alfa, boolean type) {
		
		if(nivel<=nHijos)
		if(nivel>0) {
			Random rand = new Random();
			if(type) { // Maximos
				int maxAlpha = -500, hijo=-1;
				for(int i=0;i<nHijos;i++) {
					int x = hijos[i].podarArbol(nivel-1, alfa, true);
					if(rand.nextInt(2) == 0) {
						if(maxAlpha < x) {
							maxAlpha = x;
							hijo = i;
						}
					}
					else {
						if(maxAlpha <= x) {
							maxAlpha = x;
							hijo = i;
						}
					}
				}
				Arbol auxiliar[] = new Arbol[1];
				auxiliar[0] = hijos[hijo];
				hijos = auxiliar;
				return maxAlpha;
			}
			else { // Minimos
				int minAlpha = 500, hijo = -1;
				for(int i=0;i<nHijos;i++) {
					int x = hijos[i].podarArbol(nivel-1, alfa, true);
					if(rand.nextInt(2) == 0) {
						if(minAlpha > x) {
							minAlpha = x;
							hijo = i;
						}
					}
					else {
						if(minAlpha >= x) {
							minAlpha = x;
							hijo = i;
						}
					}
				}
				Arbol auxiliar[] = new Arbol[1];
				auxiliar[0] = hijos[hijo];
				hijos = auxiliar;
				return minAlpha;
			}
		}
		else {
			return this.tab.heuristica();
		}
		else return -1;
	}

	// Uso del poderoso poder que usa el poderoso alfa/beta
/*	public int podarArbol(int nn,int raiz, int k) {
		Arbol hijoFavorito = null ; 
		int mayVal = 0 ;
		if (nn> 0)
		{
			for(int a = 0 ; a < this.nHijos ; a ++)
			{
				int valorH = this.hijos[a].podarArbol(nn-1,raiz);

				if (a == 0)
				{
					mayVal = valorH;
					hijoFavorito = this.hijos[a];
				}
				else if(valorH == mayVal)
				{
					Random rand = new Random();

					if( (rand.nextInt(10)) > 5)
					{
						mayVal = valorH;
						hijoFavorito =  this.hijos[a];
					}
				}
				else if (valorH > mayVal)
				{
					mayVal = valorH;
					hijoFavorito =  this.hijos[a];
				}


			}
		}
		else if(nn == 0)
		{
			return this.valor;
		}

		int val = this.valor + mayVal;

		//if (nn != raiz)
		{
			this.hijos = new Arbol[1];
			this.hijos[0] = hijoFavorito;
			this.nHijos = 1;
		}
		return val;

	}*/

}
