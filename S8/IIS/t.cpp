#include "ECC.h"

int main()
{
    Point P = Point(ZZ(5),ZZ(3),ZZ(29),ZZ(2),ZZ(0)) ;

    for(int i=0;i<10;i++)
    {
        cout << "Iteration " << i << endl ;
        Point R = P * i ;
        cout << "R * " << i << " = " ;
        R.display() ;
    }

    return 0 ;
}