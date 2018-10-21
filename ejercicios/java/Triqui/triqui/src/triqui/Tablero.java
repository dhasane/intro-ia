package triqui;

import java.util.Random;

@SuppressWarnings("unused")
public class Tablero{

	/*' '= 0 
	 * X = 1
	 * O = 2 
	 */
	public int[][] tablero;
	public int win; // X = 1 ; O = 2
	public int valor; //  valor en el que se guarda el valor huristico del tablero 
	
	public Tablero()// para crear nuevos y bonitos tableros
	{
		tablero = new int[3][3];

		for (int[] cs : tablero) 
		{
			for (int cs2 : cs) 
			{
				cs2 = 0;
			}
		}
		win = 0;
	}

	public Tablero(Tablero tab) // para copiar tableros
	{
		tablero = new int[3][3];

		for (int a =0 ; a < 3 ; a ++) 
		{
			for (int b = 0; b < 3 ; b++ ) 
			{
				this.tablero[a][b] = tab.tablero[a][b];
			}
		}
		valor = heuristica();
	}

	public void show() {
		int i = 1;
		System.out.println();
		for (int[] cs : tablero) {
			System.out.print("|");
			for (int cs2 : cs) {
				if(cs2==0)
					System.out.print(" |");
				else if(cs2==1)
					System.out.print("X|");
				else
					System.out.print("O|");
			}

			System.out.println();
		}
		System.out.println(valor);
	}

	public int espVac() {
		int total = 0;
		Tablero tab = this;
		for (int b = 0 ; b < 9; b++)
		{
			if ( tab.tablero[b/3][b%3] == 0)
			{
				total +=1;
			}
		}
		return total;
	}

