 /* Ahmar  Gordon */
%separate
separate([], [], []).
separate([X], [], [X]).
separate([I1,I2|Tail], [I1 | Rest], [I2|Other) :- separate(Tail,Rest,Other).

%partition
partition([Head|Tail], X, M, [Head|N]):-
X < Head, !,
partition(Tail, X, M, N).
partition([Head|Tail], X, [Head|M], N):-
 partition(Tail, X, M, N).
partition([], _, [], []).
 
%quicksort
 quicksort([Pivot|Tail], Sorted):-
	partition(Tail, Pivot, US UL),
	quicksort(US, SS), quicksort(UL,SL)
 
%mini
mini([X], X).
mini([Head|Tail], Min) :- mini(Tail, Min2), Min2 < Head, Min is Min2.
mini([Head|Tail], Min) :- mini(Tail, Min2), Head =< Min2, Min is Head.

%reverse
app([],[],[]).
app([],[H|T],[H|T]).
app([H|T], L, [H|R]) :- app(T,L,R).
rev([], []).
rev([Head|Tail], Rev) :- rev(Tail, RevT), app(RevT, [H], Rev).

%insertion sort
insertSort([Head|Tail], Ret):- insertSort(Tail, Test), insert(Head, Test, Ret).
insertSort([], []).
insert(X, [Head|Tail], [Head|Ret]):-X>Head, !, insert(X, Tail, Ret).
insert(X, Tail, [X|Tail]).
