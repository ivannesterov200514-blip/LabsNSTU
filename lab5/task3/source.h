#ifndef SOURCE_H
#define SOURCE_H
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

enum class Command {
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    INVALID
};

struct Plane {
    string name;
    vector<string> towns;
};

struct Schedule {
    map<string, Plane> planes;
    map<string, set<string>> townplanes;
};

Command getcom(const string& s);
void createplane(Schedule& s, string name, vector<string> towns);
void planefortown(const Schedule& s, string town);
void townsforplane(const Schedule& s, string planename);
void planes(const Schedule& s);

#endif