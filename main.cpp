#include <cmath>
#include <fstream>
#include <set>
#include "stage.cpp"

set<condition> col;

vector<condition> calculateCircle(vector<int> vars, vector<int> alpha, vector<int> a, int L){
    int n = a.size();
    vector<condition> output;
    vector<int> temp(n);

    condition first;
    first.a.resize(n);
    for (int i = 0; i < first.a.size(); ++i) first.a[i] = a[i];
    col.insert(first);
    output.push_back(first);

    for (int j = 1; j < pow(L, n); ++j) {
        condition cond;

        temp[0] = a[0];
        for (int i = 1; i < n; i++)
            temp[i] = a[n - i];

        for (int i = n - 1; i >= 0; --i) {

            if (i == n - 1)
                a[i] = (a[0] * vars[n - 1 - i] + alpha[n - 1 - i]) % L;
            else
                a[i] = (temp[n - 1 - i] + (a[0] * vars[n - 1 - i] + alpha[n - 1 - i]) % L) % L;
        }

        cond.a.resize(n);
        for (int i = 0; i < n; ++i) cond.a[i] = a[i];

        if (col.find(cond) == col.end())
            output.push_back(cond);

        col.insert(cond);
    }
    return output;
}

int main() {
    int n, L;

    cout << "Enter number system (L):\n";
    cin >> L;
    cout << "Enter degree of the senior polynomial (N):\n";
    cin >> n;
    vector<int> a(n), temp(n), vars(n), alpha(n);
    cout << "Enter coefficients of the polynomial F(x):\n";
    for (int i = 0; i < n; i++) cin >> vars[i]; // коэффициенты многочлена
    cout << "Enter a1, a2, ..., an:\n";
    for (int i = 0; i < n; ++i) cin >> alpha[i]; // добавочные коэффициенты
    cout<< "Enter initial state of register:\n";
    for (int i = n - 1; i >= 0; i--) cin >> a[i];


    vector<condition> collection = initCollection(L,n);

    vector<vector<condition>> outputCollection;
    outputCollection.push_back(calculateCircle(vars,alpha,a,L));


    //todo optimize code

    bool check;
    for (auto & i : collection) {
        check = false;
        for (auto & j : outputCollection) {
            for (auto & k : j) {
                if(i == k){
                    check = true;
                    break;
                }
            }
        }
        if( !check ){
            outputCollection.push_back(calculateCircle(vars,alpha,i.a,L));
        }
    }

    printCollection(outputCollection,false);

    cout<<"Total: "<< pow(L,n);

    //todo gui
}