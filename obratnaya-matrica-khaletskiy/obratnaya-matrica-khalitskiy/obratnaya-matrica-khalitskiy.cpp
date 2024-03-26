// obratnaya-matrica-khalitskiy.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    const int n = 4;
    double A[n][n] = { 
                      {-1, -1, 2, 1},
                      {1, 0, -1, -1},
                      {-1, -3, 3, 1},
                      {2, 4, -4, -3},
    };

    double L[n][n], U[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            U[i][j] = 0;
            L[i][j] = 0;
        }
    }

    // LU-разложение
    for (int i = 0; i < n; i++) {
        // вычисление элементов U
        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]); // вычисление суммы произведений элементов матриц L и U
            }
            U[i][k] = A[i][k] - sum; // вычисление элемента матрицы U
        }
        // вычисление элементов L
        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1; // установка диагонального элемента матрицы L равным 1
            }
            else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += (L[k][j] * U[j][i]); // вычисление суммы произведений элементов матриц L и U
                }
                L[k][i] = (A[k][i] - sum) / U[i][i]; // вычисление элемента матрицы L
            }
        }
    }

    // обратный ход
    double y[n][n];
    double x[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y[i][j] = 0;
            x[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        y[i][i] = 1 / L[i][i]; // установка диагональных элементов матрицы y равными 1/L[i][i]
        for (int j = i + 1; j < n; j++) {
            double sum = 0;
            for (int k = i; k < j; k++) {
                sum += (L[j][k] * y[k][i]); // вычисление суммы произведений элементов матриц L и y
            }
            y[j][i] = -sum / L[j][j];
        }
    }
    for (int i = 0; i < n; i++) {
        x[n - 1][i] = y[n - 1][i]; // установка последней строки матрицы x равной последней строке матрицы y
        for (int j = n - 2; j >= 0; j--) {
            double sum = 0;
            for (int k = j + 1; k < n; k++) {
                sum += (U[j][k] * x[k][i]); // вычисление суммы произведений элементов матриц U и x
            }
            x[j][i] = y[j][i] - sum; // вычисление элемента матрицы x
        }
    }

    // вывод результата
    cout << "Обратная матрица:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}