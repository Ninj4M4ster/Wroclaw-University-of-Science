import javax.swing.*;
import javax.swing.plaf.FontUIResource;
import javax.swing.text.AttributeSet.FontAttribute;
import javax.swing.text.StyleConstants.FontConstants;
import javax.swing.text.StyledEditorKit.FontFamilyAction;

import java.awt.Color;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Gui extends JFrame {
    JLabel ramkaNaElementy;
    JLabel opisPola;
    JLabel poleWyniku;
    JTextField poleDoWprowadzania;
    JButton przyciskStart;

    // zmienne pomocnicze okna
    private final int DLUGOSC_OKNA = 200;
    private final int SZEROKOSC_OKNA = 1400;
    private int aktualna_dlugosc_okna = DLUGOSC_OKNA;

    Gui() {
        // pola dla uzytkownika
        this.opisPola = new JLabel("Wprowadz wiersz trojkata Pascala do wyswietlenia (liczba z zakresu 0 - 29)");
        this.opisPola.setBounds(0, 10, 500, 20);

        this.poleDoWprowadzania = new JTextField();
        this.poleDoWprowadzania.setBounds(510, 0, 50, 40);

        this.przyciskStart = new JButton("Start!");
        this.przyciskStart.setBounds(570, 0, 100, 40);
        this.przyciskStart.addActionListener(this::utworzWierszTrojkata);

        // pole wyswietlajace wynik
        this.poleWyniku = new JLabel("", JLabel.CENTER);
        this.poleWyniku.setBounds(40, 120, SZEROKOSC_OKNA - 80, 0);
        this.poleWyniku.setBorder(BorderFactory.createLineBorder(Color.BLACK));

        // dodanie pol uzytkownika do osobnej ramki
        this.ramkaNaElementy = new JLabel();
        this.ramkaNaElementy.setBounds(365, 20, 670, 40);
        this.ramkaNaElementy.add(this.opisPola);
        this.ramkaNaElementy.add(this.poleDoWprowadzania);
        this.ramkaNaElementy.add(this.przyciskStart);

        // dodanie ramki i pola na wynik do okna
        this.add(this.ramkaNaElementy);
        this.add(this.poleWyniku);

        this.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent event) {
                System.exit(0);
            }
        });

        // ustawienia okna
        this.setTitle("Wiersz trojkata Pascala");
        this.setBounds(20, 20, SZEROKOSC_OKNA, DLUGOSC_OKNA);
        this.setLayout(null);
        this.setVisible(true);
    }

    void utworzWierszTrojkata(ActionEvent event) {
        String numerWiersza = this.poleDoWprowadzania.getText();
        String listaWszystkichIndeksow = "";
        String powiadomienie = "";
        if(Boolean.TRUE.equals(czyLiczbaCalkowita(numerWiersza))) {
            int numer = Integer.parseInt(numerWiersza) + 1;
            for(int i=0; i< numer; i++)
                listaWszystkichIndeksow += String.valueOf(i) + " ";
        }
        String komenda = 
            "cmd.exe /c C:\\Users\\kubad\\OneDrive\\Pulpit\\Programowanie\\Wroclaw-University-of-Science\\sem2\\list4\\zad2\\main " 
            + numerWiersza + " " + listaWszystkichIndeksow.strip();
        try {
            Process procesWierszaTrojkata = Runtime.getRuntime().exec(komenda);
                
            BufferedReader standardoweWyjscie = new BufferedReader(
                new InputStreamReader(procesWierszaTrojkata.getInputStream()));

            String linia = null;
            if(Boolean.TRUE.equals(czyLiczbaCalkowita(numerWiersza)) && Integer.parseInt(numerWiersza) >= 0 && 
              Integer.parseInt(numerWiersza) < 30) {
                while((linia = standardoweWyjscie.readLine()) != null)
                    powiadomienie += wydobadzOstatniNumer(linia) + " ";
            }
            else {
                while((linia = standardoweWyjscie.readLine()) != null)
                    powiadomienie += linia;
            }
            if(this.poleWyniku.getSize().height == 0) {
                this.poleWyniku.setSize(SZEROKOSC_OKNA - 80, 80);
                this.aktualna_dlugosc_okna += 40;
                this.setSize(SZEROKOSC_OKNA, this.aktualna_dlugosc_okna);
            }
            this.poleWyniku.setText(powiadomienie.strip());
        } catch(Exception blad) {
            System.out.println(blad.getMessage());
        }
    }

    String wydobadzOstatniNumer(String napis) {
        String odwroconyWynik = "";
        String wynik = "";
        int i = napis.length() - 1;
        while(napis.charAt(i) != ' ') {
            odwroconyWynik += napis.charAt(i);
            i -= 1;
        }
        for(int j = odwroconyWynik.length() - 1; j >= 0; j--)
            wynik += odwroconyWynik.charAt(j);
        return wynik;
    }

    Boolean czyLiczbaCalkowita(String napis) {
        try {
            Integer.parseInt(napis);
            return true;
        } catch(NumberFormatException e) {
            return false;
        }
    }

    public static void main(String[] args) {
        new Gui();
    }
}
