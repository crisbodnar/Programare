#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("damesah.in");
ofstream fout("damesah.out");

const int Nmax = 14;

int N, Queen[Nmax], sol;
bool C[Nmax], MD[Nmax * 2], SD[Nmax * 2];

void Back(int K)
{
    if(K == N + 1)
    {
        if(!sol)
        {
            for(int i = 1; i <= N; i++)
                fout << Queen[i] << ' ';
        }
        sol++;
    }
    else
    {
        for(int i = 1; i <= N; i++)
            if(!C[i] && !MD[K - i + N] && !SD[K + i])
            {
                C[i] = MD[K - i + N] = SD[K + i] = 1;
                Queen[K] = i;
                Back(K + 1);
                C[i] = MD[K - i + N] = SD[K + i] = 0;
            }
    }
}

int main()
{
    fin >> N;
    Back(1);
    fout << '\n' << sol;
    return 0;
}
