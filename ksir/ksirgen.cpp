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


pair< string, vector<long long> > generateTest(int len, int k) {
	std::mt19937 mt(time(0));
	std::uniform_int_distribution<int> dist(0, 26);
    const string sigma = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	auto nextString = [&](int length) -> string {
		string ret(length, '.');
		for (char& c : ret) {
			c = sigma[dist(mt)];
		}
		return ret;
	};

    string s = nextString(len);
    SuffixAutomaton sa(s); 
    long long num = sa.df(0) - 1;
   
	std::uniform_int_distribution<long long> kdist(1, num);
    vector<long long> v;
    for (int i = 0;; i++) {
        long long ki = kdist(mt);
        string s = sa.getKth(ki - 1);
        k -= s.size();
        if (k >= 0) { 
            v.push_back(ki);
        } else {
            break;
        }
    }
    return make_pair(s, v);
}

void printTest(const pair<string, vector<long long> >& p, const string& filename) { 
	ofstream out(filename);	
    out << p.first << "\n";
    out << p.second.size() << "\n";
    for (auto& x : p.second) {
        out << x << " ";
    }
}

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
    vector<int> len = {10, 100, 200, 300, 500, 600, 750, 900, 950, 1000, 10000,
        100000, 200000, 200000, 200000, 200000, 200000, 200000, 200000, 200000
    }; 
    vector<int> k = {50, 100, 500, 500, 500, 600, 600, 700, 800, 1000,
        100000, 200000, 200000, 200000, 200000, 200000, 200000, 200000,
        200000, 200000 
    };
    for (int i = 11; i <= 20; i++) {
        pair<string, vector<long long> > p = generateTest(len[i - 1], k[i - 1]);    
        const string name = "teste/ksir" + to_string(i);
        printTest(p, name + ".in");
        solve(name + ".in", name + ".ok"); 
    }
    return 0;
}
