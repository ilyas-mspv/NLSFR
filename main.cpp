#include <cmath>
#include <fstream>
#include <set>
#include "stage.cpp"

int main() {

    int n, L, *templ;

    cout << "Enter number system (L):\n";
    cin >> L;
    cout << "Enter degree of the senior polynomial (N):\n";
    cin >> n;
    vector<int> a(n), temp(n), vars(n), alpha(n);
    cout << "Enter coefficients of the polynomial F(x):\n";
    for (int i = 0; i < n; i++) cin >> vars[i]; // коэффициенты многочлена
    cout << "Enter a1, a2, ..., an:\n";
    for (int i = 0; i < n; ++i) cin >> alpha[i]; // добавочные коэффициенты


    vector<condition> collection;

    collection = initCollection(templ,L,n);

    // инициализация и вывод начального состояния (1 0 0 ..)
    a[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--) a[i] = 0;


    set<condition> col;
    vector<condition> outputCollection;

    outputCollection.resize(pow(L,n));
    condition initialCondition;
    initialCondition.a.resize(n);
    for (int i = 0; i < n; ++i) {
        initialCondition.a[i] = a[i];
    }
    col.insert(initialCondition);
    outputCollection[0] = initialCondition;

    for (int j = 1; j < pow(L, n); ++j) {
        condition con;

        //сохранение предыдущего состояния регистра
        temp[0] = a[0];
        for (int i = 1; i < n; i++)
            temp[i] = a[n - i];

        // обновление состояния регистра
        for (int i = n - 1; i >= 0; --i) {
            if (i == n - 1)
                // обновление крайней ячейки регистра
                a[i] = (a[0] * vars[n - 1 - i] + alpha[n - 1 - i]) % L;
            else
                // обновление остальных ячеек регистра
                a[i] = (temp[n - 1 - i] + (a[0] * vars[n - 1 - i] + alpha[n - 1 - i]) % L) % L;

        }

        con.a.resize(n);
        for (int i = 0; i < n; ++i) {
            con.a[i] = a[i];
        }

        if (col.find(con) == col.end()) {
            outputCollection[j] = con;
        }
        col.insert(con);

    }

    printCollection(outputCollection,n);

    //todo вырожденное кольцо
    //todo gui
}