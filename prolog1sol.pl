%
% Sample Solutions to Prolog-1: Families
%
% 1. Family facts
% /u/csd/jbf/pub/3490/Prolog/family.pl encodes all the family
% facts for figure 6.3 of text.

% 2. married facts
married(douglas,rita).
married(james,rosa).
married(gregory,erica).
married(george,janet).
married(william,maria).
married(jason,brittany).

% 3. mother, father, son, daughter
% the mother is the female parent
mother(M, C) :- parent(M, C), female(M).
father(F, C) :- parent(F, C), male(F).
% a son is a male child
son(P, S) :- parent(P, S), male(S).
daughter(P, D) :- parent(P, D), female(D).

% 4. sibling
% two people are siblings if they have the same mother and
% the same father and are not the same person.
sibling(X,Y) :- mother(M,X), mother(M,Y), 
                father(F,X), father(F, Y),
                X \== Y.

% 5. brother and sister
% a brother is a male sibling
brother(S,B) :- sibling(S,B), male(B).
sister(X,Y) :- sibling(X,Y), female(Y).

% 6. aunt and uncle
% aunts are female siblings of my parents
aunt(A, Me) :- parent(P,Me), sister(P,A).
uncle(U, Me) :- parent(P,Me), brother(P,U).
% aunts are also married to my parents brothers
aunt(A,Me) :- parent(P,Me), brother(P,U), married(U,A).
uncle(U, Me) :- parent(P,Me), sister(P,A), married(U,A).

% 7. cousin using grandparents
% if cousin only uses grandparent then will find cousin relationship twice,
% once for Gp is grandmother and again for Gp is grandfather.
grandparent(Gp, X) :- parent(P,X), parent(Gp,P).
grandfather(Gf, X) :- grandparent(Gp,X), male(Gf).
grandmother(Gm, X) :- grandmother(Gm,X), female(Gm).
cousin(X,Y) :- grandmother(Gm,X), grandmother(Gm,Y),
               \+(sibling(X,Y)), X \== Y.

% 8. ancestor
ancestor(X,Y) :- parent(X,Y).
ancestor(X,Y) :- parent(P,Y), ancestor(X,P).

% 9. descendent
descendent(X,Y) :- parent(Y,X).
descendent(X,Y) :- parent(P,X), descendent(Y, P).

