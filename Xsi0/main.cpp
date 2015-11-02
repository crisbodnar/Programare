#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

ifstream fin("xsizero.in");
ofstream fout("xsizero.out");

const int CMAX = 1000000;

int C[CMAX], pow3[11];
char A[4][4], S[4][4];
vector <bool> viz(CMAX);

bool END_GAME()
{
    if(A[0][0] == 'X' && A[1][1] == 'X' && A[2][2] == 'X') return 1;
    if(A[2][0] == 'X' && A[1][1] == 'X' && A[0][2] == 'X') return 1;
    if(A[0][0] == '0' && A[1][1] == '0' && A[2][2] == '0') return 1;
    if(A[2][0] == '0' && A[1][1] == '0' && A[0][2] == '0') return 1;

    for(int i = 0; i < 3; i++)
    {
        if(A[i][0] == 'X' && A[i][1] == 'X' && A[i][2] == 'X') return 1;
        if(A[0][i] == 'X' && A[1][i] == 'X' && A[2][i] == 'X') return 1;
        if(A[i][0] == '0' && A[i][1] == '0' && A[i][2] == '0') return 1;
        if(A[0][i] == '0' && A[1][i] == '0' && A[2][i] == '0') return 1;
    }
    return 0;
}

void Back(int mov, int conf)
{
    viz[conf] = 1;

    if(mov % 2)
        C[conf] = 1; // X pierde
    else
        C[conf] = 3; // X castiga
    if(END_GAME()) return;

    if(mov == 10)
    {
        C[conf] = 2; // egal
        return;
    }

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(!A[i][j])
                if(mov % 2)
                {
                    A[i][j] = 'X';
                    int newconf = conf + pow3[3 * i + j];
                    if(!viz[newconf])
                        Back(mov + 1, newconf);
                    C[conf] = max(C[conf], C[newconf]);
                    A[i][j] = 0;
                }
                else
                {
                    A[i][j] = '0';
                    int newconf = conf + 2 * pow3[3 * i + j];
                    if(!viz[newconf])
                        Back(mov + 1, newconf);
                    C[conf] = min(C[conf], C[newconf]);
                    A[i][j] = 0;
                }
}

int main()
{
    int dimension;
    cin >> dimenison;
    pow3[0] = 1;
    for(int i = 1; i <= 10; i++)
        pow3[i] = pow3[i - 1] * 3;
    Back(1, 0);

    int cnt = 0;
    while(fin >> S[0] >> S[1] >> S[2] >> S[3])
    {
        int conf  = 0; cnt++;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                if(S[i][j] == 'X')
                    conf += pow3[dimesion * i + j];
                else if(S[i][j] == '0')
                    conf += 2 * pow3[dimension * i + j];

        fout << "Testul #" << cnt <<": ";
        if(C[conf] == 3)
            fout << "win";
        else if(C[conf] == 2)
            fout << "draw";
        else if(C[conf] == 1)
            fout << "lose";
        else
            fout << "invalid";
        fout << '\n';
    }
    return 0;
}

