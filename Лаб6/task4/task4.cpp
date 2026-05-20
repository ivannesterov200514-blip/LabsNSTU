#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>

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

void printboard(vector<vector<int>>& board, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << board[i][j] << setw(3);
        }
        cout << "\n";
    }
    cout << "\n";
}

bool isright(vector<vector<int>>& board, int n, int m) {
    int mid = n / 2;

    if (n == 0 || m == 0) return true;
    int topval = board[0][0];
    int botval = 1 - topval;

    for (int i = 0; i < mid; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != topval) return false;
        }
    }
    for (int i = mid; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (board[i][j] != botval) return false;
        }
    }
    return true;
}

pair<int, int> flip(int x, int y) {
    pair<int, int> res;
    res.first = 1 - x;
    res.second = 1 - y;
    return res;
}

bool algo(vector<vector<int>> board, int n, int m, int limit, int currmove, vector<vector<vector<int>>>& path) {
    if (isright(board, n, m)) return true;
    if (currmove == limit) return false;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            board[i][j] = 1 - board[i][j];
            board[i][j + 1] = 1 - board[i][j + 1];

            if (algo(board, n, m, limit, currmove + 1, path)) {
                path.push_back(board);
                return true;
            }

            board[i][j] = 1 - board[i][j];
            board[i][j + 1] = 1 - board[i][j + 1];
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            board[i][j] = 1 - board[i][j];
            board[i + 1][j] = 1 - board[i + 1][j];

            if (algo(board, n, m, limit, currmove + 1, path)) {
                path.push_back(board);
                return true;
            }

            board[i][j] = 1 - board[i][j];
            board[i + 1][j] = 1 - board[i + 1][j];
        }
    }
    return false;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int m, n;
    cout << "Введите размер доски N x M\n";
    cin >> n >> m;
    vector<vector<int>> board(n, vector<int>(m));
    cout << "Введите доску (0 или 1):\n";
    while (true) {
        bool u = read(board, n, m);
        if (u) break;
    }

    cout << "\nДоска:\n";
    printboard(board, n, m);
    cout << "-----------------------------------------------\n";

    vector<vector<vector<int>>> path;
    int result = -1;
    for (int lim = 0; lim <= 100; ++lim) {
        if (algo(board, n, m, lim, 0, path)) {
            result = lim;
            break;
        }
        path.clear();
    }

    if (result != -1) {
        for (int i = path.size() - 1; i >= 0; --i) {
            printboard(path[i], n, m);
        }
        cout << "\nМинимальное число ходов: " << result << "\n";
    }
    else cout << "\nРешение не найдено(или превышен лимит).\n";

    return 0;
}