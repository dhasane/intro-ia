% Instrucciones de uso:
% Usar go([estado inicial],[estado final])
% Los estados tienen la forma [Robot,CajaAzul,CajaVerde,CajaMorada,Pinza]
% Ej: go([h1,h1,h1,h1,v],[h2,h1,v,h2,cv]).


% Funciones cuyo funcionamiento y razon de existir se deben confiar a seres trascendidos
empty_set([]).  %Set vacio
empty_sort_queue([]). %Cola vacia
insert_sort_queue(State, [], [State]). %Insertar a la cola ordenada (1 ite)
insert_sort_queue(State, [H|T], [H | T_new]) :-  %Insertar a la cola ordenada (Mas elementos)
    insert_sort_queue(State, T, T_new).
remove_sort_queue(First, [First|Rest], Rest). %Quitar de la cola ordenada
add_to_set(X, S, [X|S]).
add_to_set(X, S, S) :- member(X, S), !.  %Agrega al set, al ser member positivo da True
member_sort_queue(E, S) :- member(E, S). %Comprueba si es miembro de la cola ordenada
member_set(E, S) :- member(E, S). %Comprueba si es miembro del set


% Guarda los valores de los estados en forma de una lista
% G: Posición
% H: Valor Heuristico
% F: F
% Costo: Valor de función de costo
% Lista: Siguiente estado
state_record(State, Parent, G, H, F, Costo, [State, Parent, G, H, Costo, F]).

% Inicia Start estado inicial, Goal estado final.
% Los caminos estan dados por path
% Open cola los estados abiertos (Posibles), Closed los estados cerrados
go(Start, Goal) :-
    empty_set(Closed),
    empty_sort_queue(Empty_open),
    heuristica(Start, Goal, H,_,_,_,_,_),

    state_record(Start, nil, 0, H, H, 0, First_record),
    insert_sort_queue(First_record, Empty_open, Open),
    path(Open,Closed, Goal).

%Cola ordenada vacia
path(Open_pq, _,_) :-
       empty_sort_queue(Open_pq),
       write('No hay solucion.').


%Siguiente ultimo estado, final
%Escribe los estados en orden
path(Open, Closed, Goal) :-
    %saca el primer elemento
    remove_sort_queue(First_record, Open, _),
    state_record(State, _, _, _, _, _, First_record),
    State = Goal,
    write('El camino de la solución es: '), nl,
    printsolution(First_record, Closed).

% Siguiente no es ultimo 
% Genera sus hijos, agrega a abiertos y continua
path(Open, Closed, Goal) :-
    %saca el primer elemento de la lista
    remove_sort_queue(First_record, Open, Rest_of_open),
   	%Se guardan todos los hijos en children
    (bagof(Child, moves(First_record, Open, Closed, Child, Goal), Children);Children = []),
    insert_list(Children, Rest_of_open, New_open),
    add_to_set(First_record, Closed, New_closed),
    path(New_open, New_closed, Goal),!.


% Genera todos los hijos a los que no se ha pasado a abierto o cerrado y se unen dependiendo de sus valores heuristicos
moves(State_record, Open, Closed,Child, Goal) :-
    state_record(State, _, G, _, _, Costo, State_record),

   	opcion(State, Next, CostoOpcion),
   	NewCosto is Costo+CostoOpcion,
    
    state_record(Next, _, _, _, _, _, Test),
    not(member_sort_queue(Test, Open)),
    not(member_set(Test, Closed)),
    G_new is G + 1,
    heuristica(Next, Goal, H,_,_,_,_,_),
    F is G_new + H,
    state_record(Next, State, G_new, H, F, NewCosto, Child).

% Funciones de Coger
% Azul
opcion(State,Next,CostoOpcion):- 
    
    s(C1,State,L1), 
    s(C2,L1,L2),
    s(C3,L2,L3),
    s(C4,L3,L4),
    s(C5,L4,_), C5 == v, C1 == C2,
    CostoOpcion is 2,
    Next = [C1,v,C3,C4,ca].
% Verde
opcion(State,Next,CostoOpcion):- 
    
    s(C1,State,L1),
    s(C2,L1,L2),
    s(C3,L2,L3),
    s(C4,L3,L4),
    s(C5,L4,_), C5 == v, C1 == C3,
    CostoOpcion is 2,
    Next = [C1,C2,v,C4,cv].
