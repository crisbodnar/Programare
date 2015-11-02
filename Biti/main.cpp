#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

ifstream fin("biti.in");
ofstream fout("biti.out");

const int N = (1 << 20) + 100;

int n, nr, x[N], nod, nod1, nod2, lim;
vector <bool> uz(N);
vector <int> a[N];
bool done = 0;

void Back(int k)
{
    if(done) return;
    else if(k == lim + 1) {done = 1; return;}
    else
    {
        int nod = x[k-1];
        if(k == lim)
        {
            for(int j=0; j<2; j++)
            {
                int nodd = a[nod][j];
                if(!uz[nodd])
                for(int i=0; i<2; i++)
                    if(!a[nodd][i])
                    {
                        x[k] = nodd;
                        Back(k+1);
                        break;
                    }
            }
        }
        else
        {
            for(int i=0; i<2; i++)
                if(!uz[a[nod][i]])
                {
                    x[k] = a[nod][i];
                    uz[a[nod][i]] = 1;
                    Back(k+1);
                    uz[a[nod][i]] = 0;
                }
        }
    }
}

int main()
{
    fin>>n;
    lim = (1 << n);
    for(int i=0; i<lim; i++)
    {
        int x = (i << 1);
        if(x >= lim) x -= lim;
        a[i].push_back(x);
        a[i].push_back((x|1));
    }

    x[1] = 0; x[2] = 1;
    uz[0] = uz[1] = 1;

    Back(3);

    fout<<(1<<n) + (n-1)<<'\n';
    for(int i=1; i<n; i++) fout<<"0";
    for(int i=1; i<=(1<<n); i++)
        fout<<(x[i]&1);
}
