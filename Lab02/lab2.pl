/*
 * Problem 1 – Naïve prime number search
 */
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

primesFromRange(B, B) :- !.
primesFromRange(A, B) :-
    A < B,
    isPrime(A), !,
    write(A), nl,
    AA is A + 1,
    primesFromRange(AA, B).
primesFromRange(A, B) :-
    A < B,
    AA is A + 1,
    primesFromRange(AA, B).
% CALL: get_time(T0), primesFromRange(2, 10), get_time(T1), Time is T1 - T0.

/*
 * Problem 2 – Compute the entropy of a binary random sequence
 */
cntOneBits(0, L, L) :- !.
cntOneBits(R, IL, L) :-
    DR is R // 2,
    RR is R mod 2,
    % write(RR), nl,
    RR = 1, !,
    IIL is IL + 1,
    cntOneBits(DR, IIL, L).
cntOneBits(R, IL, L) :-
    DR is R // 2,
    cntOneBits(DR, IL, L).

countOneBitsInValue(V, R) :-
    cntOneBits(V, 0, R).

computeOnesAndZerosFromArray(N, N, O, O, Z) :- 
    Z is (N * 8) - O.
computeOnesAndZerosFromArray(N, I, OI, O, Z) :-
    NI is I + 1,
    random(0, 256, R),
    countOneBitsInValue(R, V),
    NOI is OI + V,
    computeOnesAndZerosFromArray(N, NI, NOI, O, Z).

log2(N, R) :-
    R is log(N) / log(2).

computeEntropy(N, O, Z, R) :-
    T is N * 8,
    OPerT is O / T,
    ZPerT is Z / T,
    log2(OPerT, LOPerT),
    log2(ZPerT, LZPerT),
    R is -OPerT * LOPerT - ZPerT * LZPerT.

computeEntropy(N, R) :-
    computeOnesAndZerosFromArray(N, 0, 0, O, Z),
    computeEntropy(N, O, Z, R).
% CALL: get_time(T0), computeEntropy(100000, R), get_time(T1), Time is T1 - T0.

/* **************************************************************************
 * Problem 3 – Compute the value of PI (π)
 */
computePi(N, N, S, S) :- !.
computePi(N, I, S, R) :-
    SS is S + 4 / (1 + ((I + 0.5) / N)**2),
    Ni is I + 1,
    computePi(N, Ni, SS, R).

computePi(N, R) :-
    computePi(N, 0, 0, RR),
    R is RR / N.
% CALL: get_time(T0), computePi(500000, R), get_time(T1), Time is T1 - T0.

/* **************************************************************************
* 4. Problem 4 – Compute the value of PI (π) using the Monte Carlo method 
*/
computePiMC(N, N, M, M) :- !.
computePiMC(N, I, IM, R) :-
    NI is I + 1,
    random(0.0, 1.0, X),
    random(0.0, 1.0, Y),
    X**2 + Y**2 =< 1, !,
    NIM is IM + 1,
    computePiMC(N, NI, NIM, R).
computePiMC(N, I, IM, R) :-
    NI is I + 1,
    computePiMC(N, NI, IM, R).

computePiMC(N, PI) :-
    computePiMC(N, 0, 0, M),
	PI is 4 * M / N.
% CALL: get_time(T0), computePiMC(10000000, R), get_time(T1), Time is T1 - T0.