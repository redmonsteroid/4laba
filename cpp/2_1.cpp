#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
vector <int> findld(const vector <int> & arr){ // втрое 
    int currentLength = 1;
    int maxLength = 1;
    int startIndex = 0;
    int maxStartindex = 0;
    int prev = arr.front();
    int index = 0;
    for (int num : arr) { // на первом этапе сравнивает два раза первое
        if (index > 0) {
            if (num < prev) {
                currentLength++;
            } else {
                if (currentLength > maxLength) {
                    maxLength = currentLength;
                    maxStartindex = startIndex;
                }
                currentLength = 1;
                startIndex = index;
            }
        }
        prev = num;
        index++;
    }
    if (currentLength > maxLength) {
        maxLength = currentLength;
        maxStartindex = startIndex;
    }
    vector<int> result;
    for (int i = maxStartindex; i < maxStartindex + maxLength; ++i) {
        result.push_back(arr[i]);
    }
    return result;
}
vector <int> ThirdVector (const vector <int> & arr){
    double srzn = 0;
    for (int n : arr){
        srzn += n;
    }
    srzn = srzn / arr.size();
    vector<int> result;
    for (double n : arr){
        if (srzn > n){
            result.push_back(n);
        }
    }
    return result;
}
vector <int> FourhVector (const vector <int> & arr){
    int first = arr[0], second = arr[1];
    int index = 0;
    int k = 0;
    vector<int> result;
    for (int n : arr){
        if (k < 2){
            k++;
            continue;
        }
        result.push_back(n);
    }
    result.push_back(first); result.push_back(second);
    return result;
}
vector <int> Fifth_1 (const vector <int> & arr){
    vector<int> result = arr;
    sort(result.begin(), result.end(), [](int a, int b) {
        return a > b; // Сортировка по убыванию: возвращаем true, если a должно идти перед b
    });
    return result;
};
vector<int> Fifth_2(const vector<int> &arr) {

    vector<int> digitCount(10, 0); // Массив для подсчёта количества вхождений каждой цифры от 0 до 9

    
    for (int num : arr) {
        int temp = num;
        while (temp > 0) {
            int digit = temp % 10; 
            digitCount[digit]++;   
            temp /= 10;             
        }
    }

    vector<int> result(digitCount.begin(), digitCount.end());//вхождений каждой цифры от 0 до 9

    return result;
}
int main () {
    vector <int> randomVector;
    vector <int> taskVector;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // чтобы были каждый раз разные используем текущее время
    ranlux48_base rng (seed); // ranlux генерирует по сидам и 
    int n = 10;
    for (int i = 0; i < n; i++) {
        randomVector.push_back(rng() % 201 + 150); // [150, 350]
    }
    taskVector = findld(randomVector);
    for (int n : randomVector){
        cout << n << " ";
    }
    cout << endl;
    for (int n : taskVector){
        cout << n << " ";
    }
    taskVector.clear();
    cout << endl;
    taskVector = ThirdVector(randomVector);
    for (int n : taskVector){
        cout << n << " ";
    }
    taskVector.clear();
    cout << endl;
    randomVector.clear(); // поменяем диапозон рандома
    for (int i = 0; i < n; i++) {
        randomVector.push_back(rng() % 93 + 31); // по ascii таблице
    }
    for (char n : randomVector){ // просто неявно преабразуем 
        cout << n << " ";        
    }
    cout << endl;
    taskVector = FourhVector(randomVector);
    for (char n : taskVector){
        cout << n << " ";
    }
    taskVector.clear();
    cout << endl;
    randomVector.clear();
    for (int i = 0; i < n; i++) {
        randomVector.push_back(rng() % 801 + 100); // [100,900]
    }
    taskVector = Fifth_1(randomVector);
    for (int n : taskVector){
        cout << n << " ";
    }
    cout << endl;
    taskVector.clear();
    taskVector = Fifth_2(randomVector);
    for (int n : taskVector){
        cout  << n << " ";
    }
}