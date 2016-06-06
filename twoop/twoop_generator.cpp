#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
using namespace std;

#define NMAX 100010
#define BILLION 1000000000

int n_lim[] = {10, 100, 500, 30000, 35000, 40000, 50000, 75000, 100000, 100000};
int nrOp1_lim[] = {100, 250, 500, 1000, 2500, 5000, 10000, 25000, 50000, 100000};
int nrOp2_lim[] = {10, 25, 100, 500, 1750, 3500, 7000, 15000, 45000, 90000};
mt19937 generator(time(0));

int generateInRange(int minim, int maxim)
{
    return uniform_int_distribution<int>(minim, maxim)(generator);
}

void generate_in(string filename, int test)
{
    int n, nrOp1, nrOp2, st, dr, val;

    ofstream g(filename);

    n = n_lim[test];
    g<<n_lim[test]<<" ";
    g<<nrOp1_lim[test]<<" ";
    g<<nrOp2_lim[test]<<'\n';
    for (int i = 1;i <= n_lim[test];i++)
        g<<generateInRange(-BILLION, BILLION)<<" ";
    g<<'\n';
    for (int i = 1;i <= nrOp1_lim[test];i++)
    {
        st = generateInRange(1, n);
        dr = generateInRange(1, n);
        if (st > dr) swap(st, dr);
        g<<st<<" "<<dr<<" "<<generateInRange(-BILLION, BILLION)<<'\n';
    }
    for (int i = 1;i <= nrOp2_lim[test];i++)
    {
        g<<generateInRange(1, n)<<'\n';
    }
    g.close();
}

void generate_out(string infile, string outfile, int test)
{
    int n, nrOp1, nrOp2, st, dr, val, poz;
    long long v[NMAX], res[NMAX];

    ifstream f(infile);
    ofstream g(outfile);
    f>>n>>nrOp1>>nrOp2;
    for (int i = 0;i <= n;i++)
        res[i] = 0;
    for (int i = 1;i <= n;i++)
        f>>v[i];
    for (int i = 1;i <= nrOp1;i++)
    {
        f>>st>>dr>>val;
        res[st] += val;
        res[dr + 1] -= val;
    }
    for (int i = 1;i <= n;i++)
        res[i] += res[i - 1];
    for (int i = 1;i<= nrOp2;i++)
    {
        f>>poz;
        g<<v[poz] + res[poz]<<'\n';
    }
    f.close();
    g.close();
}

int main()
{
    string name = "teste/twoop";
    string infile;
    string outfile;
    string number;
    for (int i = 0;i < 10;i++)
    {
        if (i == 0) number = string("0");
        if (i == 1) number = string("1");
        if (i == 2) number = string("2");
        if (i == 3) number = string("3");
        if (i == 4) number = string("4");
        if (i == 5) number = string("5");
        if (i == 6) number = string("6");
        if (i == 7) number = string("7");
        if (i == 8) number = string("8");
        if (i == 9) number = string("9");

        infile = name + number + ".in";
        outfile = name + number + ".ok";

        generate_in(infile, i);
        generate_out(infile, outfile, i);

        cout<<infile<<" "<<outfile<<'\n';
    }
}
