#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

#define ff first.first
#define fs first.second
#define newn a[x][i]

ifstream fin("banana.in");
ofstream fout("banana.out");

const int N = 16010;

typedef pair <short, short> nod;
typedef pair <nod, short> banana;
vector <short> a[N];
vector <bool> viz(N);
vector <banana> ban1, ban2;
priority_queue <short> zone;
int n, k, nr, nrc;


void dfs(int x)
{
    viz[x] = 1; nrc++;
    for(unsigned i=0; i<a[x].size(); i++)
        if(!viz[newn]) dfs(newn);
}

int main()
{
    fin>>n>>k;
    for(int i=1; i<=n; i++)
    {
        int x, y;
        fin>>x>>y; nr++;
        ban1.push_back(banana(nod(x, y), nr));
        ban2.push_back(banana(nod(y, x), nr));
    }
    sort(ban1.begin(), ban1.end());
    sort(ban2.begin(), ban2.end());
    for(size_t i=0 ; i<ban1.size()-1; i++)
    {
        if(ban1[i].ff == ban1[i+1].ff)
            if(ban1[i].fs == ban1[i+1].fs - 1)
            {
                a[ban1[i].second].push_back(ban1[i+1].second);
                a[ban1[i+1].second].push_back(ban1[i].second);
            }
        if(ban2[i].ff == ban2[i+1].ff)
            if(ban2[i].fs == ban2[i+1].fs - 1)
            {
                a[ban2[i].second].push_back(ban2[i+1].second);
                a[ban2[i+1].second].push_back(ban2[i].second);
            }
    }

    for(int i=1; i<=nr; i++)
        if(!viz[i])
        {
            nrc = 0;
            dfs(i);
            zone.push(nrc);
        }
    int sol = 0;
    while(k--)
    {
        sol += zone.top();
        zone.pop();
    }
    fout<<sol;

    return 0;
}
