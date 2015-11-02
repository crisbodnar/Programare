#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define fiu1 (nod << 1)
#define fiu2 (fiu1 + 1)
#define mid ((st + dr) >> 1)

using namespace std;

ifstream fin("scmax.in");
ofstream fout("scmax.out");

const int Nmax = 100010;

int N, bestmax, pozbest, poz, val, v[Nmax], best[Nmax], t[Nmax];

struct arbore{
    int v, best;
    arbore(){v = best = 0;}
}arb[Nmax * 3 + 100];

void Update(int nod, int st, int dr)
{
    if(st == dr)
    {
        arb[nod].v = v[poz];
        arb[nod].best = best[poz];
        return;
    }

    if(poz <= mid) Update(fiu1, st, mid);
    else Update(fiu2, mid + 1, dr);

    if(arb[fiu1].best > arb[fiu2].best)
    {
        arb[nod].best = arb[fiu1].best;
        arb[nod].v = arb[fiu1].v;
    }
    else
    {
        arb[nod].best = arb[fiu2].best;
        arb[nod].v = arb[fiu2].v;
    }
}

void Find(int nod, int st, int dr, int left, int right)
{
    if(st > right || dr < left) return;

    if(left <= st && dr <= right && arb[nod].v < val)
    {
        if(bestmax < arb[nod].best)
        {
            bestmax = arb[nod].best;
            pozbest = st;
        }
        return;
    }

    Find(fiu1, st, mid, left, right);
    Find(fiu2, mid + 1, dr, left, right);
}

void Afisare(int poz)
{
    if(!poz) return;
    Afisare(t[poz]);
    fout<<v[poz]<<' ';
}

int main()
{
    fin>>N;
    for(int i=1; i<=N; i++)
        fin>>v[i];
    best[1] = 1; poz = 1; Update(1, 1, N);
    for(int i=2; i<=N; i++)
    {
        poz = i; val = v[i];
        Find(1, 1, N, 1, poz - 1);
        best[i] = bestmax + 1;
        t[i] = pozbest;
        Update(1, 1, N);
    }

    int sol = 0;
    for(int i=1; i<=N; i++)
        if(sol < best[i])
        {
            sol = best[i];
            pozbest = i;
        }
    fout<<sol<<'\n';
    //Afisare(pozbest);
    return 0;
}
