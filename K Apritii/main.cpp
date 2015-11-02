#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream fin("aparitii.in");
ofstream fout("aparitii.out");

int N, K, FR[12][12];

int main()
{
    fin >> N >> K;
    for(int i = 1; i <= N; i++)
    {
        string s; fin >> s;
        for(int j = 0; s[j]; j++)
            FR[j + 1][s[j] - '0']++;
    }

    int nr = 0;
    for(int i = 1; i <= 10 ; i++)
        for(int j = 0; j < 10; j++)
            if(FR[i][j] % K)
            {
                nr = nr * 10 + j;
                break;
            }
    fout<<nr;
    return 0;
}
