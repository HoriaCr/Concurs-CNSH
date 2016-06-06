#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <iterator>

using namespace std;


vector<int> generateTest(int n) {
    std::mt19937 mt(time(0));
    std::uniform_int_distribution<int> dist(-1000, 1000);
    vector<int> ans(n);
    for (int& x : ans) {
        x = dist(mt);
    }
    return ans;
}

void solve(const string& in, const string& out) {
	ifstream cin(in);
    ofstream cout(out);	
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
}

void printTest(vector<int>& v, const string& filename) { 
	ofstream out(filename);	
    out << v.size() << "\n";
    for (int& x : v) {
        out << x << " ";
    }
}

void generateTests() {
    vector<int> n = {5, 10, 50, 100, 500, 600, 700, 800, 900, 1000,
                    10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000,
                    90000, 100000}; 
    for (int i = 1; i <= 20; i++) {
        vector<int> p = generateTest(n[i - 1]);     
        const string name = "teste/ursulet" + to_string(i);
        printTest(p, name + ".in");
        solve(name + ".in", name + ".ok"); 
    }

}

int main() {
    generateTests();
    return 0;
}
