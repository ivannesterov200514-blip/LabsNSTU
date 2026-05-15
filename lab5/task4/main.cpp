#include "source.h"
#include <sstream>

int main() {
    setlocale(LC_ALL, "rus");
    Schedule schedule;
    initschedule(schedule);

    int n;
    cout << "Введите количество запросов:\n";
    cin >> n;

    string line;
    getline(cin, line);

    for (int i = 0; i < n; ++i) {
        cout << ">>> ";
        getline(cin, line);
        if (line.empty()) { i-- ; continue; }

        stringstream ss(line);
        string cmd;
        ss >> cmd;

        Command cmdd = getcom(cmd);

        if (cmdd == Command::CLASS) {
            int day;
            string disc;
            ss >> day >> disc;
            addclass(schedule, day, disc);
        }
        else if (cmdd == Command::NEXT) {
            nextmonth(schedule);
        }
        else if (cmdd == Command::VIEW) {
            int day;
            ss >> day;
            viewday(schedule, day);
        }
        else cout << "Ошибка: Неизвестная команда\n";
    }
    return 0;
}