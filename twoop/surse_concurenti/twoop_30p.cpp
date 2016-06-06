#include <fstream>
using namespace std;
ifstream f("twoop.in");
ofstream g("twoop.out");

#define NMAX 100010

int n, nrOp1, nrOp2, st, dr, val, poz;
long long v[NMAX];

int main()
{
    int i, j;
    f>>n>>nrOp1>>nrOp2;
    for (i = 1;i <= n;i++)
        f>>v[i];
    for (i = 1;i <= nrOp1;i++)
    {
        f>>st>>dr>>val;
        for (j = st;j <= dr;j++)
            v[j] += val;
    }
    for (i = 1;i <= nrOp2;i++)
    {
        f>>poz;
        g<<v[poz]<<'\n';
    }
}
