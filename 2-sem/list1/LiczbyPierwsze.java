package list1;

public class LiczbyPierwsze {

    private int[] tablica;
    public int ilosc;

    public LiczbyPierwsze(int n) {
        tablica = new int[n];
        ilosc = 0;
        for(int i=2; i<=n; i++) {
            if(CzyPierwsza(i)) {
                tablica[ilosc] = i;
                ilosc ++;
            }
        }
    }

    private boolean CzyPierwsza(int n) {
        if(n < 2) {
            return false;
        }
        for(int i = 2; i <= Math.sqrt(n); i++) {
            if(n%i == 0){
                return false;
            }
        }
        return true;
    }

    public int liczba(int m) {
        return tablica[m];
    }
}

