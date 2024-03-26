// Метод Гаусса
#include <iostream>
#include <string>
#include <locale>

using namespace std;
double x[6];

void PrintMatrix(double(&a)[5][6]) {// Вывод матрицы
	int i, j = 0;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			printf_s("  % 5.3f", a[i][j]);
		}
		printf_s("\n");
	}
}



void Zamena(double(&a)[5][6], int col, int row) {// Смена местами строк 
	double arr[6];
	for (int j = 0; j < 6; j++) {
		arr[j] = a[col][j];
		a[col][j] = a[row][j];
		a[row][j] = arr[j];
	}
}

void Nulls(double(&a)[5][6], int p) {// Проверка нулей на главной диагонали	
	if (a[p][p] == 0) // Если на главной диагонали найден ноль
	{
		int m = p + 1;
		while (a[p][p] == 0) {
			if ((a[m][p] != 0)) //|| (m >= 5))
			{
				Zamena(a, m, p);
				cout << endl;
				PrintMatrix(a);
			}
			m++;
		}
	}
}

void MultDiag(double(&a)[5][6], int p) {
	for (int i = p + 1; i < 5; i++)//Произведение элементов главной диагонали минус произведение элементов на побочной диагонали
	{
		for (int j = p + 1; j < 6; j++)
		{
			if (i != p && j > p)
			{
				a[i][j] = (a[i][j] * a[p][p] - a[i][p] * a[p][j]) / a[p][p];

			}
		}
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	double matrix[5][6]{
			{-0.38,0.88,-0.4,-0.16,0.56,-0.79},
			{0.75,0.88,0.46,0.32,0.16,0.07},
			{-0.68,0.64,0.57,-0.88,-0.4,-0.52},
			{0.48,-0.27,-0.45,-0.01,-0.65,-0.24},
			{0.64,-0.83,0.47,-0.35,-0.5,0.23},
	};
	cout << " Исходная система уравнений (расширенная матрица) : \n\n";
	PrintMatrix(matrix);

	for (int k = 0; k < 5; k++) {
		Nulls(matrix, k);

		MultDiag(matrix, k);

		//Обнуление элементов k-го столбца
		for (int i = k + 1; i < 5; i++) {
			matrix[i][k] = 0;
		}
		// Деление всей строки на разрешающий элемент
		for (int j = 5; j >= k; j--) {// int j = 5; j>= k; j—
			matrix[k][j] = matrix[k][j] / matrix[k][k];
		}

		matrix[k][k] = matrix[k][k] / matrix[k][k];//Деление разрешающего элемента на самого себя
		cout << endl << " Вывод: " << endl;
		PrintMatrix(matrix);

	}

	//Обратный ход
	int k = 0;

	x[5] = matrix[4][5];
	for (int i = 4; i >= 0; i--)
	{
		x[i] = matrix[i][5];
		for (int j = i + 1; j < 5; j++) 
			x[i] -= matrix[i][j] * x[j];
	}


	cout << endl << " Корни системы уравнений : " << endl;
	for (int k = 0; k < 5; k++) {
		cout << " X" << k + 1 << "=" << x[k] << "\n";
	}
	cout << endl;
}
