#ifndef KODOWANIE_H
#define KODOWANIE_H

#include <string>
using namespace std;

class kodowanie {
    public:
        kodowanie();
        virtual ~kodowanie();
        virtual string encode(string napis);
        virtual string decode(string napis);
        virtual wchar_t* rasskazywaj();
    protected:
    private:
};

#endif // KODOWANIE_H
