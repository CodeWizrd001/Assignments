#include "ECC.h"
#include <string.h>
#include <vector>

#define K_VALUE 1234

typedef struct Key
{
   ZZ privateKey ;
   Point publicKey ;
} Key ;

// Function to calculate Legendre of a with p
int Legendre(ZZ a,ZZ p)
{
   if(a>=p || a<0)
      return Legendre(a%p,p) ;
   else if(a==0)
      return 0 ;
   else if(a==1)
      return 1 ;
   else if(a==2)
   {
      if(p%8==1 || p%8==7)
         return 1 ;
      else
         return -1 ;
   }
   else if(a==p-1)
   {
      if(p%4==1)
         return 1 ;
      else
         return -1 ;
   }
   else
   {
      if((p-1)%2==0 || (a-1)%2==0)
         return Legendre(a,p/2) ;
      else
         return -Legendre(a,p/2) ;
   }
}


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

// Some Hash Function
ZZ Hash(Point P)
{
   ZZ h ;
   h = P.x ;
   return h ;
}

// Sign
Vec<ZZ> Sign(Point Pm,ZZ privateKey,ZZ sessionKey,ZZ n,Point BasePoint)
{
   Vec<ZZ> v ;
   v.FixLength(2) ;

   Point R = BasePoint * sessionKey ;
   ZZ r = R.x ;

   ZZ s = (InvMod(sessionKey,n) * (Hash(Pm) + privateKey * r)) % n ;

   v[0] = r ;
   v[1] = s ;

   return v ;
}

// Verify
bool Verify(Vec<ZZ> key,ZZ n,Point Pm,Point publicKey,Point BasePoint)
{
   ZZ r = key[0] ;
   ZZ s = key[1] ;

   ZZ w = InvMod(s,n) ;
   ZZ u = (Hash(Pm) * w)%n ;
   ZZ v = (r * w)%n ;

   Point R = (BasePoint * u) + (publicKey * v) ;

   if(R.x==r)
      return true ;
   else
      return false ;
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

   ZZ k ;
   do {
      k = RandomBnd(n) ;
   } while (GCD(k,n)!=1) ;

   cout << "Session Key : " << endl ;
   cout << k << endl ;
   cout << "--------------------------------------------------------" << endl ;

   Vec<ZZ> sign = Sign(Pm,bobKey.privateKey,k,n,BasePoint) ;
   cout << "Signature : " << endl ;
   cout << "r    : " << sign[0] << endl ;
   cout << "s    : " << sign[1] << endl ;
   bool t = Verify(sign,n,Pm,bobKey.publicKey,BasePoint) ;
   cout << "Valid   : " << t << endl ;
   cout << "--------------------------------------------------------" << endl ;

   sign[0] = sign[0] + 1234 ;
   cout << "Signature : " << endl ;
   cout << "r    : " << sign[0] << endl ;
   cout << "s    : " << sign[1] << endl ;
   t = Verify(sign,n,Pm,bobKey.publicKey,BasePoint) ;
   cout << "Valid   : " << t << endl ;
   cout << "--------------------------------------------------------" << endl ;
}