#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

int main() {


    ofstream out("out.txt");

    int n, L;

    cout << "Enter number system (L):\n";
    cin >> L;
    cout << "Enter degree of the senior polynomial (N):\n";
    cin >> n;
    vector<int> a(n), t(n), vars(n), alpha(n);

    cout << "Enter coefficients of the polynomial F(x):\n";
    for (int i = 0; i < n; i++) cin >> vars[i]; // коэффициенты многочлена

    cout << "Enter a1, a2, ..., an:\n";
    for (int i = 0; i < n; ++i) cin >> alpha[i]; // добавочные коэффициенты

    // инициализация и вывод начального состояния (1 0 0 ..)
    a[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) a[i] = 0;

    cout << '\n';
    for (int i = n - 1; i >= 0; i--) cout << a[i] << ' ';
    cout << '\n';

    for (int i = n - 1; i >= 0; i--) out << a[i] << ' ';
    out << '\n';


    // кодовое кольцо
    for (int j = 0; j < pow(L, n) - 1; ++j) {

        //сохранение предыдущего состояния регистра
        t[0] = a[0];
        for (int i = 1; i < n; i++)
            t[i] = a[n - i];

        // обновление состояния регистра
        for (int i = n - 1; i >= 0; --i) {
            if (i == n - 1)
                // обновление крайней ячейки регистра
                a[i] = (a[0] * vars[n - 1 - i] + alpha[n - 1 - i]) % L;
            else
                // обновление остальных ячеек регистра
                a[i] = (t[n - 1 - i] + (a[0] * vars[n - 1 - i] + alpha[n - 1 - i]) % L) % L;

            cout << a[i] << ' ';
            out << a[i] << ' ';

        }

        cout << '\n'; out << '\n';
    }
    cout << "\niterations: " << pow(L,n) - 1;
    out << "\niterations: " << pow(L,n) - 1;

    //todo проверять все возможные варианты
    //todo вырожденное кольцо
    //todo gui
}