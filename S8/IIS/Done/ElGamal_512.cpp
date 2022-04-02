#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define BIT_LENGTH 512
#define ERR_THRESHOLD 1000
// Setup
// Choose prime p
// l and t bits
// Choose t bit prime q
// Choose l bit prime p
// p-1 % q == 0
// Choose  1 <= h < p
// g = (h^(p-1)/q ) % p   , repeat till g != 1
Vec<ZZ> Setup() 
{
   Vec<ZZ> v ;
   v.FixLength(3) ;

   ZZ p , q , t , g , h;

   GenGermainPrime(q,BIT_LENGTH,ERR_THRESHOLD) ;
   p = 2*q + 1 ;
   
   g = 1 ;
   while(g==1) 
   {
      h = RandomBnd(p) ;
      g = PowerMod(h,(p-1)/q,p) ;
   }

   v[0] = p ;
   v[1] = q ;
   v[2] = g ;
   return v ;
}

// Key Generation
Vec<ZZ> KeyGen(ZZ p,ZZ q,ZZ g)
{
   Vec<ZZ> v ;
   v.FixLength(2) ;

   ZZ x,y ;

   do {
      x = RandomBnd(q) ;
   } while (GCD(x,p)!=1) ;

   y = PowerMod(g,x,p); 
   v[0] = x ;
   v[1] = y ;

   return v ;
}

// Encryption
Vec<ZZ> encrypt(ZZ m,ZZ p,ZZ q,ZZ g,ZZ y)
{
   Vec<ZZ> v ;
   v.FixLength(2) ;

   ZZ k ;

   do {
      k = RandomBnd(q) ;
   } while (GCD(k,p)!=1) ;

   ZZ c1,c2 ;

   c1 = PowerMod(g,k,p) ;
   c2 = MulMod(m,PowerMod(y,k,p),p) ;
   
   v[0] = c1 ; 
   v[1] = c2 ;
   return v;
}

// Decryption
ZZ decrypt(ZZ c1,ZZ c2,ZZ x,ZZ p) 
{
   ZZ m ;
   m = MulMod(c2,PowerMod(c1,-x,p),p);
   return m ;
}

int main()
{
   ZZ p , q , n , phi , g , d ;

   Vec<ZZ> set = Setup() ;
   p = set[0] ;
   q = set[1] ;
   g = set[2] ;

   cout << "P   : " << p << endl ;
   cout << "Q   : " << q << endl ;
   cout << "G   : " << g << endl ;

   ZZ x,y ;
   Vec<ZZ> keys = KeyGen(p,q,g) ;
   x = keys[0] ;
   y = keys[1] ;
   
   cout << "Keys" << endl ;
   cout << "X   : " << x << endl ;
   cout << "Y   : " << y << endl ;

   ZZ c1 , c2 ;
   ZZ m ;

   m = 2567898 ;
   cout << "Message" << endl ;
   cout << m << endl ;
   Vec<ZZ> c = encrypt(ZZ(2567),p,q,g,y) ;
   c1 = c[0] ;
   c2 = c[1] ;

   cout << "C1  : " << c1 << endl ;
   cout << "C2  : " << c2 << endl ;

   ZZ t ;
   t = decrypt(c1,c2,x,p) ;

   cout << "T   : " << t << endl ;
}