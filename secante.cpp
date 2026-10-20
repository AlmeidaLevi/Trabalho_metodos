#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

double func(double d, double a)
{
    double ret = a * (exp(d)) - 4 * (pow(d, 2));
    return ret;
}

double calc_new_d(double d_i, double func_d_i_val, double d_i_inc, double func_d_i_inc_val)
{
    double new_d = d_i_inc - (func_d_i_inc_val * (d_i_inc - d_i)) / (func_d_i_inc_val - func_d_i_val);
    return new_d;
}

double secante(double a, double margem_de_erro, double d0, double d1)
{
    bool criterio_diferenca_de_raizes = false;
    bool criterio_funcao_proximo_de_zero = false;
    int i = 0;
    double d_i = d0;
    double d_i_inc = d1;
    double new_d;
    double func_d_i_val;
    double func_d_i_inc_val;
    while (!criterio_diferenca_de_raizes && !criterio_funcao_proximo_de_zero && i < 100)
    {
        func_d_i_val = func(d_i, a);
        cout << "f(d_i): " << func_d_i_val << "\n";
        func_d_i_inc_val = func(d_i_inc, a);
        cout << "f(d_i_inc): " << func_d_i_inc_val << "\n";
        new_d = calc_new_d(d_i, func_d_i_val, d_i_inc, func_d_i_inc_val);
        if (isnan(new_d) || isinf(new_d))
        {
            return -1;
        }
        criterio_diferenca_de_raizes = abs(new_d - d_i_inc) < margem_de_erro;
        criterio_funcao_proximo_de_zero = abs(func(new_d, a)) < margem_de_erro;
        cout << setw(5) << left << i << "  |  " << setw(15) << left << new_d << "\n";
        cout << "Diferença de raizes: " << abs(new_d - d_i_inc) << "\n";
        cout << "Valor na função:" << func(new_d, a) << "\n\n";
        d_i = new_d;
        i++;
    }

    return new_d;
}

int main()
{
    float resp = secante(1, 1e-4, 0.5, 1);
    cout << resp;
    cin.get();
    return 0;
}