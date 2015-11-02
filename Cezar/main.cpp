#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

#define ff first
#define ss second
#define newn a[x.ss][i]

using namespace std;

ifstream fin("cezar.in");
ofstream fout("cezar.out");

const int N = 10005;

int n, k, senat, tot;
typedef pair <short, short> nod;
priority_queue <nod, vector<nod>, greater<nod> > h;
vector <short> a[N];
vector <short> cost(N, 1);
vector <bool> uz(N, 0);

void dfs(int x, int lev)
{
    tot += lev;
    uz[x] = 0;
    for(unsigned i=0; i<a[x].size(); i++)
        if(uz[a[x][i]]) dfs(a[x][i], lev+1);
}

int main()
{
    fin>>n>>k;
    for(int i=1; i<n; i++)
    {
        int x, y;
        fin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    for(int i=1; i<=n; i++)
        if(a[i].size() == 1)
            h.push(nod(1, i));

    while(!h.empty())
    {
        nod x = h.top(); h.pop(); uz[x.ss] = 1;
        for(unsigned i=0; i<a[x.ss].size(); i++)
        if(!uz[newn])
        {
            cost[newn] += cost[x.ss];
            short sters = 0;
            for(unsigned j=0; j<a[newn].size(); j++)
                if(uz[a[newn][j]]) sters++;
            if(a[newn].size() - sters == 1) h.push(nod(cost[newn], newn));
        }
        senat = x.ss;
    }

    dfs(senat, 0);
    int rez = 0;
    sort(cost.begin(), cost.begin()+n+1);
        for(int i=n-1; i>=n-k; i--)
            rez += cost[i];


    fout<<tot-rez;
    return 0;
}
