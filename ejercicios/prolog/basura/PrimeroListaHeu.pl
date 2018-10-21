

/*
%saca el mayor valor de una lista, tuve que copiar un codigo casi completamente   para lograr entender esto....
mayor(Ccab, [],Ccab) .
mayor(Ccab, [Cab|L],May ):- Ccab > Cab, mayor(Ccab,L,May) .
mayor(Ccab, [Cab|L],May ):- Ccab =< Cab, mayor(Cab,L,May) .
mayor([Cab|L],May) :-mayor(Cab,L,May) .
*/

%hola = [4,5,6,7].

%hola([1,2,3,4,5].
%saca el mayor valor de una lista
mayor(Ccab, [],Ccab) .

mayor(Ccab, [Cab|L],May ):-
    heu(Ccab,Cab,Val1,Val2),
    Val1 > Val2,
    %Ccab > Cab,
    mayor(Ccab,L,May).

mayor(Ccab, [Cab|L],May ):-
    heu(Ccab,Cab,Val1,Val2),
    Val1 =< Val2,
    %Ccab =< Cab,
    mayor(Cab,L,May).

cMayor([Cab|L],May) :-
    mayor(Cab,L,May).
% ----------------------------- de aqui para abajo estoy seguro que
%esta bien

heu(C1,C2,V1,V2):- heuri(C1,V1),heuri(C2,V2).

% saca el tamaño de la lista Prioridades, lo guarda en Ubi y lo pasa
% a listPri, que ira reduciendo el valor hasta llegar al punto en el
% que este ubicado el valor, retornandolo por Val
heuri(CC,Val):-
    listPri(CC ,Val).

%caso final no encontrado
listPri(_,[],0).
%caso final encontrado
listPri(CC,[CC|L],Val):-
    length(L,Vall), Val is Vall + 1.
%%caso intermedio
listPri(CC,[_|L],Val):-
    listPri(CC,L,Val).

% la lista de prioridades, con que mas al frente este el dato, mayor
% valor tiene

prioridades(Pp) :- Pp = [1,4,5,3,6].%prueba
%prioridades(Pp) :- Pp = [coger,mover,soltar].

%llamada inicial
listPri(CC,Val):-
    prioridades(Pp),
    listPri(CC,Pp,Val)
    %,delete(Pp,CC,Pp)
    .
