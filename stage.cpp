/*
    Created by ilyas on 13.04.2020.
*/

#include <iostream>
#include <vector>

using namespace std;

ofstream out("out.txt");

struct condition{
    vector<int> a;
    bool checked;
};

inline bool operator<(const condition& lhs, const condition& rhs)
{
    return lhs.a < rhs.a;
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

vector<condition> initCollection(int *templ,int L, int n){

    vector<condition> collection;
    templ = new int[n];
    for (int i = 0; i < n; ++i)
        templ[i] = 0;

    condition f;
    f.a.resize(n);
    for (int i = 0; i < n; ++i)
        f.a[i] = templ[i];
    f.checked = false;
    collection.push_back(f);

    while(collectionReplaceSet(templ, L - 1, n)){
        condition t;
        t.a.resize(n);
        for (int i = 0; i < n; ++i)
            t.a[i] = templ[i];
        t.checked = false;
        collection.push_back(t);
    }
    return collection;
}

void printCollection(vector<condition> collection,int n){

    for (int i = 0; i < collection.size(); ++i) {
        condition t = collection[i];
        cout.width(3);
        cout<< i+1 <<": ";
        out.width(3);
        out<< i+1 <<": ";
        for (int j = n-1; j >= 0; --j) {
            cout<<t.a[j]<<' ';
            out <<t.a[j]<<' ';
        }
        //cout<< (t.checked ? "true" : "false");
        //out<< (t.checked ? "true" : "false");

        cout<<'\n';out<<'\n';
    }
}

