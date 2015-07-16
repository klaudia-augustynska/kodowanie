#include "kodowanie.h"
#include "rot47.h"

rot47::rot47()
{
    //ctor
}

rot47::~rot47()
{
    //dtor
}


string rot47::encode(string napis) {

    string output;
    int len = napis.length();
    int i;
    int wynik, x1, x2;
    const int offset = 47;

    for (i = 0; i < len; i++) {

        wynik = napis[i];

        if (napis[i] >= 33) {
            wynik = napis[i] + offset;
            if (wynik > 126)
                wynik = wynik - 94;
        }

        output.push_back( wynik );
    }

    return output;
}

string rot47::decode(string napis) {

    string output;
    int len = napis.length();
    int i;
    int wynik, x1, x2;
    const int offset = 47;

    for (i = 0; i < len; i++) {

        wynik = napis[i];

        if (napis[i] >= 33) {
            wynik = napis[i] - offset;
            if (wynik < 33)
                wynik = wynik + 94;
        }

        output.push_back( wynik );
    }


    return output;
}

wchar_t* rot47::rasskazywaj( ) {

    return L"ROT47 to szyfr przesuwający, (właściwie kodowanie), zamieniający każdy znak ASCII z przedziału 33-126 na znak znajdujący się 47 pozycji dalej, ale nie dalej niż do 126 pozycji.  \n\n(wikipedia)";

}
