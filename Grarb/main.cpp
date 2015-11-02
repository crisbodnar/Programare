#include <iostream>
#include <fstream>
#include <vector>

#define N 100005

using namespace std;

ifstream fin("grarb.in");
ofstream fout("grarb.out");

int n, m, conex;
vector <int> a[N];
vector <bool> viz(N);

void dfs(int x)
{
    viz[x] = 1;
    for(unsigned i=0; i<a[x].size(); i++)
        if(!viz[a[x][i]]) dfs(a[x][i]);
}

int main()
{
    fin>>n>>m;
    for(int i=0; i<m; i++)
    {
        int x, y;
        fin>>x>>y;
        a[x].push_back(y);
        a[y].push_back(x);
    }

    for(int i=1; i<=n; i++)
        if(!viz[i])
            conex++, dfs(i);
    fout<<m+conex-n<<'\n'<<conex-1;
    return 0;
}
