#include "source.h"

using namespace std;

bool canaddcont(const ContStack& stack, int w) { return stack.currweight + w <= stack.maxweight; }
bool isstackempty(const ContStack& stack) { return stack.containers.empty(); }

void pushcont(ContStack& stack, const Container& cont) {
    stack.containers.push(cont);
    stack.currweight += cont.mass;
}

Container pick(ContStack& stack) {
    Container cont = stack.containers.top();
    stack.currweight -= cont.mass;
    stack.containers.pop();
    return cont;
}

void addconttosec(ShipSec& section, const Container& cont) {
    section.containers.push_back(cont);
    section.totalweight += cont.mass;
}

int findorcreatestack(Port& port, const Container& cont) {
    for (auto& x : port.stacks) {
        if (canaddcont(x, cont.mass)) return x.num;
    }

    ContStack newstack;
    newstack.maxweight = port.maxstacksize;
    newstack.num = port.nextstacknumber;
    newstack.currweight = 0;

    port.stacks.push_back(newstack);
    return port.nextstacknumber++;
}

void initport(Port& port, int maxWeight, int numSections) {
    port.maxstacksize = maxWeight;
    port.nextstacknumber = 1;
    
    for (int i = 1; i <= numSections; ++i) {
        ShipSec sec;
        sec.totalweight = 0;
        sec.num = i;
        port.sections.push_back(sec);
    }
}

void arrive(Port& port, const char* contid, int weight) {
    Container cont;
    cont.name = contid;
    cont.mass = weight;
    int stacknum = findorcreatestack(port, cont);

    for (auto& x : port.stacks) {
        if (x.num == stacknum) {
            pushcont(x, cont);
            break;
        }
    }

    cout << "Контейнер " << contid << " размещён в стек " << stacknum << "\n";
}

void load(Port& port) {
    vector<Container> allCont;

    for (auto i = port.stacks.rbegin(); i != port.stacks.rend(); ++i) {
        while (!isstackempty(*i)) {
            Container cont = pick(*i);
            allCont.push_back(cont);
        }
    }

    for (auto& cont : allCont) {
        ShipSec* minsec = &port.sections[0];
        for (auto& sec : port.sections) {
            if (sec.totalweight < minsec->totalweight) minsec = &sec;
        }
        addconttosec(*minsec, cont);
    }

    for (auto& y : port.sections) {
        cout << "Секция " << y.num << " (" << y.totalweight << " тонн): ";
        bool first = true;
        for (auto t = y.containers.rbegin(); t != y.containers.rend(); ++t) {
            if (!first) cout << ", ";
            cout << t -> name;
            first = false;
        }
        cout << "\n";
    }
}