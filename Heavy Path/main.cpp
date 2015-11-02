#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define newn a[x][i]
#define nodl lant[i][j]
#define mid ((st + dr) >> 1)
#define fiu1 (nod << 1)
#define fiu2 (fiu1 + 1)

using namespace std;

ifstream fin("heavypath.in");
ofstream fout("heavypath.out");

const int N = 100010;

int n, m, nrp = 1;
vector <int> a[N], lant[N], v(N), nrnod(N), height(N), place(N), tata(N), poz(N), arb(4*N);
vector <bool> viz(N), uz(N);

void update(int nod, int st, int dr, int poz, int val, int fix)
{
    if(st == dr)
    {
        arb[nod+fix] = val;
        return ;
    }
    if(poz <= mid)
        update(fiu1, st, mid, poz, val, fix);
    else
        update(fiu2, mid+1, dr, poz, val, fix);
    arb[nod+fix] = max(arb[fiu1 + fix], arb[fiu2 + fix]);
}

int query(int nod, int st, int dr, int a, int b, int fix)
{
    if(a <= st && dr <= b)
        return arb[nod+fix];
    int rez = 0;
    if(a <= mid) rez = max(rez, query(fiu1, st, mid, a, b, fix));
    if(b > mid) rez = max(rez, query(fiu2, mid+1, dr, a, b, fix));
    return rez;
}

void dfs(int x, int level)
{
    viz[x] = 1;
    nrnod[x]++;
    height[x] = level;
    for(unsigned i=0; i<a[x].size(); i++)
        if(!viz[newn])
        {
            dfs(newn, level+1);
            nrnod[x] += nrnod[newn];
        }
}

bool cmp(const int &a, const int &b){ return nrnod[a] > nrnod[b];}

void heavy_path(int x, int path)
{
    viz[x] = 0;
    place[x] = path;
    lant[path].push_back(x);
    for(unsigned i=0; i<a[x].size(); i++)
        if(viz[newn])
        {
            if(!uz[x])
            {
                uz[x] = 1;
                heavy_path(newn, path);
            }
            else
            {
                tata[++nrp] = x;
                heavy_path(newn, nrp);
            }
        }
}

int main()
{
    fin>>n>>m;
    for(int i=1; i<=n; i++)
        fin>>v[i];
    for(int i=1; i<n; i++)
    {
        int x, y;
        fin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }

    dfs(1, 1);
    for(int i=1; i<=n; i++)
        sort(a[i].begin(), a[i].end(), cmp);
    heavy_path(1, 1);
    for(int i=1; i<=nrp; i++)
    {
        poz[i] = poz[i-1] + lant[i-1].size() * 4;
        for(unsigned j=0; j<lant[i].size(); j++)
            update(1, 1, lant[i].size(), height[nodl] - height[tata[i]], v[nodl], poz[i]);
    }

    while(m--)
    {
        bool t; int x, y;
        fin>>t>>x>>y;
        if(!t) update(1, 1, lant[place[x]].size(), height[x] - height[tata[place[x]]], y, poz[place[x]]);
        else{
                int sol = -1;
                while(place[x] != place[y])
                {
                    if(height[tata[place[x]]] < height[tata[place[y]]]) swap(x, y);
                    sol = max (sol, query(1, 1, lant[place[x]].size(), 1, height[x] - height[tata[place[x]]], poz[place[x]]));
                    x = tata[place[x]];
                }
                if(height[x] < height[y]) swap(x, y);
                sol = max(sol, query(1, 1, lant[place[x]].size(), height[y] - height[tata[place[x]]], height[x] - height[tata[place[x]]], poz[place[x]]));
                fout<<sol<<'\n';
            }
    }
    return 0;
}
