#include <bits/stdc++.h>
using namespace std;
ofstream out("10-forcoding.in");
#define VALMAX 10000
int main()
{
    int n;
    cin>>n;
    srand (time(NULL));
    out<<n<<'\n';
    for(int i=1;i<=n;i++)
    {
        out<<rand()%VALMAX+1<<' ';
    }
    out<<'\n';
    for(int i=1;i<=n;i++)
    {
        out<<rand()%i<<' ';
    }
    out<<'\n';
    for(int i=1;i<=n;i++)
    {
        out<<rand()%(n-i+1)<<' ';
    }
    out<<'\n';
    return 0;
}

