#include <vector>
using namespace std;

vector<double> produto_matriz_coluna(vector<vector<double>> A, vector<double> x){

}

vector<vector<double>> gauss_seidel(vector<vector<double>> A, vector<double> b){
    int n = A.size();
    vector<vector<double>> inversa;
    vector<double> coluna_inversa;
    coluna_inversa.assign(n, 0);

    bool criterio_de_parada = false;
    for(int i = 0; i<n; i++){
        coluna_inversa[i] = 1;
        while(!criterio_de_parada){

        }
        coluna_inversa[i] = 0;
    }
}
