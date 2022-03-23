#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <queue>
#include <cmath>
#include <numeric>
#include <set>
#include <fstream>

using namespace std;
int main(int argc, char *argv[]){
    ifstream in(argv[1]);
    cin.rdbuf(in.rdbuf());
    int n, q, sum;
    int ct[100005];
    cin >> n;
    vector<int> a(n, 0LL);
    for (int i = 0; i < n; i++){
        cin >> a[i];
        ct[a[i]] += 1;
    }
    cin >> q;
    sum = accumulate(a.begin(), a.end(), 0);

    for (int i = 0; i < q; i++){
        int b, c;
        cin >> b >> c;
        sum += ct[b] * (c - b);
        ct[c] += ct[b];
        ct[b] = 0;
        cout << sum << endl;
    }
}