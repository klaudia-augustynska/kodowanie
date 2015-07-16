#ifndef SZYFRBACONA_H
#define SZYFRBACONA_H

#include <string>
#include <cctype>
#include <stack>

using namespace std;

class szyfrBacona: public kodowanie {
    public:
        szyfrBacona();
        virtual ~szyfrBacona();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
        string alfabet;
        const int suma = 31;
    protected:
    private:
};

#endif // SZYFRBACONA_H
