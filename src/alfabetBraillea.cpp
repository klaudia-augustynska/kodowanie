#include "kodowanie.h"
#include "alfabetBraillea.h"

alfabetBraillea::alfabetBraillea()
{
    // na podstawie http://pl.wikipedia.org/wiki/Alfabet_Braille%27a
    // oraz wersji angielskiej, tam były także znaki interpunkcyjne

    /*

        litery zawsze składają się z 6 znaków, więc wszystkie znajdują się na 6 poziomie drzewa
        dlatego można w napisie nie uwzględniać poziomów 1-5 i tylko uwzględnić sumę 2^0 + 2^1 + ... + 2^5 = 63 w dalszych obliczniach

        lewy syn - kropka
        prawy syn - puste

        alfabet[i] odpowiada i-tej literze na 6. poziomie drzewa binarnego

    */

    alfabet = "  Q P RVL G F H BYNXMZOUK D C E A T S !?;WJ I.: ,n     -'";


}

alfabetBraillea::~alfabetBraillea()
{
    //dtor
}

string alfabetBraillea::encode(string napis) {

    int len = napis.length();
    int nowyOjciec, staryOjciec; // :D
    int i, j;
    string napis2, output;
    string l1, l2, l3;
    stack<char> litera; // ( 1 . ) (2 - )

    // usun zbedne spacje
    for (i = 0; i < len; i++) {
        napis2.push_back( toupper(napis[i]) );
        for (i; napis[i] == ' ' && napis[i+1] == ' '; i++);
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
            for (j = 0; j < alfabet.length() && napis2[i] != alfabet[j]; j++);

            // przeszukuj ojców

            nowyOjciec = j + suma;

            do {

                staryOjciec = nowyOjciec;
                nowyOjciec = staryOjciec / 2;

                if (nowyOjciec*2 == staryOjciec)
                    litera.push('.');
                else
                    litera.push(' ');

            } while (nowyOjciec > 1);

            // zdejmij kropki i kreski ze stosu

            /*

                stos: 654321

                l1:   1 4
                l2:   2 5
                l3:   3 6

            */

            for (j = 1; !litera.empty(); j++) {
                switch (j) {
                    case 1:
                    case 4:
                        l1.push_back( litera.top() );
                        break;
                    case 2:
                    case 5:
                        l2.push_back( litera.top() );
                        break;
                    case 3:
                    case 6:
                        l3.push_back( litera.top() );
                        break;
                }
                litera.pop();
            }

            l1.append("  ");
            l2.append("  ");
            l3.append("  ");


/*
while (!litera.empty()) {
    l1.push_back( litera.top() );
    litera.pop();
}

    l1.push_back( ' ' );
*/

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

string alfabetBraillea::decode(string napis) {

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

wchar_t* alfabetBraillea::rasskazywaj() {

    return L"Alfabet Braille'a – alfabet umożliwiający zapisywanie i odczytywanie tekstów osobom niewidomym.\n\nStworzony przez Louisa Braille'a, który w wyniku wypadku oślepł w dzieciństwie. Oparty jest na wojskowym systemie umożliwiającym odczytywanie rozkazów bez użycia światła. Jest jednym z pierwszych przykładów technologii asystujących.\n\nPodstawą, z której wyprowadza się cały system Braille'a jest sześciopunkt nazywany znakiem tworzącym. System składa się ze znaków będących kombinacją sześciu wypukłych punktów ułożonych w dwóch kolumnach po trzy punkty w każdej. Lewa kolumna zawiera umownie oznaczone punkty: 1,2,3, zaś prawą stanowią punkty: 4,5,6. Wzajemna kombinacja i rozmieszczenie punktów daje możliwość zapisu sześćdziesięciu trzech znaków. W brajlu można zapisać wszystko – istnieje kilka uzupełniających systemów zapisu brajlowskiego – notacje: matematyczna, chemiczna, fizyczna i muzyczna.\n\n(wikipedia)";

}
