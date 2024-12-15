#include "Regla.h"
#include <iostream>

parteBase Regla::parsearParte(string parte)
{
    string literal = "";
    parteBase parteBase;
    parteBase.num_literales = 0;
    for (int i = 0; i < (int)parte.size(); i++)
    {
        if (parte[i] == 'y' || parte[i] == 'o')
        {
            parteBase.operador.push_back(string(1, parte[i]));
        }
        else if (parte[i] == ' ')
        {
            literal = "";
            continue;
        }
        else
        {
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
Regla::Regla(string nombre, string antecedentes, string consecuentes, float factor_certeza)
{
    this->nombre = nombre;
    this->factor_certeza = factor_certeza;
    this->antecedente = parsearParte(antecedentes);
    this->consecuente = parsearParte(consecuentes);
}
Regla::~Regla()
{
}
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

string Regla::getNombre()
{
    return this->nombre;
}
string Regla::getConsecuente()
{
    return this->consecuente.literal[0];
}
vector<string> Regla::getAntecedentes()
{
    vector<string> antecedentes;
    for (int i = 0; i < this->antecedente.num_literales; i++)
    {
        antecedentes.push_back(this->antecedente.literal[i]);
    }
    return antecedentes;
}
parteBase Regla::getAntecedente()
{
    return this->antecedente;
}
float Regla::getFactorCerteza()
{
    return this->factor_certeza;
}
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
