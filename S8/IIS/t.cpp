#include <NTL/ZZ.h>
#include <bitset>

using namespace NTL ;
using namespace std ;

int main() 
{
    ZZ N;
    N = 2570 ;
    unsigned char* pp = new unsigned char[NumBytes(N)];
    BytesFromZZ(pp, N, NumBytes(N)); // pp = byte-representation of N
    for(int i=0;i<NumBytes(N);i+=1) 
    {
        bitset<8> x(pp[i]) ;
        for(int j=0;j<8;j+=1)
        {
            cout << x[j] ;
        }
    }
    cout << endl ;

    delete[] pp;
}