% Morada
opcion(State,Next,CostoOpcion):- 
    
    s(C1,State,L1),
    s(C2,L1,L2),
    s(C3,L2,L3),
    s(C4,L3,L4),
    s(C5,L4,_), C5 == v, C1 == C4,
    CostoOpcion is 2,
    Next = [C1,C2,C3,v,cm].

% Funciones de Movimiento 
opcion(State,Next,CostoOpcion):- 
    
    s(C1,State,L1),
    s(C2,L1,L2), 
    s(C3,L2,L3),
    s(C4,L3,L4), 
    s(C5,L4,_), C1 == h1,
    CostoOpcion is 1,
    Next = [h2,C2,C3,C4,C5].

opcion(State,Next,CostoOpcion):- 
    
    s(C1,State,L1),
    s(C2,L1,L2), 
    s(C3,L2,L3),
    s(C4,L3,L4), 
    s(C5,L4,_), C1 == h2,
    CostoOpcion is 1,
    Next = [h1,C2,C3,C4,C5].

% Funciones de Soltar
% Azul
opcion(State,Next,CostoOpcion):-
    
    s(C1,State,L1), 
    s(_,L1,L2),
    s(C3,L2,L3),
    s(C4,L3,L4),
    s(C5,L4,_), C5 \== v,
    CostoOpcion is 4,
    Next = [C1,C1,C3,C4,v].
% Verde    
opcion(State,Next,CostoOpcion):-
    
    s(C1,State,L1), 
    s(C2,L1,L2),
    s(_,L2,L3),
    s(C4,L3,L4),
    s(C5,L4,_), C5 \== v,
    CostoOpcion is 4,
    Next = [C1,C2,C1,C4,v].
% Morada
opcion(State,Next,CostoOpcion):- 
    
    s(C1,State,L1), 
    s(C2,L1,L2),
    s(C3,L2,L3),
    s(_,L3,L4),
    s(C5,L4,_), C5 \== v,
    CostoOpcion is 4,
    Next = [C1,C2,C3,C1,v].

% Funcion que sirve para recorrer listas en las opciones
s(Cabeza,[Cabeza|LoDemas],LoDemas).

% Inserta en la lista de resultados y la cola ordenada
insert_list([], L, L).
insert_list([State | Tail], L, New_L) :-
    insert_sort_queue(State, L, L2),
    insert_list(Tail, L2, New_L).



% Inicio de funcion heuristica
costoRobot([X,_,_,_,_],[A,_,_,_,_], Difer):-((X\==A) , Difer is 1) ; (X==A), Difer is 0.
costoAzul([_,X,_,_,_],[_,A,_,_,_], Difer):-((X\==A) , Difer is 1) ; (X==A), Difer is 0.
costoVerde([_,_,X,_,_],[_,_,A,_,_], Difer):-((X\==A) , Difer is 1) ; (X==A), Difer is 0.
costoMorado([_,_,_,X,_],[_,_,_,A,_], Difer):-((X\==A) , Difer is 1) ; (X==A), Difer is 0.
costoPinza([_,_,_,_,X],[_,_,_,_,A], Difer):-((X\==A) , Difer is 1) ; (X==A), Difer is 0.

heuristica(Nodo, Fin, Costo, A,B,C,D,E):- costoRobot(Nodo, Fin, A), costoAzul(Nodo, Fin, B),costoVerde(Nodo, Fin, C),costoMorado(Nodo,Fin,D),costoPinza(Nodo, Fin, E), Costo is A+B+C+D+E.
% Fin de funcion heuristica

% Predicados para impresion de solucion
% Primero en la lista
printsolution(Next_record, _):-
    state_record(State, nil, _, H, _, C, Next_record),
    write(State), write(' Valor Heuristico: '), write(H),
    write(', Costo actual: '), write(C),nl.


% El resto de la lista
printsolution(Next_record, Closed) :-
    state_record(State, Parent, _, H, _, C, Next_record),
    state_record(Parent, _, _, _, _, _, Parent_record),
    member_set(Parent_record, Closed),
    printsolution(Parent_record, Closed),
    write(State), write(' Valor Heuristico: '), write(H),
    write(', Costo actual: '), write(C), nl.

% End of file
