



% es(persona).
contiene(persona, derecho).

es(hombreAdulto,persona).
contiene(hombreAdulto,1.80).
cAltura(hombreAdulto,Altura):- contiene(hombreAdulto,Altura,_),!.

es(jugadorFutbol,hombreAdulto).
contiene(jugadorFutbol,1.85,3).
cAltura(jugadorFutbol,Altura):- contiene(jugadorFutbol,Altura,_),!.
cGoles(jugadorFutbol,Gol):- contiene(jugadorFutbol,_,Gol),!.

es(defensa,jugadorFutbol).
contiene(defensa,1).
cGoles(defensa,Gol):- contiene(defensa,Gol),!.

es(delantero,jugadorFutbol).
contiene(delantero,3).
cGoles(delantero,Gol):- contiene(delantero,Gol),!.


eq(edith,millonarios).
eq(miguel,santafe).


es(edith,defensa).
es(miguel,delantero).

/*
cual(N,Pos):- es(N,Pos).
cual(N,Pos):- es(N,Pos2),cual(Pos2,Pos).


goles(Nombre,Ngoles):-
    cual(Nombre,P),cGoles(P,Ngoles).

altura(Nombre,Altura):-
    cual(Nombre,P),cAltura(P,Altura).
equipo(Nombre,Equipo):-
    %inst(Nombre,Pos),
    eq(Nombre,Equipo).
*/
/*este ya esta completamente funcional
goles(Nombre,Ngoles):-
    inst(Nombre,Pos),contiene(Pos,Ngoles).
altura(Nombre,Altura):-
    inst(Nombre,Pos),es(Pos,Pos2),contiene(Pos2,Altura,_).
equipo(Nombre,Equipo):-
    %inst(Nombre,Pos),
    eq(Nombre,Equipo).
*/


