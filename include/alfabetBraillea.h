#ifndef ALFABETBRAILLEA_H
#define ALFABETBRAILLEA_H

#include <string>
#include <cctype>
#include <stack>

using namespace std;

struct litera {
    string kod;
    char nazwa;
};

class alfabetBraillea : public kodowanie {
    public:
        alfabetBraillea();
        virtual ~alfabetBraillea();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
        string alfabet;
        const int suma = 63;
    protected:
    private:
};

#endif // ALFABETBRAILLEA_H
