#ifndef BASECONOCIMIENTOS_H
#define BASECONOCIMIENTOS_H

#include "Regla.h"

using namespace std;

class BaseConocimientos
{
private:
    // La base de conocimientos se compone de un conjunto de reglas
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
