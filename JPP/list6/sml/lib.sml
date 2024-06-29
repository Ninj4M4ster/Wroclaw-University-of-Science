(* Binomial *)
fun binomial (n:int, k:int) : int = 
if n < 0 orelse k < 0 orelse n < k then 0 
else (if k = 0 orelse n = k then 1
else binomial(n-1, k) + binomial(n-1, k-1));

(* Binomial 2 *)
fun listsSum ([], []) = []
    | listsSum (x:int list, []) = x
    | listsSum ([], y: int list) = y
    | listsSum (x::xs:int list, y::ys:int list) = [x + y] @ listsSum(xs, ys);

fun pascal (0) = [1]
    | pascal (n:int) : int list = listsSum([0] @ pascal(n-1), pascal(n-1) @ [0]);


fun binomial2 (n:int, k:int) : int =
if n < 0 orelse k < 0 orelse n < k then 0
else List.nth(pascal(n), k);

(* Merge sort *)
fun mergesortConnect (a:int list, []) : int list = a
    | mergesortConnect ([], b:int list) : int list = b
    | mergesortConnect (x::xs:int list, y::ys:int list) : int list = 
    if x < y then [x] @ mergesortConnect(xs, [y] @ ys) else [y] @ mergesortConnect([x] @ xs, ys);

fun mergesortSplit (lis:int list, l:int, r:int) : int list = 
    if (r - l) = 0 then []
    else if (r - l) = 1 then [List.nth(lis, l)]
    else
    let
        val mid = (l + r) div 2
        val left_arr = mergesortSplit(lis, l, mid);
        val right_arr = mergesortSplit(lis, mid, r);
    in
        mergesortConnect(left_arr, right_arr)
    end;

fun mergesort ([]) = []
    | mergesort (l:int list) : int list = mergesortSplit(l, 0, length(l));

(* Diophantine equation *)
fun extendedGcd (prev_r:int, 0, prev_s, s, prev_t, t) = [prev_s, prev_t, abs(prev_r)]
    | extendedGcd(prev_r, r, prev_s, s, prev_t, t) = 
    let
        val q = prev_r div r
    in
        extendedGcd(r, prev_r - q * r, s, prev_s - q * s, t, prev_t - q * t)
    end;

fun de (0, 0) = [0, 0, 0]
    | de (a:int, b:int) : int list = extendedGcd(a, b, 1, 0, 0, 1);

(* Prime factors *)
fun smallest_divisor (k:int, i:int) : int =
    if k < i then 0 else 
    if (k mod i) = 0 then i else smallest_divisor(k, i+1)

fun prime_factors (1) = []
    | prime_factors (n:int) : int list = 
    if n <= 0 then [] else let
        val divisor = smallest_divisor(n, 2)
    in
        [divisor] @ prime_factors(n div divisor)
    end

(* Totient *)
fun gcd (x:int, 0) : int = x
    | gcd (x:int, y:int) = gcd(y, x mod y);

fun totient_step (n:int, i:int, count:int) : int =
    if i = n then count else 
    let
        val q = gcd(n, i)
    in
        if q = 1 then totient_step(n, i+1, count+1) else totient_step(n, i+1, count)
    end

fun totient (n:int) : int =
    if n <= 0 then 0 else totient_step(n, 1, 0);

(* Totient 2 *)
fun remove_duplicates [] = []
    | remove_duplicates (x::xs:int list) : int list = [x] @ remove_duplicates((List.filter (fn a => a <> x) xs))

fun totient2_step (n:int, []) : int = n
    | totient2_step (n:int, x::xs:int list) = totient2_step(n * (x-1) div x, xs);

fun totient2 (n:int) : int =
    if n <= 0 then 0 else 
    let
        val divisors = remove_duplicates(prime_factors(n))
    in
        totient2_step(n, divisors)
    end

(* Primes *)
fun is_prime_step (k:int, i:int) : bool = 
    if i * i > k then true else 
    if k mod i = 0 orelse k mod (i+2) = 0 then false else is_prime_step(k, i+6)

fun is_prime (k:int) : bool =
    if k <= 1 then false else if k <= 3 then true else 
    if k mod 2 = 0 orelse k mod 3 = 0 then false else 
    is_prime_step(k, 5)

fun primes_step (n:int, i:int, curr_list:int list) : int list =
    if i > n then curr_list else 
    if is_prime(i) then primes_step(n, i+1, curr_list @ [i]) else primes_step(n, i+1, curr_list)

fun primes (n:int) : int list =
    if n < 2 then [] else primes_step(n, 2, [])

(* Main *)
val _ = 
let
    val res1 = binomial(15, 7)
    val res2 = binomial2(15, 7)
    val res3 = mergesort([2, 35 ,1, 5, 1, 6, 8])
    val res4 = de(5, 3)
    val res5 = prime_factors(22)
    val res6 = totient(23)
    val res7 = totient2(23)
    val res8 = primes(100)
    fun listToString ([]) = "\n"
        | listToString (x::xs) = Int.toString(x) ^ ", " ^ listToString(xs);
in
    (print(Int.toString res1 ^ "\n");
    print(Int.toString res2 ^ "\n");
    print(listToString(res3));
    print(listToString(res4));
    print(listToString(res5));
    print(Int.toString res6 ^ "\n");
    print(Int.toString res7 ^ "\n");
    print(listToString(res8)))
end
