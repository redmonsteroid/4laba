#include <iostream>
#include <vector>
using namespace std;
int main () {
    vector <int> rand;
    int xi; // number for rand
    int repeat;
    bool firstAppear = false;
    cout << "Enter x0, A, B, C" << endl; // -1 error
    int x0, A, B, C; cin >> x0 >> A >> B >> C;
    if (!(0<=A && A<=C) || (!(0<=B && B<=C)) || (!(0<=x0 && x0 < C))){
        cout << "error";
        return -1;
    }
    rand.push_back(x0);
    for (int i=0; i<9; i++){
        xi = (A*rand[i] + B) % C;
        rand.push_back(xi);
        if (x0==xi && rand.size()>1 && firstAppear==false){
            repeat = i+2; // +2 потому что в индекс с нуля и прибавляется знач только на след итерации
            firstAppear = true;
        }
    }
    for (int n : rand){
        cout << n << " ";
    }
    cout << endl;
    cout << repeat;
}