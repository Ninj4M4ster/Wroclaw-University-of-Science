package main;

public class Program {
    public static void main(String[] args) throws Exception {
        Gf1234577 a = new Gf1234577(5);
        Gf1234577 b = new Gf1234577(27);
        System.out.println("a = " + a.stringify());
        System.out.println("b = " + b.stringify());
        System.out.println(a.stringify() + " + " + b.stringify() + " = " + Gf1234577.add(a, b).stringify());
        System.out.println(a.stringify() + " - " + b.stringify() + " = " + Gf1234577.subtract(a, b).stringify());
        System.out.println(a.stringify() + " * " + b.stringify() + " = " + Gf1234577.multiply(a, b).stringify());
        System.out.println(a.stringify() + " / " + b.stringify() + " = " + Gf1234577.divide(a, b).stringify());
        System.out.println();

        System.out.println(a.stringify() + " == " + b.stringify() + " = " + Gf1234577.equal(a, b));
        System.out.println(a.stringify() + " != " + b.stringify() + " = " + Gf1234577.notEqual(a, b));
        System.out.println(a.stringify() + " < " + b.stringify() + " = " + Gf1234577.less(a, b));
        System.out.println(a.stringify() + " > " + b.stringify() + " = " + Gf1234577.greater(a, b));
        System.out.println(a.stringify() + " <= " + b.stringify() + " = " + Gf1234577.lessEqual(a, b));
        System.out.println(a.stringify() + " >= " + b.stringify() + " = " + Gf1234577.greaterEqual(a, b));
        System.out.println();
    
        long a_p = Gf1234577.toLong(a);
        int b_p = Gf1234577.toInt(b);
    
        Gf1234577 c = new Gf1234577(a);
    
        System.out.println("c = a; c = " + c.stringify());
        System.out.println();
        System.out.println("Characteristic: " + Gf1234577.Characteristic());
    }
}
