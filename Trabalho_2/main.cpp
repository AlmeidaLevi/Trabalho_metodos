#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include "metodos.h"

using namespace std;

const double LIMITE_CM = 0.4;

struct Teste {
    int n;
    vector<vector<double>> A;
    vector<double> b;
};

struct Resposta {
    vector<vector<double>> inversa;
    vector<double> d;
    bool confiavel;
};

// A^-1 coluna a coluna por Gauss-Jacobi, usando a precisão informada pelo usuário
vector<vector<double>> inversa_por_gauss_jacobi(const vector<vector<double>>& A, int n, double e){
    vector<vector<double>> I = identity_matrix(n);
    vector<vector<double>> inversa(n, vector<double>(n, 0));
    for(int i = 0; i<n; i++){
        vector<double> coluna = gauss_jacobi(A, I[i], n, e);
        for(int j = 0; j<n; j++) inversa[j][i] = coluna[j];
    }
    return inversa;
}

// Confere A*d = b para detectar quando o método não convergiu
bool solucao_confiavel(const Teste& t, const vector<double>& d){
    vector<double> Ad = matrix_mul(t.A, d, t.n);
    double escala = 1;
    for(double v : t.b) if(fabs(v) > escala) escala = fabs(v);
    for(int i = 0; i<t.n; i++){
        if(!isfinite(Ad[i]) || fabs(Ad[i] - t.b[i]) > 1e-2 * escala) return false;
    }
    return true;
}

Resposta resolver(const Teste& t, int metodo, double e){
    Resposta r;
    if(metodo == 1) r.inversa = inversa_por_gauss_jacobi(t.A, t.n, e);
    else r.inversa = inversa_por_gauss_seidel(t.A, e);
    r.d = matrix_mul(r.inversa, t.b, t.n);
    r.confiavel = solucao_confiavel(t, r.d);
    return r;
}

void imprimir_matriz(const vector<vector<double>>& M){
    for(const auto& linha : M){
        for(double v : linha) cout << setw(14) << left << v;
        cout << endl;
    }
    cout << endl;
}

void imprimir_analise(const vector<double>& d, bool confiavel){
    if(!confiavel){
        cout << "Análise: o método não convergiu, resultado inconclusivo.\n";
        return;
    }
    bool problema = false;
    for(size_t i = 0; i<d.size(); i++){
        if(fabs(d[i]) > LIMITE_CM){
            cout << "d" << i+1 << " = " << d[i] << " cm passa de " << LIMITE_CM << " cm em módulo.\n";
            problema = true;
        }
    }
    if(problema) cout << "Análise: podem ocorrer sérios danos, PROBLEMA GIGANTESCO.\n";
    else cout << "Análise: todos os deslocamentos estão dentro do limite.\n";
}

void imprimir_quadro(const string& nome, const vector<Teste>& testes,
                     const vector<Resposta>& respostas){
    cout << string(60, '#') + "\n\n";
    cout << "QUADRO RESPOSTA - " << nome << "\n\n";

    for(size_t k = 0; k < testes.size(); k++){
        const Teste& t = testes[k];
        const Resposta& r = respostas[k];

        cout << "--- TESTE " << k+1 << " ---\n";
        cout << setw(4) << left << "i" << " | "
             << setw(10 * t.n) << left << "[A]" << " | "
             << setw(10) << left << "{b}" << " | "
             << "{d} (cm)" << endl;

        for(int i = 0; i<t.n; i++){
            cout << setw(4) << left << i+1 << " | ";
            for(int j = 0; j<t.n; j++) cout << setw(10) << left << t.A[i][j];
            cout << " | " << setw(10) << left << t.b[i]
                 << " | " << r.d[i] << endl;
        }

        cout << "\nA^-1:\n";
        imprimir_matriz(r.inversa);
        imprimir_analise(r.d, r.confiavel);
        cout << endl;
    }
}

bool ler_teste(Teste& t){
    cout << "Digite o número de deslocamentos (n):\n> ";
    if(!(cin >> t.n) || t.n < 1) return false;
    cout << endl;

    t.A.assign(t.n, vector<double>(t.n, 0));
    t.b.assign(t.n, 0);

    cout << "Digite a matriz A, linha por linha:" << endl;
    for(int i = 0; i<t.n; i++){
        cout << "Linha " << i+1 << ":\n> ";
        for(int j = 0; j<t.n; j++) cin >> t.A[i][j];
    }
    cout << endl;

    cout << "Digite o vetor b (" << t.n << " valores):\n> ";
    for(int i = 0; i<t.n; i++) cin >> t.b[i];
    cout << endl;

    return static_cast<bool>(cin);
}

int main(){
    int metodo;
    int quantidade;
    double e;

    cout << string(60, '#') + "\n\n";

    cout << "Que método deseja utilizar?" << endl;
    cout << "1) Gauss-Jacobi" << endl;
    cout << "2) Gauss-Seidel" << endl;
    cout << "3) Ambos";
    cout << "\n> ";
    cin >> metodo;
    cout << endl;

    if(!cin || metodo < 1 || metodo > 3){
        cout << "Método inválido." << endl;
        return 1;
    }

    cout << string(60, '-') + "\n\n";

    cout << "Digite o número de testes:\n> ";
    cin >> quantidade;
    cout << endl;
    cout << "Digite a precisão (e):\n> ";
    cin >> e;
    cout << endl;

    if(!cin || quantidade < 1 || e <= 0){
        cout << "Entrada inválida." << endl;
        return 1;
    }

    vector<Teste> testes;
    vector<Resposta> jacobi;
    vector<Resposta> seidel;

    for(int k = 0; k<quantidade; k++){
        cout << string(60, '#') + "\n\n";
        cout << "--- TESTE " << k+1 << " ---" << "\n\n";

        Teste t;
        if(!ler_teste(t)){
            cout << "Entrada inválida." << endl;
            return 1;
        }

        bool dominante = true;
        for(int i = 0; i<t.n; i++){
            if(t.A[i][i] == 0){
                cout << "A[" << i+1 << "][" << i+1 << "] é zero: reordene as equações." << endl;
                return 1;
            }
            double soma = 0;
            for(int j = 0; j<t.n; j++) if(j != i) soma += fabs(t.A[i][j]);
            if(fabs(t.A[i][i]) <= soma) dominante = false;
        }
        if(!dominante){
            cout << "Aviso: A não é estritamente diagonal dominante, a convergência não é garantida.\n\n";
        }

        testes.push_back(t);
        if(metodo == 1 or metodo == 3) jacobi.push_back(resolver(t, 1, e));
        if(metodo == 2 or metodo == 3) seidel.push_back(resolver(t, 2, e));
    }

    if(metodo == 1 or metodo == 3) imprimir_quadro("Gauss-Jacobi", testes, jacobi);
    if(metodo == 2 or metodo == 3) imprimir_quadro("Gauss-Seidel", testes, seidel);
}
