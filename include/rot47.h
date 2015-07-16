#ifndef ROT47_H
#define ROT47_H

#include <string>
#include "kodowanie.h"

using namespace std;

class rot47 : public kodowanie {
    public:
        rot47();
        virtual ~rot47();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
    protected:
    private:
};

#endif // ROT47_H
