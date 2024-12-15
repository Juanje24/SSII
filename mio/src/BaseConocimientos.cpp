#include "BaseConocimientos.h"
#include <iostream>
#include <fstream>
#include <string>

BaseConocimientos::BaseConocimientos()
{
}
BaseConocimientos::~BaseConocimientos()
{
}
void BaseConocimientos::cargarBC(string fichero)
{
    ifstream fuente;
    fuente.open(fichero);
    if (!fuente)
    {
        cerr << "No se pudo abrir el archivo " << fichero << "\n";
        return;
    }
    string linea, nombre, antecedentes, consecuentes;
    float factorCerteza;
    Regla r;
    getline(fuente, linea);
    linea.pop_back();
    cout << "Se van a cargar: " << linea << " reglas del fichero: " << fichero << endl;
    while (getline(fuente, linea))
    {
        linea.pop_back();
        int posFinNombre = linea.find(":");
        int posAntecedentes = linea.find("Si");
        int posConsecuentes = linea.find("Entonces");
        int posFC = linea.find("FC=");
        antecedentes = linea.substr(posAntecedentes + 3, posConsecuentes - posAntecedentes - 3);
        consecuentes = linea.substr(posConsecuentes + 8, posFC - posConsecuentes - 10);
        factorCerteza = stof(linea.substr(posFC + 3, (int)linea.size()));
        nombre = linea.substr(0, posFinNombre);
        r = Regla(nombre, antecedentes, consecuentes, factorCerteza);
        reglas.push_back(r);
        this->numReglas++;
    }
    fuente.close();
}
void BaseConocimientos::addRegla(Regla r)
{
    this->reglas.push_back(r);
    this->numReglas++;
}
void BaseConocimientos::imprimirBC()
{
    cout << "Base de conocimientos:" << endl;
    for (int i = 0; i < this->numReglas; i++)
    {
        this->reglas[i].imprimir();
    }
}
vector<Regla> BaseConocimientos::equiparar(string objetivo)
{
    vector<Regla> conjuntoConflicto;
    for (int i = 0; i < this->numReglas; i++)
    {
        if (this->reglas[i].getConsecuente() == objetivo)
        {
            conjuntoConflicto.push_back(this->reglas[i]);
        }
    }
    return conjuntoConflicto;
}