#include <iostream>
#include "metodos.h"
using namespace std;

int main(){
    double a;
    int n;
    double margem_de_erro;
    double d0;
    cout << "Digite o valor da amplitude (a): \n";
    cin >> a;
    cout << "Digite o numero de iterações: \n";
    cin >> n;
    cout << "Digite a margem de erro: \n";
    cin >> margem_de_erro;
    cout << "Digite o chute inicial (d0): \n";
    cin >> d0;
    cout << a << " " << n << " " << margem_de_erro << " " << d0 << "\n";
    double d_newton_modificado = newton_modificado(n, a, margem_de_erro, d0);
    cout << "d_newton_modificado: " << d_newton_modificado << "\n";
}
