#include <bits/stdc++.h>
//40p
using namespace std;
ifstream in("matop.in");
ofstream out("matop.out");
int n,k,mat[120][120];
int main()
{
    in>>n>>k;
    for(;k;k--)
    {
        int t,x,y,z;
        in>>t;
        if(t==1)
        {
            in>>x>>z;
            for(int i=1;i<=n;i++)
            if(mat[x][i] < z)
                mat[x][i]=z;
        }
        else if(t==2)
        {
            in>>y>>z;
            for(int i=1;i<=n;i++)
            if(mat[i][y] < z)
                mat[i][y]=z;
        }
        else if(t==3)
        {
            in>>x>>y;
            out<<mat[x][y]<<'\n';
        }
        else if(t==4)
        {
            int S=0;
            for(int i=1;i<=n;i++)
                S+=mat[i][i];
            out<<S<<'\n';
        }
    }
    return 0;
}

