:- dynamic memfib/2.

worker(TID, NbThreads, IStart, IStop) :-
    Start is IStart + TID,
    fibonacci(Start, IStop, NbThreads).

createThreads(N) :-
    createThreads(0, N).

createThreads(N, N) :- !.
createThreads(I, N) :-
    I < N,
    NewI is I + 1,
    thread_create(worker(I, N, 0, 664), IDX, []),
    createThreads(NewI, N),
    thread_join(IDX, _).

fibonacci(I, N, NbThreads) :-
    I =< N, !,
	% thread_self(Id),
    PREC is N // 2,
    sqrt5(PREC, SQRT5),
    % phi (1 + sqrt(5)) / 2
    PHI_NOM is 10 ^ PREC + SQRT5,
    PHI_DENOM is 10 ^ PREC * 2,
    % PHI / sqrt5 <=> PHI_NOM * sqrt5, PHI_DENOM * 5
    
   	PHI_NOM_POW is PHI_NOM ^ I * SQRT5,
    PHI_DENOM_POW is PHI_DENOM ^ I * 5 * 10 ^ PREC,
    PHI_NOM_FINAL is 2 * PHI_NOM_POW + PHI_DENOM_POW,
    PHI_DENOM_FINAL is 2 * PHI_DENOM_POW,
	RES is PHI_NOM_FINAL // PHI_DENOM_FINAL, 
    
	assertz(memfib(I, RES)),
    
	II is I + NbThreads,
    fibonacci(II, N, NbThreads).

% hax
sqrt5(N, R) :-
    A is 5 * 10 ^ (2 * N),
    nth_integer_root_and_remainder(2, A, R, _).
	
% calculate elapsed time using the get_time for executing the fibonacci with N threads
threadedFibonacci(N, T) :-
	get_time(T0),
	createThreads(N),
	get_time(T1),
	T is T1 - T0.