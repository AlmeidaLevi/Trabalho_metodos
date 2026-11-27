#include <vector>
using namespace std;

using namespace std;

vector<vector<double>> identity_matrix(int n) {
    vector<vector<double>> I(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        I[i][i] = 1;
    }
    return I;
}

double my_abs(double x) {
    return (x < 0) ? -x : x;
}

double vector_mul(const vector<double>& a, const vector<double>& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }
    return result;
}

vector<double> matrix_mul(const vector<vector<double>>& A, const vector<double>& b, int n) {
    vector<double> result(n, 0);
    for (int i = 0; i < n; i++) {
        result[i] = vector_mul(A[i], b);
    }
    return result;
}

vector<double> gauss_jacobi(const vector<vector<double>>& A, const vector<double>& b, int n,
                            double e) {
    vector<double> last_x(n, 0);
    vector<double> x(n, 0);
    double dk;
    double max_x;

    //Processo princiapal
    for (int k = 0; k < 1000; k++) {
        dk = 0;
        max_x = 0;

        for (int i = 0; i < n; i++) {
            //Cálculo da aproximação de cada x
            double numerator = b[i];
            for (int j = 0; j < n; j++) {
                if (j != i) numerator -= A[i][j] * last_x[j];
            }

            x[i] = numerator / A[i][i];

            if (my_abs(x[i]) > max_x) max_x = my_abs(x[i]);

            if (my_abs(x[i] - last_x[i]) > dk) dk = my_abs(x[i] - last_x[i]);
        }

        if (max_x > 0 && dk / max_x < e) break;

        last_x = x;
    }

    return x;
}

vector<vector<double>> inverse_matrix(const vector<vector<double>>& A, int n) {
    vector<vector<double>> I = identity_matrix(n);
    vector<vector<double>> inverse_A(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        vector<double> current_column = gauss_jacobi(A, I[i] , n, 1e-6);

        for (int j = 0; j < n; j++) {
            inverse_A[j][i] = current_column[j];
        }
    }
    return inverse_A;
}

vector<double> d_calc_jacobi (const vector<vector<double>>& A, const vector<double>& b, int n) {
    vector<vector<double>> inverse_A = inverse_matrix(A, n);
    vector<double> d = matrix_mul(inverse_A, b, n);
    return d;
}

vector<vector<double>> inversa_por_gauss_seidel(vector<vector<double>> A, double e){
    int n = A.size();
    vector<vector<double>> inversa;
    vector<double> coluna_identidade;
    coluna_identidade.assign(n, 0);
    vector<double> x;
    x.assign(n, 0);

    bool criterio_de_parada = false;
    int cont = 0;
    double diff;
    double max_diff = 0;
    double max_x;
    double x_anterior;

    //Loop que percorre cada equação Ax = I
    for(int i = 0; i<n; i++){
        // definindo a coluna i da matriz identidade
        coluna_identidade[i] = 1;
        //Resolvendo a equação Ax = I
        while(!criterio_de_parada or cont == 100){
            // Loop que calcula cada x
            for(int j = 0; j<n; j++){
                x_anterior = x[j];
                for(int k = 0; k<n; k++){
                    if(j != k){
                        x[j] -= A[j][k]*x[k];
                    }
                }
                x[j] += coluna_identidade[j];
                x[j] /= A[j][j];

                //Olhando o maior x para o criterio de parada
                if(j == 1){
                    max_x = x[j];
                }
                if(x[j] > max_x){
                    max_x = x[j];
                }

                // Pegando o maior erro absuloto para o criterio de parada
                diff = my_abs(x[j] - x_anterior);
                if(diff > max_diff){
                    max_diff = diff;
                }

            }
            if(max_diff/max_x <= e){
                criterio_de_parada = true;
            }
            cont++;
        }
        inversa.push_back(x);
        x.assign(n, 0);
        max_diff = 0;
        coluna_identidade[i] = 0;
    }
    return inversa;
}

vector<double> d_calc_seidel (const vector<vector<double>> A, const vector<double> b, int n, double err) {
    vector<vector<double>> inversa_A = inversa_por_gauss_seidel(A, err);
    vector<double> d = matrix_mul(inversa_A, b, n);
    return d;
}
