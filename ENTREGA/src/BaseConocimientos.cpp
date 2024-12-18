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
/**
 * @brief Método para cargar la base de conocimientos desde un fichero
 * @param fichero
 * @param archivo
 */
void BaseConocimientos::cargarBC(string fichero, ofstream &archivo)
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
    archivo << "Se van a cargar: " << linea << " reglas del fichero: " << fichero << endl;
    while (getline(fuente, linea))
    {
        // Se obtienen las posiciones de los carácteres que sirven de guía para identificar cada parte
        int posFinNombre = linea.find(":");
        int posAntecedentes = linea.find("Si");
        int posConsecuentes = linea.find("Entonces");
        int posFC = linea.find("FC=");
        // Los antecedentes van desde después del "Si" hasta antes del "Entonces"
        antecedentes = linea.substr(posAntecedentes + 3, posConsecuentes - posAntecedentes - 3);
        // Los consecuentes van desde después del "Entonces" hasta antes del "FC="
        consecuentes = linea.substr(posConsecuentes + 8, posFC - posConsecuentes - 10);
        // El factor de certeza va desde después del "FC=" hasta el final de la línea
        factorCerteza = stof(linea.substr(posFC + 3, (int)linea.size() - posFC - 3));
        // El nombre de la regla va desde el principio de la línea hasta ":"
        nombre = linea.substr(0, posFinNombre);
        r = Regla(nombre, antecedentes, consecuentes, factorCerteza);
        reglas.push_back(r);
        this->numReglas++;
    }
    fuente.close();
}
/**
 * @brief Método para añadir una regla a la base de conocimientos
 * @param r La regla a añadir
 */
void BaseConocimientos::addRegla(Regla r)
{
    this->reglas.push_back(r);
    this->numReglas++;
}
/**
 * @brief Método para imprimir la base de conocimientos (para propósitos de debug)
 */
void BaseConocimientos::imprimirBC()
{
    cout << "Base de conocimientos:" << endl;
    for (int i = 0; i < this->numReglas; i++)
    {
        this->reglas[i].imprimir();
    }
}
/**
 * @brief Método para equiparar un objetivo con las reglas de la base de conocimientos
 * @param objetivo El objetivo a equiparar
 * @return vector<Regla> El conjunto de reglas que tienen al objetivo como consecuente
 */
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