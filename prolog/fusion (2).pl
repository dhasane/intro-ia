%Se inicia "menu."
%Toca crearlo dinamico por que aja :v
:-dynamic(pinza/0).
:-dynamic(pinza/1).
:-dynamic(robot/1).
:-dynamic(cajaEn/2).
:-dynamic(cajasHabitacion/2).

:-dynamic(objRobot/1).
:-dynamic(cajaObjEn/2).

in():- ubicar(h1,h1,h1,h2,h2,h2,h2,h1).
ini():- init(h1,h1,h1,h2,h2,h2,h2,h1).
/*
cajaObjEn(azul,h1).
cajaObjEn(verde,h2).
objRobot(h2).
cajaEn(azul,h2).
cajaEn(verde,h1).
robot(h2).
*/
%----------------------------- objetivo
%lo que se sabe objetivo
cajaObjEn(azul,h1).
cajaObjEn(verde,h1).
cajaObjEn(morado,h2).
objRobot(h1).


%cajasObjHabitacion(h1,[azul,verde]).
%cajasObjHabitacion(h2,[]).

%Posicion del robot objetivo
posObjRobot(H):- objRobot(H).
%----------------------------- final objetivo

%----------------------------- estado actual
%lo que se sabe"
cajaEn(azul,h1).
cajaEn(verde,h1).
cajaEn(morado,h1).
robot(h2).


%cajasHabitacion(h1,[azul,verde]).
%cajasHabitacion(h2,[]).

cajasHabitacion(H,Col):- cajaEn(Col,H) .
%Posicion del robot
posRobot(H):- robot(H).
%----------------------------- final estado actual


%"objetos"
caja(azul).
caja(verde).
caja(morado).
habitacion(h1).
habitacion(h2).
puerta(h1,h2).

%Estados de la pinza (Siempre toma el primero cuando inicia el programa, no se pueden borrar
%los otros por que causa un error raro por algo dinamico)
pinza().
pinza(azul).
pinza(verde).
pinza(morado).

%Comprueba si existe puerta
existePuerta(X,Y):-
    (   puerta(X,Y); puerta(Y,X)),true.

%Comprueba si esta vacia
plib():-
    pinza()
    %,write('yes'),nl
    .

%dice que caja tiene
plib(Cajita):-
    not(plib()),
    pinza(Cajita)
    %,write('ni'),nl
    ,!.

%el menu

%Se agregan cosas a la pinza
llenarPinza(Cajita):-
    assert(pinza(Cajita)),
    !.
%Se quita la pinza vacia, se quita la habitacion de la caja, Este no se para que sirve lo dejare ahi por si acaso
%elimina las cajas de la habitacion, esto es lo que quiero arreglar arriba, agrega la lista de cajas a la habitacion
eliminarPinza():- retractall(pinza(_)).

%Se quita la pinza vacia, se quita la habitacion de la caja, Este no se para que sirve lo dejare ahi por si acaso
%elimina las cajas de la habitacion, esto es lo que quiero arreglar arriba, agrega la lista de cajas a la habitacion
eliminarCoger(Cajita):-
    posRobot(H),
    cajasHabitacion(H,Cajita),
    retractall(pinza()),
    eliminarPinza(),
    retractall(cajaEn(Cajita,_)),
    %retractall(cajasHabitacion(H,_)),
    %assert(cajasHabitacion(H,L)),
    %assert(cajasHabitacion(H)),
    !.


%Se coloca que se llena la pinza
agregarCoger(Cajita):-
    llenarPinza(Cajita).
%La caja que quiere leer, la caja, mira si la caja existe, obtiene posicion del robot, mira si
%ambos estan en el mismo cuarto, mira si la pinza esta vacia
%se hace lo de arriba, se hace lo de arriba

coger(Cajita):-
    caja(Cajita),
    posRobot(H),
    cajaEn(Cajita,H),
    plib(),
    eliminarCoger(Cajita),
    agregarCoger(Cajita).

/*
%Era para ver la posicion del robot creo que no se usa mas
posicion:-
    posRobot(H),
    write(H),
    nl.
*/
%se elimina el robot del cuarto donde esta
eliminarMover(De):-
    retractall(robot(De)),
    !.

%se agrega el robot al cuarto que quiere ir
agregarMover(A):-
    assert(robot(A)),
    !.
%Se piden los cuartos, comprueba si hay puerta, y pues lo mismo de arriba

mover(De,A):-
    existePuerta(De,A),
    eliminarMover(De),
    agregarMover(A).

%Falta agregar la caja al cuato cuando se agrega

%Se mira la pos del roboto (Creo que no es necesario, si algo luego se quita, pero por ahora dejelo ahi),
%elimina la pinza de la garra
eliminarSoltar(Cajita):-
    retractall(pinza(Cajita)),
    !.

