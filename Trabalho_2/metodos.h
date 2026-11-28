#include <vector>
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

vector<vector<double>> inversa_por_gauss_jacobi(const vector<vector<double>>& A, int n, double e) {
    vector<vector<double>> I = identity_matrix(n);
    vector<vector<double>> inverse_A(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        vector<double> current_column = gauss_jacobi(A, I[i], n, e);

        for (int j = 0; j < n; j++) {
            inverse_A[j][i] = current_column[j];
        }
    }
    return inverse_A;
}

vector<vector<double>> inversa_por_gauss_seidel(const vector<vector<double>>& A, double e){
    int n = A.size();
    vector<vector<double>> inversa(n, vector<double>(n, 0));

    for (int i = 0; i < n; i++) {          // coluna i da identidade
        vector<double> x(n, 0);

        for (int cont = 0; cont < 1000; cont++) {
            double max_diff = 0;
            double max_x = 0;

            for (int j = 0; j < n; j++) {
                double soma = (i == j) ? 1.0 : 0.0;
                for (int k = 0; k < n; k++) {
                    if (k != j) soma -= A[j][k] * x[k];
                }
                double novo = soma / A[j][j];

                if (my_abs(novo - x[j]) > max_diff) max_diff = my_abs(novo - x[j]);
                if (my_abs(novo) > max_x) max_x = my_abs(novo);

                x[j] = novo;
            }

            if (max_x > 0 && max_diff / max_x < e) break;
        }

        for (int j = 0; j < n; j++) inversa[j][i] = x[j];
    }
    return inversa;
}
