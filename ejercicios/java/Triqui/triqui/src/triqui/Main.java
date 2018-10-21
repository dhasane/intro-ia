package triqui;

import java.util.Random;

public class Main {
	public static void main(String[] args) {	
		GUI frame = new GUI();
		frame.setVisible(true);	
		Random rand = new Random();
		System.out.println(rand.nextInt(2));
	}
}
