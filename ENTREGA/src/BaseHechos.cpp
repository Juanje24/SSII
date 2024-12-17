#include "BaseHechos.h"
#include <iostream>
#include <fstream>
using namespace std;
// Método auxiliar para limpiar los saltos de línea y espacios al final de una cadena
string limpiar_final(string cadena)
{
    while (cadena[cadena.size() - 1] == '\n' || cadena[cadena.size() - 1] == '\r' || cadena[cadena.size() - 1] == ' ')
    {
        cadena.pop_back();
    }
    return cadena;
}

BaseHechos::BaseHechos()
{
}
BaseHechos::~BaseHechos()
{
}
/**
 * @brief Método que carga la base de hechos desde un fichero
 * @param fichero El fichero desde el que se va a cargar la base de hechos
 * @param archivo El archivo de salida
 */
void BaseHechos::cargaBH(string fichero, ofstream &archivo)
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
    archivo << "Se van a cargar: " << linea << " hechos " << "del fichero: " << fichero << endl;
    while (getline(fuente, linea))
    {
        linea.pop_back(); // elimina el salto de línea para poder comparar
        if (linea == "Objetivo" || linea == "objetivo")
        {
            getline(fuente, linea);
            linea = limpiar_final(linea);
            this->addObjetivo(linea); // añade el objetivo a la base de hechos
            while (getline(fuente, linea))
            {
                linea = limpiar_final(linea);
                this->addObjetivo(linea); // añade el objetivo a la base de hechos
            }
            fuente.close();
            return;
        }
        else
        {
            // se obtiene el nombre y el factor de certeza del hecho, y se añade a la base de hechos
            int posComa = linea.find(",");
            nombre = linea.substr(0, posComa);
            int posFC = linea.find("FC=");
            factorCerteza = stof(linea.substr(posFC + 3, (int)linea.size()));
            this->addHecho(nombre, factorCerteza);
        }
    }
    fuente.close();
}
/**
 * @brief Método para añadir un hecho a la base de hechos
 * @param nombre El nombre del hecho
 * @param fc El factor de certeza del hecho
 */
void BaseHechos::addHecho(string nombre, float fc)
{
    Hecho h;
    h.nombre = nombre;
    h.fc = fc;
    hechos.push_back(h);
}
/**
 * @brief Método para añadir un objetivo a la base de hechos
 * @param nombre El nombre del objetivo
 */
void BaseHechos::addObjetivo(string nombre)
{
    objetivos.push_back(nombre);
}
/**
 * @brief Método para comprobar si un hecho está en la base de hechos
 * @param nombre El nombre del hecho
 * @return bool True si el hecho está en la base de hechos, false en caso contrario
 */
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
/**
 * @brief Método para obtener el factor de certeza de un hecho
 * @param nombre El nombre del hecho
 * @return float El factor de certeza del hecho
 */
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
/**
 * @brief Método para obtener los objetivos de la base de hechos
 * @return vector<string> Los objetivos de la base de hechos
 */
vector<string> BaseHechos::getObjetivos()
{
    vector<string> nombresObjetivos;
    for (int i = 0; i < (int)objetivos.size(); i++)
    {

        nombresObjetivos.push_back(objetivos[i]);
    }
    return nombresObjetivos;
}
/**
 * @brief Método para imprimir la base de hechos (para propósitos de debug)
 */
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
        cout << "/" << objetivos[i] << "/" << endl;
    }
}