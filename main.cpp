#include <cmath>
#include <fstream>
#include <set>
#include <iostream>
#include <vector>
using namespace std;

struct condition{
    vector<int> a;
};

set<condition> col;

//оператор сравнения массивов для set
inline bool operator<(const condition& lhs, const condition& rhs){
    return lhs.a < rhs.a;
}
//оператор уравнения
inline bool operator==(const condition& lhs, const condition& rhs){
    return lhs.a == rhs.a;
}
// размещения с повторениями
bool collectionReplaceSet(int *a, int n, int m){
    int j = m - 1;
    while (j >= 0 && a[j] == n) j--;
    if (j < 0) return false;
    if (a[j] >= n)
        j--;
    a[j]++;
    if (j == m - 1) return true;
    for (int k = j + 1; k < m; k++)
        a[k] = 0;
    return true;
}
// инициализация размещений в vector из vector ов
vector<condition> initCollection(int L, int n){
    int *templ;
    vector<condition> collection;
    templ = new int[n];
    for (int i = 0; i < n; ++i)
        templ[i] = 0;

    condition f;
    f.a.resize(n);
    for (int i = 0; i < n; ++i)
        f.a[n-i-1] = templ[i];
    collection.push_back(f);

    while(collectionReplaceSet(templ, L - 1, n)){
        condition t;
        t.a.resize(n);
        for (int i = 0; i < n; ++i)
            t.a[n-i-1] = templ[i];
        collection.push_back(t);
    }
    return collection;
}

//вывод в файл и в консоль
void printCollection(vector<vector<condition>> collection, bool withNum = true){
    int circles[collection.size()];
    ofstream out("out.txt");
    for (int k = 0; k < collection.size(); ++k) {
        cout<< k+1 << " circle:\n";
        out<< k+1 << " circle:\n";
        for (int i = 0; i < collection[k].size(); ++i) {
            condition t = collection[k][i];
            cout.width(3);
            out.width(3);
            if (withNum) {
                cout << i + 1 << ": ";
                out << i + 1 << ": ";
            }
            for (int j = t.a.size() - 1; j >= 0; --j) {
                cout << t.a[j] << ' ';
                out << t.a[j] << ' ';
            }
            cout << '\n';
            out << '\n';
        }
        circles[k] = collection[k].size();
        cout<<'\n';out<<'\n';
    }
    cout<<"Circles in total:\n";
    out<<"Circles in total:\n";
    for (int i = 0; i < collection.size(); ++i) {
        cout<<circles[i]<<" ";
        out<<circles[i]<<" ";
    }
    cout<<"\n";out<<'\n';
}

//счет кольца с заданным начальным состоянием
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

    vector<condition> collection = initCollection(L,n); // добавили все размещения

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
        if(!check){
            outputCollection.push_back(calculateCircle(vars,alpha,i.a,L));
        }
    }

    printCollection(outputCollection);
    //todo gui
}