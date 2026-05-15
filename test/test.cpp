#include <iostream>
#include <utility>

using namespace std;

pair<int, int> Twe(int a, int b){
    if (a<=b) return {a, b};
    else return {b, a};
}

int main(){
    pair<int, int> res;
    cout << "Vvedite 2 chisla: \n";
    cin >> res.first;
    cin >> res.second;
    auto sult = Twe(res.first, res.second);
    cout << "\n" << sult.first << "\t" << sult.second;
}