#ifndef MOTORINFERENCIAS_H
#define MOTORINFERENCIAS_H
#include "BaseConocimientos.h"
#include "BaseHechos.h"
using namespace std;

class MotorInferencias
{
private:
    BaseConocimientos BC;
    BaseHechos BH;
    vector<string> metas;
    float verificarFC(string objetivo, int nivel);

public:
    MotorInferencias();
    MotorInferencias(string baseConocimiento, string baseHecho);
    MotorInferencias(string baseConocimiento, string baseHecho, bool debug);
    ~MotorInferencias();
    void encadenamientoHaciaAtras();
};

#endif // MOTORINFERENCIAS_H