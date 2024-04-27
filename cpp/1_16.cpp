#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;
double f(double x) {
    return cos(x + 0.3) - x * x;
}

double df(double x) {
    return -sin(x + 0.3) - 2 * x; // Производная функции f(x)
}

double g(double x) {
    return sqrt(cos(x + 0.3)); // Функция g(x) для метода простых итераций
}

double newtonMethod(double x0, double epsilon) {
    double x = x0; 
    int iteration = 1;
    cout << "Newton's Method Iterations:" << endl;
    cout << "Iteration" << setw(10) << "x" << setw(25)  << "difference" << endl;
    cout << "__________________________________________________" << endl;
    
    do {
        double f_x = f(x);
        double df_x = df(x);
        x = x - f_x / df_x;   // след значение x
        cout << iteration << setw(20) << x << setw(20) << abs(-f_x / df_x) << endl;
        iteration++;
    } while (abs(f(x)) > epsilon);
    
    return x;
}

double simpleIterationMethod(double x0, double epsilon) {
    double xn = x0;
    double xn_plus_1;
    int iteration = 0;
    bool isRepeated = false;
    vector<double> roots; 

    cout << "\nSimple Iteration Method Iterations:" << endl;
    cout << "Iteration" << setw(10) << "xn" << setw(15) << "xn+1" << setw(20) << "difference" << endl;
    cout << "__________________________________________________" << endl;
    
    do {
        xn_plus_1 = g(xn);
        cout << iteration << setw(20) << xn << setw(15) << xn_plus_1 << setw(15) << abs(xn_plus_1 - xn) << endl;

        for (double root : roots) {
            if (abs(xn_plus_1 - root) < epsilon) {
                isRepeated = true; // проверка на повтор корня
                break;
            }
        }
        if (!isRepeated) {
            roots.push_back(xn_plus_1); 
        } 
        xn = xn_plus_1;
        iteration++;
    } while (abs(g(xn) - xn) > epsilon && iteration < 100 && !isRepeated);

    return xn;
}

// Метод половинного деления для уточнения корня с заданной точностью
double halfDivisionMethod(double a, double b, double epsilon) {
    int iteration = 1;
    double midPoint;

    cout << "\nHalf Division Method:" << endl;
    cout << "N" << setw(10) << "a" << setw(14) << "b" << setw(14) << "b-a" << endl;
    cout << "_______________________________________" << endl;

    if (f(a) * f(b) >= 0) {
        cout << "Интервал выбран неправильно. В данном сегменте нет корня." << endl;
        return NAN;
    }

    while (abs(b - a) > epsilon) {
        midPoint = (a + b) / 2.0;
        cout << iteration << setw(10) << a << setw(14) << b << setw(14) << b - a << endl;

        if (f(midPoint) == 0.0) {
            return midPoint; // Найден точный корень
        } else if (f(a) * f(midPoint) < 0) {
            b = midPoint; // Корень находится в левой половине отрезка
        } else {
            a = midPoint; // Корень находится в правой половине отрезка
        }

        iteration++;
    }
    return (a + b) / 2.0;   // Возвращаем середину последнего интервала как приближенный корень
}

int main() {
    double a = 0.0; // Начало интервала
    double b = 1.0;  // Конец интервала
    double epsilon = 0.0001; // Точность

    cout << "Ищем корень уравнения cos(x + 0.3) - x^2 = 0 с использованием различных методов:" << endl;

    double newton = newtonMethod((a + b) / 2, epsilon);
    cout << "Найденный корень методом Ньютона: x = " << newton << endl;

    double simpleIteration = simpleIterationMethod((a + b) / 2, epsilon);
    cout << "Найденный корень простым итерационным методом: x = " << simpleIteration << endl;

    double halfDivision = halfDivisionMethod(a, b, epsilon);
    cout << "Найденный корень методом половинного деления: x = " << halfDivision << endl;

    return 0;
}
