package packages;

public class WierszTrojkataPascala {

    int[] tablica;

    public WierszTrojkataPascala(int n) throws ArgumentMniejszyOdZera, ZaDuzyWierszTrojkataPascala {
        if(n < 0)
            throw new ArgumentMniejszyOdZera("Nieprawidlowy numer wiersza");
        tablica = new int[n+1];
        for(int i = 0; i <= n; i++) {
            tablica[i] = wartoscDwumianu(n, i);
            if(tablica[i] < 0)
                throw new ZaDuzyWierszTrojkataPascala("Wartosci wiersza przekraczaja maksymalna wartosc typu liczb calkowitych");
        }
    }
    static int wartoscDwumianu(int n, int k) {
        int wynik = n;
        for(int i=1; i<=k; i++) {
            wynik *= n-i;
            wynik /= i+1;
        }
        return wynik;
    }
    public int wspolczynnik(int m) throws ArgumentWiekszyOdArgumentuKonstruktora, ArgumentMniejszyOdZera {
        if(m < 0)
            throw new ArgumentMniejszyOdZera("liczba spoza zakresu");
        else if(m >= tablica.length)
            throw new ArgumentWiekszyOdArgumentuKonstruktora("liczba spoza zakresu");
        else
            return tablica[m];
    }
}