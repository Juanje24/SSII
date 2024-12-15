#include "Regla.h"
#include <iostream>
/**
 * @brief Parsea una parte de la regla de string a parteBase
 * @param parte La parte de la regla a parsear en formato string
 * @return parteBase La parte de la regla parseada al tipo parteBase
 */
parteBase Regla::parsearParte(string parte)
{
    string literal = "";
    parteBase parteBase;
    parteBase.num_literales = 0;
    for (int i = 0; i < (int)parte.size(); i++)
    {
        // reconocimiento de literales y operadores
        if (parte[i] == 'y' || parte[i] == 'o')
        {
            parteBase.operador.push_back(string(1, parte[i]));
        }
        else if (parte[i] == ' ')
        {
            // en caso de que haya espacios entre literales sabemos que hemos cambiado de literal
            literal = "";
            continue;
        }
        else
        {
            // se lee el literal hasta un espacio o el final de la cadena
            while (parte[i] != ' ' && i < (int)parte.size())
            {
                literal += parte[i];
                i++;
            }
            i--;
            parteBase.literal.push_back(literal);
            parteBase.num_literales++;
        }
    }
    return parteBase;
}

/**
 * @brief Convierte una parteBase a string
 * @param parte La parte de la regla a convertir a string
 * @return string La parte de la regla convertida a string
 */
string Regla::toString(parteBase parte)
{
    string cadena = "";
    for (int i = 0; i < parte.num_literales; i++)
    {
        cadena += parte.literal[i];
        if (i < parte.num_literales - 1)
        {
            cadena += " " + parte.operador[i] + " ";
        }
    }
    return cadena;
}
Regla::Regla()
{
}
/**
 * @brief Constructor de la clase Regla
 * @param nombre El nombre de la regla
 * @param antecedentes Los antecedentes de la regla en formato string
 * @param consecuentes Los consecuentes de la regla en formato string
 * @param factor_certeza El factor de certeza de la regla
 */
Regla::Regla(string nombre, string antecedentes, string consecuentes, float factor_certeza)
{
    this->nombre = nombre;
    this->factor_certeza = factor_certeza;
    // se parsean las partes de la regla
    this->antecedente = parsearParte(antecedentes);
    this->consecuente = parsearParte(consecuentes);
}
Regla::~Regla()
{
}

/**
 * @brief Imprime la regla (para propósitos de debug)
 */
void Regla::imprimir()
{
    cout << nombre << ": ";
    cout << "Si ";
    for (int i = 0; i < antecedente.num_literales; i++)
    {
        cout << antecedente.literal[i];
        if (i < antecedente.num_literales - 1)
        {
            cout << " " << antecedente.operador[i] << " ";
        }
    }
    cout << ", Entonces ";
    for (int i = 0; i < consecuente.num_literales; i++)
    {
        cout << consecuente.literal[i] << " ";
        if (i < consecuente.num_literales - 1)
        {
            cout << " " << consecuente.operador[i] << " ";
        }
    }
    cout << " con FC= " << to_string(factor_certeza).substr(0, to_string(factor_certeza).find(".") + 4) << endl;
}
/**
 * @brief Obtiene el nombre de la regla
 * @return string El nombre de la regla
 */
string Regla::getNombre()
{
    return this->nombre;
}
/**
 * @brief Obtiene el consecuente de la regla (solo el primer literal)
 * @return string El consecuente de la regla
 */
string Regla::getConsecuente()
{
    return this->consecuente.literal[0];
}
/**
 * @brief Obtiene los antecedentes de la regla en un vector de strings
 * @return vector<string> Los antecedentes de la regla
 */
vector<string> Regla::getAntecedentes()
{
    vector<string> antecedentes;
    for (int i = 0; i < this->antecedente.num_literales; i++)
    {
        antecedentes.push_back(this->antecedente.literal[i]);
    }
    return antecedentes;
}
/**
 * @brief Obtiene los antecedentes de la regla en formato parteBase
 * @return parteBase Los antecedentes de la regla
 */
parteBase Regla::getAntecedente()
{
    return this->antecedente;
}
/**
 * @brief Obtiene el factor de certeza de la regla
 * @return float El factor de certeza de la regla
 */
float Regla::getFactorCerteza()
{
    return this->factor_certeza;
}
/**
 * @brief Convierte la regla a string
 * @return string La regla convertida a string
 */
string Regla::reglaToString()
{
    string cadena = "";
    cadena += nombre + ": ";
    cadena += "Si ";
    cadena += toString(antecedente);
    cadena += ", Entonces ";
    cadena += toString(consecuente);
    cadena += " Con FC= " + to_string(factor_certeza).substr(0, to_string(factor_certeza).find(".") + 4);
    return cadena;
}
