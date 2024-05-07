package main;

import java.security.SecureRandom;

class User<T extends GF1234567891> {
    private DHSetup<T> dh_setup_;
    private T encrypting_key_;
    private boolean key_set_ = false;
    private long secret;
    private SecureRandom random = new SecureRandom();


    public User(DHSetup<T> dh_setup) {
        dh_setup_ = dh_setup;
        long characteristic = T.Characteristic();
        secret = random.nextLong(characteristic - 2) + 1;
    }

    public T getPublicKey() {
        return dh_setup_.power(dh_setup_.getGenerator(), secret);
    }

    public void setKey(T a) {
        encrypting_key_ = dh_setup_.power(a, secret);
        key_set_ = true;
    }

    public T encrypt(T m) throws Exception {
        if (!key_set_) {
            throw new Exception("No key was set, data cannot be encrypted");
        }
        return (T) T.multiply(m, encrypting_key_);
    }

    public T decrypt(T c) throws Exception {
        if (!key_set_) {
            throw new Exception("No key was set, data cannot be decrypted");
        }
        return (T) T.divide(c, encrypting_key_);
    }
}
