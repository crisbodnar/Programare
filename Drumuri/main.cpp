#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define newn a[x][i]

using namespace std;

ifstream fin("drumuri.in");
ofstream fout("drumuri.out");

const int N = 10105;

int n, m, t[N], corect[N];
vector <int> a[N], nod, n1, n2, n3;
vector <bool> sters(N), viz(N);

void Dfs(int x)
{
    viz[x] = 1; int vecini = 0, poz;
    for(unsigned i=0; i<a[x].size(); i++)
        if(!viz[newn])
        {
            t[newn] = x;
            Dfs(newn);
        }
    nod.clear();
    for(unsigned j=0; j<a[x].size(); j++)
    {
        if(a[x][j] == t[x]) poz = j;
        if(!sters[a[x][j]]) nod.push_back(a[x][j]), vecini++;
    }
    if(corect[x]) vecini++, nod.push_back(corect[x]);
    if(vecini % 2 == 0)
    {
        sters[x] = 1;
        for(unsigned j=0; j<nod.size(); j+=2)
            n1.push_back(nod[j]), n2.push_back(x), n3.push_back(nod[j+1]);
    }
    else
    {
        sters[x] = 1; corect[t[x]] = x;
        swap(nod[poz], nod[nod.size()-1]); nod.pop_back();
        for(unsigned j=0; j<nod.size(); j+=2)
            n1.push_back(nod[j]), n2.push_back(x), n3.push_back(nod[j+1]);
    }
    nod.clear();
}

int main()
{
    fin>>n>>m;
    for(int i=1; i<=m; i++)
    {
        int x, y;
        fin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }

    if(m%2 == 0) Dfs(1);
    else
    {
        fout<<0; return 0;
    }

    fout<<1<<'\n';
    for(unsigned i=0; i<m/2; i++)
        fout<<n1[i]<<' '<<n2[i]<<' '<<n3[i]<<'\n';
    return 0;
}
