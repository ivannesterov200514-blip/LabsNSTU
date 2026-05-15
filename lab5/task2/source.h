#ifndef SOURCE_H
#define SOURCE_H
#pragma once

#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;

struct Container {
    string name;
    int mass;
};

struct ContStack {
    stack<Container> containers;
    int currweight = 0;
    int maxweight;
    int num;
};

struct ShipSec {
    vector<Container> containers;
    int totalweight = 0;
    int num;
};

struct Port {
    vector<ContStack> stacks;
    vector<ShipSec> sections;
    int maxstacksize;
    int nextstacknumber = 1;
};

void initport(Port& port, int maxWeight, int numSections);
void arrive(Port& port, const char* contid, int weight);
void load(Port& port);

bool canaddcont(const ContStack& stack, int weight);
void pushcont(ContStack& stack, const Container& cont);
Container pick(ContStack& stack);
bool isstackempty(const ContStack& stack);
void addconttosec(ShipSec& section, const Container& cont);
int findorcreatestack(Port& port, const Container& cont);



#endif