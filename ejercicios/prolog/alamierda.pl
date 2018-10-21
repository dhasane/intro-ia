




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

% hice estas funciones para ponerlo un poco mas generico mas adelante
% las de objetivo funcionan igual y tienen el mismo objetivo
ubiC(azul,A):- estado(_,A,_,_). % consigue el estado de azul
ubiC(verde,V):- estado(_,_,V,_).% consigue el estado de verde
ubiC(morado,M):- estado(_,_,_,M).% consigue el estado de morado

%----------------------------- final estado actual

%----------------------------- objetivo
%lo que se sabe objetivo
%objetivo(rob,c azul, c verde, c morado
%

objetivo(h2,h2,h2,h2).

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
    heu(HE),

    not(final()),

    nl,write('------------------------------------'),nl,
    accion( _ ),

    not(final()),




    NCic is Cic -1,
    cicObj(NCic)
    .


final():- % cuando sean iguales
    est(R,A,V,M),obj(R,A,V,M)
    .

% inicio de las funcione de heuristica -------------------------------


heu(D):-
    cFin(azul,Da),
    cFin(verde,Dv),
    cFin(morado,Dm),
    rFin(Dr),
    D is Da + Dv + Dm + Dr,
    !
    .

% true si rob = estado final, false si rob dif a estado final


rFin(Dif):-
    (   not(rrFin()) , Dif is  1);
    (  rrFin() , Dif is 0 ) .

rrFin():- est(R,_,_,_),obj(R,_,_,_).


cFin(Col,Dif):-
   ccFin(Col,Dif);(not(ccFin(Col,Dif)),Dif is 0) .

% bloque este en cuarto diferente al objetivo y diferente al robot
ccFin(Col,Dif):-
    ubiC(Col,H),ubiOC(Col,H1), H\== H1,
    est(AR,_,_,_) , H \== AR,
    Dif is 2.

% bloque este en cuarto diferente al objetivo e igual al robot
ccFin(Col,Dif):-
    ubiC(Col,H),ubiOC(Col,H1), H\== H1,
    est(H,_,_,_) ,Dif is 1.




% final de las funcione de heuristica -------------------------------


accion(I):-
    accionc(I,azul),
    accionc(I,verde),
    accionc(I,morado),
    accionm(I),% solo es moverse de un cuarto al otro
    accions(I),% solo tiene sentido si ya habia cogido algo
    /*(
        (   accionm(M), Val is M );
        (   accionc(C), Val is C );
        (   accions(S), Val is S )
    )*/
    !.

accionc(I,Col):-
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
% importancia 15, ya que verdaderamente es lo que nuestro pequeño rob
% mas desea en la vida

aaCoger(Imp,Col):- %para cajas
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
%importancia 10
aaCCuarto(Imp,H,H2):- %con caja
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
    Imp is 20
    .
