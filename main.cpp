#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "metodos.h"

using namespace std;

int main(){
    double a;
    int n;
    double margem_de_erro;
    double d0;
    double d1;
    int metodo;
    
    cout << string(60, '#') + "\n\n";
    
    cout << "Que método deseja utilizar?" << endl;
    cout << "1) Newton-Raphson" << endl;
    cout << "2) Newton modificado" << endl;
    cout << "3) Secante" << endl;
    cout << "4) Todos";
    cout << "\n> ";
    cin >> metodo;
    cout << endl;
    
    cout << string(60, '#') + "\n\n";
    
    cout << "Digite o numero de a's:\n> ";
    cin >> n;
    cout << endl;
    cout << "Digite a margem de erro:\n> ";
    cin >> margem_de_erro;
    cout << endl;

    vector<double> all_a;
    vector<double> all_newton_modificado;
    vector<double> all_newton_raphson;
    vector<double> all_secante;

    for(int i = 0; i<n; i++){
        cout << string(60, '#') + "\n\n";
        cout << "--- TESTE " << i+1 << " ---" << "\n\n";
        
        cout << "Digite o valor da amplitude (a):\n> ";
        cin >> a;
        cout << endl;
        all_a.push_back(a);

        cout << "Digite o chute inicial (d0):\n> ";
        cin >> d0;
        cout << endl;
            
        if (metodo == 3 or metodo == 4){
            cout << "Digite o segundo chute inicial (d1):\n> ";
            cin >> d1;
            cout << endl;
        }
        
        if (metodo == 1 or metodo == 4){
            cout << string(60, '#') + "\n\n";
            cout << "Newton Raphson: \n\n";
            
            double d_newton_raphson = newton_raphson(a, d0, margem_de_erro);
            all_newton_raphson.push_back(d_newton_raphson);
            
            cout << "d_newton_raphson: " << d_newton_raphson << "\n\n";
        }
        
        if (metodo == 2 or metodo == 4){
            cout << string(60, '#') + "\n\n";
            cout << "Newton Modificado: \n\n";
            
            double d_newton_modificado = newton_modificado(a, margem_de_erro, d0);
            all_newton_modificado.push_back(d_newton_modificado);
    
            cout << "d_newton_modificado: " << d_newton_modificado << "\n\n";
        }

        if (metodo == 3 or metodo == 4){
            cout << string(60, '#') + "\n\n";
            cout << "Secante: \n\n";
            
            double d_secante = secante(a, margem_de_erro, d0, d1);
            all_secante.push_back(d_secante);
            
            cout << "d_secante: " << d_secante << "\n\n";
        }
    }
    
    cout << string(60, '#') + "\n\n";
    
    cout << setw(6) << left << "a" << " | ";
    
    if (metodo == 1 or metodo == 4) cout << setw(20) << left << "d_newton_raphson" << " | ";
    if (metodo == 2 or metodo == 4) cout << setw(20) << left << "d_newton_modificado" << " | ";
    if (metodo == 3 or metodo == 4) cout << setw(20) << left << "d_secante" << " | ";
    
    cout << setw(5) << left << "Problema gigantesco?" << endl;
    
 
    for(int i = 0; i<n; i++){
        string problemas;
        int cont_problemas = 0;
        if (metodo == 1 or metodo == 4){
            if(all_newton_raphson[i] > 0.7) cont_problemas++;
        }
        
        if (metodo == 2 or metodo == 4){
            if(all_newton_modificado[i] > 0.7) cont_problemas++;
        }
        
        if (metodo == 3 or metodo == 4){
            if(all_secante[i] > 0.7) cont_problemas++;
        }
        
        if (metodo == 4){
            problemas = to_string(cont_problemas) + "/3";
        }
        else {
            if (cont_problemas == 0) problemas = "Não";
            else problemas = "Sim";
        }
        
        cout << setw(6) << left << all_a[i] << " | ";
        
        if (metodo == 1 or metodo == 4) cout << setw(20) << left << all_newton_raphson[i] << " | ";
        if (metodo == 2 or metodo == 4) cout << setw(20) << left << all_newton_modificado[i] << " | ";
        if (metodo == 3 or metodo == 4) cout << setw(20) << left << all_secante[i] << " | ";
        
        cout << setw(5) << left << problemas << endl;
    }
}
