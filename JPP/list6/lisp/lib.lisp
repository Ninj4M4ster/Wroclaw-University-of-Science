; Binomial 
(defun binomial (n k)
    (if (or (< n 0) (< k 0) (< n k)) 0
    (if (or (= k 0) (= n k)) 1
    (+ (binomial (- n 1) k) (binomial (- n 1) (- k 1))))))

; Binomial 2
(defun pascal (n)
    (if (= n 0) 
    (list 1) 
    (let* ((p (pascal (- n 1))) (q (append p (list 0))) (g (push 0 p)))
    (mapcar #'+ g q))))

(defun binomial2 (n k)
    (if (or (< n 0) (< k 0) (< n k)) 0
    (nth k (pascal n))))

; Merge sort
(defun mergesortConnect (L R l_i r_i final)
    (if (and (= (length L) l_i) (= (length R) r_i)) 
        final 
        (if (= (length L) l_i) 
            ; append from R to final and recurse
            (progn (setq final (append final (list (nth r_i R)))) 
            (mergesortConnect L R l_i (+ r_i 1) final))
            (if (= (length R) r_i) 
                ; append from L to final and recurse
                (progn (setq final (append final (list (nth l_i L)))) 
                (mergesortConnect L R (+ l_i 1) r_i final))
                (if (< (nth l_i L) (nth r_i R)) 
                    ; append from L to final and recurse
                    (progn (setq final (append final (list (nth l_i L)))) 
                    (mergesortConnect L R (+ l_i 1) r_i final))
                    ; append from R to final and recurse
                    (progn (setq final (append final (list (nth r_i R)))) 
                    (mergesortConnect L R l_i (+ r_i 1) final))
                )
            )
        )
    )
)

(defun mergesortSplit (Li l r) 
    (if (= (- r l) 0) 
    nil 
        (if (= (- r l) 1) 
        (list (nth l Li))
        (let* ((mid (floor (+ l r) 2)) (left_arr (mergesortSplit Li l mid)) (right_arr (mergesortSplit Li mid r)))
        (mergesortConnect left_arr right_arr 0 0 nil))
        )
    )
)

(defun mergesort (L) 
    (mergesortSplit L 0 (length L)))

; Diophantine equation
(defun extendedGcd (prev_r r prev_s s prev_t t_c)
    (if (= r 0) 
        (list prev_s prev_t (abs prev_r))
        (let ((q (floor prev_r r)))
        (extendedGcd r (- prev_r (* q r)) s (- prev_s (* q s)) t_c (- prev_t (* q t_c)))
        )
    )
)
(defun de (a b)
    (if (and (= a 0) (= b 0)) 
        (list 0 0 0)
        (extendedGcd a b 1 0 0 1)
        )
)

; Prime factors
(defun smallest_divisor (k i)
    (if (< k i) 
    0
    (if (= (mod k i) 0) i (smallest_divisor k (+ i 1))))
)
(defun prime_factors (n)
    (if (= n 1) 
    nil 
    (if (<= n 0) 
        nil 
        (let* ((divisor (smallest_divisor n 2)) (next_factors_list (prime_factors (floor n divisor))))
        (append next_factors_list (list divisor)))))
)

; Totient
(defun totient_step (n i count)
    (if (= i n) count 
    (if (= (gcd n i) 1) (totient_step n (+ i 1) (+ count 1)) (totient_step n (+ i 1) count)))
)

(defun totient (n)
    (if (<= n 0) 0 (totient_step n 1 0))
)

; Totient 2
(defun totient2_step (n divisors i)
    (if (= i (length divisors)) n
    (totient2_step (floor (* n (- (nth i divisors) 1)) (nth i divisors)) divisors (+ i 1)))
)

(defun totient2 (n) 
    (if (<= n 0) 0 
    (totient2_step n (remove-duplicates (prime_factors n)) 0))
)

; Primes
(defun is_prime_step (k i)
    (if (> (* i i) k) t 
        (if (or (= (mod k i) 0) (= (mod k (+ i 2)) 0)) nil (is_prime_step k (+ i 6))))
)

(defun is_prime (k)
    (if (<= k 1) nil 
        (if (<= k 3) t 
            (if (or (= (mod k 2) 0) (= (mod k 3) 0)) nil (is_prime_step k 5))))
)

(defun primes_step (n i curr_list)
    (if (> i n) curr_list 
        (if (is_prime i) 
            (primes_step n (+ i 1) (append curr_list (list i)))
            (primes_step n (+ i 1) curr_list)))
)

(defun primes (n)
    (if (< n 2) nil (primes_step n 2 nil))
)

(write-line (write-to-string (primes 20)))