#ifndef BASECONOCIMIENTOS_H
#define BASECONOCIMIENTOS_H

#include "Regla.h"

using namespace std;

class BaseConocimientos
{
private:
    int numReglas = 0;
    vector<Regla> reglas;

public:
    BaseConocimientos();
    ~BaseConocimientos();
    void cargarBC(string fichero, ofstream &archivo);
    void addRegla(Regla r);
    void imprimirBC();
    vector<Regla> equiparar(string objetivo);
};

#endif // BASECONOCIMIENTOS_H
