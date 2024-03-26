// Метод Жордана-Гаусса.
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <iomanip>
#include <cstdlib>
#include <vector>

using namespace std;

void PrintMatrix(double(&matrix)[5][6]) {// Вывод матрицы
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if ((j + 1) % 6 == 0)
				cout << setw(12) << fixed << setprecision(4) << matrix[i][j] << endl;
			else
				cout << setw(12) << fixed << setprecision(4) << matrix[i][j];
		}
	}

}

void Zamena(double(&matrix)[5][6], int x, int y) {// Смена местами строк 
	double arr[6];
	for (int j = 0; j < 6; j++) {
		arr[j] = matrix[x][j];
		matrix[x][j] = matrix[y][j];
		matrix[y][j] = arr[j];
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	vector <double> vector(5);
	double matrix[5][6]{
			{-0.38,0.88,-0.4,-0.16,0.56,-0.79},
			{0.75,0.88,0.46,0.32,0.16,0.07},
			{-0.68,0.64,0.57,-0.88,-0.4,-0.52},
			{0.48,-0.27,-0.45,-0.01,-0.65,-0.24},
			{0.64,-0.83,0.47,-0.35,-0.5,0.23},
	};

	cout << " Исходная система уравнений (расширенная матрица) : \n\n";
	PrintMatrix(matrix);
	for (int k = 0; k < 5; k++) {// кусочек кода для проверки 0 на главной диагонали и перестановки !=0 значения
		if (matrix[k][k] == 0)
		{
			int rows = k + 1;
			while (matrix[k][k] == 0) {
				if ((matrix[rows][k] != 0) || (rows > 5)) {
					Zamena(matrix, rows, k);
					cout << endl;
					PrintMatrix(matrix);
				}
				rows++;
			}
		} 
		// Правило прямоугольника
		for (int i = 0; i < 5; i++)
		{
			for (int j = k + 1; j < 6; j++)
			{
				if (i != k && j > k)
				{
					matrix[i][j] = (matrix[i][j] * matrix[k][k] - matrix[i][k] * matrix[k][j]) / matrix[k][k];

				}
			}
		}
		// обнуление элементов i столбца
		for (int i = 0; i <= 5 - 1; i++) { 
			if (i != k)
				matrix[i][k] = 0;
		}
		// деление элементов
		for (int j = 5; j>=k; j--) { 
			matrix[k][j] = matrix[k][j] / matrix[k][k];
		}
		matrix[k][k] = matrix[k][k] / matrix[k][k]; // х3 для чего и без него работает
		cout << endl << " Вывод: " << endl;
		PrintMatrix(matrix);

	}
		
	cout << endl << " Корни системы уравнений : " << endl;
	for (int i = 0; i < 5; i++) 
	{
		cout << " X" << i+1 << "=" << matrix[i][5] << "\n";
	}
	cout << endl;
	system("pause ");
	return 0;
}