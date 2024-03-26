// Ithirachii.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <math.h>
#include <iostream>
using namespace std;

int main() {

	int n = 5;
	double A[5][5] = { 
		    {36, -6, 3, 5, 9},
			{-8, 24, -8, 4, -2},
			{-5, -5, 34, 6, 7},
			{2, -4, 2, 19, 3},
			{-6, 4, -1, 6, 26}
	};
	double C[5] = { 47, 20, 111, 44, 29 };
	double X[5] = { 0,0,0,0,0 };
	double XX[5];

	int how_many = 0;


	/// вывод начального вектора
	for (int i = 0; i < n; i++) {
		cout << X[i] << " ";
	}

	/// вычисление х(К+1)
	do {
		for (int i = 0; i < n; i++) {
			XX[i] = C[i];
			for (int j = 0; j < n; j++) {
				if (j != i) {
					XX[i] = XX[i] - A[i][j] * X[j];
				}
			}
			XX[i] = XX[i] / A[i][i];
		}

		how_many = 0;
		///проверка модулей разности
		for (int i = 0; i < n; i++) {
			if (fabs(X[i] - XX[i]) < 0.0001) {
				how_many = how_many + 1;
			}
			X[i] = XX[i];
		}
		/// вывод результирующего вектора
		for (int i = 0; i < n; i++) {
			cout << X[i] << " ";
		}
		cout << endl;
	} while (how_many != n);



}