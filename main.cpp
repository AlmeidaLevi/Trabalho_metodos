#include <iostream>
#include <iomanip>
#include "metodos.h"
using namespace std;

int main(){
    double a;
    int n;
    double margem_de_erro;
    double d0;
    double d1;
    cout << "Digite o numero de a's: \n";
    cin >> n;
    cout << "Digite a margem de erro: \n";
    cin >> margem_de_erro;

    double all_a[n];
    double all_newton_modificado[n];
    double all_newton_raphson[n];
    double all_secante[n];

    for(int i = 0; i<n; i++){
        cout << "Digite o valor da amplitude (a): \n";
        cin >> a;
        all_a[i] = a;

        cout << "Digite o chute inicial (d0): \n";
        cin >> d0;
        cout << "Digite o segundo chute inicial (d1): \n";
        cin >> d1;

        cout << "Newton Modificado: \n\n";
        double d_newton_modificado = newton_modificado(a, margem_de_erro, d0);
        all_newton_modificado[i] = d_newton_modificado;

        cout << "d_newton_modificado: " << d_newton_modificado << "\n\n\n";
        cout << "###########################################################\n\n\n";

        cout << "Newton Raphson: \n\n";
        double d_newton_raphson = newton_raphson(a, d0, margem_de_erro);
        all_newton_raphson[i] = d_newton_raphson;

        cout << "d_newton_raphson: " << d_newton_raphson << "\n\n\n";
        cout << "###########################################################\n\n\n";

        cout << "Secante: \n\n";
        double d_secante = secante(a, margem_de_erro, d0, d1);
        all_secante[i] = d_secante;
        cout << "d_secante: " << d_secante << "\n\n\n";
    }

    cout << setw(2) << left << "a" << " | "
         << setw(20) << left << "d_newton_modificado" << " | "
         << setw(20) << left << "d_newton_raphson" << " | "
         << setw(20) << left << "d_secante" << " | "
         << setw(5) << left << "Problema gigantesco?" << endl;

    string problema_gigantesco;
    for(int i = 0; i<n; i++){
        if(all_newton_raphson[i] > 0.7){
            problema_gigantesco = "Sim";
        }else{
            problema_gigantesco = "Não";
        }

        cout << setw(2) << left << all_a[i] << " | "
             << setw(20) << left << all_newton_modificado[i] << " | "
             << setw(20) << left << all_newton_raphson[i] << " | "
             << setw(20) << left << all_secante[i] << " | "
             << setw(5) << left << problema_gigantesco << endl;
    }
}
