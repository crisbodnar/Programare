#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("ceva.in");
ofstream fout("ceva.out");

long long k, lim, s[10000], a[10000], prod[10000], n, m, pro, np;

void back(int p,long pr)
{ int i,j;
  for (i=s[p-1]+1;i<=n-k+p;i++)
   {s[p]=i;
    if (a[i] > lim / pr) return;
    if (p==1)
     { pro=1;
       for (j=1;j<=k;j++)
	{  if (pro <= lim/a[i+j-1])
	      pro = pro*a[i+j-1];
	   else
	      return;
	}
     }
    if (p==k)
      { pro=1;
	for (j=1;j<=k;j++)
	 { if (pro <= lim/a[s[j]])
	     pro = pro*a[s[j]];
	   else return;
	   //if (pro>lim) return;
	 }
	if (pro<=lim)
	{ np++;
	 //cout<<np<<' ';
	  if (k%2==1)
	   prod[np]=pro;
	  else
	   prod[np]=-pro;

	}
	else return;
      }
    else
      back(p+1,pr*a[i]);
    }
}

int main()
{
    fin>>n>>m;
    for(int i=1; i<=n; i++)
        fin>>a[i];
    lim = m * a[1];

    for(k=1; k<=n; k++)
        back(1, 1);
    for(int i=1;i<=np; i++)
        cout<<prod[i]<<' ';
    cout<<np;
    return 0;
}
