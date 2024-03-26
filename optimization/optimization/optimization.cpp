// optimization.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

﻿#include <iostream>
#include <cmath>

using namespace std;

double f(double x) {
    return (2 * pow(x, 2) - 2 * x + 5) / (pow(x, 2) - x + 4);
}

/// Метод Свенна
double sven(double x0, double d) {
    double xC = x0;
    double xL = x0 - d;
    double xR = x0 + d;
    while (!((f(xL) > f(xC)) && (f(xR) > f(xC)))) {
        if ((f(xL) > f(xC)) && (f(xC) > f(xR))) {
            double xN = xR + 2 * d;
            xL = xC;
            xC = xR;
            xR = xN;
        }
        else {
            if ((f(xL) < f(xC)) && (f(xC) < f(xR))) {
                double xN = xL - 2 * d;
                xR = xC;
                xC = xL;
                xL = xN;
            }
            d = 2 * d;
        }
    }

    double a = xL;
    double b = xR;

    return (a + b) / 2;
}

/// Метод половинного деления
double half_division(double a, double b, double epsilon) {
    while ((b - a) >= 2 * epsilon) {
        double x1 = (3 * a + b) / 4;
        double x2 = (a + b) / 2;
        double x3 = (a + 3 * b) / 4;
        if ((f(x1) < f(x2)) && (f(x2) < f(x3))) {
            b = x2;
        }
        else if ((f(x1) > f(x2)) && (f(x2) > f(x3))) {
            a = x2;
        }
        else {
            a = x1;
            b = x3;
        }
    }

    return (a + b) / 2;
}

/// Метод золотого сечения
double golden_section(double a, double b, double epsilon) {
    double phi = (sqrt(5) - 1) / 2;
    double x1 = b - phi * (b - a);
    double x2 = a + phi * (b - a);
    while (abs(b - a) >= epsilon) {
        if (f(x1) < f(x2)) {
            b = x2;
            x2 = x1;
            x1 = b - phi * (b - a);
        }
        else {
            a = x1;
            x1 = x2;
            x2 = a + phi * (b - a);
        }
    }

    return (a + b) / 2;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double x0, d, epsilon;
    cout << "Введите начальное значение x0: ";
    cin >> x0;
    cout << "Введите значение d: ";
    cin >> d;
    cout << "Введите значение epsilon: ";
    cin >> epsilon;

    double x1 = sven(x0, d);
    double x2 = half_division(x1 - d, x1 + d, epsilon);
    double x3 = golden_section(x1 - d, x1 + d, epsilon);

    cout << "Метод Свенна: " << x1 << endl;
    cout << "Метод половинного деления: " << x2 << endl;
    cout << "Метод золотого сечения: " << x3 << endl;
}