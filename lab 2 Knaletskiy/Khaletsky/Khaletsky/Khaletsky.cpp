// Метод халетского 
#include <iostream>
#include <string>
#include <locale>

using namespace std;

// Вывод матрицы
void PrintMatrix(double(&a)[5][5]) {
	int i, j = 0;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			printf_s("  % 5.3f", a[i][j]);//Форматный вывод
		}
		cout << endl;
	}
}

// Вывод вектора
void PrintVector(double(&a)[5]) {
	int i = 0;
	for (i = 0; i < 5; i++) {
			printf_s("  % 5.3f", a[i]);//Форматный вывод
	}
}

// Поменять местами строки 
void Change(double(&a)[5][5], int row1, int row2) {
	double arr[6];//Буферный вектор
	for (int i = 0; i < 5; i++) {
		arr[i] = a[row1][i];
		a[row1][i] = a[row2][i];
		a[row2][i] = arr[i];
	}
}


int main()
{
	setlocale(LC_ALL, "rus");
	double matrix_a[5][5]{
			{-0.38,0.88,-0.4,-0.16,0.56},
			{0.75,0.88,0.46,0.32,0.16},
			{-0.68,0.64,0.57,-0.88,-0.4},
			{0.48,-0.27,-0.45,-0.01,-0.65},
			{0.64,-0.83,0.47,-0.35,-0.5},
	};

	double matrix_b[5][5]; // нижняя треугольная матрица
	double matrix_t[5][5]; // верхняя треугольная матрица
	double vector_x[5];	   // корни уравнения
	double vector_y[5];	   // промежуточный вектор произведения матрицы T на вектор X с помощью деления
	double vector_c[5]{ -0.79,0.07,-0.52,-0.24,0.23 }; // столбец свободных коэффицентов

	int n = 5;
	cout << " Исходная система уравнений: \n\n";
	PrintMatrix(matrix_a);
	
	//Заполнение матриц B и T нулями
	for (int i = 0; i <= n - 1; i++)
	{
		for (int j = 0; j <= n - 1; j++)
		{
			matrix_b[i][j] = 0;
			
			matrix_t[i][j] = 0;
		}
	}

	//Заполнение массивов				// уточнить про заполнение нулями?
	for (int i = 0; i <= n - 1; i++)
	{
		for (int j = 0; j <= n - 1; j++)
		{
			matrix_b[i][j] = 0;
			if (i = j) matrix_t[i][j] = 1;
			else matrix_t[i][j] = 0;
		}
	} 
	/*cout << endl << " Матрица B ";
	cout << endl;
	PrintMatrix(matrix_b);
	cout << endl << " Матрица T ";
	cout << endl;
	PrintMatrix(matrix_t);*/

	//Заполнение крайнего столбца матрицы B
	for (int i = 0; i <= n - 1; i++)
	{
		matrix_b[i][0] = matrix_a[i][0];
	}

	
	//Заполнение 1 верхнего столбца матрицы T
	for (int j = 0; j <= n - 1; j++)
	{
		matrix_t[0][j] = matrix_a[0][j]/matrix_b[0][0];
	}

	/*cout << endl << " Матрица B ";
	cout << endl;
	PrintMatrix(matrix_b);
	cout << endl << " Матрица T ";
	cout << endl;
	PrintMatrix(matrix_t);*/


	//Заполнение матриц B и Т по формулам из книги bookpdf
	for (int k = 1; k <= n - 1; k++)
	{
		for (int i = k; i <= n - 1; i++)
		{
			matrix_b[i][k] = matrix_a[i][k];
			for (int m = 0; m <= k - 1; m++)
			{
				matrix_b[i][k] = matrix_b[i][k] - matrix_b[i][m] * matrix_t[m][k];
			}
		}
		if (k <= n - 2)
			for (int j = k + 1; j <= n - 1; j++)
			{
				matrix_t[k][j] = matrix_a[k][j];
				for (int m = 0; m <= k - 1; m++)
				{
					matrix_t[k][j] = matrix_t[k][j] - matrix_b[k][m] * matrix_t[m][j];
				}
				matrix_t[k][j] = matrix_t[k][j] / matrix_b[k][k];
			}
	}


	//Вывод на лист матриц B и T
	cout << endl << " Матрица B ";
	cout << endl;
	PrintMatrix(matrix_b);
	cout << endl << " Матрица T ";
	cout << endl;
	PrintMatrix(matrix_t);

	//Заполнение векторов нулями
	for (int i = 0; i <= n - 1; i++)
	{
		vector_x[i] = 0;
		vector_y[i] = 0;
	}

	//Вычисление вектора y
	vector_y[0] = vector_c[0] / matrix_b[0][0];

	for (int i = 1; i <= n - 1; i++)
	{
		vector_y[i] = vector_c[i];
		for (int m = 0; m <= i - 1; m++)
		{
			vector_y[i] = vector_y[i] - matrix_b[i][m] * vector_y[m];
		}
		vector_y[i] = vector_y[i] / matrix_b[i][i];
	}


	//Вывод на лист вектора Y
	cout << endl << " Вектор Y " << endl;
	PrintVector(vector_y);
	cout << endl;

	//Вычисление вектора X
	vector_x[n - 1] = vector_y[n - 1];

	for (int i = n - 2; i >= 0; i--)
	{
		vector_x[i] = vector_y[i];
		for (int m = i + 1; m <= n - 1; m++)
		{
			vector_x[i] = vector_x[i] - matrix_t[i][m] * vector_x[m];
		}
	}

	cout << endl << " Вектор X " << endl;
	PrintVector(vector_x);
	cout << endl;

}