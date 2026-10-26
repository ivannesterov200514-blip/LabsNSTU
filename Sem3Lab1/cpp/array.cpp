#include "array.h"

static void arr_resize (Arr* arr, int newcap) {
    string* newdata = new string[newcap];
    for (int i = 0; i < arr->size; i++) newdata[i] = arr->data[i];
    delete[] arr->data;
    arr->data = newdata;
    arr->capacity = newcap;
}

string arr_search (Arr* arr, int idx) {
    if (idx >= arr->size || idx < 0) {
        cout << "Ошибка: Такого индекса нет\n";
        return "";
    }
    return arr->data[idx];
}

void arr_insert_tail (Arr* arr, string val) {
    if (arr->size >= arr->capacity) arr_resize(arr, arr->capacity*2);
    arr->data[arr->size] = val;
    arr->size++;
}

void arr_insert_idx (Arr* arr, string val, int idx) {
    if (idx > arr->size || idx < 0) {
        cout << "Ошибка: Такого индекса нет\n";
        return;
    }
    if (arr->size >= arr->capacity) arr_resize(arr, arr->capacity*2);
    for (int i = arr->size; i > idx; --i) {
        arr->data[i] = arr->data[i-1];
    }
    arr->data[idx] = val;
    arr->size++;
}

void arr_delete_idx (Arr* arr, int idx) {
    if (idx >= arr->size || idx < 0) {
        cout << "Ошибка: Такого индекса нет\n";
        return;
    }
    for (int i = idx; i < arr->size - 1; ++i) {
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
}

void arr_change_idx (Arr* arr, string val, int idx) {
    if (idx >= arr->size || idx < 0) {
        cout << "Ошибка: Такого индекса нет\n";
        return;
    }
    arr->data[idx] = val;
}

int arr_getsz(Arr* arr) {
    return arr->size;
}

void arr_print(Arr* arr) {
    cout << "Массив: ";
    for (int i = 0; i < arr->size; ++i) cout << arr->data[i] << " ";
    cout << endl;
}