	public int heuristica(){
		
		int[][] t = this.tablero;
		int nx=0, no=0, cont =0;

		//Caso 1
		for(int i=0;i<3;i++){
			if(t[0][i] == 1){
				nx++;
			}
			else if(t[0][i] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		//Caso 2
		nx=0;
		no=0;

		for(int i=0;i<3;i++){
			if(t[1][i] == 1){
				nx++;
			}
			else if(t[1][i] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		//Caso 3
		nx=0;
		no=0;
		for(int i=0;i<3;i++){
			if(t[2][i] == 1){
				nx++;
			}
			else if(t[2][i] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		//Caso 4
		nx=0;
		no=0;
		for(int i=0;i<3;i++){
			if(t[i][0] == 1){
				nx++;
			}
			else if(t[i][0] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		//Caso 5
		nx=0;
		no=0;
		for(int i=0;i<3;i++){
			if(t[i][1] == 1){
				nx++;
			}
			else if(t[i][1] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		//Caso 6
		nx=0;
		no=0;
		for(int i=0;i<3;i++){
			if(t[i][2] == 1){
				nx++;
			}
			else if(t[i][2] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		//Caso 7
		nx=0;
		no=0;
		int nnx=0,nno=0;
		for(int i=0;i<3;i++){
			if(t[i][i] == 1){
				nx++;
			}
			else if(t[i][i] == 2){
				no++;
			}

		}
		cont += comp(nx,no);

		//Caso 8
		nx=0;
		no=0;
		for(int i=0;i<3;i++){
			if(t[2-i][i] == 1){
				nx++;
			}
			else if(t[2-i][i] == 2){
				no++;
			}
		}
		cont += comp(nx,no);

		return cont;
	}

	static private int comp(int nx, int no){
		if(no==3 && nx ==0){
			return -100;    
		}
		else if(no==2 && nx ==0){
			return -5;    
		}
		else if(no==1 && nx ==0){
			return -1;
		}
		else if(no !=0 && nx !=0){
			return 0;
		}
		else if(nx ==1 && no ==0){
			return 1;
		}
		else if(nx ==2 && no ==0){
			return 5;
		}
		else if(nx ==3 && no ==0){
			return 100;
		}

		return 0;
	}

	public void ganador() {
		if(espVac()==0) {
			win = -1;
		}
		int nx=0,no=0;
		int[][] t = tablero;
		
		// Caso 1
		for(int i=0;i<3;i++){
			if(t[0][i] == 1){
				nx++;
			}
			else if(t[0][i] == 2){
				no++;
			}

		}
		
		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 2
		for(int i=0;i<3;i++){
			if(t[1][i] == 1){
				nx++;
			}
			else if(t[1][i] == 2){
				no++;
			}

		}

		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 3
		for(int i=0;i<3;i++){
			if(t[2][i] == 1){
				nx++;
			}
			else if(t[2][i] == 2){
				no++;
			}

		}

		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 4
		for(int i=0;i<3;i++){
			if(t[i][0] == 1){
				nx++;
			}
			else if(t[i][0] == 2){
				no++;
			}

		}

		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 5
		for(int i=0;i<3;i++){
			if(t[i][1] == 1){
				nx++;
			}
			else if(t[i][1] == 2){
				no++;
			}

		}

		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 6
		for(int i=0;i<3;i++){
			if(t[i][2] == 1){
				nx++;
			}
			else if(t[i][2] == 2){
				no++;
			}

		}

		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 7
		for(int i=0;i<3;i++){
			if(t[i][i] == 1){
				nx++;
			}
			else if(t[i][i] == 2){
				no++;
			}

		}

		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
		nx=0;
		no=0;

		// Caso 8
		for(int i=0;i<3;i++){
			if(t[2-i][i] == 1){
				nx++;
			}
			else if(t[2-i][i] == 2){
				no++;
			}
		}
		
		if(nx==3)
			win = 1;
		else if(no==3)
			win = 2;
	}

	// se modifica el tablero en la posicion espvac, agregandole el simbolo en turn (x u o)
	public boolean modificarTablero(int a, int turno) 
	{
		// 0,0 = 0 | 3,3 = 8
		if(this.tablero[a/3][a%3] == 0) {
			this.tablero[a/3][a%3] = turno;
			this.valor = this.heuristica(); // se le da valor al tablero despues de modificarlo
			this.ganador();
			return true;
		}
		else {
			return false;
		}
	}
	
	public boolean modificarTableroPos(int a, int turno) 
	{
		// 0,0 = 0 | 3,3 = 8
		if(this.tablero[a/3][a%3] == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public int mejorJugada() {
		
		int n=0;
		int tam = espVac();
		Tablero heritage[];
		int valores[] = new int[tam];
		heritage = new Tablero[tam];
		for(int i=0;i<tam;i++) {
			heritage[i] = new Tablero(this);
		}
		for(int i=0,j=0;i<tam;i++,j++) {
			boolean x;
			x = heritage[i].modificarTablero(j, 1);
			if(!x) {
				i--;
			}
			else {
				valores[i] = j;				
			}
		}
		int max = -500;
		for(int i=0;i<tam;i++) {
			if(max<heritage[i].valor) {
				max = heritage[i].valor;
				n = i;
			}
		}
		return valores[n];
	}
	
	public int marcarJugada(Tablero t) {
		int a = -1;
		for(int i=0;i<9;i++) {
			if(this.tablero[i/3][i%3] != t.tablero[i/3][i%3]) {
				a = i;
			}
		}
		return a;
	}
	
	public int casoX() {
		if(this.espVac() == 8 && tablero[1][1] == 0) {
			int mark = 0;
			for(int i=0;i<9;i++) {
				if(tablero[i/3][i%3] != 0) {
					return 4;
				}
			}
		}
		else{
			int cont = 0, mark = -1;
			for(int i=0;i<9;i++) {
				if(tablero[i/3][i%3] == 2) {
					cont++;
				}
			}
			if(cont == 2) {
				cont = 0;
				if(tablero[0][0] == 2 && tablero[2][2] == 2) {
					cont+=2;
				}
				if(tablero[0][2] == 2 && tablero[2][0] == 2) {
					cont+=2;
				}
			}
			
			if(cont == 2) {
				System.out.println("caso XX");
				Random rand = new Random();
				switch(rand.nextInt(4)) {
					case(0):{
						return 1;
					}
					case(1):{
						return 3;
					}
					case(2):{
						return 5;
					}
					case(3):{
						return 7;
					}
				}
				return this.mejorJugada();
			}
			else {
				if(tablero[0][0] == 2 && tablero[0][2] == 2) {
					return 1;
				}
				if(tablero[0][0] == 2 && tablero[2][0] == 2) {
					return 3;
				}
				if(tablero[2][2] == 2 && tablero[0][2] == 2) {
					return 5;
				}
				if(tablero[2][2] == 2 && tablero[2][0] == 2) {
					return 7;
				}
			}
		}
		return -1;
	}
}



