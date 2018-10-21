package triqui;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.URL;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

public class GUI extends JFrame implements ActionListener{

	private static final long serialVersionUID = 1L;
	URL urlX = Main.class.getResource("/resources/X.png");
	URL urlO = Main.class.getResource("/resources/O.png");
	URL urlW = Main.class.getResource("/resources/W.png");
	URL urlT = Main.class.getResource("/resources/Tr.png");
	ImageIcon iconX = new ImageIcon(urlX);
	ImageIcon iconO = new ImageIcon(urlO);
	ImageIcon iconW = new ImageIcon(urlW);
	ImageIcon iconT = new ImageIcon(urlT);
	

	
	Arbol arb;
	private JPanel contentPane;
	private JButton button_0;
	private JButton button_1;
	private JButton button_2;
	private JButton button_3;
	private JButton button_4;
	private JButton button_5;
	private JButton button_6;
	private JButton button_7;
	private JButton button_8;
	private JButton btnNewGame;
	private JLabel actTurn;
	private int turno;
	Tablero tablero;


	/**
	 * Create the frame.
	 */
	public GUI() {
		
		this.setIconImage(iconT.getImage());
		setTitle("Triqui IA");
		turno = 1;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 240, 340);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		
		setContentPane(contentPane);
		contentPane.setLayout(null);

		button_0 = new JButton();
		button_0.setBounds(28, 103, 50, 50);
		button_0.addActionListener(this);
		button_0.setActionCommand("0");
		button_0.setIcon(iconW);
		contentPane.add(button_0);

		button_1 = new JButton();
		button_1.setBounds(88, 103, 50, 50);
		button_1.addActionListener(this);
		button_1.setActionCommand("1");
		button_1.setIcon(iconW);
		contentPane.add(button_1);

		button_2 = new JButton();
		button_2.setBounds(148, 103, 50, 50);
		button_2.addActionListener(this);
		button_2.setActionCommand("2");
		button_2.setIcon(iconW);
		contentPane.add(button_2);

		button_3 = new JButton();
		button_3.setBounds(28, 164, 50, 50);
		button_3.addActionListener(this);
		button_3.setActionCommand("3");
		button_3.setIcon(iconW);
		contentPane.add(button_3);

		button_4 = new JButton();
		button_4.setBounds(88, 164, 50, 50);
		button_4.addActionListener(this);
		button_4.setActionCommand("4");
		button_4.setIcon(iconW);
		contentPane.add(button_4);

		button_5 = new JButton();
		button_5.setBounds(148, 164, 50, 50);
		button_5.addActionListener(this);
		button_5.setActionCommand("5");
		button_5.setIcon(iconW);
		contentPane.add(button_5);

		button_6 = new JButton();
		button_6.setBounds(28, 225, 50, 50);
		button_6.addActionListener(this);
		button_6.setActionCommand("6");
		button_6.setIcon(iconW);
		contentPane.add(button_6);

		button_7 = new JButton();
		button_7.setBounds(88, 225, 50, 50);
		button_7.addActionListener(this);
		button_7.setActionCommand("7");
		button_7.setIcon(iconW);
		contentPane.add(button_7);

		button_8 = new JButton();
		button_8.setBounds(148, 225, 50, 50);
		button_8.addActionListener(this);
		button_8.setActionCommand("8");
		button_8.setIcon(iconW);
		contentPane.add(button_8);

		btnNewGame = new JButton("New Game");
		btnNewGame.setBounds(28, 32, 170, 23);
		btnNewGame.addActionListener(this);
		btnNewGame.setActionCommand("New");
		contentPane.add(btnNewGame);

		JLabel lblTurno = new JLabel("Turno:");
		lblTurno.setBounds(45, 78, 46, 14);
		contentPane.add(lblTurno);

		actTurn = new JLabel();
		actTurn.setBounds(112, 78, 46, 14);
		actTurn.setText("O");
		contentPane.add(actTurn);
		
		JLabel label = new JLabel("");
		label.setIcon(new ImageIcon(GUI.class.getResource("/resources/bg.png")));
		label.setBounds(0, 0, 224, 301);
		contentPane.add(label);

		tablero = new Tablero();
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String action = e.getActionCommand();

		boolean cambio = false;
		
