#include <bits/stdc++.h>
using namespace std;
ifstream in("matop.in");
ofstream out("matop.out");
int lin[100002],col[100002],n,k;
int main()
{
    in>>n>>k;
    int diagSum=0;
    for(;k;k--)
    {
        int t,x,y,z;
        in>>t;
        if(t==1)
        {
            in>>x>>z;
            if(lin[x] < z)
            {
                if(z > max(lin[x],col[x]))
                {
                    diagSum-=max(lin[x],col[x]);
                    diagSum+=z;
                }
                lin[x]=z;
            }
        }
        else if(t==2)
        {
            in>>y>>z;
            if(col[y] < z)
            {
                if(z > max(lin[y],col[y]))
                {
                    diagSum-=max(lin[y],col[y]);
                    diagSum+=z;
                }
                col[y]=z;
            }
        }
        else if(t==3)
        {
            in>>x>>y;
            out<<max(lin[x],col[y])<<'\n';
        }
        else if(t==4)
        {
            out<<diagSum<<'\n';
        }
    }
    return 0;
}
