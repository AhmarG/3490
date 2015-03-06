% Feb 24 worksheet problems

% separate
% separate([a,b,c,d,e],[a,c,e],[b,d]) is true.

separate([],[],[]).
separate([X],[X],[]).
separate([A,B|T],[A|T1],[B|T2]) :- separate(T,T1,T2).



%------------------------------------------
%
% mini
% no fact for mini of empty list means it is "no"

mini([X],X).
mini([H|T], H) :- mini(T,R), H < R.
mini([H|T], R) :- mini(T,R), H >= R.


%------------------------------------------
%
% partition
partition([X],Value,[X],[]) :- X =< Value.
partition([X],Value,[],[X]) :- X > Value.
partition([H|T],Value,[H|X],Y) :- H =< Value, partition(T,Value,X,Y).
partition([H|T],Value,X,[H|Y]) :- H > Value, partition(T,Value,X,Y).


%------------------------------------------
%
% rev - reverse a list inefficiently
rev([],[]).
rev([H|T], L) :- rev(T,Z), append(Z,[H],L).


% rev2 - reverse efficiently
rev2([],[]).
rev2(Original, Reversed) :- rev2helper(Original, [], Reversed).
rev2helper([], Reversed, Reversed).
rev2helper([H|T], Partial, Reversed) :- rev2helper(T, [H|Partial], Reversed).



%------------------------------------------
%
% quicksort
quicksort([],[]).
quicksort([X],[X]).
quicksort([Pivot|Tail], Sorted) :- 
    partition(Tail,Pivot,X,Y), 
    quicksort(X,SX), quicksort(Y,SY), 
    append(SX,[Pivot],Z), append(Z,SY,Sorted).
    


%----------------------------------
%
% insertion sort
insertionsort([],[]).
insertionsort([X],[X]).
insertionsort(Unsorted,Sorted) :- isorthelper(Unsorted, [], Sorted).
isorthelper([],Sorted,Sorted).
isorthelper([H|T], Partial, Sorted) :- insert(H,Partial,Z), isorthelper(T,Z,Sorted).
insert(Value, [], [Value]).
insert(Value, [H|T], [Value,H|T]) :- Value =< H.
insert(Value, [H|T], [H|Y]) :- Value > H, insert(Value, T, Y).


