#include <iostream>
#include <vector>
#include <random>
using namespace std;

random_device rd;
ranlux48_base rng(rd());

bool eyeForAnEye(int32_t round_number, vector<bool>& self_choices, vector<bool>& enemy_choices){
    if (round_number == 0){
        return true;
    } else {
        return enemy_choices[round_number - 1];
    }
}

bool spy(int32_t round_number, vector<bool>& self_choices, vector<bool>& enemy_choices){ // не знаю как назвать пусть будет шпион 
    if (round_number == 0){
        return true;
    } else {
        int event = rng () % 10; // с вероятностью 10% отказывает в сотрудничестве
        if (event == 0){
            return false;
        } 
        return self_choices[round_number - 1]; // в остальном как в око за око
    }
}

bool random (int32_t round_number, vector<bool>& self_choices, vector<bool>& enemy_choices){
    return rng () % 2;
}
void logic (bool first, bool second, int& firstPlayer, int& secondPlayer){
    if (first == second && first == false) {
        firstPlayer+=4;
        secondPlayer+=4;
    }
    if (first == second && first == true) {
        firstPlayer+=24;
        secondPlayer+=24;
    }
    if (first > second) {
        firstPlayer+=0;
        secondPlayer+=20;
    }
    if (first < second) {
        firstPlayer+=20;
        secondPlayer+=0;
    }
}
void resulTable(int firstPlayer, int secondPlayer){
    if (firstPlayer > secondPlayer) {
        cout << firstPlayer << " " << secondPlayer << endl;
        cout << "first player wins" << endl;
    } else if (firstPlayer < secondPlayer) {
        cout << firstPlayer << " " << secondPlayer << endl;
        cout << "second player wins" << endl;
    } else {
        cout << firstPlayer << " " << secondPlayer << endl;
        cout << "draw" << endl;
    }
}


int main () {
    int ammountOfRounds = rng() % 101 + 100;
    vector <bool> firstStrateg;
    vector <bool> secondStrateg;
    int firstPlayer = 0, secondPlayer = 0;
    cout << "eyes for an eye vs spy" << endl; 
    for (int32_t round_number = 0; round_number < ammountOfRounds; round_number++){
        firstStrateg.push_back(eyeForAnEye(round_number, firstStrateg, secondStrateg)); // глаз за глаз
        secondStrateg.push_back(spy(round_number, secondStrateg, firstStrateg)); // шпион
        logic(firstStrateg.back(), secondStrateg.back(), firstPlayer, secondPlayer);
    }
    resulTable(firstPlayer, secondPlayer);
    firstStrateg.clear(); secondStrateg.clear(); firstPlayer = 0; secondPlayer = 0; // обнуляем результаты перед новой игрой
    cout << "eyes for an eye vs random" << endl;
    for (int32_t round_number = 0; round_number < ammountOfRounds; round_number++){
        firstStrateg.push_back(eyeForAnEye(round_number, firstStrateg, secondStrateg));
        secondStrateg.push_back(random(round_number, firstStrateg, secondStrateg));
        logic(firstStrateg.back(), secondStrateg.back(), firstPlayer, secondPlayer);
    }
    resulTable(firstPlayer, secondPlayer);
    firstStrateg.clear(); secondStrateg.clear(); firstPlayer = 0; secondPlayer = 0;
    cout << "spy vs random" << endl;
    for (int32_t round_number = 0; round_number < ammountOfRounds; round_number++){
        firstStrateg.push_back(spy(round_number, firstStrateg, secondStrateg));
        secondStrateg.push_back(random(round_number, firstStrateg, secondStrateg));
        logic(firstStrateg.back(), secondStrateg.back(), firstPlayer, secondPlayer);
    }
    resulTable(firstPlayer, secondPlayer);
    firstStrateg.clear(); secondStrateg.clear(); firstPlayer = 0; secondPlayer = 0;
    return 0;
     
}

// по идеи самая лучшая стратегия всегда отказываться, но так не интересно 
// true - сотрудничает false - предательство  