#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Arr {
    string* data;
    int size;
    int capacity;
    Arr(int cap = 2) {
        capacity = cap > 0 ? cap : 2;
        data = new string[capacity];
        size = 0;
    }
    ~Arr() { delete[] data; }
};

string arr_search (Arr* arr, int idx);
void arr_insert_tail (Arr* arr, string val);
void arr_insert_idx (Arr* arr, string val, int idx);
void arr_delete_idx (Arr* arr, int idx);
void arr_change_idx (Arr* arr, string val, int idx);
int arr_getsz(Arr* arr);
void arr_print(Arr* arr);