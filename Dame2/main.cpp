#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("dame2.in");
ofstream fout("dame2.out");

const int Nmax = 12;
const int oo = 0x3f3f3f3f;
const int N = 8;

int Queen[Nmax], SOL[Nmax], best = oo;
char M[Nmax][Nmax];
bool C[Nmax], L[Nmax], MD[Nmax * 2], SD[Nmax * 2];

bool OK()
{
    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= N; j++)
            if(M[i][j] == '0')
                if(!(L[i] || C[j] || MD[i - j + N] || SD[i + j]))
                    return 0;
    return 1;
}

void Back(int K, int nr)
{
    if(K == N + 1)
    {
        if(OK() && nr < best)
        {
            best = nr;
            for(int i = 1; i <= N; i++)
                SOL[i] = Queen[i];
        }
    }
    else
    {

        for(int i = 1; i <= N; i++)
            if(M[K][i] == '0' && !C[i] && !MD[K - i + N] && !SD[K + i])
            {
                C[i] = L[K] = MD[K - i + N] = SD[K + i] = 1;
                Queen[K] = i;
                Back(K + 1, nr + 1);
                C[i] = L[K] = MD[K - i + N] = SD[K + i] = 0;
            }

        Queen[K] = 0;
        Back(K + 1, nr);
    }
}

int main()
{
    for(int i = 1; i <= N; i++)
        fin.getline(M[i] + 1, Nmax);
    Back(1, 0);
    fout << best << '\n';
    for(int i = 1; i <= N; i++)
        if(SOL[i])
            fout << i << ' ' << SOL[i] << ' ';
    return 0;
}
