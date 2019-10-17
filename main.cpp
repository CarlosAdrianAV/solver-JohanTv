#include "Solver.h"
#include <cstdlib>

int main() {

    char op;
    Solver ecuacion;
    do{
        string expresion;
        cout << "Inserte la ecuacion: ";
        cin >> expresion;
        ecuacion.setExpresion(expresion);
        cout << "Resultado: " << ecuacion.getResult() <<endl;
        cout<<"Seguir S/N: "; cin>>op;
        system("cls");
    }while(tolower(op) != 'n');


    return 0;
}