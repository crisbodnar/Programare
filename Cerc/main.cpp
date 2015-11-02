#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#define xx first.first
#define yy first.second
#define rr second

using namespace std;

ifstream fin("cerc.in");
ofstream fout("cerc.out");

const int N = 2000;

int n, raz[N];
double lim[N];
typedef pair <double, double> pct;
typedef pair <pct, int> cerc;
vector <cerc> c;


inline bool cmp(const cerc a, const cerc b)
{
        if(tg1 < tg2) return 1;
        else if(tg1 == tg2) return lim[a.rr] < lim[b.rr];
}

int main()
{
    fin>>n;
    for(int i=1; i<=n; i++)
    {
        int x, y, r;
        fin>>x>>y>>r;
        c.push_back(cerc(pct(x, y), i-1));
        raz[i-1] = r;
    }

    for(int i=0; i<n; i++)
    {
        double tg = (double)(c[i].yy / c[i].xx);
        double atg = atan(tg); double cs = cos(atg);
        lim[i] = cs * raz[i] + c[i].xx;
    }

    sort(c.begin(), c.end(), cmp);
    cout<<c[0].xx<<' '<<c[0].yy;
    return 0;
}
