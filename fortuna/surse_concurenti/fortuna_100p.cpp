#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream f("fortuna.in");
ofstream g("fortuna.out");

#define NMAX 1010

int n, m, x, y, k, p, maxim;
int viz[NMAX];
vector<int> v[NMAX];
queue<int> q;

void bfs()
{
    int nod;
    vector<int>::iterator it;
    q.push(k);
    viz[k] = 1;
    while (!q.empty())
    {
        nod = q.front();
        q.pop();
        for (it = v[nod].begin();it != v[nod].end();it++)
            if (!viz[*it])
            {
                q.push(*it);
                viz[*it] = viz[nod] + 1;
            }
    }
}

int main()
{
    int i;
    f>>n>>m;
    for (i = 1;i <= m;i++)
    {
        f>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    f>>k>>p;
    bfs();
    for (i = 1;i <= n;i++)
    {
        if (!viz[i])
        {
            g<<-1;
            return 0;
        }
    }
    for (i = 1;i <= n;i++)
        if (viz[i] > maxim)
            maxim = viz[i];
    g<<maxim + p - 1;
}
