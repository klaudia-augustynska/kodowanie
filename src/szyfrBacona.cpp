#include "kodowanie.h"
#include "szyfrBacona.h"

szyfrBacona::szyfrBacona()
{
    // jak alfabet braille'a, tylko że litery są na 5 a nie 6 poziomie
    alfabet = " ABCDEFGHIKLMNOPQRSTUWXYZ";
}

szyfrBacona::~szyfrBacona()
{
    //dtor
}

string szyfrBacona::encode(string napis) {

    int len = napis.length();
    int nowyOjciec, staryOjciec; // :D
    int i, j;
    string napis2, output;
    string l1, l2, l3;
    stack<char> litera; // ( 1 . ) (2 - )
    char c;

    // usun zbedne znaki
    for (i = 0; i < len; i++) {
        for (i; napis[i] == ' ' && napis[i+1] == ' '; i++);
        c = toupper(napis[i]);
        if (c == 74) // J jest traktowane jako I
            c = 73;
        else if (c == 86) // V jest traktowane jako U
            c = 85;
        if ((c < 65 && c != 32) || c > 90)
            continue;
        napis2.push_back( c );
    }

    len = napis2.length();

    for (i = 0; i < len; i++) {

        if (napis2[i] == ' ') {
            output.append("/ ");
        }
        else {
            // sprawdz jaki ID ma ta litera
            for (j = 0; j < alfabet.length() && napis2[i] != alfabet[j]; j++);

            // przeszukuj ojców

            nowyOjciec = j + suma;

            do {

                staryOjciec = nowyOjciec;
                nowyOjciec = staryOjciec / 2;

                if (nowyOjciec*2 == staryOjciec)
                    litera.push('a');
                else
                    litera.push('b');

            } while (nowyOjciec > 1);

            // zdejmij literki ze

            while (!litera.empty()) {
                output.push_back( litera.top() );
                litera.pop();
            }

            output.push_back(' ');

        }

    }

    return output;

}

string szyfrBacona::decode(string napis) {

    /*

    Przykładowe wejście:

    ._____ ...___ ._____ / ._..__ ._____ / ._.___ ._._._ _...._ ._____
       A      L      A        M      A         K      O     T       A

    */

    napis.push_back(' ');

    int len = napis.length();
    int x, i;
    string output;

    x = 1;
    for (i = 0; i < len; i++) {
        switch (napis[i]) {
            case ' ':
                if (x != 1)
                    output.push_back( alfabet[x-suma] );
                x = 1;
                break;
            case '/':
                output.push_back(' ');
                break;
            case 'b':
            case 'B':
                x = 2*x + 1;
                break;
            case 'a':
            case 'A':
                x = 2*x;
                break;
        }
    }

    return output;

}

wchar_t* szyfrBacona::rasskazywaj() {

    return L"Szyfr Bacona to szyfr, w którym każdej literze przyporządkowana jest kolejna permutacja liter A i B, gdzie każda permutacja liczy 5 liter.";

}
