#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

double exponencial_de_euler(double x){
    double termo = 1.0;
    double resultado = 1.0;

    for (int i = 1; i < 101; i++){
        termo *= x / i;
        resultado += termo;
    }

    return resultado;
}

double func(double d, double a){
    double resposta = a;
    resposta *= exponencial_de_euler(d);
    resposta -= 4 * d * d;
    return resposta;
}

double derivada(double d, double a){
    double resposta = a;
    resposta *= exponencial_de_euler(d);
    resposta -= 8 * d;
    return resposta;
}

double newton_modificado(double a, double margem_de_erro, double d0){

    cout << setw(2) << left << "k" << " | "
         << setw(12) << left << "d_k" << " | "
         << setw(12) << left << "d_k+1" << " | "
         << setw(12) << left << "f(d)" << " | "
         << setw(12) << left << "f'(d0)" << " | "
         << setw(12) << left << "|f(d_k+1)|" << " | "
         << setw(12) << left << "|d_k+1 - d_k|" << endl;

    double derivada_de_d0 = derivada(d0, a);
    if (derivada_de_d0 == 0){
        return -1;
    }

    bool criterio_diferenca_de_raizes = false;
    bool criterio_funcao_proximo_de_zero = false;
    bool criterio_numero_valido = false;
    int k = 0;
    double d_k = d0;
    double new_d;
    double func_d_i_val;
    double func_new_d;
    double diff;
    while (!criterio_diferenca_de_raizes && !criterio_funcao_proximo_de_zero){
        func_d_i_val = func(d_k, a);
        new_d = d_k - (func_d_i_val / derivada_de_d0);
        if (isnan(new_d) || isinf(new_d)){
            cout << setw(2) << left << k << " | "
                 << setw(12) << left << d_k << " | "
                 << setw(12) << left << new_d << " | "
                 << setw(12) << left << func_d_i_val << " | "
                 << setw(12) << left << derivada_de_d0 << " | "
                 << setw(12) << left << "-" << " | "
                 << setw(12) << left << "-" << endl;

            cout << "Metodo não converge pois d_k+1 = " << new_d << "\n";
            return new_d;
        }
        diff = fabs(new_d - d_k);
        func_new_d = fabs(func(new_d, a));

        criterio_diferenca_de_raizes = diff < margem_de_erro;
        criterio_funcao_proximo_de_zero = func_new_d < margem_de_erro;

        cout << setw(2) << left << k << " | "
             << setw(12) << left << d_k << " | "
             << setw(12) << left << new_d << " | "
             << setw(12) << left << func_d_i_val << " | "
             << setw(12) << left << derivada_de_d0 << " | "
             << setw(12) << left << func_new_d << " | "
             << setw(12) << left << diff << endl;

        d_k = new_d;
        k++;
    }

    if(criterio_diferenca_de_raizes){
        cout << "\nConvergencia pelo criterio de diferença de raizes.\n";
    }
    if(criterio_funcao_proximo_de_zero){
        cout << "\nConvergencia pelo criterio da função proxima de 0.\n";
    }

    return new_d;
}

double newton_raphson(double a, double d0, double err){
    double last_d = d0;
    double current_d = last_d;
    double f = func(last_d, a);
    double f_ = derivada(last_d, a);
    double diff;

    cout << setw(2) << left << "k" << " | "
         << setw(12) << left << "d_k" << " | "
         << setw(12) << left << "d_k+1" << " | "
         << setw(12) << left << "f(d_k)" << " | "
         << setw(12) << left << "f'(d_k)" << " | "
         << setw(12) << left << "|f(d_k+1)|" << " | "
         << setw(12) << left << "|d_k+1 - d_k|" << endl;

    for (int k = 0; k < 100; k++){
        if (f_ != 0){
            last_d = current_d;
            current_d = last_d - (f / f_);
            diff = fabs(current_d - last_d);

            cout << setw(2) << left << k << " | "
                << setw(12) << left << last_d << " | "
                << setw(12) << left << current_d << " | "
                << setw(12) << left << f << " | "
                << setw(12) << left << f_ << " | "
                << setw(12) << left << fabs(func(current_d, a)) << " | "
                << setw(12) << left << diff << endl;

            if (diff < err){
                cout << "Convergência atingida por diferença de raízes no passo " << k << ". Erro atual: " << diff << endl;
                return current_d;
            }
            else if (fabs(func(current_d, a)) < err){
                cout << "Convergência atingida por função próxima de zero no passo " << k << ". Erro atual: " << fabs(func(current_d, a)) << endl;
                return current_d;
            }
            else{
                f = func(current_d, a);
            }
            f_ = derivada(current_d, a);
        }else{
            cout << setw(2) << left << k << " | "
                << setw(12) << left << last_d << " | "
                << setw(12) << left << "-" << " | "
                << setw(12) << left << f << " | "
                << setw(12) << left << f_ << " | "
                << setw(12) << left << "-" << " | "
                << setw(12) << left << "-" << endl;
            cout << "Derivada é zero no passo " << k << ". Método não converge." << endl;
            return -1;
        }
    }

    cout << "Número máximo de iterações atingido." << endl;
    return -1;
}

double secante(double a, double m_e, double d0, double d1)
{
    double d_i = d0, d_i_inc = d1, new_d = d1;

    cout << setw(2) << "k" << " | "
         << setw(12) << "d_k-1" << " | "
         << setw(12) << "d_k" << " | "
         << setw(12) << "d_k+1" << " | "
         << setw(12) << "f(d_k-1)" << " | "
         << setw(12) << "f(d_k)" << " | "
         << setw(12) << "|f(d_k+1)|" << " | "
         << setw(12) << "|d_k+1 - d_k|" << endl;

    for (int i = 0; i < 100; i++)
    {
        double f_i = func(d_i, a);
        double f_i_inc = func(d_i_inc, a);
        new_d = d_i_inc - (f_i_inc * (d_i_inc - d_i)) / (f_i_inc - f_i);
        if (isnan(new_d) || isinf(new_d))
        {
            return -1;
        }
        double f_new = func(new_d, a);
        double dif = fabs(new_d - d_i_inc);

        cout << left
             << setw(2)  << left << i  << " | "
             << setw(12) << left << d_i  << " | "
             << setw(12) << left << d_i_inc  << " | "
             << setw(12) << left << new_d  << " | "
             << setw(12) << left << f_i  << " | "
             << setw(12) << left << f_i_inc  << " | "
             << setw(12) << left << fabs(f_new)  << " | "
             << setw(12) << left << dif << endl;

        if (dif < m_e || fabs(f_new) < m_e)
        {
            cout << "\nConvergiu em " << i + 1 << " iteracoes ("
                 << (dif < m_e ? "diferenca entre aproximacoes" : "|f(x)| proximo de zero")
                 << " < " << m_e << ").\n";
            return new_d;
        }

        d_i = d_i_inc;
        d_i_inc = new_d;
    }

    cout << "Numero maximo de iteracoes atingido.\n";
    return -1;
}
