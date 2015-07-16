#include "kodowanie.h"
#include "szyfrVigenerea.h"

szyfrVigenerea::szyfrVigenerea()
{
    tajnyklucz = "TAJNE";
    alfabet = "ABCDEFHGIJKLMNOPQRSTUVWXYZ";
}

szyfrVigenerea::szyfrVigenerea(string klucz)
{
    char c;
    int i;
    int len = klucz.length();

    // usun zbedne znaki z klucza
    for (i = 0; i < len; i++) {
        c = toupper(klucz[i]);
        if (c < 65 || c > 90)
            continue;
        tajnyklucz.push_back( c );
    }

    alfabet = "ABCDEFHGIJKLMNOPQRSTUVWXYZ";

}

szyfrVigenerea::~szyfrVigenerea()
{
    //dtor
}


string szyfrVigenerea::encode(string napis) {

    string output;
    string napis2;
    int nlen = napis.length();
    int klen = tajnyklucz.length();
    int alen = alfabet.length();
    int i, j;
    int x, y, wynik;

    // konwertuj na duze litery
    for (i = 0; i < nlen; i++)
        napis2.push_back( toupper(napis[i]) );

    /*
        każdej literze w stringu alfabet odpowiada jakaś litera z klucza, jak go zapętlamy
        no chyba że to nie jest litera - wtedy pomijamy ten znak

        jeśli literze napis[i] odpowiada litera np. T, to należy sprawdzić, która litera leży w odległości "i" od litery T - to wynik
    */

    nlen = napis2.length();

    for (i = j = 0; i < nlen; i++) {

        // jeśli znak nie jest literą, jedź dalej
        if (napis2[i] < 65 || napis2[i] > 90) {
            output.push_back(napis2[i]);
            continue;
        }

        // jeśli to jednak litera - sprawdź czy nie czas przewinąć wskaźnik od klucza
        if (j == klen)
            j = 0;

        // sprawdź, którą literą w alfabecie jest tajnyklucz[j]
        for (y = 0; y < alen && tajnyklucz[j] != alfabet[y]; y++);

        // sprawdź, którą literą w afabecie jest napis2[i]
        for (x = 0; x < alen && napis2[i] != alfabet[x]; x++);

        // sprawdź jaka będzie litera po przewinięciu od napis2[y] o "x" miejsc
        wynik = (y + x) % alen;

        output.push_back(alfabet[wynik]);
        j++;

    }

    return output;
}

string szyfrVigenerea::decode(string napis) {


    string output;
    string napis2;
    int nlen = napis.length();
    int klen = tajnyklucz.length();
    int alen = alfabet.length();
    int i, j;
    int x, y, wynik;

    // konwertuj na duze litery
    for (i = 0; i < nlen; i++)
        napis2.push_back( toupper(napis[i]) );

    nlen = napis2.length();

    for (i = j = 0; i < nlen; i++) {

        // jeśli znak nie jest literą, jedź dalej
        if (napis2[i] < 65 || napis2[i] > 90) {
            output.push_back(napis2[i]);
            continue;
        }

        // jeśli to jednak litera - sprawdź czy nie czas przewinąć wskaźnik od klucza
        if (j == klen)
            j = 0;

        // sprawdź, którą literą w alfabecie jest tajnyklucz[j]
        for (y = 0; y < alen && tajnyklucz[j] != alfabet[y]; y++);

        // sprawdź, którą literą w afabecie jest napis2[i]
        for (x = 0; x < alen && napis2[i] != alfabet[x]; x++);

        // sprawdź jaka będzie litera po przewinięciu DO TYŁU napis2[y] o "x" miejsc

        wynik = x - y;
        if (wynik < 0)
            wynik = alen + wynik;

        output.push_back(alfabet[wynik]);
        j++;

    }

    return output;

}

wchar_t* szyfrVigenerea::rasskazywaj( ) {

    return L"Algorytm Vigenère'a jest jednym z klasycznych algorytmów szyfrujących. Należy on do grupy tzw. wieloalfabetowych szyfrów podstawieniowych. Szyfr ten błędnie został przypisany twórcy bardziej skomplikowanego szyfru Blaise'owi de Vigenère.\n\nSzyfr, który obecnie nazywamy szyfrem Vigenère'a po raz pierwszy został opisany przez Giovana Batista Belaso w 1553 w broszurze zatytułowanej La cifra del. Sig. Giovan Batista Belaso.\n\n(wikipedia)";

}
