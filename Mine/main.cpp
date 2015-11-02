#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>

#define cc first
#define nn second

using namespace std;

const int N = 10005;
const int E = 1000005;
const int inf = (1 << 30);

ifstream fin("mine.in");
ofstream fout("mine.out");

int n, m, e, maxi;
typedef pair <long long, int> nod;
vector <nod> a[N], w;
vector <int> d(N, inf);
vector <bool> viz(N, 0);
priority_queue <nod, vector<nod> , greater<nod> > h;

int bs(int val, int st)
{
    int dr = e, m;
    while(dr - st > 1)
    {
        m = (st + dr) / 2;
        if(val <= w[m].cc) dr = m;
        else st = m;
    }
    return w[dr].nn;
}

void Dijkstra()
{
    int stau;
    h.push(nod(0, 1)); d[1] = 1;
    while(!h.empty() && !viz[n])
    {
        int x = h.top().nn; h.pop();
        viz[x] = 1;
            for(unsigned i=0; i<a[x].size(); i++)
            if(!viz[a[x][i].nn])
            {
                int newn = a[x][i].nn; long cost = a[x][i].cc;
                if(cost <= w[d[x]].cc)
                    if(d[newn] > d[x] + 1)
                    {
                        d[newn] = d[x] + 1;
                        h.push(nod(d[newn], newn));
                    }
                    else;
                else if(cost <= w[e].cc)
                {
                    stau = bs(cost, d[x]);
                        if(d[newn] > stau)
                        {
                            d[newn] = stau;
                            h.push(nod(d[newn], newn));
                        }
                }
            }
    }
}

int main()
{
    fin>>n>>m;
    while(m--)
    {
        int x, y, c;
        fin>>x>>y>>c;
        a[x].push_back(nod(c, y));
        a[y].push_back(nod(c, x));
    }
    fin>>e; long x;
    w.push_back(nod(0, 0));
    for(int i=1; i<=e; i++){
        fin>>x;
        w.push_back(nod(x, i));
    }
    sort(w.begin()+1, w.end());

    Dijkstra();
    fout<<d[n];

    return 0;
}
