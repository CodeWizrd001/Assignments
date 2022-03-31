#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define BIT_LENGTH 512
#define ERR_THRESHOLD 1000 
// Error in range 2^(-ERR_THRESHOLD)

// KEY GENERATION
// p = Prime
// q = Prime
// n = pq
// (p-1)(q-1) = phi
// choose e , gcd(e,phi) = 1 
// find e^-1 % phi
// 

// ENCRYPTION
// message , m
// 
Vec<ZZ> KeyGen() 
{
   ZZ p , q , n , phi , e , d ;
   Vec<ZZ> v ;
   v.FixLength(3) ;

   GenPrime(p,BIT_LENGTH/2,ERR_THRESHOLD) ;
   GenPrime(q,BIT_LENGTH/2,ERR_THRESHOLD) ;
   n = p * q ;
   phi = (p-1) * (q-1) ;

   // cout << "P   : " << p << endl ;
   // cout << "Q   : " << q << endl ;
   // cout << "N   : " << n << endl ;
   // cout << "Phi : " << phi << endl ;

   ZZ t ;
   t = 0 ;
   e = 0 ;
   while (t != 1 && e != 1) 
   {
      e = RandomBnd(phi) ;
      t = GCD(e,phi) ;
   }
   // cout << "E   : " << e << endl ;
   d = InvMod(e,phi) ;
   // cout << "D   : " << d << endl ;
   
   v[0] = n ;
   v[1] = e ;
   v[2] = d ;
   return v ;
}

// Encrypt
ZZ encrypt(ZZ m,ZZ e,ZZ n) 
{
   ZZ c ;
   c = PowerMod(m,e,n) ;
   return c ;
}

// Decrypt
ZZ decrypt(ZZ c,ZZ d,ZZ n) 
{
   ZZ m ;
   m = PowerMod(c,d,n) ;
   return m ;
}


int main()
{
   ZZ p , q , n , phi , e , d ;

   Vec<ZZ> keys = KeyGen() ;
   n = keys[0] ;
   e = keys[1] ;
   d = keys[2] ;

   // cout << "N   : " << n << endl ;
   // cout << "E   : " << e << endl ;
   // cout << "D   : " << d << endl ;

   ZZ m , c , t ;

   m = 2567 ;
   cout << "M   : " << m << endl ;
   c = encrypt(m,e,n) ;
   cout << "C   : " << c << endl ;
   t = decrypt(c,d,n) ;
   cout << "T   : " << t << endl ;

   // Random select 1 < e < phi
   // find d , inverse e with respect to phi

}