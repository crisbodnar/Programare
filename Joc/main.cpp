#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("joc.in");
ofstream fout("joc.out");

const int M = 5000;
const int K = 11;
const int oo = 0x3f3f3f3f;
const int dx[] = {1, 0}, dy[] = {0, -1};
const int dx2[] = {-1, 0}, dy2[] = {0, -1};
int n, k, a[2][M], dp[2][M][K];


int Comp(int i, int j, int c)
{
    if(dp[i][j][c] != oo) return dp[i][j][c];
    else
    if(i == 2)
    {
        if(c == 1)
        for(int t=2; t<=k; t++)
            dp[i][j][c] = min(dp[i][j][c], Comp(1, j, t));
        if(c > 1) dp[i][j][c] = min(dp[i][j][c], Comp(i, j-1, c-1));
        dp[i][j][c] += a[i][j];
    }
    else
    {
        if(c == 1)
        for(int t=2; t<=k; t++)
            dp[i][j][c] = min(dp[i][j][c], Comp(2, j, t));
        if(c > 1) dp[i][j][c] = min(dp[i][j][c], Comp(i, j-1, c-1));
        dp[i][j][c] += a[i][j];
    }
    return dp[i][j][c];
}

int main()
{
    fin>>n>>k;
    for(int i=1; i<=2; i++)
        for(int j=1; j<=n; j++)
            fin>>a[i][j];

    for(int i=1; i<=2; i++)
        for(int j=1; j<=n; j++)
            for(int t=1; t<=k; t++)
                dp[i][j][t] = oo;
    dp[1][1][1] = a[1][1];
    for(int i=1; i<=k; i++)
        Comp(2, n, i);
    int sol = oo;
    for(int i=1; i<=k; i++)
        sol = min(sol, dp[2][n][i]);
    cout<<sol;
    return 0;
}
