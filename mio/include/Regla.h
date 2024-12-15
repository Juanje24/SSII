#ifndef REGLA_H
#define REGLA_H

#include <string>
#include <vector>

using namespace std;

struct parteBase
{
    vector<string> literal;
    vector<string> operador;
    int num_literales;
};
class Regla
{

private:
    string nombre;
    parteBase antecedente;
    parteBase consecuente;
    float factor_certeza;
    parteBase parsearParte(string parte);
    string toString(parteBase parte);

public:
    Regla();
    Regla(string nombre, string antecedentes, string consecuentes, float factor_certeza);
    ~Regla();
    void imprimir();
    string getNombre();
    string getConsecuente();
    vector<string> getAntecedentes();
    parteBase getAntecedente();
    float getFactorCerteza();
    string reglaToString();
};
;

#endif // REGLA_H
