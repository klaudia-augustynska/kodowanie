#include "kodowanie.h"
#include "szyfrCmentarny.h"

szyfrCmentarny::szyfrCmentarny()
{
    cmentarz = " OE XND WRH  QG ZPF Y    SI      LB UKA T        MC V";

    // jest zupełnie jak z alfabetem brailea, tylko że będzie się inaczej wypisywało wynik

    /*

        drzewo ułożone jest zgodnie z zasadą:

        true - lewy syn
        false - prawy syn

        i tak układamy w kolejności, że jeśli występuje:
            1. T - górna ramka
            2. R - prawa ramka
            3. B - dolna ramka
            4. L - lewa ramka
            5. 1 - pierwsza kropka
            6. 2 - druga kropka
        to układamy literę odpowiednio na lewo lub na prawo...

    */
}

szyfrCmentarny::~szyfrCmentarny()
{
    //dtor
}

string szyfrCmentarny::encode(string napis) {

    int len = napis.length();
    int nowyOjciec, staryOjciec; // :D
    int i, j, k;
    string napis2, output;
    string l1, l2, l3;
    bool litera[6];
    char c;

    // usun zbedne znaki
    for (i = 0; i < len; i++) {
        c = toupper(napis[i]);
        if (c == 74) // J jest traktowane jako I
            c = 73;
        if (c < 65 || c > 90)
            continue;
        napis2.push_back( c );
    }

    len = napis2.length();

    for (i = 0; i < len; i++) {

        if (napis2[i] == ' ') {
            l1.append("    ");
            l2.append("    ");
            l3.append("    ");
        }
        else {
            // sprawdz jaki ID ma ta litera
            for (j = 0; j < cmentarz.length() && napis2[i] != cmentarz[j]; j++);

            // przeszukuj ojców

            nowyOjciec = j + suma;
            k = 5;

            do {

                staryOjciec = nowyOjciec;
                nowyOjciec = staryOjciec / 2;

                if (nowyOjciec*2 == staryOjciec)
                    litera[k] = true;
                else
                    litera[k] = false;

                k--;

            } while (nowyOjciec > 1);
/*
            for (k = 0; k < 6; k++)
                if (litera[k] == true)
                    l1.push_back('.');
                else
                    l1.push_back('-');
            l1.append("   ");
*/

            // narysuj wg tego literę:

            /*
                        012345
                litera: TRBL12  true/false

                l1:  TL  T  RT
                l2:   L  12 R
                l3:  BL  B  RB

                kody ramki:

                    218  196  191
                    179       179
                    192  196  217

            */


            char tl, rt, bl, rb, h, v;
            tl = 218;
            rt = 191;
            bl = 192;
            rb = 217;
            v = 196;
            h = 179;

            // linia 1
            if (litera[0] == true) {

                if (litera[3] == true)
                    l1.push_back( tl );
                else
                    l1.push_back( v );

                l1.push_back( v );
                l1.push_back( v );

                if (litera[1] == true)
                    l1.push_back( rt );
                else
                    l1.push_back( v );

                l1.push_back( ' ' );

            } else {
                l1.append("     ");
            }

            // linia 2
            if (litera[3] == true)
                l2.push_back( h );
            else
                l2.push_back( ' ' );

            if (litera[4] == true)
                if (litera[5] == true)
                    l2.push_back( ':' );
                else
                    l2.push_back( '.' );
            else
                l2.push_back( ' ' );
            l2.push_back( ' ' );

            if (litera[1] == true)
                l2.push_back( h );
            else
                l2.push_back( ' ' );

            l2.push_back( ' ' );

            // linia 3
            if (litera[2] == true) {

                if (litera[3] == true)
                    l3.push_back( bl );
                else
                    l3.push_back( v );

                l3.push_back( v );
                l3.push_back( v );

                if (litera[1] == true)
                    l3.push_back( rb );
                else
                    l3.push_back( v );

                l3.push_back( ' ' );

            } else {
                l3.append("     ");
            }

        }

    }

    output.append(l1);
    output.push_back('\n');
    output.append(l2);
    output.push_back('\n');
    output.append(l3);
    output.push_back('\n');

    return output;


}

string szyfrCmentarny::decode(string napis) {

    /*

    Przykładowe wejście:

    -..-.-  -.....  -..-.-  --....  -..-.-  -..-..  ......  -..---  -..-.-
       A      L       A        M      A       K       O        T       A

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
                    output.push_back( cmentarz[x-suma] );
                x = 1;
                break;
            case '/':
                output.push_back(' ');
                break;
            case '_':
            case '-':
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

wchar_t* szyfrCmentarny::rasskazywaj() {

    return L"Szyfr cmentarny to szyfr podstawieniowy reprezentujący literę jako symbole przybierające postać kwadratu (któremu może brakować którejś krawędzi), opcjonalnie z kropkami w środku (jedna lub dwie). ";

}
