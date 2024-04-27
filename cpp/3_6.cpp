#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

void fillVectorWithRandom(vector<int>& vec) {
    random_device rd;
    ranlux48_base gen(rd());  // Use ranlux48_base random number engine
    uniform_int_distribution<int> dis(1, 100);

    for (int& num : vec) {
        num = dis(gen);
    }
}

int countOccurrences(const vector<int>& container, int element) {
    int count = 0;
    for (int value : container) {
        if (value == element) {
            count++;
        }
    }
    return count;
}

double mean(const vector<int>& container) {
    double n = 0;
    for (int i : container){
        n += i;
    }
    return n/container.size();
}

double variance(const vector<int>& container) {
    double m = mean(container);
    double sum_sq_diff = 0.0;
    for (int value : container) {
        sum_sq_diff += (value - m) * (value - m);
    }
    return sum_sq_diff / (container.size() - 1);
}

double normalCDF(double x) {
    return (1.0 / 2.0) * (1.0 + erf(x / sqrt(2.0)));
}

double chiSquareTest(const vector<int>& container) {
    int size = container.size();
    double chi2 = 0;
    double mean_val = mean(container);
    double std_dev = sqrt(variance(container));

    for (int i = 1; i <= 100; i++) {
        double expected_freq = size * (normalCDF((i - mean_val) / std_dev) - normalCDF((i - 1 - mean_val) / std_dev));
        double observed_freq = countOccurrences(container, i);
        chi2 += pow(observed_freq - expected_freq, 2) / expected_freq;
    }

    return chi2;
}

void chiPrint(const vector<int>& vec, double& criticalValue) {
    double chiSquareValue = chiSquareTest(vec);
    double meanExpected = mean(vec);
    double meanObserved = mean(vec);

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
    vector<int> vector50(50);
    vector<int> vector100(100);
    vector<int> vector1000(1000);
    fillVectorWithRandom(vector50);
    fillVectorWithRandom(vector100);
    fillVectorWithRandom(vector1000);
    double criticalValue = 124.342;  // Critical chi-square value for 99 degrees of freedom and 0.05 significance level
    chiPrint(vector50, criticalValue);
    chiPrint(vector100, criticalValue);
    chiPrint(vector1000, criticalValue);
    return 0;
}
