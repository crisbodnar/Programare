#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("immortal.in");
ofstream fout("immortal.out");

const int N = 22;
const int NM = N * N;
const int dx[] = {0, 0, -1, 1},
          dy[] = {-1, 1, 0, 0};
const int dx2[] = {0, 0, 1, -1},
          dy2[] = {1, -1, 0, 0};
const int mx[] = {0, 0, 2, -2},
          my[] = {2, -2, 0, 0};

short n, m, I, xx[NM], yy[NM], sx[N], sy[N], sens[N], a[N][N];
bool stop = 0, uz[NM];

void Afisare()
{
    for(int i=1; i<I; i++)
    {
        fout<<sx[i]<<' '<<sy[i]<<' ';
        fout<<sx[i] + mx[sens[i]]<<' '<<sy[i] + my[sens[i]]<<'\n';
    }
}

void Back(short int k)
{
    if(stop) return;
    if(k == I)
    {
        stop = 1;
        Afisare();
        return;
    }
    else
    {
        for(int i=1; i<=I; i++)
            if(!uz[i])
            {
                int x = xx[i], y = yy[i];
                for(int t=0; t<4; t++)
                {
                    int xvec = x + dx[t], yvec = y + dy[t];
                    int xnou = x + dx2[t], ynou = y + dy2[t];
                    int nri = a[xvec][yvec];
                    if(a[xvec][yvec] > 0 && !a[xnou][ynou])
                    {
                        uz[i] = 1; a[x][y] = 0; sens[k] = t; xx[nri] += mx[t]; yy[nri] += my[t];
                        a[xnou][ynou] = nri; a[xvec][yvec] = 0; sx[k] = xvec, sy[k] = yvec;
                        Back(k+1);
                        uz[i] = 0; a[x][y] = i; xx[nri] -= mx[t]; yy[nri] -= my[t]; a[xnou][ynou] = 0;
                        a[xvec][yvec] = nri;
                    }
                }
            }
    }
}

void Bordare()
{
    for(int i=0; i<=n+1; i++)
        a[i][0] = a[i][m+1] = -1;
    for(int i=0; i<=m+1; i++)
        a[0][i] = a[n+1][i] = -1;
}

int main()
{
    fin>>n>>m>>I;
    for(int i=1; i<=I; i++)
    {
        int x, y;
        fin>>x>>y;
        a[x][y] = i;
        xx[i] = x; yy[i] = y;
    }


    Bordare();
    Back(1);
    return 0;
}
