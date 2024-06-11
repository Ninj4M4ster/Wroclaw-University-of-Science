import qualified Data.List as List

-- Binomial
binomial :: Integer -> Integer -> Integer
binomial n k = 
    if n < 0 || k < 0 || n < k then 0
    else
        if (k == 0 || n == k) then 1 
        else binomial (n-1) k + binomial (n-1) (k-1);

-- Binomial2
elementWiseListSum :: [Integer] -> [Integer] -> [Integer]
elementWiseListSum [] [] = []
elementWiseListSum _ [] = []
elementWiseListSum [] _ = []
elementWiseListSum (x:xs) (y:ys) = (x + y) : elementWiseListSum xs ys

pascal :: Integer -> [Integer]
pascal 0 = [1]
pascal n = elementWiseListSum ([0] ++ pascal (n-1)) (pascal (n-1) ++ [0])


binomial2 :: Integer -> Integer -> Integer
binomial2 n k = 
    if n < 0 || k < 0 || n < k then 0
    else (pascal n) !! fromInteger k

-- Merge sort
mergeSortConnect :: [Integer] -> [Integer] -> [Integer]
mergeSortConnect [] [] = []
mergeSortConnect a [] = a
mergeSortConnect [] b = b
mergeSortConnect (a:as) (b:bs) = if a < b then a:[] ++ mergeSortConnect as (b:[] ++ bs) else b:[] ++ mergeSortConnect (a:[] ++ as) bs

mergeSortSplit :: [Integer] -> [Integer]
mergeSortSplit [] = []
mergeSortSplit [a] = [a]
mergeSortSplit a = do mergeSortConnect (mergeSortSplit a1) (mergeSortSplit a2) where
    (a1, a2) = splitAt (((length a) + 1) `div` 2) a 

mergesort :: [Integer] -> [Integer]
mergesort [] = []
mergesort l = mergeSortSplit l

-- Diophantine equation
extendedGcd :: Integer -> Integer -> Integer -> Integer -> Integer -> Integer -> (Integer, Integer, Integer)
extendedGcd prev_r 0 prev_s s prev_t t = (prev_s, prev_t, abs prev_r)
extendedGcd prev_r r prev_s s prev_t t = extendedGcd r (prev_r - q * r) s (prev_s - q * s) t (prev_t - q * t) where
    q = prev_r `div` r

de :: Integer -> Integer -> (Integer, Integer, Integer)
de a b = if (a == 0 && b == 0) then (0, 0, 0) 
        else
            extendedGcd a b 1 0 0 1
    
-- Prime factors
smallest_divisor :: Integer -> Integer -> Integer
smallest_divisor k i = if (k < i) then 0 else if (k `mod` i) == 0 then i else smallest_divisor k (i+1) 

prime_factors :: Integer -> [Integer]
prime_factors 1 = []
prime_factors n = if n <= 0 then [] else divisor:[] ++ prime_factors (n `div` divisor) where
    divisor = smallest_divisor n 2

-- Totient
totient_step :: Integer -> Integer -> Integer -> Integer
totient_step n i count = if i == n then count else 
    if q == 1 then totient_step n (i+1) (count + 1) else totient_step n (i+1) count where
        q = gcd n i


totient :: Integer -> Integer
totient n = if n <= 0 then 0 else totient_step n 1 0

-- Totient 2
totient2_step :: Integer -> [Integer] -> Integer
totient2_step n [] = n
totient2_step n (p:ps) = totient2_step (n * (p - 1) `div` p) ps

totient2 :: Integer -> Integer
totient2 n = if n <= 0 then 0 else totient2_step n divisors where
    divisors = List.nub (prime_factors n)

-- Primes
is_prime_step :: Integer -> Integer -> Bool
is_prime_step k i = if i * i > k then True else if k `mod` i == 0 || k `mod` (i+2) == 0 then False else is_prime_step k (i+6)

is_prime :: Integer -> Bool
is_prime k = if k <= 1 then False else if k <= 3 then True else if k `mod` 2 == 0 || k `mod` 3 == 0 then False else is_prime_step k 5 

primes_step :: Integer -> Integer -> [Integer] -> [Integer]
primes_step n i curr_list = if i > n then curr_list else 
    if is_prime i then primes_step n (i + 1) (curr_list ++ i:[]) else primes_step n (i+1) curr_list

primes :: Integer -> [Integer]
primes n = if n < 2 then [] else primes_step n 2 [] 

main = print (mergesort [2, 35 ,1, 5, 1, 6, 8])