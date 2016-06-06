#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <utility>

#define NMAX 350000
#define EXPMAX 1000

using namespace std;

long k, sn, m, L, i, j, numar, T, x;
long lungime[NMAX], stanga[NMAX];
long n;
vector<pair<int, int> > exps;
vector<int> primes;

char p[NMAX];

int primesSieve(int n) {
    int i, j, nr = 1;
        for (i = 1; ((i * i) << 1) + (i << 1) <= n; i += 1) {
            if (p[i] == 0) {
                for (j = ((i * i) << 1) + (i << 1); (j << 1) + 1 <= n; j += (i << 1) + 1) {
                    p[j] = 1;
            }
        }
    }
    for (i = 3; i <= EXPMAX; ++ i)
        if (p[i] == 0) {
            primes.push_back(i);
        }
}

void factorization(int n) {
    int d = 0;
    while (n % 2 == 0) {
        n /= 2;
        ++ d;
    }

    exps.push_back(make_pair(2, d));

    int sqr = sqrt(n);
    for (int i = 3; i <= sqr; i += 2) {
        d = 0;
        while (! (n % i)) {
            ++ d;
            n /= i;
        }
        exps.push_back(make_pair(i, d));
    }

    if (n > 2)
        exps.push_back(make_pair(n, 1));
}

int getNumber(int modes) {
    factorization(modes);
    primesSieve(20000);
    int k = 0;
    int number = 1;
    for (int i = 0; i < exps.size(); ++ i) {
        while(exps[i].second) {
            number *= (pow(primes[k], exps[i].first - 1));
            ++ k;
            -- exps[i].second;
        }
    }
    return number;
}

int main() {
    freopen("consecutive.in", "r", stdin);
    freopen("consecutive.out", "w", stdout);
    long N;
    scanf("%ld", &N);
    int nr = getNumber(N + 1);
    printf("%d\n", nr);

    sn = 2 * sqrt(nr);
    for(L = 2; L <= sn; ++ L) {
        n = 2 * nr + L * L + L;
        if(n % (2 * L) == 0) {
            x = (2 * nr - (L * L - L)) / (2 * L);
            if(x > 0) {
                stanga[k++] = x;
                lungime[k - 1] = L;
            }
        }
    }

    for(i = 0; i < k; ++i) {
        printf("%lld\n", 1LL * (lungime[i]));
    }

    return 0;
}
