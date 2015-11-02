#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("piese2.in");
ofstream fout("piese2.out");

long long t, n, k, sum, poz1, poz2;

int main()
{
    fin>>t>>n>>k;
    while(t--)
    {
        sum = 0;
        for(int i=1; i<=k; i++)
        {
            fin>>poz1>>poz2;
            sum += poz2 - poz1 - 1;
        }
        if(sum&1) fout<<"Miruna\n";
        else fout<<"Aglaia\n";
    }
    return 0;
}
