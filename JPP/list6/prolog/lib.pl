% Merge sort
mergesortConnect([], []).
mergesortConnect([], Right, Right).
mergesortConnect(Left, [], Left).
mergesortConnect([Left|Left_rest], [Right|Right_rest], [Left|Y_rest]):-
    Left < Right,
    mergesortConnect(Left_rest, [Right|Right_rest], Y_rest).
mergesortConnect([Left|Left_rest], [Right|Right_rest], [Right|Y_rest]):-
    Right =< Left,
    mergesortConnect([Left|Left_rest], Right_rest, Y_rest).

mergesort([], []).
mergesort([A|[]],[A]).
mergesort(X,Y):-
    length(X, N),
    Mid is //(N, 2),
    Length_r is N - Mid,
    length(Left, Mid),
    length(Right, Length_r),
    append(Left, Right, X),
    mergesort(Left, Result_left),
    mergesort(Right, Result_right),
    mergesortConnect(Result_left, Result_right, Y).

% Diophantine equation
extendedGcd(Prev_r, 0, Prev_s, S, Prev_t, T, Prev_s, Prev_t, Abs_prev_r) :- 
    Abs_prev_r is abs(Prev_r).

extendedGcd(Prev_r, R, Prev_s, S, Prev_t, T, X, Y, Z) :-
    Q is //(Prev_r, R),
    New_r is -(Prev_r, *(Q, R)),
    New_s is -(Prev_s, *(Q, S)),
    New_t is -(Prev_t, *(Q, T)),
    extendedGcd(R, New_r, S, New_s, T, New_t, X, Y, Z).

de(0,0,0,0,0).
de(A,B,X,Y,Z):-
    extendedGcd(A,B,1,0,0,1,X,Y,Z).

% Prime factors
smallest_divisor(K, I, 0):- K < I.
smallest_divisor(K, I, I):-
    Res is mod(K, I),
    Res == 0.
smallest_divisor(K, I, Result):- 
    Next_I is +(I, 1),
    smallest_divisor(K, Next_I, Result).

prime_factors(X, []):- X =< 1.
prime_factors(N, [Divisor|Out_Rest]):-
    smallest_divisor(N, 2, Divisor),
    New_n is //(N, Divisor),
    prime_factors(New_n, Out_Rest).

% Totient
gcd(A, 0, A).
gcd(A, B, Res):- 
    B \= 0,
    New_b is A mod B,
    gcd(B, New_b, Res).

totient_step(N, N, Count, Count).
totient_step(N, I, Count, Res):-
    gcd(N, I, 1),
    New_I is +(I, 1),
    New_count is +(Count, 1),
    totient_step(N, New_I, New_count, Res).
totient_step(N, I, Count, Res):-
    gcd(N, I, Q),
    Q \= 1,
    New_I is +(I, 1),
    totient_step(N, New_I, Count, Res).

totient(N, 0):- N =< 0.
totient(N, T):- totient_step(N, 1, 0, T).

% Primes
is_prime_step(K, I):-
    I * I > K.
is_prime_step(K, I):-
    Mod_I_res is K mod I,
    Mod_I_2_res is K mod (I + 2),
    Mod_I_res \= 0,
    Mod_I_2_res \= 0,
    New_I is +(I, 5),
    is_prime_step(K, New_I).

is_prime(K):-
    K > 1,
    K =< 3.
is_prime(K):-
    K > 1,
    Mod_2_res is (K mod 2),
    Mod_3_res is (K mod 3),
    Mod_2_res \= 0,
    Mod_3_res \= 0,
    is_prime_step(K, 5).

primes_step(N, I, Res):- I > N.
primes_step(N, I, [I|Xs]):-
    is_prime(I),
    New_I is +(I, 1),
    primes_step(N, New_I, Xs).

primes_step(N, I, X):-
    \+is_prime(I),
    New_I is +(I, 1),
    primes_step(N, New_I, X).

primes(N, []):- N < 2.
primes(N, X):-
    primes_step(N, 2, X).


print_list([]):-write("\n").
print_list([L|List]):- write(L), write(", "), print_list(List).

main:-
    List = [2, 6, 1, 6, 8, 3, 7],
    write("Merge sort:\nBefore merge\n"),
    print_list(List),
    mergesort(List, Result),
    write("After merge\n"),
    print_list(Result),
    write("\nDE\n"),
    A = 5,
    B = 3,
    de(A,B,X,Y,Z),
    format("~dX + ~dY = Z\n", [A, B]),
    format("Result: X = ~d, Y = ~d, Z = ~d\n", [X,Y,Z]),
    N = 20,
    format("\nPrime factors, N = ~d\n", [N]),
    prime_factors(N, Factors),
    print_list(Factors),
    D = 23,
    format("\nTotient, N = ~d\n", [D]),
    totient(D, Tot),
    writeln(Tot),
    G = 100,
    format("\nPrimes, N = ~d\n", [G]),
    primes(G, Prim),
    print_list(Prim).
