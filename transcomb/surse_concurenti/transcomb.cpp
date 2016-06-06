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

int main() {
    ifstream cin("transcomb.in");
    ofstream cout("transcomb.out"); 
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
