#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

ifstream fin("prefix.in");
ofstream fout("prefix.out");

const int N = 1000010;
vector <bool> ok(N);
int pi[N];
char s[N];

int main()
{
    int t; fin>>t; fin.get();
    while(t--)
    {
        fin.getline(s, N);
        int n = strlen(s), k = 0, rez = 0;
        for(int i=n; i>0; i--) s[i] = s[i-1];

        pi[1] = 0;
        for(int i=2; i<=n; i++)
        {
            while(k && s[k+1] != s[i])
                k = pi[k];
            if(s[k+1] == s[i]) k++;
            pi[i] = k;
        }
        ok.assign(n+1, 0);
        for(int i=1; i<=n; i++)
            if((i-pi[i] == pi[i]) || (i-pi[i]==pi[i]-pi[pi[i]] && ok[pi[i]]))
            {
                ok[i] = 1;
                rez = i;
            }
            else
                ok[i] = 0;
        fout<<rez<<'\n';
    }
    return 0;
}
