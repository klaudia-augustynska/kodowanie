#include "kodowanie.h"
#include "kodowanieMorsea.h"


kodowanieMorsea::kodowanieMorsea()
{
    // na podstawie http://pl.wikipedia.org/wiki/Kod_Morse'a
    kropkiKreskiItd = "  ETIANMSURWDKGOHVF L PJBXCYZQ c54     2  +    16=/   ( 7   8 90            ?_    \"  .    @   '  -        ;! )     ,    :";

    /*

    gdzie

        i = numer w drzewie

        i 0 1 2 3
              E T I A

        i = x + 2

        lewy syn:
            kropka .
            2i

        prawy syn:
            kreska -
            2i + 1

        ojciec:
            i / 2

    */



}

kodowanieMorsea::~kodowanieMorsea()
{
    //dtor
}
string kodowanieMorsea::encode(string napis) {

    int len = napis.length();
    int nowyOjciec, staryOjciec; // :D
    int i, j;
    string napis2, output;
    stack<char> litera; // ( 1 . ) (2 - )

    // usun zbedne spacje
    for (i = 0; i < len; i++) {
        napis2.push_back( toupper(napis[i]) );
        for (i; napis[i] == ' ' && napis[i+1] == ' '; i++);
    }

    len = napis2.length();

    for (i = 0; i < len; i++) {
        if (napis2[i] == ' ')
            output.append("/ ");
        else {
            // sprawdz jaki ID ma ta litera
            for (j = 0; j < kropkiKreskiItd.length() && napis2[i] != kropkiKreskiItd[j]; j++);

            // przeszukuj ojców i zapisuj czy kreska czy kropka na stos
                /*
                    dopóki nowyOjciec > 1, sprawdzaj kto jest ojcem
                    jeśli nowyOjciec*2 == staryOjciec => chodziło o kropkę
                    inaczej => chodziło o kreskę
                */

            nowyOjciec = j;

            do {

                staryOjciec = nowyOjciec;
                nowyOjciec = staryOjciec / 2;

                if (nowyOjciec*2 == staryOjciec)
                    litera.push('.');
                else
                    litera.push('_');

            } while (nowyOjciec > 1);

            // zdejmij kropki i kreski ze stosu

            while (!litera.empty()) {
                output.push_back( litera.top() );
                litera.pop();
            }

            output.push_back(' ');

        }
    }

    return output;

}

string kodowanieMorsea::decode(string napis) {

    napis.push_back(' ');

    int len = napis.length();
    int x, i;
    string output;

    /*

    -- --- .-. ... . / -.-. --- -.. .

    M   O   R   S  E /  C    O   D  E

    */

    x = 1;
    for (i = 0; i < len; i++) {
        switch (napis[i]) {
            case ' ':
                if (x != 1)
                    output.push_back( kropkiKreskiItd[x] );
                x = 1;
                break;
            case '/':
                output.push_back(' ');
                break;
            case '-':
            case '_':
                x = 2*x + 1;
                break;
            case '.':
            case '*':
                x = 2*x;
                break;
        }
    }

    return output;
}

wchar_t* kodowanieMorsea::rasskazywaj( ) {

    return L"Kod Morse'a – stworzony w 1840 przez Samuela Morse'a i Alfreda Vaila sposób reprezentacji alfabetu, cyfr i znaków specjalnych za pomocą dźwięków, błysków światła, impulsów elektrycznych lub znaków popularnie zwanych kreską i kropką.\n\nWszystkie znaki reprezentowane są przez kilkuelementowe serie sygnałów – krótkich (kropek) i długich (kresek). Kreska powinna trwać co najmniej tyle czasu, co trzy kropki. Odstęp pomiędzy elementami znaku powinien trwać jedną kropkę. Odstęp pomiędzy poszczególnymi znakami – jedną kreskę. Odstęp pomiędzy grupami znaków – trzy kreski.\n\n(wikipedia)";
}
