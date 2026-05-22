#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>

using namespace std;

random_device rd;
mt19937 rng(rd());

vector<vector<int>> init(int m, int n, int dist1, int dist2) {
    
    uniform_int_distribution<int> dist(dist1, dist2);
    vector<vector<int>> matr(m, vector<int>(n));
    for (auto& x : matr) {
        for (int& y : x) {
            y = dist(rng);
            cout << y << " ";
        }
        cout << "\n";
    }
    cout << "\n\n";

    return matr;
}

void func1(vector<vector<int>>& matrx) {
    vector<int> raz;
    raz.reserve(matrx.size());
    for (auto& x : matrx) {
        auto minim = min_element(x.begin(), x.end());
        auto maxim = max_element(x.begin(), x.end());
        raz.push_back(*maxim - *minim);
        swap(*maxim, *minim);
    }
    for (auto& x : matrx) {
        for (int& y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
    
    auto t = max_element(raz.begin(), raz.end());
    int maxid = distance(raz.begin(), t);

    cout << "\nРазности: \n";
    for (int i = 0; i < raz.size(); ++i) {
        cout << i + 1 << ". " << raz[i] << "\n";
    }
    cout << "Масимальная разность в строке: " << maxid + 1 << "\n";
}

void func2(vector<vector<int>>& matrx) {
    vector<int> sums;
    for (auto x : matrx) {
        int numsum = 0;
        for (int u : x) {
            int ch = u;
            for (int i = 0; i < 3; ++i) {
                int md = ch % 10;
                numsum += md;
                ch /= 10;
            }
        }
        sums.push_back(numsum);
    }

    auto t = max_element(sums.begin(), sums.end());
    int maxid = distance(sums.begin(), t);

    cout << "Суммы цифр всех элементов строк: \n";
    for (int i = 0; i < sums.size(); ++i) {
        cout << i + 1 << ". " << sums[i] << "\n";
    }
    cout << "Максимальная сумма: " << maxid + 1 << "\n";
}

int cntneighbours(vector<vector<int>>& matrx, int x, int y, int m, int n) {
    int count = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) count += matrx[nx][ny];
        }
    }
    return count;
}

void nextGen(vector<vector<int>>& matrx, int m, int n) {
    vector<vector<int>> newmat = matrx;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int ngbr = cntneighbours(matrx, i, j, m, n);
            if (matrx[i][j] == 1) {
                newmat[i][j] = (ngbr == 2 || ngbr == 3) ? 1 : 0;
            }
            else {
                newmat[i][j] = (ngbr == 3) ? 1 : 0;
            }
        }
    }
    matrx = newmat;
}

void print(vector<vector<int>>& matrx, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            cout << (matrx[i][j] ? "0 " : ". ");
        cout << endl;
    }
}

void clearmat(vector<vector<int>>& matrx, int m, int n) {
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrx[i][j] = 0;
}
void addGlider(vector<vector<int>>& matrx, int x, int y) {
    matrx[x][y + 1] = 1;
    matrx[x + 1][y + 2] = 1;
    matrx[x + 2][y] = matrx[x + 2][y + 1] = matrx[x + 2][y + 2] = 1;
}
void addLWSpaceship(vector<vector<int>>& matrx, int x, int y) {
    matrx[x][y + 1] = matrx[x][y + 2] = 1;
    matrx[x + 1][y] = matrx[x + 1][y + 3] = 1;
    matrx[x + 2][y + 3] = 1;
    matrx[x + 3][y] = matrx[x + 3][y + 3] = 1;
}
void addMWSpaceship(vector<vector<int>>& matrx, int x, int y) {
    matrx[x][y + 1] = matrx[x][y + 2] = 1;
    matrx[x + 1][y] = matrx[x + 1][y + 4] = 1;
    matrx[x + 2][y + 4] = 1;
    matrx[x + 3][y] = matrx[x + 3][y + 3] = matrx[x + 3][y + 4] = 1;
}
void addHWSpaceship(vector<vector<int>>& matrx, int x, int y) {
    matrx[x][y + 1] = matrx[x][y + 2] = 1;
    matrx[x + 1][y] = matrx[x + 1][y + 5] = 1;
    matrx[x + 2][y + 5] = 1;
    matrx[x + 3][y] = matrx[x + 3][y + 3] = matrx[x + 3][y + 4] = matrx[x + 3][y + 5] = 1;
}
void addQueenBee(vector<vector<int>>&
matrx, int x, int y) {
    matrx[x][y + 1] = matrx[x][y + 2] = 1;
    matrx[x + 1][y] = matrx[x + 1][y + 3] = 1;
    matrx[x + 2][y + 1] = matrx[x + 2][y + 2] = 1;
    matrx[x][y + 5] = matrx[x][y + 6] = matrx[x + 1][y + 5] = matrx[x + 1][y + 6] = 1;
    matrx[x][y - 3] = matrx[x][y - 2] = matrx[x + 1][y - 3] = matrx[x + 1][y - 2] = 1;
}

