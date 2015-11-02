#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#define x first
#define y second

ifstream fin("patrate3.in");
ofstream fout("patrate3.out");

const double dif = 0.0001;

int n, sol;
typedef pair <double, double> punct;
vector <punct> a;
punct p1, p2;

inline double Abs(const double x)
{
    if(x < 0) return -x;
    return x;
}

inline bool Cmp(punct a, punct b)
{
    if(Abs(a.x - b.x) <= dif)
        return (a.y < b.y);
    return a.x < b.x;
}

inline bool Cb(punct p)
{
    int st = 0, dr = n-1, mid;
    while(st <= dr)
    {
        mid = (st + dr) >> 1;
        if(Abs(p.x - a[mid].x) <= dif && Abs(p.y - a[mid].y) <= dif)
            return 1;
        if(Cmp(p, a[mid]))
           dr = mid - 1;
        else
           st = mid + 1;
    }
    return 0;
}

int main()
{
    fin>>n;
    for(int i=1; i<=n; i++)
    {
        double xx, yy;
        fin>>xx>>yy;
        a.push_back(punct(xx, yy));
    }
    sort(a.begin(), a.end());
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            {
                p1.x = a[i].x + a[i].y - a[j].y;
                p1.y = a[i].y + a[j].x - a[i].x;
                p2.x = a[j].x + a[i].y - a[j].y;
                p2.y = a[j].y + a[j].x - a[i].x;
                if(Cb(p1))
                    if(Cb(p2))
                        sol++;
            }
    fout<<(sol>>1);

    return 0;
}
