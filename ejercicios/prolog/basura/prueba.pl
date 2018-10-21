


%lista de elementos de larbol
estado(cajaEn(azul,h1),cajaEn(verde,h1),robot(h1)).
objetivo(cajaEn(azul,h2),cajaEn(verde,h1),robot(h2)).

/*
estado(cajaEn(azul,h1),cajaEn(verde,h1),robot(h1)).
objetivo(cajaEn(azul,h2),cajaEn(verde,h1),robot(h2)).
*/

cicloACompObjetivo():-
    %alguna de estas se cumpla
    %o que la caja azul este en el cuarto equivocado
    (   (   cActCuartoC(CAa,azul),cObjCuartoC(COa,azul),CAa \== COa);
    %o que la caja verde este en el cuarto equivocado
    (   cActCuartoC(CAv,verde),cObjCuartoC(COv,verde), CAv \== COv);
    %o que el robot este en el cuarto equivocado
    (   cActCuartoRob(CAr),cObjCuartoRob(COr), CAr \== COr)),

    %entonces decide actuar
    actuar(),
    cicloACompObjetivo()
    .


%nodo([coger(1),cambiarCuarto(2),soltar(3)]).


%esta es la funcion que se llama para decidir cual es el siguiente paso
actuar():-accion(N,Col), N = 1 ,/**/ coger(Col).
actuar():-accion(N,H1,H2), N = 2,/**/ cambiarC(H1,H2).
actuar():-accion(N), N = 3, /**/ soltarC().



% peligro si saben lo que les conviene, no pasen de este punto peligro
% ya no se si siquiera entiendo lo que esta pasando, aunque falta
% terminar las funciones aNombre, principalmente aCCuarto y aSoltar









%estas funciones deciden cual es la suiguiente accion a tomar

% algo le llama la atencion en las cajas regadas en el piso, por lo que
% decide recojer una
accion(N,Col):- aCoger(AC,Col),aCCuarto(ACC,_,_),aSoltar(AS),
    AC > ACC , AC > AS , N is 1.
% le dan unas extrañas ganas de cambiar de cuarto, por lo que cambia de
% cuarto
accion(N,H1,H2):- aCoger(AC,_),aCCuarto(ACC,H1,H2),aSoltar(AS),
    AC < ACC , AC > AS , N is 2 .
% decide que realmente quiere soltar el cubo que tiene
accion(N):- aCoger(AC,_),aCCuarto(ACC,_,_),aSoltar(AS),
    AC > ACC , AC < AS , N is 3 .






% este pequeño conjunto de funciones supone facilitar la vida a la hora
% de sacar valores de los estados

% saca los cuartos en el estado actual
cActCuartoC(Cuarto, Col):- Col == azul , estado([_|Cuarto],_,_). % caja azul
cActCuartoC(Cuarto, Col):- Col == verde , estado(_,[_|Cuarto],_).% caja verde
cActCuartoRob(Cuarto):- estado(_,_,[Cuarto|[]]). % robot

% saca los cuartos en el estado objetivo
cObjCuartoC(Cuarto,Col):- Col == azul , objetivo([_|Cuarto],_,_). % caja azul
cObjCuartoC(Cuarto,Col):- Col == verde , objetivo(_,[_|Cuarto],_).% caja verde
cObjCuartoRob(Cuarto):- objetivo(_,_,[Cuarto|[]]). % robot






% importancia 15, ya que verdaderamente es lo que nuestro pequeño rob mas
% desea en la vida
%cajaEn(azul,h2)
aCoger(Imp,Col):-
    cActCuartoRob(H) ,% conocer la ubicacion del robot
    Col = azul,%para la caja azul
    cActCuartoC(H,Col),%estado actual caja
    cObjCuartoC(H2,Col),%estado final
    H \== H2 , % en caso de ser diferente, significa que el cubo quiere cambiar
    /**/ plib,
    Imp is 15.

aCoger(Imp,Col):-
    cActCuartoRob(H) ,% conocer la ubicacion del robot
    Col = verde,% para la caja verde
    cActCuartoC(H,Col),%estado actual caja
    cObjCuartoC(H2,Col),%estado final
    H \== H2 , % en caso de ser diferente, significa que el cubo quiere cambiar
    /**/plib,
    Imp is 15.

%importancia 10
aCCuarto(Imp,H,H2):- %con caja
   /**/ noplib,
   /**/ cuboenpinza(Col),
   cObjCuartoC(HH,Col),
   cActCuartoRob(Cr),
   Cr \== HH,
   H is Cr,
   H2 is HH,
   Imp is 10.

aCCuarto(Imp,H,H2):- %sin caja
   cActCuartoRob(H),
   cObjCuartoRob(H2),
   H \== H2,
   /**/ puertaEntre(H,H2),
   Imp is 10.

% importancia 20, va a querer soltar lo que traiga para poder hacer algo
% mas, pero solo si el cubo asi lo quiere
% % Cubo: no me sueltes Rob-senpai
% % Rob: nunca te soltaria caja-chan
%   *procede a soltar a caja-chan*
% por favor quitar esto antes de entregar
aSoltar(Imp):-
    /**/ noplib, % pinza no vacia preguntarle a camilo como organizo esto
    /**/ cuboenpinza(Col), % para saber cual es el cubo en la pinza
    cActCuartoRob(H),% saber ubicacion de rob
    cObjCuartoC(H,Col), % el objetivo es el cuarto en el que esta rob
    Imp is 20.


