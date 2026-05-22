#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

bool read(vector<vector<int>>& board, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> board[i][j];
            if (board[i][j] < 0 || board[i][j] > 1) {
                cout << "\nНеверно, вводим только 1 или 0\n";
                return false;
            }
        }
    }
    return true;
}

void printboard(const vector<vector<int>>& board, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << board[i][j] << setw(3);
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<vector<int>> generateTarget(int n, int m, int startVal) {
    vector<vector<int>> target(n, vector<int>(m));
    int mid = n / 2;
    for (int i = 0; i < mid; ++i)
        for (int j = 0; j < m; ++j)
            target[i][j] = startVal;
    for (int i = mid; i < n; ++i)
        for (int j = 0; j < m; ++j)
            target[i][j] = 1 - startVal;
    return target;
}

int solve(vector<vector<int>> board, int n, int m, const vector<vector<int>>& target, vector<vector<vector<int>>>& path) {
    path.clear();
    int moves = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != target[i][j]) {
                moves++;
                board[i][j] ^= 1;

                if (j + 1 < m && board[i][j + 1] != target[i][j + 1])
                    board[i][j + 1] ^= 1;
                else if (i + 1 < n && board[i + 1][j] != target[i + 1][j])
                    board[i + 1][j] ^= 1;
                else if (j + 1 < m)
                    board[i][j + 1] ^= 1;
                else if (i + 1 < n)
                    board[i + 1][j] ^= 1;
                else
                    return -1;
                path.push_back(board);
            }
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (board[i][j] != target[i][j])
                return -1;
    return moves;
}

int main() {
    setlocale(LC_ALL, "rus");
    int n, m;

    cout << "Введите размер доски N x M\n";
    cin >> n >> m;

    vector<vector<int>> board(n, vector<int>(m));
    cout << "Введите доску (0 или 1):\n";
    while (true) {
        if (read(board, n, m)) break;
    }

    cout << "\nДоска:\n";
    printboard(board, n, m);
    cout << "-----------------------------------------------\n";

    vector<vector<int>> target1 = generateTarget(n, m, 0);
    vector<vector<int>> target2 = generateTarget(n, m, 1);

    vector<vector<vector<int>>> path1, path2;
    int moves1 = solve(board, n, m, target1, path1);
    int moves2 = solve(board, n, m, target2, path2);

    cout << "Паттерн 1 (верхняя часть 0):\n";
    printboard(target1, n, m);
    cout << "Нужно ходов: " << (moves1 == -1 ? "невозможно" : to_string(moves1)) << "\n\n";

    cout << "Паттерн 2 (верхняя часть 1):\n";
    printboard(target2, n, m);
    cout << "Нужно ходов: " << (moves2 == -1 ? "невозможно" : to_string(moves2)) << "\n\n";

    int bestMoves = -1;
    const vector<vector<vector<int>>>* bestPath = nullptr;

    if (moves1 != -1 && moves2 != -1) {
        if (moves1 <= moves2) { bestMoves = moves1; bestPath = &path1; }
        else { bestMoves = moves2; bestPath = &path2; }
    } 
    else if (moves1 != -1) {
        bestMoves = moves1; bestPath = &path1;
    } 
    else if (moves2 != -1) {
        bestMoves = moves2; bestPath = &path2;
    }

    if (bestMoves != -1) {
        cout << "Путь решения:\n";
        for (int i = bestPath->size() - 1; i >= 0; --i) {
            printboard((*bestPath)[i], n, m);
        }
        cout << "\nМинимальное число ходов: " << bestMoves << "\n";
    } 
    else {
        cout << "\nРешение не найдено.\n";
    }
    return 0;
}