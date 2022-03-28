#include <stdio.h>
#include <stdlib.h>

FILE *Fin, *Fout;

int Par[4][10001] ;
int Rank[2][10001] ;
int S[4] = {0,0,0,0} ; 

void MakeSet(int x)
{
    if (Par[0][x] >= 0)
        fprintf(Fout, "PRESENT\n");
    else
    {
        fprintf(Fout,"%d\n",x);
        Par[0][x] = Par[1][x] = Par[2][x] = Par[3][x] = x;
    }
}

int _Find(int x,int i)
{
    S[i]++;
    if (Par[i][x] == x)
        return x;
    return _Find(Par[i][x],i) ;
}

int __Find(int x,int i)
{
    S[i]++;
    if (Par[i][x] == x)
        return x;
    return Par[i][x] = __Find(Par[i][x],i) ;
}

void Find(int x)
{
    if (Par[0][x] < 0)
        fprintf(Fout, "NOT FOUND NOT FOUND NOT FOUND NOT FOUND\n");
    else
        fprintf(Fout, "%d %d %d %d\n",_Find(x,0),_Find(x,1),__Find(x,2),__Find(x,3));
}

int _Link(int x,int y,int i)
{
    if(i)
    {
        x = __Find(x,2);
        y = __Find(y,2);
    }
    else
    {
        x = _Find(x,i);
        y = _Find(y,i);
    }
    Par[i][y] = x;
    return x;
}

int __Link(int x,int y,int i,int j)
{
    x = _Find(x,i);
    y = _Find(y,i);
    if(x==y)
        return x;
    if (Rank[j][x] == Rank[j][y])
    {
        Rank[j][x]++;
        return Par[i][y] = x;
    }
    if (Rank[j][x] >= Rank[j][y])
        return Par[i][y] = x;
    else
        return Par[i][x] = y;
}

void Union(int x, int y)
{
    if (Par[0][x] < 0 || Par[0][y] < 0)
        fprintf(Fout, "ERROR ERROR ERROR ERROR\n");
    else
        fprintf(Fout,"%d %d %d %d\n", _Link(x,y,0),__Link(x,y,1,0), _Link(x,y,2),__Link(x,y,3,1));
}

void main()
{
    Fin = stdin ;
    Fout = stdout ;
    for(int i = 0; i <= 10000; ++i)
    {
        Par[0][i] = Par[1][i] = Par[2][i] = Par[3][i] = -1;
        Rank[0][i] = Rank[1][i] = 0;
    }
    char ch[3];
    int x, y;
    while (!feof(Fin))
    {
        if(feof(Fin)) 
            break ;
        fscanf(Fin, "%s", ch);
        switch (ch[0])
        {
        case 'm': fscanf(Fin,"%d",&x);
                  MakeSet(x);
                  break;
        case 'f': fscanf(Fin, "%d\n", &x);
                  Find(x);
                  break;
        case 'u': fscanf(Fin, " %d %d\n", &x, &y);
                  Union(x, y);
                  break;
        case 's': fprintf(Fout, "%d %d %d %d\n", S[0], S[1], S[2], S[3]);
                  exit(0) ;
        default : continue ;
        }
    }
}