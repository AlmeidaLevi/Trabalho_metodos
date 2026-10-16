#include <stdlib.h>
#include <cmath>
#include <iostream>

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
    while(!criterio_diferenca_de_raizes && !criterio_funcao_proximo_de_zero ){
        new_d = d_i - (func(d_i, a)/derivada_de_d0);
        if(isnan(new_d) || isinf(new_d)){
            return -1;
        }
        criterio_diferenca_de_raizes = abs(new_d - d_i) < margem_de_erro;
        criterio_funcao_proximo_de_zero = abs(func(new_d, a)) < margem_de_erro;
        cout << i << ": " << new_d << "\n";
        cout << "Diferença de raizes: " << abs(new_d - d_i) << "\n";
        cout << "Valor na função:" << func(new_d, a) << "\n\n";
        d_i = new_d;
        i++;
    }

    return new_d;
}
