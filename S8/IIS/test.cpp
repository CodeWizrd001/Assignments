#include "ECC.h" 

using namespace std ;

int main() 
{
    Point P = Point(ZZ(5),ZZ(7),ZZ(29),ZZ(4)) ;
    Point Q = Point(ZZ(5),ZZ(22),ZZ(29),ZZ(4)) ;
    Point X = Q + Q ;
    X.display() ;
    return 0;
}