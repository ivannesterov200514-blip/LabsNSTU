#ifndef SOURCE_H
#define SOURCE_H
#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class Command {
    CLASS,
    NEXT,
    VIEW,
    INVALID
};

struct Day {
    vector<string> disciplines;
};

struct Month {
    vector<Day> days;
    int num;
};

struct Schedule {
    Month months[12];
    int currmonth;
};

Command getcom(const string& s);
void addclass (Schedule& s, int day, const string& discipline);
void nextmonth(Schedule& s);
void viewday(Schedule& s, int day);

int getdays(int monthnum);
void initschedule(Schedule& s);
bool isvalidday(Schedule& s, int day);

#endif