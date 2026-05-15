#include "source.h"

using namespace std;

int main() {
    setlocale(LC_ALL, ".UTF8");

    int maxStacksize, numSec;
    cout << "Введите максимальный размер стека:\n";
    cout << ">>> ";
    cin >> maxStacksize;
    
    cout << "Введите количество секций судна:\n";
    cout << ">>> ";
    cin >> numSec;

    Port port;
    initport(port, maxStacksize, numSec);
    char command[20];   
    while (true) {
        cout << ">>> ";
        cin >> command;
        if (strcmp(command, "ARRIVE") == 0) {
            char id[20];
            int weight;
            std::cin >> id >> weight;
            arrive(port, id, weight);
        }
        else if (strcmp(command, "LOAD") == 0) {
            load(port);
            break;
        }
        else {
            cout << "Неизвестная команда.\n";
            cin.ignore(1000, '\n');
        }
    }
    
    return 0;
}