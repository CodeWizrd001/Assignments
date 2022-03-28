#include "ECC.h"

int main() 
{
    Point P = Point(ZZ(3),ZZ(6),ZZ(97),ZZ(2),ZZ(3)) ;
    ZZ n = ZZ(4) ;
    Point R = P.Double() ;
    Point Q = P * 3 ;
    Point S = P * 4 ;
    R.display() ;
    Q.display() ;
    S.display() ;
}