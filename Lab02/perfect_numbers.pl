/*% Problem 5, perfect numbers: use Euclid-Euler theorem: all even perfect numbers = q*(q+1)/2 where q is 2^p-1 with p prime, q prime
% there are no known odd perfect numbers up to 2^82589933 − 1 so for this problem, checking only evens should do it

% Note: Solution performs 'too good' because of its ~log(N) runtime complexity, only way I managed to make it take longer was
% at around 10 quintillion i.e. 10000000000000000000 ( for N = 1 quintillion, it took about 0.07 seconds, so I suspect there is 
% some Prolog runtime business here, and not the algorithm slowing down drastically)*/

divisible(X, Y) :-
    0 is X mod Y, !.
divisible(X, Y) :-
    Y =< sqrt(X),
    divisible(X, Y+1).

isPrime(2) :- 
    true, !.
isPrime(X) :-
    X < 2, !,
    false.
isPrime(X) :-
    not(divisible(X, 2)).

getPrimesFromRange(B, B, R, R) :- !.
getPrimesFromRange(A, B, ACC, R) :-
    A =< B,
    isPrime(A), !,
    AA is A + 1,
    getPrimesFromRange(AA, B, [A|ACC], R).
getPrimesFromRange(A, B, ACC, R) :-
    A =< B,
    AA is A + 1,
    getPrimesFromRange(AA, B, ACC, R).

getPrimesFromRange(FROM, TO, R):-
    getPrimesFromRange(FROM, TO, [], R).

log2(N, R) :-
    R is log(N) / log(2).

getPerfectNumbers([], _, R, R):- !.
getPerfectNumbers([H|T], L, ACC, R):-
    MP is 2**H - 1,
    isPrime(MP),
    PN is MP * (MP + 1) / 2,
    PN =< L, !,
    getPerfectNumbers(T, L, [PN|ACC], R).

getPerfectNumbers([_|T], L, ACC, R):-
    getPerfectNumbers(T, L, ACC, R).

getPerfectNumbers(N, R):-
    log2(N, LN),
    M is round((LN + 1) / 2) + 1,
    getPrimesFromRange(1, M, P),
    getPerfectNumbers(P, N, [], R).

% CALL: get_time(T0), getPerfectNumbers(1000000000000000000, R), get_time(T1), T is T1 - T0.