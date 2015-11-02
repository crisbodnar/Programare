#include <iostream>
#include <fstream>
#include <iomanip>

#define x first
#define y second

using namespace std;

ifstream fin("aria.in");
ofstream fout("aria.out");

const int N = 100005;

int n;
long double arie;
typedef pair <long double, long double> punct;
punct p0, p1, p[N];

inline long double Arie(punct p2, punct p3)
{
    return((p2.x - p0.x) * (p3.y - p0.y) - (p3.x - p0.x) * (p2.y-p0.y));
}

int main()
{
    fin>>n;

    long double c1, c2;
    fin>>c1>>c2;
    p0 = punct(c1, c2);
    fin>>c1>>c2;
    p1 = punct(c1, c2);

    for(int i=3; i<=n; i++)
    {
        fin>>p[i].x>>p[i].y;
        arie += Arie(p1, p[i]);
        p1 = p[i];
    }
    arie /= 2.0;
    fout<<setprecision(6)<<fixed<<arie;
    return 0;
}
