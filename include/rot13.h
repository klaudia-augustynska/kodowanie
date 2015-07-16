#ifndef ROT13_H
#define ROT13_H

#include <string>
#include "szyfrCezara.h"

using namespace std;

class rot13 : public szyfrCezara {
    public:
        rot13();
        virtual ~rot13();
        wchar_t* rasskazywaj();
        int offset;
    protected:
    private:
};

#endif // ROT13_H