%La posicion del robot (aqui si importa), agrega a L(lista antigua) la nueva caja,
%elimina las cajas de la habitacion, agrega la nueva lista (L), a la caja le agrega el cuarto al que corresponde
agregarSoltar(Cajita):-
    posRobot(H),
    cajaObjEn(Cajita,H),
    assert(cajaEn(Cajita,H)),
    !.

%Mira si la pinza tiene algo, hace lo de arriba, hace lo de arriba, se agrega la pinza vacia
soltar():-
    plib(Cajita),
    agregarSoltar(Cajita),
    eliminarSoltar(Cajita),
    assert(pinza()).


%---------------------------------------------------------------------------------
help():-
    nl, write('son 6 datos, solo pueden ser h1 o h2'),nl,
    nl, write('los primeros 3 son del estado actual y los ultimos 3 son del estado objetivo'),nl.
init(Ar,Aa,Av,Am,Or,Oa,Ov,Om):-
    ubicar(Ar,Aa,Av,Am,Or,Oa,Ov,Om),
    %Tot is 0,
    not(cicloObjetivo(50,0)),
    nl,write('------------------------------------'),nl,
    write('se ha llegado al estado objetivo').


ubicar(Ar,Aa,Av,Am,Or,Oa,Ov,Om):-
    retractall(robot(_)),
    assert(robot(Ar)),

    retractall(objRobot(_)),
    assert(objRobot(Or)),

    retractall(cajaEn(azul,_)),
    assert(cajaEn(azul,Aa)),

    retractall(cajaEn(verde,_)),
    assert(cajaEn(verde,Av)),

    retractall(cajaObjEn(azul,_)),
    assert(cajaObjEn(azul,Oa)),

    retractall(cajaObjEn(verde,_)),
    assert(cajaObjEn(verde,Ov)),

    retractall(cajaEn(morado,_)),
    assert(cajaEn(morado,Am)),

    retractall(cajaObjEn(morado,_)),
    assert(cajaObjEn(morado,Om)).



cicloObjetivo(Cic, Tot):-
    not(final()),
    Cic > 0,
    nl,write('------------------------------------'),nl,
    imp(),
    accion( Val ),
    %/*
    (
        %(   heuristica(Heu), nl,write('heuristica '),write( Heu ));
        not(heuristica(_));
        heuristica(_)
    ),
    %*/
    NTot is Tot + Val,
    nl,write('valor total es '),write(NTot),nl,
    imp(),

    not(final()),
    NCic is Cic -1,
    cicloObjetivo(NCic,NTot)
    %,read(A)
    .

heuristica(Dif):-

     (

         heu(azul,Difa);
         heu(verde,Difv);
         heu(morado,Difm)


    ),

     posObjRobot(COr) , posRobot(CAr),
     (
                            (   ( CAr \== COr), Difr is  1);
                            (  ( CAr == COr), Difr is 0 )


     ),
     %------------------------

     Dif is Difa + Difv + Difm + Difr ,
     write('Heuristica '+ Dif)
    .

heu(Col,Dif):-
   aheu(Col,Dif);(not(aheu(Col,Dif)),Dif is 0) .

aheu(Col,Dif):-
    posRobot(CAr),
    cajaEn(Col,CAc),
    cajaObjEn(Col,COc) ,
    (   (
           ( CAc \== COc),
           (CAr == CAc),
           Dif is 1
         );

        (
            ( CAc \== COc),
            (CAr \== COc),
            Dif is 2
        )
    )
    .
/*
 posRobot(CAr),cajaEn(morado,CAc),cajaObjEn(morado,COc),( CAc \== COc),(CAr /== CAc).
 posRobot(CAr),cajaEn(morado,CAc),cajaObjEn(morado,COc),(CAr /== CAc).
*/
/*



    (
        posRobot(CAr);%h1 o h2
    cajaEn(azul,CAa); %h1 , h2 o Na
    cajaEn(verde,CAv);%h1 , h2 o Na
    cajaEn(morado,CAm)%h1 , h2 o Na

    ),(
        posObjRobot(COr);
         cajaObjEn(azul,COa);
         cajaObjEn(verde,COv);
         cajaObjEn(morado,COm)
    ),( CAa \== COa),
            (CAr == CAa),
            Diferencia is Diferencia + 1

    */

final():-
    (
        posRobot(CAr),cajaEn(azul,CAa), cajaEn(verde,CAv),cajaEn(morado,CAm)
    ),
    (
        posObjRobot(COr),cajaObjEn(azul,COa),cajaObjEn(verde,COv),cajaObjEn(morado,COm)
    ),
    (
        ( CAa == COa),
        ( CAv == COv),
        ( CAm == COm),
        ( CAr == COr)
    )
    .
imp():- write('ACT: '),impRob(),impCa(),impCv(),impCm(),nl,

    write('OBJ: '),impObjRob(),impObjCa(),impObjCv(),impObjCm(),nl,! .

impRob():- nl,write(' | RB : '),
    (posRobot(Dat),       write(Dat));(write('NA')).
