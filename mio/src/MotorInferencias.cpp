#include "MotorInferencias.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
// Método auxiliar para añadir espacios según la profundidad
string espacios(int nivel)
{
    string s = "";
    for (int i = 0; i < nivel; i++)
    {
        s += "  ";
    }
    return s;
}
MotorInferencias::MotorInferencias()
{
}
MotorInferencias::~MotorInferencias()
{
    delete archivo;
}
/**
 * @brief Constructor de la clase MotorInferencias
 * @param baseConocimiento
 * @param baseHecho
 */
MotorInferencias::MotorInferencias(string baseConocimiento, string baseHecho)
{
    // Se extrae el nombre de los archivos para crear el archivo de salida
    int posFinnombreBC = baseConocimiento.find_last_of(".");
    int posFinnombreBH = baseHecho.find_last_of(".");
    int posInicioNombreBC = baseConocimiento.find_last_of("B") + 1;
    int posInicioNombreBH = baseHecho.find_last_of("B") + 1;
    string nombreBC = baseConocimiento.substr(posInicioNombreBC - 1, posFinnombreBC - posInicioNombreBC + 1);
    string nombreBH = baseHecho.substr(posInicioNombreBH - 1, posFinnombreBH - posInicioNombreBH + 1);
    nombreSalida = nombreBC + "_" + nombreBH + ".txt";
    archivo = new ofstream(nombreSalida);
    BC.cargarBC(baseConocimiento, *archivo);
    BH.cargaBH(baseHecho, *archivo);
}
/**
 * @brief Constructor de la clase MotorInferencias con debug
 * @param baseConocimiento
 * @param baseHecho
 * @param debug
 */
MotorInferencias::MotorInferencias(string baseConocimiento, string baseHecho, bool debug)
{
    // Se extrae el nombre de los archivos para crear el archivo de salida
    int posFinnombreBC = baseConocimiento.find_last_of(".");
    int posFinnombreBH = baseHecho.find_last_of(".");
    int posInicioNombreBC = baseConocimiento.find_last_of("B") + 1;
    int posInicioNombreBH = baseHecho.find_last_of("B") + 1;
    string nombreBC = baseConocimiento.substr(posInicioNombreBC - 1, posFinnombreBC - posInicioNombreBC + 1);
    string nombreBH = baseHecho.substr(posInicioNombreBH - 1, posFinnombreBH - posInicioNombreBH + 1);
    nombreSalida = nombreBC + "_" + nombreBH + ".txt";
    archivo = new ofstream(nombreSalida);
    BC.cargarBC(baseConocimiento, *archivo);
    BH.cargaBH(baseHecho, *archivo);
    this->debug = debug;
    if (debug)
    {
        BC.imprimirBC();
        BH.imprimirBH();
    }
}
/**
 * @brief Método que realiza el encadenamiento hacia atrás, se basa en verificarFC
 */
void MotorInferencias::encadenamientoHaciaAtras()
{
    // Podría haber más de un objetivo
    vector<string> objetivos = BH.getObjetivos();
    for (int i = 0; i < (int)objetivos.size(); i++)
    {
        *archivo << "Objetivo: " << objetivos[i] << endl;
        // Llamada a verificarFC
        float fc = verificarFC(objetivos[i], 0);
        // Se comprueba si el FC es correcto
        if (fc >= -1 && fc <= 1)
        {
            *archivo << "La meta " << objetivos[i] << " es cierta con FC = " << fc << endl;
            cout << "Resultado guardado en: " << nombreSalida << endl;
            if (debug)
            {
                cout << "La meta " << objetivos[i] << " es cierta con FC = " << fc << endl;
            }
        }
        else
        {
            *archivo << "Se ha producido algún error procesando el objetivo " << objetivos[i] << endl;
        }
    }
}
/**
 * @brief Método que verifica el factor de certeza de un objetivo recursivamente
 * @param objetivo El objetivo a verificar
 * @param nivel La profundidad de la función (para imprimir espacios)
 * @return float
 */
