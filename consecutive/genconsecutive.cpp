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



int countWays(int n) {
    int ret = 0;
    int N = n * 2;
    for (int m = 2; m * m <= 2 * n; m++) {
        if (m % 2 == 0) {
            // n/m + 1/2 integer
            if ((N + m) % (m * 2) == 0) {
                ret++;
            }
        } else {
            // n / m integer
            if (n % m == 0) {
                ret++;
            }
        }
    }
    return ret;
}

vector<int> getWays(int n) {
    vector<int> ret;
    int N = n * 2;
    for (int m = 2; m * m <= 2 * n; m++) {
        if (m % 2 == 0) {
            // n/m + 1/2 integer
            if ((N + m) % (m * 2) == 0) {
                ret.push_back(m);
            }
        } else {
            // n / m integer
            if (n % m == 0) {
                ret.push_back(m);
            }
        }
    }
    return ret;
}

pair<int, vector<int> > solve(int n) {
    const int amax = int(1e6);
    for (int i = 1; i <= amax; i++) {
        int num = countWays(i);
        if (num == n) {
            return make_pair(i, getWays(i));
        }
    }
    return make_pair(-1, vector<int>());
}

void printTest(int n, const string& filename) {
	ofstream out(filename);
    out << n << "\n";
}

void writeAnswer(const string& in, const string& out) {
    ifstream cin(in);
    ofstream cout(out);
    int n;
    cin >> n;
    pair<int, vector<int> > ans = solve(n);
    cout << ans.first << "\n";
    for (int& x : ans.second) {
        cout << x << "\n";
    }
}

void test() {
    const int nmax = int(1e6);
    vector<int> sol(100);
    for (int i = 1; i < nmax; i++) {
        int x = countWays(i);
        if (!sol[x]) {
            sol[x] = i;
        }
    }
    for (int i = 1; i < 100; i++) {
        if (sol[i] != 0) cout << i << " " << sol[i] << "\n";
    }
}

string To_string(int i) {
    string ret = "";
    if (i == 0) {
        ret = "0";
    } else {
        while (i) {
            ret += (char)('0' + i % 10);
            i /= 10;
        }
    }
    reverse(begin(ret), end(ret));
    return ret;
}

void generateTests() {
    vector<int> n = {3,4,5,6,7,9,10,13,14,15,17,19,20,31,39,44,62,63,71,79,95};
    for (int i = 1; i <= 20; i++) {
        const string name = "teste/" +  To_string(i) + "-consecutive";
        printTest(n[i - 1], name + ".in");
        writeAnswer(name + ".in", name + ".ok");
    }

}

int main() {
    generateTests();
    return 0;
}
