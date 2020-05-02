/*
    Created by ilyas on 13.04.2020.
*/

#include <iostream>
#include <vector>

using namespace std;


struct condition{
    vector<int> a;
};

inline bool operator<(const condition& lhs, const condition& rhs){
    return lhs.a < rhs.a;
}

inline bool operator==(const condition& lhs, const condition& rhs){
    return lhs.a == rhs.a;
}

bool collectionReplaceSet(int *a, int n, int m)
{
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

void printCollection(vector<vector<condition>> collection, bool withNum = true){
    ofstream out("out.txt");
    for (int k = 0; k < collection.size(); ++k) {
        cout<< k+1 << " circle:\n";
        out<< k+1 << "circle:\n";
        for (int i = 0; i < collection[k].size(); ++i) {
            condition t = collection[k][i];
            cout.width(3);
            out.width(3);
            if(withNum){
                cout<< i+1 <<": ";
                out<< i+1 <<": ";
            }
            for (int j = t.a.size()-1; j >= 0; --j) {
                cout<<t.a[j]<<' ';
                out <<t.a[j]<<' ';
            }
            cout<<'\n';out<<'\n';
        }
        cout<<'\n';out<<'\n';
    }
}

