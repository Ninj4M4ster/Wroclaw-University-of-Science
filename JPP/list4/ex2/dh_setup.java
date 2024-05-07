package main;

import java.security.SecureRandom;
import java.util.ArrayList;
import java.util.List;

class DHSetup<T extends GF1234567891> {
    private final T body_generator_;
    private final SecureRandom rand_gen = new SecureRandom();

    public DHSetup(T instance) throws Exception {
        body_generator_ = instance;
        long characteristic = T.Characteristic() - 1;
        List<Long> dividers = new ArrayList<>();
        for(long i = 1; i <= Math.sqrt(characteristic); i++) {
            if(isNumberPrimary(i) && characteristic % i == 0) {
                dividers.add(i);
            }
        }
        do {
            body_generator_.assign(rand_gen.nextLong(characteristic - 1) + 1);
        } while (!isGeneratorLegal(body_generator_, dividers));
    }

    public T getGenerator() {
        return body_generator_;
    }

    public T power(T a, long b) {
        T result = (T) body_generator_.clone();
        result.assign(1);
        T a_copy = (T) a.clone();
        while(b > 0) {
            if(b % 2 == 0) {
                b /= 2;
                a_copy.multiplyEqual(a_copy);
            } else {
                b --;
                result.multiplyEqual(a_copy);
    
                b /= 2;
                a_copy.multiplyEqual(a_copy);
            }
        }
        return result;
    }

    private boolean isNumberPrimary(long number) {
        if(number <= 2) {
            return true;
        }
        for(long i = 2; i < number; i++) {
            if(number % i == 0) {
                return false;
            }
        }
        return true;
    }

    private boolean isGeneratorLegal(T possible_generator, List<Long> dividers) throws Exception {
        long characteristic = T.Characteristic() - 1;
        T one_t = (T) body_generator_.clone();
        one_t.assign(1);
        for(Long val : dividers) {
            T multiplied_val = (T) body_generator_.clone();
            multiplied_val.assign(characteristic / val);
            if(T.equal(T.multiply(possible_generator, multiplied_val), one_t))
                return false;
        }
        return true;
    }
}
