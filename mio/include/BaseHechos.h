#ifndef BASEHECHOS_H
#define BASEHECHOS_H
#include "Regla.h"
#include <set>

using namespace std;
struct Hecho
{
    string nombre;
    float fc;
    bool objetivo;
};
class BaseHechos
{
private:
    vector<Hecho> hechos;
    vector<string> objetivos;

public:
    BaseHechos();
    ~BaseHechos();
    void cargaBH(string fichero, ofstream &archivo);
    void addHecho(string nombre, float fc);
    void addObjetivo(string nombre);
    bool contiene(string nombre);
    float getFC(string nombre);
    vector<string> getObjetivos();
    void imprimirBH();
};

#endif // BASEHECHOS_H