// neleneynie-yravnenia.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

﻿#include <iostream>
#include <cmath>

using namespace std;

// Функция, вычисляющая значение функции x + 2^x + 1
double f(double x) {
	return x + pow(2, x) + 1;
}

// Функция, вычисляющая значение производной функции x + 2^x + 1
double f_derivative(double x) {
	return 1 + log(2) * pow(2, x);
}

// Функция, вычисляющая значение второй производной функции x + 2^x + 1
double f_second_derivative(double x) {
	return log(2) * log(2) * pow(2, x) + 1;
}

// Метод половинного деления
double bisection_method(double a, double b, double epsilon) {
	while (b - a > 2 * epsilon) { // Пока не достигнута заданная точность
		double c = (a + b) / 2; // Середина интервала
		if (f(a) * f(c) < 0) { // Если знаки функции на концах интервала разные
			b = c; // Сужаем интервал до [a, c]
		}
		else {
			a = c; // Сужаем интервал до [c, b]
		}
	}
	double x = (a + b) / 2; // Найденное приближение к корню
	return x;
}

// Метод касательных для нахождения корня уравнения f(x) = 0 на интервале [a,b] с заданной точностью epsilon
// a - начало интервала, b - конец интервала, epsilon - заданная точность
double tangent_method(double a, double b, double epsilon) {
	double c_old;
	if (f(a) * f_second_derivative(a) > 0) { // Если f(a)*f''(a) > 0, то начальное приближение c_old = a
		c_old = a;
	}
	else if (f(b) * f_second_derivative(b) > 0) { // Если f(b)*f''(b) > 0, то начальное приближение c_old = b
		c_old = b;
	}
	else {
		cout << "Не выполнено условие выбора начального приближения" << endl; // Если условие выбора начального приближения не выполнено, выводим сообщение об ошибке
		return 0;
	}
	bool t = true;
	double c_new;

	while (t) { // Запускаем цикл, пока не будет достигнута заданная точность
		if (f(a) * f_second_derivative(a) > 0) { // Если f(a)*f''(a) > 0
			c_new = a - f(a) / f_derivative(a); // Вычисляем новое приближение c_new с помощью формулы метода касательных
			a = c_new; // Обновляем значение начала интервала
		}
		else {
			c_new = b - f(b) / f_derivative(b); // Вычисляем новое приближение c_new с помощью формулы метода касательных
			b = c_new; // Обновляем значение конца интервала
		}
		t = abs(c_new - c_old) > epsilon; // Проверяем выполнение условия окончания цикла: |c_new - c_old| > epsilon
		c_old = c_new; // Обновляем значение предыдущего приближения
	}
	return c_new; // Возвращаем найденное значение корня
}

// Основная функция
int main() {
	setlocale(LC_ALL, "Russian");
	double a = -5, b = 5; // Интервал, на котором ищем корень методами половинного деления и касательных
	double epsilon = 0.0001; // Задаем значение точности
	double x_bisection = bisection_method(a, b, epsilon); // Находим корень методом половинного деления
	double x_tangent = tangent_method(a, b, epsilon); // Находим корень методом касательных
	cout << "Приближенное решение методом половинного деления: " << x_bisection << endl; // Выводим результат для метода половинного деления
	cout << "Приближенное решение методом касательных: " << x_tangent << endl; // Выводим результат для метода касательных
	return 0;
}