#include <iostream>
#include <string>
#include "MotorInferencias.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cerr << "Uso: " << argv[0] << " <base_hechos> <base_conocimiento>\n";
        return 1;
    }
    string bc = argv[1];
    string bh = argv[2];
    if (argc == 4)
    {
        MotorInferencias motor(bc, bh, true);
        motor.encadenamientoHaciaAtras();
    }
    else
    {
        MotorInferencias motor(bc, bh);
        motor.encadenamientoHaciaAtras();
    }

    return 0;
}
