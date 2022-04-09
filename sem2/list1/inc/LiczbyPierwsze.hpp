#ifndef LICZBYPIERWSZE_HPP
#define LICZBYPIERWSZE_HPP

namespace liczbyPierwsze {
    
    class LiczbyPierwsze {

        private:
          int* tablica;
          int ilosc;

        public:
          LiczbyPierwsze(int n);
          ~LiczbyPierwsze();
          int liczba(int m);
          int podajIlosc();
          bool czyPierwsza(int n);
    };
} // namespace liczbyPierwsze

#endif // LICZBYPIERWSZE_HPP