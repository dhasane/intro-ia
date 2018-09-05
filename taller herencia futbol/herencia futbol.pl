



% es(persona).
contiene(persona, derecho).

es(hombreAdulto,persona).
contiene(hombreAdulto,1.80).


es(jugadorFutbol,hombreAdulto).
contiene(jugadorFutbol,1.85,3).



es(defensa,jugadorFutbol).
contiene(defensa,1).

es(delantero,jugadorFutbol).
contiene(delantero,3).


eq(edith,millonarios).
eq(miguel,santafe).




inst(edith,defensa).

inst(miguel,delantero).

goles(Nombre,Ngoles):-
    inst(Nombre,Pos),contiene(Pos,Ngoles).
altura(Nombre,Altura):-
    inst(Nombre,Pos),es(Pos,Pos2),contiene(Pos2,Altura,_).
equipo(Nombre,Equipo):-
    %inst(Nombre,Pos),
    eq(Nombre,Equipo).
