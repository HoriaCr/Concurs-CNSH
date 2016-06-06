#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define INF numeric_limits<int>::max()
#define int64 long long
#define lsb(x) (x)&(-x)
using namespace std;
ifstream in("forcoding.in");
ofstream out("forcoding.out");
int n,a[10002],lf[10002],rt[10002],dp[10002];
int main()
{
    in>>n;
    for(int i=1;i<=n;i++)
        in>>a[i];
    for(int i=1;i<=n;i++)
        in>>lf[i];
    for(int i=1;i<=n;i++)
        in>>rt[i];
    for(int i=1;i<=n;i++)
    {
        int x=0;
        for(int j=1;j<i-lf[i];j++)
        if(dp[j]>dp[x] && j+rt[j]<i)
            x=j;
        dp[i]=dp[x]+a[i];
    }
    int sol=0;
    for(int i=1;i<=n;i++)
        sol=max(sol,dp[i]);
    out<<sol<<'\n';
    return 0;
}
