:-dynamic(pinza/0).

caja(azul).
caja(verde).
habitacion(h1).
habitacion(h2).
puerta(h1,h2).

cajaEn(azul,h1).
cajaEn(verde,h1).
cajasHabitacion(h1,[azul,verde]).
cajasHabitacion(h2,[]).

pinza().
robot(h1).
posRobot(H):- robot(H).

%Comprueba si esta vacia
plib():- pinza(),write('yes'),nl.
plib():- not(pinza()),write('no'),nl.
%falta quitarla de las cajas del cuarto
eliminar:- write('yes2.1'),retractall(pinza()),write('yes2.2'),nl,!.
agregar:- assert(pinza(Cajita)),write('yes3'),nl,!.
coger():- write('Elemento a coger'),read(Cajita),caja(Cajita),posRobot(H),cajaEn(Cajita,H),plib()
    ,eliminar,agregar.

ejecutar(Opcion):- Opcion == 1,coger(),menu;
				Opcion == 2,plib(),menu;
				Opcion == 0,true.
menu:- write('1. coger: (Nombre de la caja)'),nl,write('2. vacia pinza ?'),nl,write('0. salir')
    ,read(Opcion),ejecutar(Opcion).











