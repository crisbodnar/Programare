#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

#define newn a[x][i]
#define newn2 b[x][i]

using namespace std;

ifstream fin("pm2.in");
ofstream fout("pm2.out");

const int N = 105;

int n, s, d, timp[N], erl[N], lat[N];
vector <int> a[N], b[N];
queue <int> q;
vector <bool> inq(N);

void Erli()
{
    for(int i=1; i<=n; i++)
    {
        lat[i] = 0x3f3f3f3f;
        if(!a[i].size())
        {
            a[i].push_back(d);
            b[d].push_back(i);
        }
    }

    q.push(s);
    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(unsigned i=0; i<a[x].size(); i++)
        {
            erl[newn] = max(erl[newn], erl[x] + timp[x]);
            if(!inq[newn]) inq[newn] = 1, q.push(newn);
        }
    }
}

void Late()
{
    q.push(d); lat[d] = erl[d];
    inq.assign(n+2, 0);

    while(!q.empty())
    {
        int x = q.front(); q.pop();
        inq[x] = 0;
        for(unsigned i=0; i<b[x].size(); i++)
        {
            lat[newn2] = min(lat[newn2], lat[x] - timp[newn2]);
            if(!inq[newn2]) inq[newn2] = 1, q.push(newn2);
        }
    }
}

int main()
{
    fin>>n;
    s = 0, d = n + 1;
    for(int i=1; i<=n; i++)
        fin>>timp[i];
    for(int i=1; i<=n; i++)
    {
        int nrk; fin>>nrk;
        if(!nrk)
        {
            a[s].push_back(i);
            b[i].push_back(s);
        }
        for(int j=1; j<=nrk; j++)
        {
            int k; fin>>k;
            a[k].push_back(i);
            b[i].push_back(k);
        }
    }

    Erli();
    Late();

    fout<<erl[d]<<'\n';
    for(int i=1; i<=n; i++)
        fout<<erl[i]<<' '<<lat[i]<<'\n';
    return 0;
}
