#include <fstream>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

int main() {

    ifstream cin("ursulet.in");
    ofstream cout("ursulet.out");
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = numeric_limits<int>::min();
    int s = 0, j = 0, l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (s < 0) {
            s = a[i];
            j = i + 1;
        } else {
            s += a[i];
        }
        if (s > ans) {
            ans = s;
            l = j;
            r = i + 1;
        } 
    }
    cout << ans << "\n"  << l << " " << r << "\n";
    return 0;
}
