#include <stdio.h>
#include <stdlib.h>

FILE *fin, *fout;

int parent0[10001], parent1[10001], parent2[10001], parent3[10001];
int rank1[10001], rank3[10001];

void init()
{
    for (int i = 0; i <= 10000; ++i)
    {
        parent0[i] = parent1[i] = parent2[i] = parent3[i] = -1;
        rank1[i] = rank3[i] = 0;
    }
}

void make_set(int u)
{
    if (parent0[u] >= 0)
        fprintf(fout, "PRESENT\n");
    else
    {
        fprintf(fout, "%d\n", u);
        parent0[u] = parent1[u] = parent2[u] = parent3[u] = u;
    }
}

int f0 = 0, f1 = 0, f2 = 0, f3 = 0;

int find0(int u)
{
    f0++;
    if (parent0[u] == u)
        return u;
    return find0(parent0[u]);
}

int find1(int u)
{
    f1++;
    if (parent1[u] == u)
        return u;
    return find1(parent1[u]);
}

int find2(int u)
{
    f2++;
    if (parent2[u] == u)
        return u;
    return parent2[u] = find2(parent2[u]);
}

int find3(int u)
{
    f3++;
    if (parent3[u] == u)
        return u;
    return parent3[u] = find3(parent3[u]);
}

void find_set(int u)
{
    if (parent0[u] < 0)
        fprintf(fout, "NOT FOUND NOT FOUND NOT FOUND NOT FOUND\n");
    else
    {
        fprintf(fout, "%d %d %d %d\n", find0(u), find1(u), find2(u), find3(u));
    }
}

int link0(int u, int v)
{
    u = find0(u);
    v = find0(v);
    parent0[v] = u;
    return u;
}

int link1(int u, int v)
{
    u = find1(u);
    v = find1(v);
    if(u==v)
        return u;
    if (rank1[u] == rank1[v])
    {
        rank1[u]++;
        return parent1[v] = u;
    }
    if (rank1[u] >= rank1[v])
        return parent1[v] = u;
    else
        return parent1[u] = v;
}

int link2(int u, int v)
{
    u = find2(u);
    v = find2(v);
    parent2[v] = u;
    return u;
}

int link3(int u, int v)
{
    u = find3(u);
    v = find3(v);
    if(u==v)
        return u;
    if (rank3[u] == rank3[v])
    {
        rank3[u]++;
        return parent3[v] = u;
    }
    if (rank3[u] >= rank3[v])
        return parent3[v] = u;
    else
        return parent3[u] = v;
}

void union_set(int u, int v)
{
    if (parent0[u] < 0 || parent0[v] < 0)
        fprintf(fout, "ERROR ERROR ERROR ERROR\n");
    else
    {
        fprintf(fout, "%d %d %d %d\n", link0(u, v), link1(u, v), link2(u, v), link3(u, v));
    }
}

int main()
{
    fin = stdin ;
    fout = stdout ;
    if (fin == NULL || fout == NULL)
    {
        printf("Unable to open files\n");
        return 0;
    }
    init();
    char ch;
    int u, v;
    while (ch != 's')
    {
 if(feof(fin)) return 0; 
        fscanf(fin, "%c\n", &ch);
 //printf("%c\n",ch);
        switch (ch)
        {
        case 'm':
            fscanf(fin, "%d\n", &u);
            make_set(u);
            break;
        case 'f':
            fscanf(fin, "%d\n", &u);
            find_set(u);
            break;
        case 'u':
            fscanf(fin, " %d %d\n", &u, &v);
            union_set(u, v);
     //return 0;
            break;
        case 's':
            fprintf(fout, "%d %d %d %d", f0, f1, f2, f3);
            return 0;
        default:
            fprintf(fout, "Invalid choice\n");
        }
    }
    return 0;
}