void randomFill(vector<vector<int>>& matrx, int m, int n, int density) {
    uniform_int_distribution<int> dist(1, 100);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrx[i][j] = (dist(rng) <= density) ? 1 : 0;
        }
    }
}

void runSimulation(vector<vector<int>>& matrx, int m, int n, int maxGenerations) {
    cout << "\nСимуляция запущена (макс. " << maxGenerations << " поколений)\n";
    cout << "Нажмите Enter для остановки...\n\n";

    for (int gen = 0; gen < maxGenerations; gen++) {
        system("clear");
        cout << "=== Поколение: " << gen + 1 << " ===\n\n";
        print(matrx, m, n);

        nextGen(matrx, m, n);
        this_thread::sleep_for(chrono::milliseconds(150));
    }

    cout << "\n\nСимуляция завершена. Нажмите Enter...";
    cin.get();
}

void lifeMenu(int m, int n) {
    while (true) {
        system("clear");
        cout << "=== ИГРА ЖИЗНЬ КОНВЕЯ ===\n\n";
        cout << "1. Glider (Глайдер)\n";
        cout << "2. Lightweight Spaceship (LWSS)\n";
        cout << "3. Middleweight Spaceship (MWSS)\n";
        cout << "4. Heavyweight Spaceship (HWSS)\n";
        cout << "5. Queen Bee Shuttle\n";
        cout << "6. Случайная генерация\n";
        cout << "0. Выход\n\n";
        cout << "Выберите фигуру: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        vector<vector<int>> matrx(m, vector<int>(n, 0));

        switch (choice) {
        case 1:
            addGlider(matrx, 2, 2);
            runSimulation(matrx, m, n, 100);
            break;
        case 2:
            addLWSpaceship(matrx, 5, 2);
            runSimulation(matrx, m, n, 100);
            break;
        case 3:
            addMWSpaceship(matrx, 5, 2);
            runSimulation(matrx, m, n, 100);
            break;
        case 4:
            addHWSpaceship(matrx, 5, 2);
            runSimulation(matrx, m, n, 100);
            break;
        case 5:
            addQueenBee(matrx, m / 2, n / 2);
            runSimulation(matrx, m, n, 150);
            break;
        case 6: {
            int density;
            cout << "Введите плотность заполнения (10-40%): ";
            cin >> density;
            cin.ignore();
            randomFill(matrx, m, n, density);
            runSimulation(matrx, m, n, 200);
            break;
        }
        default:
            cout << "Неверный выбор!\n";
            cout << "Нажмите Enter...";
            cin.get();
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int m, n;
    cout << "Введите размер матрицы(m n): ";
    cin >> m >> n;
    cout << "\n";
    
    vector<vector<int>> mat1 = init(m, n, 10, 50);
    func1(mat1);
    cout << "\n\n";

    cout << "Введите размер матрицы(m n): ";
    cin >> m >> n;
    cout << "\n";

    vector<vector<int>> mat2 = init(m, n, 100, 200);
    func2(mat2);

    bool l = true;
    while (l) {
        cout << "\nВведите размер поля клеток(m n), не меньше 30: ";
        cin >> m >> n;
        if (m >= 30 && n >= 30) l = false;
        else cout << "Неверно.\n";
    }

    lifeMenu(m, n);

    return 0;
}