#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

double exponencial_de_euler(double x){
    double termo = 1.0;
    double resultado = 1.0;

    for(int i = 1; i<101; i++){
        termo *= x/i;
        resultado += termo;
    }

    return resultado;
}

double func(double d, double a) {
    double resposta = a;
    resposta *= exponencial_de_euler(d);
    resposta -= 4*d*d;
    return resposta;
}

double derivada(double d, double a){
    double resposta = a;
    resposta *= exponencial_de_euler(d);
    resposta -= 8*d;
    return resposta;
}

double newton_modificado(double a, double margem_de_erro, double d0){
    double derivada_de_d0 = derivada(d0, a);
    if(derivada_de_d0 == 0){
        return -1;
    }
    bool criterio_diferenca_de_raizes = false;
    bool criterio_funcao_proximo_de_zero = false;
    bool criterio_numero_valido = false;
    int i = 0;
    double d_i = d0;
    double new_d;
    double func_d_i_val;
    while(!criterio_diferenca_de_raizes && !criterio_funcao_proximo_de_zero ){
        func_d_i_val = func(d_i, a);
        cout << "f(d_i): " << func_d_i_val << "\n";
        new_d = d_i - (func_d_i_val/derivada_de_d0);
        if(isnan(new_d) || isinf(new_d)){
            return -1;
        }
        criterio_diferenca_de_raizes = abs(new_d - d_i) < margem_de_erro;
        criterio_funcao_proximo_de_zero = abs(func(new_d, a)) < margem_de_erro;
        cout << setw(5) << left << i << "  |  " << setw(15) << left << new_d << "\n";
        cout << "Diferença de raizes: " << abs(new_d - d_i) << "\n";
        cout << "Valor na função:" << func(new_d, a) << "\n\n";
        d_i = new_d;
        i++;
    }

    return new_d;
}

double newton_raphson(double a, double d0, double err) {
    double last_d = d0;
    double current_d = last_d;
    double f = func(last_d, a);
    double f_ = derivada(last_d, a);
    double diff;

    cout << setw(5) << "k" << "  |  " << setw(15) << "d_k" << "  |  " << setw(15) << "d_k+1" << "  |  " << setw(15) << "f(d)" << "  |  " << setw(15) << "f'(d)" << "  |  " << setw(15) << "|f(d_k+1)|" << "  |  " << setw(15) << "|d_k+1 - d_k|" << endl;
    for (int k=0; k < 100; k++) {
        if (f_ != 0) {
            last_d = current_d;
            current_d = last_d - (f / f_);
            diff = abs(current_d - last_d);

            cout << setw(5) << left << k << "  |  " << setw(15) << left << last_d << "  |  " << setw(15) << left << current_d << "  |  " << setw(15) << left << f << "  |  " << setw(15) << left << f_ << "  |  " << setw(15) << left << abs(func(current_d, a)) << "  |  " << setw(15) << left << diff << endl;

            if (diff < err) {
                cout << "Convergência atingida por diferença de raízes no passo " << k << ". Erro atual: " << diff << endl;
                return current_d;
            } else if (abs(func(current_d, a)) < err) {
                cout << "Convergência atingida por função próxima de zero no passo " << k << ". Erro atual: " << abs(func(current_d, a)) << endl;
                return current_d;
            } else        

            f = func(current_d, a);
            f_ = derivada(current_d, a);

        } else {
            cout << setw(5) << left << k << "  |  " << setw(15) << left << last_d << "  |  " << setw(15) << left << "-" << "  |  " << setw(15) << left << f << "  |  " << setw(15) << left << f_ << "  |  " << setw(15) << left << "-" << "  |  " << setw(15) << left << "-" << endl;
            cout << "Derivada é zero no passo " << k << ". Método não converge." << endl;
            return -1;
        }
    }

    cout << "Número máximo de iterações atingido." << endl;
    return -1;
}
