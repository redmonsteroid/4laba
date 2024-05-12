#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

// Функция для заполнения вектора случайными целыми числами от 1 до 100
void fillVectorWithRandom(vector<int>& vec) {
    random_device rd;
    ranlux48_base gen(rd());  // Создаем генератор случайных чисел ranlux48_base
    uniform_int_distribution<int> dis(1, 100);  // Определяем распределение от 1 до 100

    for (int& num : vec) {
        num = dis(gen);  // Заполняем вектор случайными числами
    }
}

// Функция для подсчета количества вхождений элемента в векторе
int countOccurrences(const vector<int>& container, int element) {
    int count = 0;
    for (int value : container) {
        if (value == element) {
            count++;
        }
    }
    return count;
}

// Функция для вычисления среднего значения элементов вектора
double mean(const vector<int>& container) {
    double n = 0;
    for (int i : container){
        n += i;
    }
    return n/container.size();
}

// Функция для вычисления дисперсии элементов вектора
double variance(const vector<int>& container) {
    double m = mean(container);  // Вычисляем среднее значение элементов вектора
    double sum_sq_diff = 0.0;
    for (int value : container) {
        sum_sq_diff += (value - m) * (value - m);  // Суммируем квадраты отклонений от среднего
    }
    return sum_sq_diff / (container.size() - 1);  // Возвращаем дисперсию
}

// Функция для вычисления функции нормального распределения (Cumulative Distribution Function - CDF)
double normalCDF(double x) {
    return (1.0 / 2.0) * (1.0 + erf(x / sqrt(2.0)));  // Возвращаем значение CDF
}

// Функция для проведения теста хи-квадрат на нормальность выборки
double chiSquareTest(const vector<int>& container) {
    int size = container.size();  // Размер выборки
    double chi2 = 0;
    double mean_val = mean(container);  // Среднее значение выборки
    double std_dev = sqrt(variance(container));  // Стандартное отклонение выборки

    for (int i = 1; i <= 100; i++) {
        // Вычисляем ожидаемую частоту для интервала [i-1, i)
        double expected_freq = size * (normalCDF((i - mean_val) / std_dev) - normalCDF((i - 1 - mean_val) / std_dev));
        // Вычисляем наблюдаемую частоту (количество вхождений числа i в выборку)
        double observed_freq = countOccurrences(container, i);
        // Вычисляем величину хи-квадрат
        chi2 += pow(observed_freq - expected_freq, 2) / expected_freq;
    }

    return chi2;  // Возвращаем значение статистики хи-квадрат
}

// Функция для вывода результатов теста хи-квадрат
void chiPrint(const vector<int>& vec, double& criticalValue) {
    double chiSquareValue = chiSquareTest(vec);  // Вычисляем статистику хи-квадрат
    double meanExpected = mean(vec);  // Вычисляем ожидаемое среднее значение
    double meanObserved = mean(vec);  // Вычисляем наблюдаемое среднее значение

    // Выводим результаты теста хи-квадрат и сравниваем с критическим значением
    cout << "Chi-Square P-value: " << chiSquareValue << endl;
    if (chiSquareValue <= criticalValue) {
        cout << "Hypothesis of normal distribution is not rejected." << endl;
    } else {
        cout << "Hypothesis of normal distribution is rejected." << endl;
    }
    cout << "Expected mean: " << meanExpected << endl;
    cout << "Observed mean: " << meanObserved << endl;
    cout << endl;
}

int main() {
    // Создаем векторы различных размеров и заполняем их случайными числами
    vector<int> vector50(50);
    vector<int> vector100(100);
    vector<int> vector1000(1000);
    fillVectorWithRandom(vector50);
    fillVectorWithRandom(vector100);
    fillVectorWithRandom(vector1000);

    double criticalValue = 124.342;  // Критическое значение для теста хи-квадрат
    // Проводим тест хи-квадрат и выводим результаты для каждого вектора
    chiPrint(vector50, criticalValue);
    chiPrint(vector100, criticalValue);
    chiPrint(vector1000, criticalValue);

    return 0;
}
