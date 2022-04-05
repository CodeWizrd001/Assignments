// Implementation of ECC algorithm using 192 Bit Primary Field
// Point Arithmetics and supporting functions are stored in ECC.h

#include "ECC.h"
#include <string.h>
#include <vector>

#define K_VALUE 1234

typedef struct Key
{
    ZZ privateKey ;
    Point publicKey ;
} Key ;

Key KeyGen(ZZ n,Point B) 
{
    ZZ PrivateKey = RandomBnd(n) ;
    Point PublicKey = B * PrivateKey ;
    Key k = {PrivateKey,PublicKey} ;
    return k ;
}

Point messageEncode(ZZ m,Point BasePoint)
{
    ZZ k = ZZ(K_VALUE) ;
    ZZ Xj , Yj , Sj ;

    for(int j=0;j<k;j+=1)
    {
        Xj = k * m + j ;
        Sj = power(Xj,3) + BasePoint.get_a()*Xj + BasePoint.get_b() ;
        Sj = Sj % BasePoint.get_p() ;
        if(Jacobi(Sj,BasePoint.get_p())==1)
        {
            Yj = PowerMod(Sj,(BasePoint.get_p()+1)/ZZ(4),BasePoint.get_p()) ;   
            return Point(Xj,Yj,BasePoint.get_p(),BasePoint.get_a(),BasePoint.get_b()) ;
        }
    }
    return BasePoint * m ;
}

ZZ messageDecode(Point Pm,Point BasePoint)
{
    ZZ k = ZZ(K_VALUE) ;
    return Pm.x / k ;
}

vector<Point> encrypt(ZZ k,Point BasePoint,Point Pm,Point publicKey)
{
    Point C1 = BasePoint * k ;
    Point C2 = Pm + (publicKey * k) ;

    vector<Point> cipher ;

    cipher.reserve(2) ;

    cipher.push_back(C1) ;
    cipher.push_back(C2) ;

    return cipher ;
}

Point decrypt(ZZ privateKey,Point C1,Point C2)
{
    Point t = (C1 * privateKey).inverse() ;
    Point Pm = C2 + t ;
    return Pm ;
}

int main() 
{
    Vec<ZZ> curveParams ;
    curveParams.SetLength(3) ;
    curveParams[0] = power(ZZ(2),192) - power(ZZ(2),64) - ZZ(1) ;   // p
    curveParams[1] = ZZ(-3) ;                                       // a
    curveParams[2] = conv<ZZ>("2455155546008943817740293915197451784769108058161191238065") ;    // b

    ZZ p = curveParams[0] ;
    ZZ a = curveParams[1] ;
    ZZ b = curveParams[2] ;

    ZZ n = conv<ZZ>("6277101735386680763835789423176059013767194773182842284081") ;    // n - Order
    ZZ seed = conv<ZZ>("275585503993527016686210752207080241786546919125") ;
    ZZ h = ZZ(1) ;
    ZZ r = conv<ZZ>("1191689908718309326471930603292001425137626342642504031845") ;

    ZZ x = conv<ZZ>("602046282375688656758213480587526111916698976636884684818") ;
    ZZ y = conv<ZZ>("174050332293622031404857552280219410364023488927386650641") ;

    Point BasePoint = Point(
        x,              // x
        y,              // y
        curveParams[0],
        curveParams[1],
        curveParams[2]
    ) ;

    Key key = KeyGen(n,BasePoint) ;

    int message = 4321 ;
    ZZ m = ZZ(message) ;

    Point Pm = messageEncode(m,BasePoint) ;
    
    cout << "Actual Message : " << endl ;
    cout << m << endl ;
    cout << "--------------------------------------------------------" << endl ;

    cout << "Encoded Message : " << endl ;
    Pm.display() ;
    cout << "--------------------------------------------------------" << endl ;

    Key aliceKey = KeyGen(n,BasePoint) ;
    cout << "Alice Keys : " << endl ;
    cout << aliceKey.privateKey << endl ;
    aliceKey.publicKey.display() ;
    cout << "--------------------------------------------------------" << endl ;

    Key bobKey = KeyGen(n,BasePoint) ;
    cout << "Bob Keys : " << endl ;
    cout << bobKey.privateKey << endl ;
    bobKey.publicKey.display() ;
    cout << "--------------------------------------------------------" << endl ;

    ZZ k = RandomBnd(curveParams[0]) ;

    vector<Point> cipher = encrypt(k,BasePoint,Pm,bobKey.publicKey) ;
    cout << "Encrypted Message : " << endl ;
    cout << "C1 : " << endl ;
    cipher[0].display() ;
    cout << "C2 : " << endl ;
    cipher[1].display() ;
    cout << "--------------------------------------------------------" << endl ;

    Point tm = decrypt(bobKey.privateKey,cipher[0],cipher[1]) ;
    cout << "Decrypted Message : " << endl ;
    tm.display() ;
    cout << "--------------------------------------------------------" << endl ;

    ZZ decodedMessage = messageDecode(tm,BasePoint) ;
    cout << "Decoded Message : " << endl ;
    cout << decodedMessage << endl ;
    cout << "--------------------------------------------------------" << endl ;
}