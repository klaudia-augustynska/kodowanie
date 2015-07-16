#ifndef SZYFRVIGENEREA_H
#define SZYFRVIGENEREA_H

#include <string>
#include <iostream>

using namespace std;

class szyfrVigenerea : public kodowanie {
    public:
        szyfrVigenerea();
        szyfrVigenerea(string klucz);
        virtual ~szyfrVigenerea();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
        string alfabet;
        string tajnyklucz;
    protected:
    private:
};

#endif // SZYFRVIGENEREA_H
