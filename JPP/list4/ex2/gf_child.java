package main;

class GF1234567891 extends Gf1234577 {
    protected static long BODY = 1234567891;

    // constructors 

    public GF1234567891() {}

    public GF1234567891(int val) {
        long new_val = val;
        if(new_val < 0) {
            new_val *= -1;
            new_val %= (int) this.getBody();
            new_val = (int)this.getBody() - new_val;
        }
        super.value_ = new_val % this.getBody();
    }

    public GF1234567891(long val) {
        if(val < 0) {
            val *= -1;
            val %= this.getBody();
            val = this.getBody() -val;
        }
        super.value_ = val % this.getBody();
    }

    public GF1234567891(Gf1234577 other) {
        super.value_ = other.value_;
    }

    public static long Characteristic() {
        return BODY;
    }

    // arithmetic 

    public static GF1234567891 add(GF1234567891 first, GF1234567891 second) {
        return new GF1234567891((first.value_ + second.value_) % BODY);
    }

    public static GF1234567891 subtract(GF1234567891 first, GF1234567891 second) {
        long val = first.value_ - second.value_;
        if(val < 0) {
            val += BODY;
        }
        return new GF1234567891(val);
    }

    public static GF1234567891 multiply(GF1234567891 first, GF1234567891 second) {
        return new GF1234567891(first.value_ * second.value_);
    }

    public static GF1234567891 divide(GF1234567891 first, GF1234567891 second) throws Exception{
        long inverse = 1;
        while((inverse * second.value_) % BODY != 1 && inverse < BODY) {
            inverse++;
        }
        if(inverse == BODY) {
            throw new Exception(second.value_ + " is not reversible.");
        }
        return new GF1234567891(first.value_ * inverse);
    }

    protected long getBody() {
        return BODY;
    }

    public GF1234567891 clone() {
        return new GF1234567891(value_);
    }
}
