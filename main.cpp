#include <iostream>
#include "Solver.h"
using namespace std;

int main() {

    string expresion;
    cout << "Inserte la ecuacion: ";
    cin >> expresion;

    Solver ecuacion(expresion);
    cout << "Resultado: " << ecuacion.getResult() <<endl;

    return 0;
}