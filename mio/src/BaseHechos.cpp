#include "BaseHechos.h"
#include <iostream>
#include <fstream>
using namespace std;

BaseHechos::BaseHechos()
{
}
BaseHechos::~BaseHechos()
{
}
void BaseHechos::cargaBH(string fichero)
{
    ifstream fuente;
    fuente.open(fichero);
    if (!fuente)
    {
        cerr << "No se pudo abrir el archivo " << fichero << "\n";
        return;
    }
    string linea, nombre;
    float factorCerteza;
    getline(fuente, linea);
    linea.pop_back();
    cout << "Se van a cargar: " << linea << " hechos " << "del fichero: " << fichero << endl;
    while (getline(fuente, linea))
    {
        linea.pop_back();
        if (linea == "Objetivo")
        {
            getline(fuente, linea);
            linea = linea.substr(0, (int)linea.size() - 1);
            this->addObjetivo(linea);
            fuente.close();
            return;
        }
        else
        {
            int posComa = linea.find(",");
            nombre = linea.substr(0, posComa);
            int posFC = linea.find("FC=");
            factorCerteza = stof(linea.substr(posFC + 3, (int)linea.size()));
            this->addHecho(nombre, factorCerteza);
        }
    }
    fuente.close();
}
void BaseHechos::addHecho(string nombre, float fc)
{
    Hecho h;
    h.nombre = nombre;
    h.fc = fc;
    hechos.push_back(h);
}
void BaseHechos::addObjetivo(string nombre)
{
    objetivos.push_back(nombre);
}
bool BaseHechos::contiene(string nombre)
{
    for (int i = 0; i < (int)hechos.size(); i++)
    {
        if (hechos[i].nombre == nombre)
        {
            return true;
        }
    }
    return false;
}
float BaseHechos::getFC(string nombre)
{
    for (int i = 0; i < (int)hechos.size(); i++)
    {
        if (hechos[i].nombre == nombre)
        {
            return hechos[i].fc;
        }
    }
    return -9999;
}
vector<string> BaseHechos::getObjetivos()
{
    vector<string> nombresObjetivos;
    for (int i = 0; i < (int)objetivos.size(); i++)
    {

        nombresObjetivos.push_back(objetivos[i]);
    }
    return nombresObjetivos;
}
void BaseHechos::imprimirBH()
{
    cout << "Base de Hechos:" << endl;
    for (int i = 0; i < (int)hechos.size(); i++)
    {
        cout << hechos[i].nombre << ", FC=" << hechos[i].fc;
        cout << endl;
    }
    cout << "Objetivos:" << endl;
    for (int i = 0; i < (int)objetivos.size(); i++)
    {
        cout << objetivos[i] << endl;
    }
}