		//Si el boton tiene el comando de acción de "ingresar" va a la pestaña 1 
		if(action.equals("New")){
			cambio = false;
			turno = 1;
			actTurn.setText("O");
			tablero = new Tablero();
			button_0.setIcon(iconW);
			button_1.setIcon(iconW);
			button_2.setIcon(iconW);
			button_3.setIcon(iconW);
			button_4.setIcon(iconW);
			button_5.setIcon(iconW);
			button_6.setIcon(iconW);
			button_7.setIcon(iconW);
			button_8.setIcon(iconW);
		}
		else if(action.equals("0")){
			cambio = tablero.modificarTablero(0, turno+1);
			if(cambio)
				if(turno==1)
					button_0.setIcon(iconO);
				else
					button_0.setIcon(iconX);
		}
		else if(action.equals("1")){
			cambio = tablero.modificarTablero(1, turno+1);
			if(cambio)
				if(turno==1)
					button_1.setIcon(iconO);
				else
					button_1.setIcon(iconX);
		}
		else if(action.equals("2")){
			cambio = tablero.modificarTablero(2, turno+1);
			if(cambio)
				if(turno==1)
					button_2.setIcon(iconO);
				else
					button_2.setIcon(iconX);
		}
		else if(action.equals("3")){
			cambio = tablero.modificarTablero(3, turno+1);
			if(cambio)
				if(turno==1)
					button_3.setIcon(iconO);
				else
					button_3.setIcon(iconX);
		}
		else if(action.equals("4")){
			cambio = tablero.modificarTablero(4, turno+1);
			if(cambio)
				if(turno==1)
					button_4.setIcon(iconO);
				else
					button_4.setIcon(iconX);
		}
		else if(action.equals("5")){
			cambio = tablero.modificarTablero(5, turno+1);
			if(cambio)
				if(turno==1)
					button_5.setIcon(iconO);
				else
					button_5.setIcon(iconX);
		}
		else if(action.equals("6")){
			cambio = tablero.modificarTablero(6, turno+1);
			if(cambio)
				if(turno==1)
					button_6.setIcon(iconO);
				else
					button_6.setIcon(iconX);
		}
		else if(action.equals("7")){
			cambio = tablero.modificarTablero(7, turno+1);
			if(cambio)
				if(turno==1)
					button_7.setIcon(iconO);
				else
					button_7.setIcon(iconX);
		}
		else if(action.equals("8")){
			cambio = tablero.modificarTablero(8, turno+1);
			if(cambio)
				if(turno==1)
					button_8.setIcon(iconO);
				else
					button_8.setIcon(iconX);

		}
		if(cambio) {
			turno = (turno+1)%2;
			if(turno==1)
				actTurn.setText("O");
			else
				actTurn.setText("X");

		}
		
		if(tablero.win == 2) {
			infoMensaje("Ganó el jugador");
		}
		else if(tablero.win == 1) {
			infoMensaje("Ganó la Inteligencia Artificial");
		}
		else if(tablero.win == -1){
			infoMensaje("Juego Empatado");
		}
		else {
			if(turno == 0) {
				if(tablero.espVac() < 5) {
					int jugadaSig= tablero.mejorJugada();ActionEvent event = new ActionEvent(this, ActionEvent.ACTION_PERFORMED, Integer.toString(jugadaSig));
					this.actionPerformed(event);
				}
				else {
					arb = new Arbol(tablero);
					arb.podarArbol();
					int jugadaSig;
					if(tablero.casoX() != -1) {
						jugadaSig = tablero.casoX();
					}else {
						jugadaSig = tablero.marcarJugada(arb.hijos[0].tab);
					}
					ActionEvent event = new ActionEvent(this, ActionEvent.ACTION_PERFORMED, Integer.toString(jugadaSig));
					this.actionPerformed(event);
				}
				
			}
		}
		contentPane.setVisible(true);
		this.setVisible(true);
		
	}
	
	public void infoMensaje(String txt){
		JOptionPane.showMessageDialog(this,txt,
				"Información",JOptionPane.INFORMATION_MESSAGE);
	}
	
	public void errorMensaje(String txt){
		JOptionPane.showMessageDialog(this,txt,
				"Error",JOptionPane.ERROR_MESSAGE);
	}
}
