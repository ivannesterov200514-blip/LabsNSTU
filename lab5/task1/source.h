#ifndef SOURCE_H
#define SOURCE_H
#pragma once

#include <iostream>
#include <string.h>
#include <iomanip>

const int ZONES = 3;
const int STEL = 14;
const int SECTIONS = 4;
const int SHELVES = 8;
const int TOTAL = 13440;
const int TOTALLOC = 1344;

struct Location {
    char zone;
    int stel;
    int sec;
    int shelf;
};

struct Good {
    char name[50];
    int quan;
    Location loc;
    bool isEmpty;
};

Location parsecode(const char* code);
bool isvalidloc(const Location& loc);
void additem(Good* sklad, int& currload, const char* name, int qt, const char* code);
void removeitem(Good* sklad, int& currload, const char* name, int qt, const char* code);
void info(Good* sklad, int currload);

#endif