float MotorInferencias::verificarFC(string objetivo, int nivel)
{
    *archivo << espacios(nivel) << "Verificando " << objetivo << endl;
    // Si el objetivo ya está en BH se devuelve su FC
    if (BH.contiene(objetivo))
    {
        *archivo << espacios(nivel) << "El FC de " << objetivo << " es " << BH.getFC(objetivo) << endl;
        return BH.getFC(objetivo);
    }
    else
    {
        // Se busca el conjunto de reglas que tienen el objetivo en el consecuente
        vector<Regla> conjuntoConflicto = BC.equiparar(objetivo);
        vector<float> factoresCerteza;
        if (conjuntoConflicto.empty())
        {
            // Si no hay reglas con el objetivo en el consecuente, se añade a BH con FC 0
            *archivo << "El objetivo " << objetivo << " no tiene ninguna regla con antecedentes. " << endl;
            BH.addHecho(objetivo, 0);
            return 0;
        }
        // Se recorren las reglas del conjunto de conflicto
        for (int i = 0; i < (int)conjuntoConflicto.size(); i++)
        {

            Regla regla = conjuntoConflicto[i];
            parteBase antecedentes = regla.getAntecedente();
            // Se calcula el FC de los antecedentes
            float actualFC = verificarFC(antecedentes.literal[0], nivel + 1);

            for (int i = 0; i < antecedentes.num_literales - 1; i++)
            {
                // Para cada 2 antecedentes se calcula el FC en base al caso 1
                string operador = antecedentes.operador[i];
                string literal1 = antecedentes.literal[i];
                string literal2 = antecedentes.literal[i + 1];
                if (operador == "o")
                {
                    actualFC = max(actualFC, verificarFC(literal2, nivel + 1));
                    *archivo << espacios(nivel + 2) << "Aplicando el caso 1 a " << literal1 << " o " << literal2 << " FC=" << actualFC << endl;
                }
                else if (operador == "y")
                {
                    actualFC = min(actualFC, verificarFC(literal2, nivel + 1));
                    *archivo << espacios(nivel + 2) << "Aplicando el caso 1 a " << literal1 << " y " << literal2 << " FC=" << actualFC << endl;
                }
                else
                {
                    cerr << "Error, operador incorrecto: " << antecedentes.operador[i] << endl;
                }
            }
            // max(actualFC, 0); Parte del caso 3 del máximo entre el FC calculado y 0
            if (actualFC <= 0)
            {
                actualFC = 0;
            }
            // Segunda parte del caso 3
            *archivo << espacios(nivel + 1) << "El FC calculado aplicando el caso 3 para la regla " << regla.reglaToString() << ", es " << actualFC * regla.getFactorCerteza() << endl;
            factoresCerteza.push_back(actualFC * regla.getFactorCerteza());
        }
        // Una vez se tiene el FC de cada regla del CC, se aplica el caso 2 a pares
        for (int i = 0; i < (int)factoresCerteza.size() - 1; i++)
        {
            *archivo << espacios(nivel + 2) << "Aplicando el caso 2 a las reglas " << conjuntoConflicto[i].getNombre() << " y " << conjuntoConflicto[i + 1].getNombre();
            if (factoresCerteza[i] >= 0 && factoresCerteza[i + 1] >= 0)
            {
                factoresCerteza[i + 1] = factoresCerteza[i] + factoresCerteza[i + 1] * (1 - factoresCerteza[i]);
            }
            else if (factoresCerteza[i] <= 0 && factoresCerteza[i + 1] <= 0)
            {
                factoresCerteza[i + 1] = factoresCerteza[i] + factoresCerteza[i + 1] * (1 + factoresCerteza[i]);
            }
            else
            {
                factoresCerteza[i + 1] = (factoresCerteza[i] + factoresCerteza[i + 1]) / (1 - min(abs(factoresCerteza[i]), abs(factoresCerteza[i + 1])));
            }
            *archivo << ", FC=" << factoresCerteza[i + 1] << endl;
        }
        // Se añade el objetivo a BH con el FC calculado y se devuelve
        BH.addHecho(objetivo, factoresCerteza.back());
        *archivo << espacios(nivel + 1) << "El FC calculado para " << objetivo << " es " << factoresCerteza.back() << endl;
        return factoresCerteza.back();
    }
}
