
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

class SuffixAutomaton {

    struct Node {
        string str;
        map<char, int> next;
        int link;
        long long substringsNumber;
        int length;
        bool isClone;
        Node() : link(-1), substringsNumber(0), length(0), isClone(false) {}
    };

    vector< Node > state;
    vector<long long> cnt;
    int size;
    int last;

    void extend(const string& data) {
        int current;
        int q, p;
        int clone;
        for (const char& c : data) {
            current = size++;
            state[current].length = state[last].length + 1;
            for (p = last; p != -1 && !state[p].next.count(c); p = state[p].link) {
                state[p].next[c] = current;
            }

            if (p == -1) {
                state[current].link = 0;
            } else {
                q = state[p].next[c];
                if (state[p].length + 1 == state[q].length) {
                    state[current].link = q;
                } else {
                    clone = size++;
                    state[clone].link = state[q].link;
                    state[clone].next = state[q].next;
                    state[clone].length = state[p].length + 1;
                    state[clone].isClone = true;

                    for (; p != -1 && state[p].next[c] == q; p = state[p].link) {
                        state[p].next[c] = clone;
                    }
                    state[q].link = state[current].link = clone;
                }
            }
            last = current;
        }
    }

    int getState(const string& str) {
        int v = 0;
        for (size_t i = 0; i < str.size(); i++) {
            auto it = state[v].next.find(str[i]);
            if (it == state[v].next.end()) return -1;
            v = it->second;
        }
        return v;
    }

public:

    SuffixAutomaton(const string &data = "") {
        state.resize(data.size() << 1);
        state[0].link = -1;
        state[0].substringsNumber = 0;
        size = 1;
        last = 0;
        extend(data);
    }

    long long df(int v) {
        if (state[v].substringsNumber) {
            return state[v].substringsNumber;
        }

        state[v].substringsNumber = 1;
        for (const auto& w : state[v].next) {
            state[v].substringsNumber += df(w.second);
        }
        return state[v].substringsNumber;
    }

    void go(int v) {
        for (const auto& w : state[v].next) {
            go(w.second);
        }
    }

    bool isIn(const string &str) {
        int v = 0;
        for (size_t i = 0; i < str.size(); i++) {
            auto it = state[v].next.find(str[i]);
            if (it == state[v].next.end()) return false;
            v = it->second;
        }

        return true;
    }

    string getMin(int v, int n) {
        if (!n) return "";
        if (!state[v].next.empty()) {
            return state[v].next.begin()->first + getMin(state[v].next.begin()->second, n - 1);
        }
        return "";
    }

    string getKth(int v, long long k) {
        for (auto w = state[v].next.rbegin(); w != state[v].next.rend(); w++) {
            if (state[w->second].substringsNumber <= k) {
                k -= state[w->second].substringsNumber;
            }
            else {
                return w->first + getKth(w->second, k);
            }
        }
        return "";
    }

    string getKth(long long k) {
        const long long substringTotal = state[0].substringsNumber - 1;
        return getKth(0, substringTotal - k - 1);
    }

    void computeCnt() {
        vector<int> p(size);
        vector< Node >& state_ = state;
        cnt.resize(size);
        for (int i = 0; i < size; i++){
            p[i] = i;
            if (state[i].isClone == false) {
                cnt[i] = 1;
            }
        }
        sort(p.begin(), p.end(), [&state_](const int& i, const int& j) -> bool {
            return state_[i].length > state_[j].length;
        });

        for (int i = 0; i < size; i++) {
            if (state[p[i]].link != -1) {
                cnt[state[p[i]].link] += cnt[p[i]];
            }
        }
    }

    long long getStrCnt(const string& s) {
        int v = getState(s);
        if (v == -1) return 0;
        return cnt[v];
    }
};

void solve(const string& in, const string& out) {
	ifstream cin(in);
    ofstream cout(out);	
	int k;
    string s;
    getline(cin, s);
    cin >> k;
    vector<long long> v(k);
    for (int i = 0; i < k; i++) {
        cin >> v[i];
    }
    SuffixAutomaton sa(s);
    sa.df(0);
    for (int i = 0; i < k; i++) {
        cout << sa.getKth(v[i] - 1) << "\n";
    }
}

int main() {
    solve("ksir.in", "ksir.out");
}
