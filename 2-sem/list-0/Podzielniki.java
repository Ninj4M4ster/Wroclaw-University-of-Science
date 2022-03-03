public class Podzielniki {
    public static void main(String[] args) {
        for(int i = 0; i < args.length; i++) {
            int n = 0;
            try { 
                n = Integer.parseInt(args[i]);
                int dzielnik = div(n);
                System.out.println("Najwiekszy dzielnik " + args[i] + ": " + dzielnik);
            }
            catch (NumberFormatException ex) {
                System.out.println(args[i] + " nie jest liczba calkowita");
            }
        }
    }
    public static int div(int n) {
        int i = 1;
        int maks = 0;
        while(i <= Math.abs(n/2)) {
            if(n%i == 0) {
                maks = i;
            }
            i++;
        }
        return maks;
    }
}
