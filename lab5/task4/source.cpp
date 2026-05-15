#include "source.h"

Command getcom(const string& s) {
    if (s == "CLASS") return Command::CLASS;
    if (s == "NEXT") return Command::NEXT;
    if (s == "VIEW") return Command::VIEW;
    return Command::INVALID;
}

int getdays(int monthnum) {
    if (monthnum == 2) return 28;
    if (monthnum == 4 || monthnum == 6 || monthnum == 9 || monthnum == 11) return 30;
    else return 31;
}

void initschedule(Schedule& s) {
    s.currmonth = 0;
    int monthNum = 1;

    for (auto& month : s.months) {
        month.num = monthNum;
        int dayscnt = getdays(monthNum);
        for (int i = 0; i < dayscnt; ++i) {
            month.days.push_back({});
        }
        monthNum++;
    }
}

bool isvalidday(Schedule& s, int day) {
    int maxdays = getdays(s.months[s.currmonth].num);
    return day >= 1 && day <= maxdays;
}

void addclass(Schedule& s, int day, const string& discipline) {
    if (!isvalidday(s, day)) {
        int maxdays = getdays(s.months[s.currmonth].num);
        cout << "Ошибка: В этом месяце всего " << maxdays << " дней\n";
        return;
    }

    auto& currday = s.months[s.currmonth].days[day - 1];

    for (const auto& dupl : currday.disciplines) {
        if (dupl == discipline) {
            cout << "Ошибка: Дисциплина " << discipline << " уже есть в этот день\n";
            return;
        }
    }

    currday.disciplines.push_back(discipline);
    cout << "Добавлена дисциплина " << discipline << " на день " << day << "\n";
}

void nextmonth(Schedule& s) {
    int currmnth = s.currmonth;
    int nextmnth = (currmnth + 1) % 12;

    int currdays = getdays(s.months[currmnth].num);
    int nextdays = getdays(s.months[nextmnth].num);

    int daystocopy = (currdays < nextdays) ? currdays : nextdays;
    
    for (int i = 0; i < daystocopy; ++i) {
        auto& currday = s.months[currmnth].days[i];
        auto& nextday = s.months[nextmnth].days[i];
        
        for (const auto& disc : currday.disciplines) {
            nextday.disciplines.push_back(disc);
        }
    }

    if (nextdays < currdays) {
        auto& lastdaynext = s.months[nextmnth].days[nextdays - 1];

        for (int i = nextdays; i < currdays; ++i) {
            auto& extraday = s.months[currmnth].days[i];

            for (const auto& disc : extraday.disciplines) {
                lastdaynext.disciplines.push_back(disc);
            }
        }
    }

    s.currmonth = nextmnth;
    cout << "Переход на следующий месяц\n";
}

void viewday(Schedule& s, int day) {
    if (!isvalidday(s, day)) {
        int maxdays = getdays(s.months[s.currmonth].num);
        cout << "Ошибка: В этом месяце всего " << maxdays << " дней\n";
        return;
    }

    const auto& currday = s.months[s.currmonth].days[day - 1];

    if (currday.disciplines.empty()) {
        cout << "В день " << day << " мы свободны!\n";
    }
    else {
        cout << "В день " << day << " занятия в университете: ";
        bool first = true;

        for (const auto& disc : currday.disciplines) {
            if (!first) cout << ", ";
            cout << disc;
            first = false;
        }
        cout << "\n";
    }
}