#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

ifstream fin("arbciclu.in");
ofstream fout("arbciclu.out");

const int N = 100110;

int t, n, m;
set <int> a[N];
queue <int> q;
vector <bool> uz(N), viz(N);

void dfs(int x)
{
    viz[x] = 1;
    set <int> :: iterator newn = a[x].begin();
    for(; newn != a[x].end(); newn++)
        if(!viz[*newn]) dfs(*newn);
}

int main()
{
    fin>>t;
    while(t--)
    {
        fin>>n>>m;
        while(m--)
        {
            int x, y;
            fin>>x>>y;
            a[x].insert(y);
            a[y].insert(x);
        }

        bool ok = 0; dfs(1);
        for(int i=1; i<=n; i++)
            if(a[i].size() == 2) q.push(i);
            else if(a[i].size() < 2 || !viz[i])
            {
                fout<<"NO\n";
                for(int i=1; i<=n; i++)
                    a[i].clear();
                while(!q.empty()) q.pop();
                ok = 1;
                break;
            }
        if(ok) continue;
        while(!q.empty())
        {
            int x = q.front(); q.pop();
            if(a[x].size() != 2) continue; uz[x] = 1;
            set <int> :: iterator newn1 = a[x].begin(), newn2 = a[x].begin(); newn2++;
            a[*newn1].erase(x); a[*newn2].erase(x);
            a[x].erase(*newn1); a[x].erase(*newn2);
            if(!a[*newn1].count(*newn2))
            {
                a[*newn1].insert(*newn2);
                a[*newn2].insert(*newn1);
            }
            if(a[*newn1].size() == 2) q.push(*newn1);
            if(a[*newn2].size() == 2) q.push(*newn2);
        }

        int nrn = 0;
        for(int i=1; i<=n; i++)
        {
            if(!uz[i]) nrn++;
            a[i].clear();
        }
        if(nrn == 2 && n >= 3) fout<<"YES\n";
        else fout<<"NO\n";
    }
    return 0;
}
