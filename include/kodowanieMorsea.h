#ifndef KODOWANIEMORSEA_H
#define KODOWANIEMORSEA_H

#include <string>
#include <cctype>
#include <stack>

using namespace std;

class kodowanieMorsea : public kodowanie {
    public:
        kodowanieMorsea();
        virtual ~kodowanieMorsea();
        string encode(string napis);
        string decode(string napis);
        wchar_t* rasskazywaj();
        string kropkiKreskiItd;
    protected:
    private:
};

#endif // KODOWANIEMORSEA_H
