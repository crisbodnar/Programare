#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory.h>

using namespace std;

ifstream fin("recurenta2.in");
ofstream fout("recurenta2.out");

int N, A, B, C, X1, X2;

const int MOD = 666013;

int REZ[8][8], M[8][8], SOL[8][8];

void Prod(int A[][8], int B[][8], int C[][8])
{
    for(int i = 1; i < 8; i++)
        for(int j = 1; j < 8; j++)
            for(int k = 1; k < 8; k++)
                C[i][j]  = (C[i][j] + 1LL * A[i][k] * B[k][j]) % MOD;
}

void POW(int X[][8], int p)
{
    int AUX[8][8];
    for(int i = 1; i <= 7; i++)
        REZ[i][i] = 1;

    for(; p; p >>= 1)
    {
        if(p & 1)
        {
            memset(AUX, 0, sizeof AUX);
            Prod(REZ, X, AUX);
            memcpy(REZ, AUX, sizeof AUX);
        }

        memset(AUX, 0, sizeof AUX);
        Prod(X, X, AUX);
        memcpy(X, AUX, sizeof AUX);
    }
}

int main()
{
    fin >> A >> B >> C >> X1 >> X2 >> N;

    M[2][1] = M[2][5] = M[3][3] = M[3][7] = M[4][4] = M[6][5] = M[7][7] = 1;
    M[1][2] = M[1][6] = M[5][4] = M[5][6] = B;
    M[2][2] = M[2][6] = M[6][4] = M[6][6] = A;
    M[3][2] = M[3][6] = M[7][4] = M[7][6] = C;

    POW(M, N - 2);
    memset(M, 0, sizeof M);

    M[1][1] = X1; M[1][2] = X2; M[1][3] = 1; M[1][4] = X1 + 2 * X2;
    M[1][5] = 3 * X1; M[1][6] = 3 * X2; M[1][7] = 3;

    Prod(M, REZ, SOL);
    fout<<SOL[1][4];
    return 0;
}
