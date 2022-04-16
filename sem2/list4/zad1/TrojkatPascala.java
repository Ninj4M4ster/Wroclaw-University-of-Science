import zad1.NiepoprawneDane;

import java.awt.event.*;
import java.awt.Color;
import javax.swing.*;

public class TrojkatPascala {
    // komponenty
    private JTextField poleDoWprowadzania;
    private JFrame glowneOkno;
    private JPanel obszarTrojkata;
    private JLabel[] wierszeTrojkata;
    private JLabel ramkaWiadomosciBledu;

    // wartosci statyczne
    static final int STARTOWA_SZEROKOSC_OKNA = 1400;
    static final int STARTOWA_DLUGOSC_OKNA = 135;
    static final int STARTOWA_POZYCJA_X = 50;
    static final int STARTOWA_POZYCJA_Y = 50;

    // zmienne pomocniczne
    private Timer usunWiadomosc;
    private boolean trojkatUtworzony = false;
    private boolean bladWyswietlony = false;
    private int aktualnaDlugoscOkna = STARTOWA_DLUGOSC_OKNA;
    private int aktualnaPozycjaYTrojkata = 85;
    private int aktualnaWysokoscTrojkata = 0;
    private int aktualnaIloscWierszy = 0;

    TrojkatPascala() {
        glowneOkno = new JFrame();
        glowneOkno.setTitle("Trojkat Pascala");

        // potrzebne komponenty
        JLabel opisPola = new JLabel("Wprowadz liczbe wierszy trojkata (liczba od 1 do 30)");
        opisPola.setBounds(425, 40, 300, 15);

        this.poleDoWprowadzania = new JTextField();
        poleDoWprowadzania.setBounds(725, 30, 100, 35);

        JButton przyciskStart = new JButton("Utworz trojkat");
        przyciskStart.setBounds(845, 30, 150, 35);

        this.ramkaWiadomosciBledu = new JLabel("", SwingConstants.CENTER);
        this.ramkaWiadomosciBledu.setForeground(Color.red);

        // obszar na trojkat razem z 
        this.obszarTrojkata = new JPanel();
        this.obszarTrojkata.setLayout(null);
        this.obszarTrojkata.setBounds(40, 85, STARTOWA_SZEROKOSC_OKNA - 80, 0);  // TODO: dodać wyglad typu obramowanie

        this.wierszeTrojkata = new JLabel[30];
        for(int i=0; i < 30; i++) {
            this.wierszeTrojkata[i] = new JLabel("", SwingConstants.CENTER);
            this.wierszeTrojkata[i].setBounds(10, 10 + 20 * i, STARTOWA_SZEROKOSC_OKNA - 80, 15);
            this.obszarTrojkata.add(this.wierszeTrojkata[i]);
        }
        

        // dodanie nasluchiwania wydarzen
        przyciskStart.addActionListener(this::stworzTrojkat);

        // dodanie komponentow do glownego obszaru
        glowneOkno.add(opisPola);
        glowneOkno.add(this.poleDoWprowadzania);
        glowneOkno.add(przyciskStart);
        glowneOkno.add(this.obszarTrojkata);

        // logika zamykania okna
        glowneOkno.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                System.exit(0);
            }
        });

        glowneOkno.setBounds(STARTOWA_POZYCJA_X, STARTOWA_POZYCJA_Y, STARTOWA_SZEROKOSC_OKNA, STARTOWA_DLUGOSC_OKNA);
        glowneOkno.setLayout(null);
        glowneOkno.setVisible(true);

        //TODO: Dodać obsługę wydarzen gdy uzytkownik poszerzy i zwezi okno
    }
    public static void main(String[] args) {
        new TrojkatPascala();
    }

    private void stworzTrojkat(ActionEvent e) {
        String napis = this.poleDoWprowadzania.getText();
        try {
            if(Boolean.FALSE.equals(czyLiczbaCalkowita(napis))) {
                throw new NiepoprawneDane("Nie wprowadzono liczby.");
            }
            else {
                int iloscWierszy = Integer.parseInt(napis);
                if(iloscWierszy <= 0)
                    throw new NiepoprawneDane("Wprowadzono liczbe mniejsza od 1.");
                if(iloscWierszy > 30)
                    throw new NiepoprawneDane("Wprowadzono liczbe wieksza od 30.");
                int roznicaIlosciWierszy = iloscWierszy - this.aktualnaIloscWierszy;
                this.aktualnaDlugoscOkna += roznicaIlosciWierszy * 20;
                this.aktualnaWysokoscTrojkata = iloscWierszy*20 + 10;
                if(!this.trojkatUtworzony)
                    this.aktualnaDlugoscOkna += 20;

                this.trojkatUtworzony = true;
                this.aktualnaIloscWierszy = iloscWierszy;

                this.glowneOkno.setSize(STARTOWA_SZEROKOSC_OKNA, this.aktualnaDlugoscOkna);
                this.obszarTrojkata.setSize(STARTOWA_SZEROKOSC_OKNA - 80, this.aktualnaWysokoscTrojkata);

                for(int i = 0; i < iloscWierszy; i ++) {
                    this.wierszeTrojkata[i].setText(obliczWiersz(i));
                }
            }
        } catch(NiepoprawneDane blad) {
            // logika wyswietlania bledu
            this.ramkaWiadomosciBledu.setText(blad.getMessage());
            if(!bladWyswietlony) {
                this.aktualnaDlugoscOkna += 35;
                this.ramkaWiadomosciBledu.setBounds(40, 85, STARTOWA_SZEROKOSC_OKNA - 80, 15);
                this.glowneOkno.add(this.ramkaWiadomosciBledu);
                this.glowneOkno.setSize(STARTOWA_SZEROKOSC_OKNA, this.aktualnaDlugoscOkna);

                this.aktualnaPozycjaYTrojkata += 35;
                this.obszarTrojkata.setLocation(40, this.aktualnaPozycjaYTrojkata);
            
                this.usunWiadomosc = new Timer(5, this::usunBlad);
                this.usunWiadomosc.setInitialDelay(5000);
                this.usunWiadomosc.setRepeats(false);

                bladWyswietlony = true;
            }
            this.usunWiadomosc.restart();
        }
    }

    private void usunBlad(ActionEvent event) {
        this.glowneOkno.remove(this.ramkaWiadomosciBledu);
        this.aktualnaDlugoscOkna -= 35;
        this.glowneOkno.setSize(STARTOWA_SZEROKOSC_OKNA, this.aktualnaDlugoscOkna);

        
        this.aktualnaPozycjaYTrojkata -= 35;
        this.obszarTrojkata.setLocation(40, this.aktualnaPozycjaYTrojkata);

        this.bladWyswietlony = false;
    }
    
    private String obliczWiersz(int numerWiersza) {
        String[] elementy = new String[numerWiersza + 1];
        for(int i = 0; i <= numerWiersza; i++) {
            elementy[i] = String.valueOf(wartoscDwumianu(numerWiersza, i));
        }
        return String.join(" ", elementy);
    }

    private int wartoscDwumianu(int n, int k) {
        if(k == n || k == 0)
            return 1;
        int wynik = n;
        for(int i = 1; i < k; i++) {
            wynik *= n - i;
            wynik /= i + 1;
        }
        return wynik;
    }

    private Boolean czyLiczbaCalkowita(String napis) {
        try {
            Integer.parseInt(napis);
            return true;
        } catch(NumberFormatException e) {
            return false;
        }
    }
}