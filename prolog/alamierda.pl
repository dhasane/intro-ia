




estado(h1).
estado(h2).
estado(rob).
puerta(h1,h2).
existePuerta(X,Y):-
    (   puerta(X,Y); puerta(Y,X)),true.

%----------------------------- estado actual
%lo que se sabe"
estado(h1,h1,h1,h1).

est(R,A,V,M):- estado(R,A,V,M).
ubiC(azul,A):- estado(_,A,_,_).
ubiC(verde,V):- estado(_,_,V,_).
ubiC(morado,M):- estado(_,_,_,M).

%----------------------------- final estado actual

%----------------------------- objetivo
%lo que se sabe objetivo
%objetivo(rob,c azul, c verde, c morado
%

objetivo(h1,h1,h1,h1).

obj(R,A,V,M):- objetivo(R,A,V,M).

ubiOC(azul,A):- objetivo(_,A,_,_).
ubiOC(verde,V):- objetivo(_,_,V,_).
ubiOC(morado,M):- objetivo(_,_,_,M).

%----------------------------- final objetivo

init():-
    not(cicObj(50)),
    nl,write('------------------------------------'),nl,
    write('se ha llegado al estado objetivo').

cicObj(Cic):-
    Cic > 0,
    nl,write('------------------------------------'),nl,
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

accion(Val):-
    (
        (   accionm(M), Val is M );
        (   accionc(C), Val is C );
        (   accions(S), Val is S )
    ),!.

accionc(I):-
    aCoger(AC,Col),
    coger(Col)
    ,nl,write('----- coger '+Col),nl
    ,I is AC
    ,!
     .
accionm(I):-
    aCCuarto(ACC,H1,H2),
    mover(H1,H2)
    ,nl,write('----- mover de '+H1+' a '+H2 ),nl
    ,I is ACC
    ,!

     .
accions(I):-
    aSoltar(AS,Col),
    AS \== 0,
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

aaCoger(Imp,Col):- %para la caja azul -- probado 2
    plib(),
    est(H,_,_,_),ubiC(Col,H),
    ubiOC(Col,H2) ,
    H \== H2 , % en caso de ser diferente, significa que el cubo quiere cambiar
    Imp is 15.

aCCuarto(Imp,H,H2):-
    (   not(aaCCuarto(Imp,H,H2)),Imp is 0 ,!);
    (   aaCCuarto(Imp,H,H2))
    ,!
    .

%hmmm(I,H,H2):-aCCuarto(I,H,H2).
%importancia 10
aaCCuarto(Imp,H,H2):- %con caja -- probado
   not(plib()),
   plib(Col),
   est(H,_,_,_),
   ubiOC(Col,H2),
   H \== H2,
   Imp is 10
   %, write('con caja'),nl
   %,!
   .


% H2,existePuerta(H,H2),write('funciona'),nl.
aaCCuarto(Imp,H,H2):- %sin caja -- probado
    plib(),
    est(H,_,_,_),
    obj(H2,_,_,_) ,

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
    est(H,_,_,_),
    ubiOC(Col,H), % el objetivo es el cuarto en el que esta rob
    Imp is 20,
    soltar()
    .
