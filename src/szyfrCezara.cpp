#include "kodowanie.h"
#include "szyfrCezara.h"

szyfrCezara::szyfrCezara()
{
    offset = 13;
}

szyfrCezara::szyfrCezara(int o)
{
    offset = o;
}

szyfrCezara::~szyfrCezara()
{
    //dtor
}

string szyfrCezara::encode(string napis) {

    string output;
    int len = napis.length();
    int i;
    int wynik, x1, x2;

    for (i = 0; i < len; i++) {

        wynik = napis[i] + offset;
        x1 = x2 = 1000;
        if ( // wielkie litery
            napis[i] >= 65 &&
            napis[i] <= 90
            ) {
                x1 = 65;
                x2 = 90;
            }
        else if ( // małe litery
            napis[i] >= 97 &&
            napis[i] <= 122
            ) {
                x1 = 97;
                x2 = 122;
            }
        else {
            wynik = napis[i];
        }

        if (wynik > x2) {
            wynik = wynik - x2 + x1 - 1;
        }

        output.push_back( wynik );
    }

    return output;
}

string szyfrCezara::decode(string napis) {

    string output;
    int len = napis.length();
    int i;
    int wynik, x1, x2;

    for (i = 0; i < len; i++) {

        wynik = napis[i] - offset;
        x1 = x2 = 0;
        if ( // wielkie litery
            napis[i] >= 65 &&
            napis[i] <= 90
            ) {
                x1 = 65;
                x2 = 90;
            }
        else if ( // małe litery
            napis[i] >= 97 &&
            napis[i] <= 122
            ) {
                x1 = 97;
                x2 = 122;
            }
        else {
            wynik = napis[i];
        }

        if (wynik < x1) {
            wynik = wynik + x2 - x1 + 1;
        }

        output.push_back( wynik );
    }

    return output;
}

wchar_t* szyfrCezara::rasskazywaj( ) {

    return L"Szyfr Cezara (zwany też szyfrem przesuwającym, kodem Cezara lub przesunięciem Cezariańskim) – w kryptografii jedna z najprostszych technik szyfrowania. Jest to rodzaj szyfru podstawieniowego, w którym każda litera tekstu jawnego (niezaszyfrowanego) zastępowana jest oddaloną od niej o stałą liczbę pozycji w alfabecie inną literą (szyfr monoalfabetyczny), przy czym kierunek zamiany musi być zachowany. Nie rozróżnia się przy tym liter dużych i małych. Nazwa szyfru pochodzi od Juliusza Cezara, który prawdopodobnie używał tej techniki do komunikacji ze swymi przyjaciółmi.\n\n(wikipedia)";

}
