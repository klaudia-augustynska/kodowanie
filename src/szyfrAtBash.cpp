#include "kodowanie.h"
#include "szyfrAtBash.h"

szyfrAtBash::szyfrAtBash()
{
    //ctor
}

szyfrAtBash::~szyfrAtBash()
{
    //dtor
}

string szyfrAtBash::encode(string napis) {

    string output;
    int len = napis.length();
    int i;
    int wynik, x;

    for (i = 0; i < len; i++) {

        /*
            jeśli
                początek = 65 (A)
                koniec = 90 (Z)

            a szyfr ma od Z odejmować różnicę między np. B a A, to:

                wynik = koniec - (napis[i] - początek)
                = koniec - napis[i] + początek
                = (koniec + początek) - napis[i]

            (koniec + początek) = np. 65 + 90 = 155
        */

        x = 0;
        if ( // wielkie litery
            napis[i] >= 65 &&
            napis[i] <= 90
            ) {
                x = 155;
            }
        else if ( // małe litery
            napis[i] >= 97 &&
            napis[i] <= 122
            ) {
                x = 219;
            }
        else {
            wynik = napis[i];
        }

        if (x > 0) {
            wynik = x - napis[i];
        }

        output.push_back( wynik );
    }

    return output;

}

string szyfrAtBash::decode(string napis) {

    return szyfrAtBash::encode(napis);

}

wchar_t* szyfrAtBash::rasskazywaj() {

    return L"Szyfr AtBash (z hebr. AtBasz) – prosty monoalfabetyczny szyfr podstawieniowy pochodzenia hebrajskiego, którego działanie polega na zamianie litery leżącej w odległości X od początku alfabetu na literę leżącą w odległości X od jego końca. Prawdopodobnie został on opracowany około roku 500 p.n.e.\n\n(wikipedia)";

}
