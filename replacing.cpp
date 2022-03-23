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
    cin >> n;
    vector<int> a(n, 0LL);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> q;
    for (int i = 0; i < q; i++){
        int b, c;
        sum = 0;
        cin >> b >> c;
        for (int j = 0; j < n; j++){
            a[j] = (a[j] == b) ? c : a[j];
            sum += a[j];
        }
        cout << sum << endl;
    }
}