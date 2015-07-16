#ifndef SZYFRCEZARA_H
#define SZYFRCEZARA_H

#include <string>

using namespace std;

class szyfrCezara : public kodowanie {
    public:
        szyfrCezara();
        szyfrCezara(int o);
        virtual ~szyfrCezara();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
        int offset;
    protected:
    private:
};

#endif // SZYFRCEZARA_H
