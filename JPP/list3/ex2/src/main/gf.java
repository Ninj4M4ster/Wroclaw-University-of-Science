package main;

class Gf1234577 {
    private long value_;
    protected static long BODY = 1234577;

    public Gf1234577() {}

    public Gf1234577(int val) {
        if(val < 0) {
            val *= -1;
            val %= BODY;
            val = (int)BODY - val;
        }
        value_ = val % BODY;
    }

    public Gf1234577(long val) {
        if(val < 0) {
            val *= -1;
            val %= BODY;
            val = BODY -val;
        }
        value_ = val % BODY;
    }

    public Gf1234577(Gf1234577 other) {
        value_ = other.value_;
    }

    public static long Characteristic() {
        long val = 1;
        long counter = 1;
        while(val % BODY != 0) {
            val++;
            counter++;
        }
        return counter;
    }

    // casting

    public String stringify() {
        return String.valueOf(value_);
    }

    public static int toInt(Gf1234577 obj) {
        return (int)obj.value_;
    }

    public static long toLong(Gf1234577 obj) {
        return obj.value_;
    }

    // comparisons

    public static boolean equal(Gf1234577 first, Gf1234577 second) {
        return first.value_ == second.value_;
    }

    public static boolean notEqual(Gf1234577 first, Gf1234577 second) {
        return first.value_ != second.value_;
    }

    public static boolean lessEqual(Gf1234577 first, Gf1234577 second) {
        return first.value_ <= second.value_;
    }

    public static boolean greaterEqual(Gf1234577 first, Gf1234577 second) {
        return first.value_ >= second.value_;
    }

    public static boolean less(Gf1234577 first, Gf1234577 second) {
        return first.value_ < second.value_;
    }

    public static boolean greater(Gf1234577 first, Gf1234577 second) {
        return first.value_ > second.value_;
    }

    // arithmetic 

    public static Gf1234577 add(Gf1234577 first, Gf1234577 second) {
        return new Gf1234577((first.value_ + second.value_) % Gf1234577.BODY);
    }

    public static Gf1234577 subtract(Gf1234577 first, Gf1234577 second) {
        long val = first.value_ - second.value_;
        if(val < 0) {
            val += Gf1234577.BODY;
        }
        return new Gf1234577(val);
    }

    public static Gf1234577 multiply(Gf1234577 first, Gf1234577 second) {
        return new Gf1234577(first.value_ * second.value_);
    }

    public static Gf1234577 divide(Gf1234577 first, Gf1234577 second) {
        long inverse = 1;
        while((inverse * other.value_) % Gf1234577.BODY != 1) {
            inverse++;
        }
        if(inverse == Gf1234577.BODY) {
            throw new Exception(String.valueOf(other.value_) + " is not reversible.");
        }
        return new Gf1234577(first.value_ * inverse);
    }

    // assignments

    public void assign(Gf1234577 other) {
        value_ = other.value_;
    }

    public void plusEqual(Gf1234577 other) {
        value_ += other.value_;
        value_ %= BODY;
    }

    public void minusEqual(Gf1234577 other) {
        value_ -= other.value_;
        if(value_ < BODY) {
            value_ += BODY;
        }
        value_ %= BODY;
    }

    public void multiplyEqual(Gf1234577 other) {
        value_ *= other.value_;
        value_ %= BODY;
    }

    public void divideEqual(Gf1234577 other) {
        long inverse = 1;
        while((inverse * other.value_) % Gf1234577.BODY != 1) {
            inverse++;
        }
        if(inverse == Gf1234577.BODY) {
            throw new Exception(String.valueOf(other.value_) + " is not reversible.");
        }
        value_ = (value_ * inverse) % BODY;
    }
}