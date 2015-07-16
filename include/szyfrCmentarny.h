#ifndef SZYFRCMENTARNY_H
#define SZYFRCMENTARNY_H

#include <string>
#include <cctype>

using namespace std;

class szyfrCmentarny : public kodowanie {
    public:
        szyfrCmentarny();
        virtual ~szyfrCmentarny();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
        string cmentarz;
        const int suma = 63;
    protected:
    private:
};

#endif // SZYFRCMENTARNY_H
