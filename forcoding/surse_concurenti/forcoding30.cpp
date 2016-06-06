#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define INF numeric_limits<int>::max()
#define int64 long long
#define lsb(x) (x)&(-x)
using namespace std;
ifstream in("forcoding.in");
ofstream out("forcoding.out");
int n,a[10002],lf[10002],rt[10002],dp[10002],sol;
int st[10002];
bool valid(int k)
{
    for(int i=1;i<k;i++)
    if((st[i]-lf[ st[i] ] <= st[i-1] && i-1!=0) || (st[i]+rt[ st[i] ] >=st[i+1] && i+1!=k))
        return false;
    return true;
}
void backtrack(int k,int sum,int pos)
{
    if(k!=1)
    {
        if(valid(k))
            sol=max(sol,sum);
    }
    if(k+1<=n)
    for(int i=pos+1;i<=n;i++)
    {
        st[k]=i;
        backtrack(k+1,sum+a[i],i);
    }
}
int main()
{
    in>>n;
    for(int i=1;i<=n;i++)
        in>>a[i];
    for(int i=1;i<=n;i++)
        in>>lf[i];
    for(int i=1;i<=n;i++)
        in>>rt[i];
    backtrack(1,0,0);
    out<<sol<<'\n';
    return 0;
}
