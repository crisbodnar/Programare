#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define newn a[x][i]

using namespace std;

ifstream fin("iepuri.in");
ofstream fout("iepuri.out");

const int N = 105;

int rez;
short n, k, s, mmin[N], hmax[N], sol = 1;
vector <short> a[N];
vector <bool> t(N);

void dfs(int x, int lev)
{
    mmin[x] = lev;
    hmax[x] = lev;
    for(unsigned i=0; i<a[x].size(); i++)
    {
        dfs(newn, lev + 1);
        hmax[x] = max(hmax[x], hmax[newn]);
    }
}

int main()
{
    fin>>n>>k;
    for(int i=1; i<n; i++)
    {
        short x, y;
        fin>>x>>y;
        a[x].push_back(y);
        t[y] = 1;
    }

    for(int i=1; i<=n; i++)
        if(!t[i])
        {
            s = i;
            break;
        }

    dfs(s, 1);

    for(int i=1; i<=n; i++)
        if(mmin[i] != hmax[i])
        {
            int nr = k - hmax[i] + 1;
            if(nr > 0) sol *= nr;
            if(nr < 0) sol = 0;
        }
        else
        {
            int nr = k - mmin[i] + 1;
            if(nr) sol *= nr;
        }
    cout<<sol;
    return 0;
}
