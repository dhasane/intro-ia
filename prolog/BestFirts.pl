

/*
%saca el mayor valor de una lista, tuve que copiar un codigo casi completamente   para lograr entender esto....
mayor(Ccab, [],Ccab) .
mayor(Ccab, [Cab|L],May ):- Ccab > Cab, mayor(Ccab,L,May) .
mayor(Ccab, [Cab|L],May ):- Ccab =< Cab, mayor(Cab,L,May) .
mayor([Cab|L],May) :-mayor(Cab,L,May) .
*/


%saca el mayor valor de una lista
mayor(Ccab, [],Ccab) .

mayor(Ccab, [Cab|L],May ):- heu(Ccab,Cab,Val1,Val2), Val1 > Val2, mayor(Ccab,L,May) .
mayor(Ccab, [Cab|L],May ):- heu(Ccab,Cab,Val1,Val2), Val1 =< Val2, mayor(Cab,L,May) .

mayor(Ccab, [Cab|L],May ):- Ccab =< Cab,
mayor(Cab,L,May) .

mayor([Cab|L],May) :-mayor(Cab,L,May) .



heu(C1,C2,V1,V2):- heuri(C1,V1),heuri(C2,V2).

heuri(CC,1/CC).% en esta parte es que se pondria la formula


%Heu(Ccab,Val1),Heu(Cab,Val2).
