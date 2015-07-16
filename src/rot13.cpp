#include "kodowanie.h"
#include "rot13.h"

rot13::rot13()
{
    offset = 13;
}

rot13::~rot13()
{
    //dtor
}

wchar_t* rot13::rasskazywaj( ) {

    return L"ROT13 - prosty szyfr przesuwający, którego działanie polega na zamianie każdego znaku alfabetu łacińskiego na znak występujący 13 pozycji po nim, przy czym wielkość liter nie ma przy przekształcaniu znaczenia. ROT13 jest przykładem szyfru cezara, opracowanego w Starożytnym Rzymie.\n\n(wikipedia)";

}
