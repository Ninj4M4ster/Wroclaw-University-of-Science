package main;

class Gf1234577 {
    protected long value_;
    protected static long BODY = 1234577;

    public Gf1234577() {}

    public Gf1234577(int val) {
        long new_val = val;
        if(new_val < 0) {
            new_val *= -1;
            new_val %= this.getBody();
            new_val = this.getBody() - new_val;
        }
        value_ = new_val % this.getBody();
    }

    public Gf1234577(long val) {
        if(val < 0) {
            val *= -1;
            val %= this.getBody();
            val = this.getBody() -val;
        }
        value_ = val % this.getBody();
    }

    public Gf1234577(Gf1234577 other) {
        value_ = other.value_;
    }

    public static long Characteristic() {
        return BODY;
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
        return new Gf1234577((first.value_ + second.value_) % BODY);
    }

    public static Gf1234577 subtract(Gf1234577 first, Gf1234577 second) {
        long val = first.value_ - second.value_;
        if(val < 0) {
            val += BODY;
        }
        return new Gf1234577(val);
    }

    public static Gf1234577 multiply(Gf1234577 first, Gf1234577 second) {
        return new Gf1234577(first.value_ * second.value_);
    }

    public static Gf1234577 divide(Gf1234577 first, Gf1234577 second) throws Exception{
        long inverse = 1;
        while((inverse * second.value_) % BODY != 1 && inverse < BODY) {
            inverse++;
        }
        if(inverse == BODY) {
            throw new Exception(String.valueOf(second.value_) + " is not reversible.");
        }
        return new Gf1234577(first.value_ * inverse);
    }

    // assignments

    public void assign(Gf1234577 other) {
        value_ = other.value_;
    }

    public void assign(long value) {
        value_ = value;
    }

    public void plusEqual(Gf1234577 other) {
        value_ += other.value_;
        value_ %= this.getBody();
    }

    public void minusEqual(Gf1234577 other) {
        value_ -= other.value_;
        if(value_ < this.getBody()) {
            value_ += this.getBody();
        }
        value_ %= this.getBody();
    }

    public void multiplyEqual(Gf1234577 other) {
        value_ *= other.value_;
        value_ %= this.getBody();
    }

    public void divideEqual(Gf1234577 other) throws Exception {
        long inverse = 1;
        while((inverse * other.value_) % this.getBody() != 1 && inverse < this.getBody()) {
            inverse++;
        }
        if(inverse == this.getBody()) {
            throw new Exception(other.value_ + " is not reversible.");
        }
        value_ = (value_ * inverse) % this.getBody();
    }

    public Gf1234577 clone() {
        return new Gf1234577(value_);
    }

    protected long getBody() {
        return BODY;
    }
}