impCa() :- write(' | CA : '),
    (cajaEn(azul,Dat) ,   write(Dat));(write('NA')).

impCv() :- write(' | CV : '),
    (cajaEn(verde,Dat),   write(Dat));(write('NA')).

impCm() :- write(' | CM : '),
    (cajaEn(morado,Dat),   write(Dat));(write('NA')).

impObjRob():- nl,write(' | RB : '),
    (posObjRobot(Dat)    ,write(Dat));(write('NA')).

impObjCa() :- write(' | CA : '),
    (cajaObjEn(azul,Dat) ,write(Dat));(write('NA')).

impObjCv() :- write(' | CV : '),
    (cajaObjEn(verde,Dat),write(Dat));(write('NA')).

impObjCm() :- write(' | CM : '),
    (cajaObjEn(morado,Dat),write(Dat));(write('NA')).



accion(Val):-
    (
        (   accionm(M), Val is M );
        (   accionc(C), Val is C );
        (   accions(S), Val is S )
    ),!.


accionc(I):-
    aCoger(AC,Col),
    aCCuarto(ACC,_,_),
    aSoltar(AS,_),
    AC >= ACC , AC >= AS ,
    coger(Col)
    ,nl,write('----- coger '+Col),nl
    ,I is AC
    ,!
     .
accionm(I):-
    aCoger(AC,_),
    aCCuarto(ACC,H1,H2),
    aSoltar(AS,_),
    %write('2'),
    ACC >= AC , ACC >= AS,
    %write(' mover') ,
    mover(H1,H2)
    ,nl,write('----- mover de '+H1+' a '+H2 ),nl
    ,I is ACC
    ,!

     .
accions(I):-
    aCoger(AC,_),
    aCCuarto(ACC,_,_),
    aSoltar(AS,Col),
    AS >= AC , AS >= ACC,
    %write(' soltar'),
    soltar()
    ,nl,write('----- soltar '+ Col),nl
    ,
    I is AS
    ,!
     .

%*/





%----------------------
%de aqui en adelante hay dos tipos de funciones
% aa : funciones que consiguen datos
% a : funciones que en caso que las aa sean false, retornaran 0




aCoger(Imp,Col):-
    (   not(aaCoger(Imp,Col)),Imp is 0 ,!);
    aaCoger(Imp,Col)
    ,!
    .
% importancia 15, ya que verdaderamente es lo que nuestro peque�o rob
% mas desea en la vida

aaCoger(Imp,azul):- %para la caja azul -- probado 2
    plib(),
    posRobot(H),cajaEn(azul,H),
    cajaObjEn(azul,H2) ,
    H \== H2 , % en caso de ser diferente, significa que el cubo quiere cambiar
    Imp is 15.
%plib(),posRobot(H),cajaEn(azul,H),cajaObjEn(azul,H2) ,H \== H2.
%
aaCoger(Imp,verde):- %para la caja -- probado 2
    plib(),
    (posRobot(H),cajaEn(verde,H)),
    (cajaObjEn(verde,H2)) ,
    H \== H2 , % en caso de ser diferente, significa que el cubo quiere cambiar
    Imp is 15.

aaCoger(Imp,morado):- %para la caja -- probado 2
    plib(),
    (posRobot(H),cajaEn(morado,H)),
    (cajaObjEn(morado,H2)) ,
    H \== H2 , % en caso de ser diferente, significa que el cubo quiere cambiar
    Imp is 15.



aCCuarto(Imp,H,H2):-
    (   not(aaCCuarto(Imp,H,H2)),Imp is 0 ,!);
    aaCCuarto(Imp,H,H2)
    ,!
    .

%hmmm(I,H,H2):-aCCuarto(I,H,H2).
%importancia 10
aaCCuarto(Imp,H,H2):- %con caja -- probado
   not(plib()),
   plib(Col),
   posRobot(H),
   cajaObjEn(Col,H2),
   H \== H2,
   %A is H,
   %B is H2,
   Imp is 10
   %, write('con caja'),nl
   %,!
   .


% H2,existePuerta(H,H2),write('funciona'),nl.
aaCCuarto(Imp,H,H2):- %sin caja -- probado
    plib(),
    posRobot(H),
    posObjRobot(H2) ,

    H \== H2,
    existePuerta(H,H2),
    %H is H,
    %H2 is H2,
    Imp is 10
    %, write('sin caja'),nl
    ,!
    .

aSoltar(Imp,Col):- % probado 2
    (   not(aaSoltar(Imp,Col)),Imp is 0 ,!);
    aaSoltar(Imp,Col)
    ,!
    .

aaSoltar(Imp,Col):- % -- probado 2
    not(plib()), % pinza no vacia
    plib(Col), % para saber cual es el cubo en la pinza
    posRobot(H),% saber ubicacion de rob
    cajaObjEn(Col,H), % el objetivo es el cuarto en el que esta rob
    Imp is 20.
