#ifndef BASEHECHOS_H
#define BASEHECHOS_H
#include "Regla.h"
#include <set>

using namespace std;
// Un hecho se compone de un nombre y un factor de certeza
struct Hecho
{
    string nombre;
    float fc;
};
class BaseHechos
{
private:
    // La base de hechos se compone de un conjunto de hechos y un conjunto de objetivos
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