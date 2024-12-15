#include "MotorInferencias.h"
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
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
    archivo->close();
    delete archivo;
}
MotorInferencias::MotorInferencias(string baseConocimiento, string baseHecho)
{
    int posFinnombreBC = baseConocimiento.find_last_of(".");
    int posFinnombreBH = baseHecho.find_last_of(".");
    int posInicioNombreBC = baseConocimiento.find_last_of("B") + 1;
    int posInicioNombreBH = baseHecho.find_last_of("B") + 1;
    string nombreBC = baseConocimiento.substr(posInicioNombreBC - 1, posFinnombreBC - posInicioNombreBC + 1);
    string nombreBH = baseHecho.substr(posInicioNombreBH - 1, posFinnombreBH - posInicioNombreBH + 1);
    string nombre = "..\\output\\" + nombreBC + "_" + nombreBH + ".txt";
    archivo = new ofstream(nombre);
    BC.cargarBC(baseConocimiento, *archivo);
    BH.cargaBH(baseHecho, *archivo);
}
MotorInferencias::MotorInferencias(string baseConocimiento, string baseHecho, bool debug)
{
    int posFinnombreBC = baseConocimiento.find_last_of(".");
    int posFinnombreBH = baseHecho.find_last_of(".");
    int posInicioNombreBC = baseConocimiento.find_last_of("B") + 1;
    int posInicioNombreBH = baseHecho.find_last_of("B") + 1;
    string nombreBC = baseConocimiento.substr(posInicioNombreBC - 1, posFinnombreBC - posInicioNombreBC + 1);
    string nombreBH = baseHecho.substr(posInicioNombreBH - 1, posFinnombreBH - posInicioNombreBH + 1);
    string nombre = "..\\output\\" + nombreBC + "_" + nombreBH + ".txt";
    archivo = new ofstream(nombre);
    BC.cargarBC(baseConocimiento, *archivo);
    BH.cargaBH(baseHecho, *archivo);
    if (debug)
    {
        BC.imprimirBC();
        BH.imprimirBH();
    }
}

void MotorInferencias::encadenamientoHaciaAtras()
{

    vector<string> objetivos = BH.getObjetivos();
    cout << "Se van a verificar " << objetivos.size() << " objetivos." << endl;
    for (int i = 0; i < (int)objetivos.size(); i++)
    {
        *archivo << "Objetivo: " << objetivos[i] << endl;
        float fc = verificarFC(objetivos[i], 0);
        if (fc >= -1 && fc <= 1)
        {
            *archivo << "La meta " << objetivos[i] << " es cierta con FC = " << fc << endl;
            cout << "Resultado guardado en " << "..\\output\\" << endl;
            cout << "La meta " << objetivos[i] << " es cierta con FC = " << fc << endl;
        }
        else
        {
            *archivo << "Se ha producido algún error procesando el objetivo " << objetivos[i] << endl;
        }
    }
}
float MotorInferencias::verificarFC(string objetivo, int nivel)
{
    *archivo << espacios(nivel) << "Verificando " << objetivo << endl;
    if (BH.contiene(objetivo))
    {
        *archivo << espacios(nivel) << "El FC de " << objetivo << " es " << BH.getFC(objetivo) << endl;
        return BH.getFC(objetivo);
    }
    else
    {
        vector<Regla> conjuntoConflicto = BC.equiparar(objetivo);
        vector<float> factoresCerteza;
        if (conjuntoConflicto.empty())
        {
            *archivo << "El objetivo " << objetivo << " no tiene ninguna regla con antecedentes. " << endl;
            BH.addHecho(objetivo, 0);
            return 0;
        }
        for (int i = 0; i < (int)conjuntoConflicto.size(); i++)
        {
            // R=Resolver(CC);
            Regla regla = conjuntoConflicto[i];
            parteBase antecedentes = regla.getAntecedente();
            float actualFC = verificarFC(antecedentes.literal[0], nivel + 1);

            for (int i = 0; i < antecedentes.num_literales - 1; i++)
            {
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
                    *archivo << "Error, operador incorrecto: " << antecedentes.operador[i] << endl;
                }
            }
            // max(actualFC, 0); // caso 3
            if (actualFC <= 0)
            {
                actualFC = 0;
            }
            *archivo << espacios(nivel + 1) << "El FC calculado aplicando el caso 3 para la regla " << regla.reglaToString() << ", es " << actualFC * regla.getFactorCerteza() << endl;
            factoresCerteza.push_back(actualFC * regla.getFactorCerteza());
        }
        for (int i = 0; i < (int)factoresCerteza.size() - 1; i++)
        {
            *archivo << espacios(nivel + 2) << "Aplicando el caso 2 a las reglas " << conjuntoConflicto[i].getNombre() << " y " << conjuntoConflicto[i + 1].getNombre();
            if (factoresCerteza[i] == -0)
            {
                factoresCerteza[i] = 0;
            }
            if (factoresCerteza[i + 1] == -0)
            {
                factoresCerteza[i + 1] = 0;
            }
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
            *archivo << " FC=" << factoresCerteza[i + 1] << endl;
        }
        BH.addHecho(objetivo, factoresCerteza.back());
        *archivo << espacios(nivel + 1) << "El FC calculado para " << objetivo << " es " << factoresCerteza.back() << endl;
        return factoresCerteza.back();
    }
}
