#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

int main(){


    ofstream out("out.txt");

    int n, L;

    cout<<"Enter number system (L):\n";
    cin >> L;
    cout<<"Enter degree of the senior polynomial (N):\n";
    cin >> n;
    vector<int> a(n), t(n), vars(n), alpha(n);

    cout<<"Enter coefficients of the polynomial F(x):\n";
    for (int i = 0; i < n; i++) cin >> vars[i];

    cout<<"Enter a1, a2, ..., an:\n";
    for (int i = 0; i < n; ++i) cin>> alpha[i];

    // инициализация начального состояния
    a[n-1] = 1;
    for (int i = n - 2; i >= 0; i--) a[i] = 0;

    cout << '\n';
    for (int i = n - 1; i >= 0; i--) cout << a[i] << ' ';
    cout << '\n';

    for (int i = n - 1; i >= 0; i--) out << a[i] << ' ';
    out << '\n';


    for (int g = 1; g < pow(L,n) - 1; g++) {

        //сохраняем предыдущее состояние регистра
        t[0] = a[0];
        for (int i = 1; i < n; i++) {
            t[i] = a[n - i];
        }

        for (int i = n - 1; i >= 0; --i) {
            if(i == n-1)
                a[i] = (a[0] * vars[n-1-i] + alpha[n-1-i]) % L;
            else
                a[i] = (t[n-1-i] + (a[0] * vars[n-1-i] + alpha[n-1-i]) % L) % L;

            cout << a[i] << ' ';
            out  << a[i] << ' ';
        }


        cout << '\n';
        out << '\n';
    }

    cout<<"\niterations: " << pow(L,n)-1;
    out<<"\niterations: " << pow(L,n)-1;

    //todo check all possible values
    //todo gui

}