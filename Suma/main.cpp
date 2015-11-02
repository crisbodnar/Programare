#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("suma.in");
ofstream fout("suma.out");

const int N = 70;
const int K = 50;

short a[N][N][N];
short d[N][N][N];
short nr[N][N][N];
vector <short> sol;
int n;

const short dx[] = {0, 0, 1, 1},
            dy[] = {0, 1, 0, 1};

int main()
{
    fin>>n;
    int nn = 0, nrc = 0;
    for(int i=0; i<=n; i += nn*nn)
    {
        nn++;
        for(int ii = 1; ii <= nn; ii++)
            for(int jj=1; jj <= nn; jj++)
            {
                nrc++;
                fin>>a[nn][ii][jj];
                //cout<<a[nn][ii][jj]<<' ';
                nr[nn][ii][jj] = nrc;
            }
    }

    short int camera = 70000, nrcamera;
    for(int i=1; i<=nn; i++)
        for(int j=1; j<=nn; j++)
        {
            d[nn][i][j] = a[nn][i][j];
            if(d[nn][i][j] < camera)
            {
                camera = d[nn][i][j];
                nrcamera = nr[nn][i][j];
            }
        }
    sol.push_back(nrcamera);

    int niv = --nn;
    for(int k=niv; k>0; k--)
    {
        camera = 70000;
        for(int i=1; i<=nn; i++)
            for(int j=1; j<=nn; j++)
            {
                short int mini = 600000;
                for(int kk=0; kk<4; kk++)
                    mini = min(mini, d[nn+1][i+dx[kk]][j+dy[kk]]);
                d[nn][i][j] = a[nn][i][j] + mini;
                if(d[nn][i][j] < camera)
                {
                    camera = d[nn][i][j];
                    nrcamera = nr[nn][i][j];
                }
            }
        sol.push_back(nrcamera);
        nn--;
    }

    fout<<d[1][1][1]<<'\n';
    for(int i=sol.size()-1; i>=0; i--)
        fout<<sol[i]<<' ';
    return 0;
}
