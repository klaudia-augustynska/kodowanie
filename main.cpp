/*

    .--.   .--.      ,-----.     ______         ,-----.    .--.      .--.   ____    ,---.   .--..-./`)     .-''-.
    |  | _/  /     .'  .-,  '.  |    _ `''.   .'  .-,  '.  |  |_     |  | .'  __ `. |    \  |  |\ .-.')  .'_ _   \
    | (`' ) /     / ,-.|  \ _ \ | _ | ) _  \ / ,-.|  \ _ \ | _( )_   |  |/   '  \  \|  ,  \ |  |/ `-' \ / ( ` )   '
    |(_ ()_)     ;  \  '_ /  | :|( ''_'  ) |;  \  '_ /  | :|(_ o _)  |  ||___|  /  ||  |\_ \|  | `-'`"`. (_ o _)  |
    | (_,_)   __ |  _`,/ \ _/  || . (_) `. ||  _`,/ \ _/  || (_,_) \ |  |   _.-`   ||  _( )_\  | .---. |  (_,_)___|
    |  |\ \  |  |: (  '\_/ \   ;|(_    ._) ': (  '\_/ \   ;|  |/    \|  |.'   _    || (_ o _)  | |   | '  \   .---.
    |  | \ `'   / \ `"/  \  ) / |  (_.\.' /  \ `"/  \  ) / |  '  /\  `  ||  _( )_  ||  (_,_)\  | |   |  \  `-'    /
    |  |  \    /   '. \_/``".'  |       .'    '. \_/``".'  |    /  \    |\ (_ o _) /|  |    |  | |   |   \       /
    `--'   `'-'      '-----'    '-----'`        '-----'    `---'    `---` '.(_,_).' '--'    '--' '---'    `'-..-'


| |                | | / / |               | (_)             / _ \                      | |                 | |
| |__  _   _       | |/ /| | __ _ _   _  __| |_  __ _       / /_\ \_   _  __ _ _   _ ___| |_ _   _ _ __  ___| | ____ _
| '_ \| | | |      |    \| |/ _` | | | |/ _` | |/ _` |      |  _  | | | |/ _` | | | / __| __| | | | '_ \/ __| |/ / _` |
| |_) | |_| |      | |\  \ | (_| | |_| | (_| | | (_| |      | | | | |_| | (_| | |_| \__ \ |_| |_| | | | \__ \   < (_| |
|_.__/ \__, |      \_| \_/_|\__,_|\__,_|\__,_|_|\__,_|      \_| |_/\__,_|\__, |\__,_|___/\__|\__, |_| |_|___/_|\_\__,_|
        __/ |                                                             __/ |               __/ |
       |___/                                                             |___/               |___/

*/


#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <cstring>
#include <cctype>

#include "kodowanie.h"
#include "szyfrCezara.h"
#include "rot13.h"
#include "rot47.h"
#include "kodowanieMorsea.h"
#include "alfabetBraillea.h"
#include "szyfrAtBash.h"
#include "szyfrCmentarny.h"
#include "szyfrBacona.h"
#include "szyfrVigenerea.h"

using namespace std;

/*

Kodowanie
Zestaw klas realizujących kodowanie różnymi metodami (np. kodowanie Morse'a, szyfr cezara, itp). Klasa ogólna powinna zawierać metody wirtualne koduj() oraz dekoduj() działające na napisach. Implementacja konkretnych typów kodowania powinna być realizowana przez klasy dziedziczące. Dodatkowym atutem projektu bedzie dostępność bardziej zaawansowanych operacji, np. możliwość zakodowania/odkodowania pliku, itp.

*/

void print_utf(wchar_t s[]);
void get_window_width(int& columns);
void separator(int width, char c = 177);

struct przypadki {
    string m; // mianownik
    string n; // narzędnik
    string msc; // miejscownik
};

