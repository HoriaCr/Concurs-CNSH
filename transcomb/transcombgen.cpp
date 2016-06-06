
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

template<class DataType>
class Combinatorics {

        vector< vector<DataType> > C;
    
    public:

        void precomputeBinomial(uint32_t n, uint32_t k) {
            C = computeBinomial(n, k); 
        }

        vector< vector<DataType> > computeBinomial(uint32_t n, uint32_t k) {
            vector< vector<DataType> > C(n + 1, vector<DataType>(k + 1));
            C[0][0] = 1;
            for (size_t i = 1; i <= n; i++) {
                C[i][0] = 1;
                for (size_t j = 1; j <= k; j++) {
                    C[i][j] = C[i - 1][j - 1] + C[i - 1][j];  
                }
            }
            return C;
        }

        DataType comb(uint32_t n, uint32_t k) {
            // return 0 if undefined
            if (n < k) return 0;
            return C[n][k];
        }

        DataType getIndex(const vector<int>& cb, const int& n, const int& k) {
            int ret = 0;
            for (int i = 0; i < k; i++) {
                ret += comb(n - cb[i], k - i);
            }
            
            return comb(n, k) - ret - 1;
        }

        vector<int> indexToVector(DataType index, const int& n, const int& k) {
            vector<int> cb(k);
            int cIndex = 1;
            index = comb(n, k) - index - 1; 
            for (int i = 0; i < k; i++) {
                while (
                    static_cast<DataType>(comb(n - cIndex, k - i)) > index) {
                    cIndex += 1;
                }
                cb[i] = cIndex;
                index -= comb(n - cIndex, k - i);
                cIndex += 1;
            
            }
            return cb;
        }
};

void solve(const string& in, const string& out) {
	ifstream cin(in);
    ofstream cout(out);
    Combinatorics<long long> comb;
    comb.precomputeBinomial(63, 63);
    string s, q;
    int Q, t, n, k;
    long long index;
    getline(cin, s);
    n = s.size();
    auto toCombination = [&](const string& w) {
        vector<int> ret(w.size()); 
        for (size_t i = 0; i < ret.size(); i++) {
            ret[i] = s.find(w[i]) + 1;
        }
        return ret;
    };

    auto toString = [&](vector<int>& c) {
        string ret(c.size(), '.');
        for (size_t i = 0; i < c.size(); i++) {
            ret[i] = s[c[i] - 1];
        }
        return ret;
    };
    cin >> Q;
    while (Q--) {
        cin >> t;
        if (t == 1) {
            cin >> k >> index;
            vector<int> c = comb.indexToVector(index - 1, n, k); 
            string ans = toString(c);
            cout << ans << "\n";

        } else {
            cin >> q;
            vector<int> c = toCombination(q);
            cout << comb.getIndex(c, n, c.size()) + 1 << "\n"; 
        }
    }
}

void printTests(const string& name) {
	std::mt19937 mt(time(0));
	std::uniform_int_distribution<int> dist(1, 60);
    const string sigma = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	auto nextString = [&](int length) -> string {
		string ret(length, '.');
		vector<int> p(60);
        for (size_t i = 0; i < 60; i++) {
            p[i] = i;
        }
        for (char& c : ret) {
            int pos = dist(mt) % p.size();
			c = sigma[p[pos]];
            swap(p.back(), p[pos]);
            p.pop_back();
		}
		return ret;
	};

    Combinatorics<long long> comb;
    comb.precomputeBinomial(63, 63);
	std::uniform_int_distribution<int> d2(1, 100000);
	std::uniform_int_distribution<int> dc(1, 1 << 20);
    for (int i = 1; i <= 10; i++) {
        int len = dist(mt) % 20 + 1;
        string s = nextString(len);
        const string filename = name + to_string(i) + ".in";
        ofstream cout(filename);
        int Q = d2(mt);

	    std::uniform_int_distribution<int> d3(1, len);
        cout << s << "\n" << Q << "\n";
        for (int j = 0; j < Q; j++) {
           int k = d3(mt);
           int num = dc(mt) % comb.comb(len, k) + 1;
            cout << 1 << " " << k << " " << num << "\n"; 
        }
    }



	std::uniform_int_distribution<long long> dcl(1, 1LL << 60);
	std::uniform_int_distribution<int> dq(0, 1);
    for (int i = 11; i <= 20; i++) {
        int len = dist(mt);
        string s = nextString(len);
        const string filename = name + to_string(i) + ".in";
        ofstream cout(filename);
        int Q = d2(mt);

	    std::uniform_int_distribution<int> d3(1, len);
        cout << s << "\n" << Q << "\n";
        for (int j = 0; j < Q; j++) {
           int k = d3(mt);
           int t = dq(mt);
           long long num = dcl(mt) % comb.comb(len, k);
           if (t == 1) { 
               cout << t << " " << k << " " << num + 1 << "\n";
           } else {
                vector<int> l = comb.indexToVector(num, len, k); 
                string w(l.size(), '.');
                for (size_t j = 0; j < l.size(); j++) {
                    w[j] = s[l[j]];
                }

                cout << 2 << " " << w << "\n";
           }
        }
    }

    for (int i = 1; i <= 20; i++) {
        solve(name + to_string(i) + ".in", name + to_string(i) + ".ok");
    }
}

int main() {
    printTests("teste/transcomb");
}
