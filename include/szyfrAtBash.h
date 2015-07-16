#ifndef SZYFRATBASH_H
#define SZYFRATBASH_H

#include <string>

using namespace std;

class szyfrAtBash : public kodowanie {
    public:
        szyfrAtBash();
        virtual ~szyfrAtBash();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
    protected:
    private:
};

#endif // SZYFRATBASH_H
