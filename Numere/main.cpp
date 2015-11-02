#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin("numere.in");
ofstream fout("numere.out");

const int oo = 0x3f3f3f3f;
long long a, b, sol[11], fr[11], power[11][14], fact[115], raspuns;

void Precomp()
{
    for(int i=1; i<=9; i++)
    {
        power[i][0] = 1;
        power[i][1] = i;
        for(int j=2; j<=13; j++)
            power[i][j] = i * power[i][j-1];
    }

    fact[1] = fact[0] = 1;
    for(int i=2; i<=100; i++)
        fact[i] = i * fact[i-1];
}

void Solve()
{
    long long rez = fact[b];
    for(int i=1; i<=9; i++)
        rez /= fact[sol[i]];
    raspuns += fact[rez];
}

void Back(int k, int prod, int sum)
{
    if(k > 9)
        if(sum == a)
            if(prod == b) Solve();
            else;
        else;
    else
    {
        for(int i=0; i<=fr[k]; i++)
            if(prod * power[k][i] <= b)
                if(sum + i <= a)
                {
                    sol[k] = i;
                    prod = prod * power[k][i];
                    sum += i;
                    Back(k+1, prod, sum);
                }
    }
}

int main()
{
    fin>>a>>b;
    Precomp();
    if(b%2 == 0)
            while(!(b&1))
            {
                fr[2]++;
                b /= 2;
            }

        for(int i=3; i < 10 ; i += 2)
            if(b % i == 0)
            {
                while(b % i == 0)
                {
                    fr[i]++;
                    b /= i;
                }
            }
    if(b != 1)
    {
        fout<<0;
        return 0;
    }

    fr[1] = a - fr[2] - fr[3] - fr[5] - fr[7];
    fr[4] = fr[2] / 2;
    fr[6] = min(fr[2], fr[3]);
    fr[9] = fr[3] / 2;
    fr[8] = fr[2] / 3;

    Back(1, 1, 0);
    fout<<raspuns;

    return 0;
}