int main() {

    // pobieranie danych
    char operacja;
    int szyfr;
    string napis;
    int offset = -1;
    string klucz;

    // obsługa plików
    ifstream plik_in;
    ofstream plik_out;
    int len;
    bool dziala;
    string line, line_out;

    // rozpisanie metod
    const int metody_ilosc = 10;
    przypadki metody[metody_ilosc];
    int i;

    metody[1].m = "szyfr Cezara";
    metody[1].n = "szyfrem Cezara";
    metody[1].msc = "szyfrze Cezara";

    metody[2].m = "szyfr ROT13";
    metody[2].n = "szyfrem ROT13";
    metody[2].msc = "szyfrze ROT13";

    metody[3].m = "szyfr ROT47";
    metody[3].n = "szyfrem ROT47";
    metody[3].msc = "szyfrze ROT47";

    metody[4].m = "kod Morse'a";
    metody[4].n = "kodem Morse'a";
    metody[4].msc = "kodzie Morse'a";

    metody[5].m = "alfabet Braille'a";
    metody[5].n = "alfabetem Braille'a";
    metody[5].msc = "alfabecie Braille'a";

    metody[6].m = "szyfr AtBash";
    metody[6].n = "szyfrem AtBash";
    metody[6].msc = "szyfrze AtBash";

    metody[7].m = "szyfr cmentarny";
    metody[7].n = "szyfrem cmentarnym";
    metody[7].msc = "szyfrze cmentarnym";

    metody[8].m = "szyfr Bacona";
    metody[8].n = "szyfrem Bacona";
    metody[8].msc = "szyfrze Bacona";

    metody[9].m = "szyfr Vigenere'a";
    metody[9].n = "szyfrem Vigenere'a";
    metody[9].msc = "szyfrze Vigenere'a";

    // szerokość okna
    int windowWidth;
    get_window_width(windowWidth);

    // POWITANIE

    cout << "  __ __   ___   ____     ___   __    __  ___  __  __ __  ____" << endl;
    cout << "  || //  // \\\\  || \\\\   // \\\\  ||    || // \\\\ ||\\ || || ||  " << endl;
    cout << "  ||<<  ((   )) ||  )) ((   )) \\\\ /\\ // ||=|| ||\\\\|| || ||== " << endl;
    cout << "  || \\\\  \\\\_//  ||_//   \\\\_//   \\V/\\V/  || || || \\|| || ||___" << endl << endl;


    print_utf(L"Program służy do kodowania oraz dekodowania nastepującymi metodami:");
    for (i = 1; i < metody_ilosc; i++)
        cout << "  - " << metody[i].n << endl;
    cout << endl;


    print_utf(L"Zostaniesz poproszony w 3 krokach o:");
    print_utf(L"  1. Powiedzenie, co chcesz zrobić (zakoduj / dekoduj / opowiedz o danym kodowaniu :D)");
    print_utf(L"  2. Podanie interesującej Cię metody");
    print_utf(L"  3. Wprowadzenie napisu lub ścieżki do pliku, który chcesz przetworzyć");

    separator(windowWidth);


    // KROK 1

    print_utf(L"KROK 1: Co chcesz zrobić?");
    cout << endl;
    cout << "  [Z] Zakoduj" << endl;
    cout << "  [D] Dekoduj" << endl;
    cout << "  [O] Opowiedz o danym kodowaniu!" << endl << endl;

    cout << "  Wybieram: ";
        cin >> operacja;
    operacja = toupper(operacja);

    separator(windowWidth,205);

    // KROK 2

    print_utf(L"KROK 2: Wybierz metodę:");
    cout << endl;
    for (i = 1; i < metody_ilosc; i++)
        cout << "  [" << i << "] - " << metody[i].m << endl;
    cout << endl;

    cout << "  Wybieram: ";
        cin >> szyfr;

    // dodatkowe dane

    switch (szyfr) {
        case 1:
            if (operacja == 'Z' || operacja == 'D') {
                print_utf(L"\n  Skoro wybrałeś szyfr Cezara, to podaj jeszcze jakiego przesunięcia chcesz użyć: \n");
                cout << "  Offset = ";
                cin >> offset;
            }
            break;
        case 9:
            if (operacja == 'Z' || operacja == 'D') {
                print_utf(L"\n  Podaj Tajny Klucz, jakiego chcesz użyć (ciąg liter z zakresu A-Z). Małe litery zostaną potraktowane jako wielkie, a znaki niebędące literami - zignorowane. \n");
                cout << "  Tajny Klucz = ";
                cin >> klucz;
            }
    }

    if (operacja == 'Z' || operacja == 'D') {

        separator(windowWidth,205);

        // KROK 3

        cout << "KROK 3: Podaj tekst do przetworzenia" << endl;
        cout << endl;
        print_utf(L"  - wpisz linijkę tekstu ALBO");
        print_utf(L"  - podaj ścieżkę do pliku *.txt, wówczas zostanie na jego podstawie utworzony plik nazwapliku_out.txt oraz na ekranie zostanie wypisana jego zawartość, tak na pamiątkę");


        // dodatkowe komunikaty
        switch (szyfr) {
            case 1:
            case 2:
            case 6:
                if (operacja == 'Z')
                    print_utf(L"\n  Szyfr koduje znaki A-Z a-z, reszta znaków jest przepisywana.");
                break;
            case 3:
                if (operacja == 'Z')
                    print_utf(L"\n  Szyfr koduje znaki o kodach ASCII z zakresu 33-126, reszta znaków (spacje) jest przepisywana.");
                break;
            case 4:
                if (operacja == 'D')
                    print_utf(L"\n  Program koduje znaki z zakresu A-Z (małe litery zostaną potraktowane jako wielkie), cyfry 0-9 oraz znaki:  +=/()?!@'\":;.,_-  \n\n  Przykład:\n\n  -- --- .-. ... . / -.-. --- -.. .\n\n  M   O   R   S  E /  C    O   D  E\n");
                break;
            case 5:
                if (operacja == 'D')
                    print_utf(L"\n  Program koduje znaki z zakresu A-Z (małe litery zostaną potraktowane jako wielkie), cyfry 0-9 oraz (zgodnie z notacją angielską) znaki: !?:;.,-'\n\n  Proszę użyć następującej notacji:\n\n    123456\n\n    1 4\n    2 5\n    3 6\n\n  Gdzie:\n    - kropka        (.)  oznacza wypukły punkt,\n    - podkreślenie  (_)  oznacza niewypukły punkt,\n    - spacja        ( )  rozdziela kolejne znaki,\n    - ukośnik       (/)  rozdziela kolejne wyrazy.\n\n  Przykład:  .----- ...--- .----- / .-..-- .----- / .-.--- .-.-.- -....- .-----  (ala ma kota)");
                break;
            case 7:
                if (operacja == 'Z')
                    print_utf(L"\n   Szyfrem cmentarnym można kodować jedynie znaki z zakresu A-Z. Litera J jest traktowana jak litera I. Małe litery zostaną potraktowane jako wielkie, a pozostałe znaki (w tym spacje) zostaną pominięte.");
                if (operacja == 'D')
                    print_utf(L"\n  Proszę użyć następującej notacji:\n\n    TRBL12\n\n    LTTTTTR\n    L  1  R\n    L  2  R\n    LBBBBBR\n\n  TRBL - to poszczególne ramki, 1 - obecność pierwszej kropki, 2 - obecność drugiej kropki.\n\n  Proszę zaznaczyć obecność elementu kropką (.), a jego brak myślnikiem (-). Kolejne \"litery\" proszę rozdzielać spacją.\n\nPrzykład:  -..-.- -..... -..-.- --.... -..-.- -..-.. ...... -..--- -..-.-  (alamakota)");
                break;
            case 8:
                if (operacja == 'Z')
                    print_utf(L"\n   Szyfrem Bacona można kodować jedynie znaki z zakresu A-Z. Litera J jest traktowana jak litera I, a litera V jako U. Małe litery zostaną potraktowane jako wielkie, a pozostałe znaki (oprócz spacji) zostaną pominięte.");
                if (operacja == 'D')
                    print_utf(L"\n   Przykład:  aaaaa ababa aaaaa / ababb aaaaa / abaab abbab baaba aaaaa  (ala ma kota)");
                break;
            case 9:
                if (operacja == 'Z')
                    print_utf(L"\n   Szyfrem Vigenère'a można kodować jedynie znaki z zakresu A-Z. Małe litery zostaną potraktowane jako wielkie, a pozostałe znaki zostaną przepisane.");
                break;
        }

        cin.ignore(1000,'\n');
        cout << endl << "Pisz: " << endl;
            getline(cin,napis);

    }

    separator(windowWidth);

    // PODSUMOWANIE TEGO "KREATORA"

    switch (operacja) {
    case 'Z':
        cout << "ZAKODUJ  \"" << napis << "\"  ";
        break;
    case 'D':
        cout << "ZDEKODUJ  \"" << napis << "\"  ";
        break;
    case 'O':
        cout << "OPOWIEDZ O...  ";
        break;
    }

    if (operacja == 'O')
        cout << metody[szyfr].msc;
    else
        cout << metody[szyfr].n;

    if (operacja == 'Z' || operacja == 'D') {
        switch (szyfr) {
            case 1:
                cout << " z przesunieciem rownym  " << offset;
                break;
            case 9:
                cout << " z uzyciem klucza  \"" << klucz << "\"";
                break;
        }
    }


    separator(windowWidth,205);

    // PRZETWARZANIE

    kodowanie* wsk;

    switch (szyfr) {
        case 1:
            wsk = new szyfrCezara(offset);
            break;
        case 2:
            wsk = new rot13();
            break;
        case 3:
            wsk = new rot47();
            break;
        case 4:
            wsk = new kodowanieMorsea();
            break;
        case 5:
            wsk = new alfabetBraillea();
            break;
        case 6:
            wsk = new szyfrAtBash();
            break;
        case 7:
            wsk = new szyfrCmentarny();
            break;
        case 8:
            wsk = new szyfrBacona();
            break;
        case 9:
            wsk = new szyfrVigenerea(klucz);
            break;
    }

    // sprawdź, czy użytkownik zażyczył sobie przetworzyć plik
    dziala = false;
    len = napis.length();
    if (
        (operacja == 'Z' || operacja == 'D') &&
        len >= 5 &&
        napis[len-4] == '.' &&
        napis[len-3] == 't' &&
        napis[len-2] == 'x' &&
        napis[len-1] == 't'
        ) {

            // spraw, żeby funkcja file.open() umiała odczytać string z wejścia jako parametr...
            char napis2[len+20];

            for (i = 0; i < len; i++)
                napis2[i] = napis[i];
            napis2[i] = '\0';

            char* napis3;

            napis3 = (char*) malloc (len+1);

            strcpy (napis3,napis2);


            plik_in.open(napis3, std::ifstream::in);
            if (plik_in.is_open()) {

                dziala = true;

                // spraw, żeby
                char* napis4;
                napis4 = (char*) malloc (len+20);
                napis2[len-4] = '\0';
                strcat(napis2,"_out.txt");
                strcpy(napis4,napis2);

                plik_out.open(napis4);

                cout << "  " << napis4;
                print_utf(L" - podgląd zawartości pliku: ");
                cout << endl;

                while ( plik_in.good() ) {
                    getline (plik_in,line);

                    switch (operacja) {
                        case 'Z':
                            line_out = wsk->encode(line);
                            plik_out << line_out << endl;
                            cout << line_out << endl;
                            break;
                        case 'D':
                            line_out = wsk->decode(line);
                            plik_out << line_out << endl;
                            cout << line_out << endl;
                            break;
                    }
                }

                free(napis4);

                plik_out.close();
                plik_in.close();

            }

            free(napis3);

        }

    if (dziala == false) {

        switch (operacja) {
            case 'Z':
                cout << wsk->encode(napis) << endl;
                break;
            case 'D':
                cout << wsk->decode(napis) << endl;
                break;
            case 'O':
                print_utf(wsk->rasskazywaj());
                break;
        }

    }

    separator(windowWidth);

    system("pause");

    return 0;
}

void print_utf(wchar_t s[]) {
// http://www.codeproject.com/Articles/34068/Unicode-Output-to-the-Windows-Console

    UINT oldcp = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, s, -1, NULL, 0, NULL, NULL);
	char* m = new char[bufferSize];
	WideCharToMultiByte(CP_UTF8, 0, s, -1, m, bufferSize, NULL, NULL);
	wprintf(L"%S\n", m);
	delete m;
    SetConsoleOutputCP(oldcp);

}

void get_window_width(int& columns) {
// http://www.cplusplus.com/forum/windows/2761/
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(
            GetStdHandle( STD_OUTPUT_HANDLE ),
            &csbi
        )
    ) {
        columns = csbi.srWindow.Right  -csbi.srWindow.Left +1;
    } else
        columns = 0;
}

void separator(int width, char c) {
    int i;

    cout << endl;
    for (i = 0; i < width; i++)
        cout << c;
    cout << endl;

}
