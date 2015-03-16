%Relationships

married(X,Y) :- wife(X,Y).
married(X,Y) :- wife(Y,X).
wife(vera,cl).
wife(brenda,jack).
wife(michelle,larry).
mother(M,C) :- parent(M,C), female(M).
father(F,C) :- parent(F,C), male(F).
child(C,P) :- parent(P,C).
son(S,P) :- child(S,P), male(S).
daughter(D,P) :- child(D,P), female(D).
sibling(X,Y) :- father(Z,X), father(Z,Y), \+(X=Y).
brother(X,Y) :- sibling(X,Y), male(X).
sister(X,Y) :- sibling(X,Y), female(X).
aunt(X,Y):- female(X), parent(P,Y),sister(X,P).
aunt(X,Y) :- parent(P,Y), sibling(P,S), married(S,X).
uncle(X,Y) :- male(X), parent(P,Y), brother(X,P).
uncle(X,Y) :- parent(P,Y), sibling(P,S), married(S,X).
cousin(X,Y) :- uncle(U,X), parent(U,Y), X\=Y.
ancestor(X,Y):- parent(X,Y).
ancestor(X,Y):- parent(P,X), ancestor(Y,P).
descendant(X,Y)  :-  parent(X,Y).
descendant(X,Y)  :-  parent(X,Z), descendant(Z,Y).
