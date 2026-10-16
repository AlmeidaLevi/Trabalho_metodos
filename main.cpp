#include <iostream>
#include "metodos.h"
using namespace std;

int main(){
    double a;
    int n;
    double margem_de_erro;
    double d0;
    cout << "Digite o numero de a's: \n";
    cin >> n;
    cout << "Digite a margem de erro: \n";
    cin >> margem_de_erro;
    cout << "Digite o chute inicial (d0): \n";
    cin >> d0;
    for(int i = 0; i<n; i++){
        cout << "Digite o valor da amplitude (a): \n";
        cin >> a;
        double d_newton_modificado = newton_modificado(a, margem_de_erro, d0);
        cout << "d_newton_modificado: " << d_newton_modificado << "\n\n";
        double d_newton_raphson = newton_raphson(a, d0, margem_de_erro);
        cout << "d_newton_raphson: " << d_newton_raphson << "\n\n";
    }
}
