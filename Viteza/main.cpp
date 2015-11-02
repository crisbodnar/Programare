#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>

#define newn a[x][i]

using namespace std;

ifstream fin("viteza.in");
ofstream fout("viteza.out");

const int Nmax = 100100;
const int Emax = Nmax * 3;
const int LG = 25;

int N, M, nr, n, euler[Emax], h[Emax], first[Nmax], lg[Emax],
rmq[LG][Emax], sol[Nmax], arb[Emax], viteza[Nmax], liniar[Emax], ffirst[Nmax], last[Nmax];
vector <int> a[Nmax];
vector <bool> viz(Nmax);

struct intersectie{
    int v, poz;
}vit[Nmax];

struct queryuri{
    int x, y, k, poz;
}query[Nmax];

bool cmp(const intersectie a, const intersectie b)
{
    return a.v < b.v;
}

bool cmp2(const queryuri a, const queryuri b)
{
    return a.k < b.k;
}

void DFS(int x, int lev)
{
    viz[x] = 1;
    liniar[++n] = x;
    euler[++nr] = x;
    h[nr] = lev;
    first[x] = nr;
    ffirst[x] = n;
    for(unsigned i=0; i<a[x].size(); i++)
        if(!viz[newn])
        {
            DFS(newn, lev + 1);
            liniar[++n] = x;
            euler[++nr] = x;
            h[nr] = lev;
        }
    if(x != 1 && a[x].size() == 1)
        liniar[++n] = x;
    last[x] = n;
}

void RMQ()
{
    for(int i=2; i<=nr; i++)
        lg[i] = lg[i>>1] + 1;
    for(int i=1; i<=nr; i++)
        rmq[0][i] = i;
    for(int i=1; (1 << i) <= nr; i++)
        for(int j=1; j + (1 << i) <= nr; j++)
        {
            const int lu = 1 << (i-1);
            rmq[i][j] = rmq[i-1][j];
            if(h[rmq[i][j]] > h[rmq[i-1][j+1]])
                rmq[i][j] = rmq[i-1][j+1];
        }
}

int LCA(int x, int y)
{
    x = first[x], y = first[y];
    if(x > y) swap(x, y);
    const int lu = lg[y-x+1];
    int poz = rmq[lu][x];
    if(h[poz] > h[rmq[lu][y-(1<<lu)+1]])
        poz = rmq[lu][y-(1<<lu)+1];
    return euler[poz];
}

void Push(int poz, int val)
{
    while(poz <= n)
    {
        arb[poz] += val;
        poz += (poz^(poz-1)) & poz;
    }
}

void Insert_AIB(int c)
{
    int nod = vit[c].poz;
    Push(ffirst[nod], 1);
    Push(last[nod], -1);
}

int Sum(int poz)
{
    int rez = 0;
    while(poz)
    {
        rez += arb[poz];
        poz -= (poz^(poz-1)) & poz;
    }
    return rez;
}

int main()
{
    fin>>N>>M;
    for(int i=1; i < N; i++)
    {
        int x, y; fin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }

    DFS(1, 0); RMQ();

    for(int i=1; i<=N; i++)
    {
        fin>>vit[i].v;
        vit[i].poz = i;
        viteza[i] = vit[i].v;
    }

    for(int i=1; i<=M; i++)
    {
        fin>>query[i].x>>query[i].y>>query[i].k;
        query[i].poz = i;
    }

    sort(vit + 1, vit + N + 1, cmp);
    sort(query + 1, query + M + 1, cmp2);

    int lastk = -1, con = 1;
    for(int i=1; i<=M; i++)
    {

        while(vit[con].v <= query[i].k && con <= N)
        {
                Insert_AIB(con);
                con++;
        }

        int sum = 0;
        int x = query[i].x, y = query[i].y;

        int lca = LCA(x, y);
        if(x != y) sum = Sum(ffirst[x]) + Sum(ffirst[y]) - 2 * Sum(ffirst[lca]);

        if(viteza[lca] <= query[i].k) sum++;
        sol[query[i].poz] = sum;
    }

    for(int i=1; i<=M; i++)
        fout<<sol[i]<<'\n';
    return 0;
}
