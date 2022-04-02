#include <NTL/ZZ.h>
#include <openssl/sha.h>

#include "crypto.h"

using namespace std;
using namespace NTL;

#define BIT_LENGTH 512
#define ERR_THRESHOLD 1000

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

// Sign
Vec<ZZ> Sign(ZZ m,ZZ p,ZZ q,ZZ g,ZZ x)
{
   Vec<ZZ> v ;
   v.FixLength(2) ;

   ZZ k,r,t ;

   do {
      k = RandomBnd(q) ;
      t = PowerMod(g,k,p) ;
      r = (t%q) ;
   } while (r==0) ;

   ZZ h = Hash(m) ;

   ZZ s = (InvMod(k,q)*(h+x*r))%q ;

   v[0] = r ;
   v[1] = s ;

   return v ;
}

// Verify
bool Verify(ZZ m,Vec<ZZ> v,ZZ y,ZZ p,ZZ q,ZZ g)
{
   ZZ r = v[0] ;
   ZZ s = v[1] ;

   if(r<0 || r>=q) return false ;
   if(s<0 || s>=q) return false ;

   ZZ h = Hash(m) ;

   ZZ w = InvMod(s,q) ;
   ZZ u1 = (h*w)%q ;
   ZZ u2 = (r*w)%q ;

   ZZ t = (PowerMod(g,u1,p) * PowerMod(y,u2,p))%p ;

   ZZ r_ = (t%q) ;

   if (r_==r) 
      return true ;
   else 
      return false ;
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
   cout << "------------------------------------------------------------------------------------------" << endl ;

   ZZ x,y ;
   Vec<ZZ> keys = KeyGen(p,q,g) ;
   x = keys[0] ;
   y = keys[1] ;
   
   cout << "Keys" << endl ;
   cout << "X   : " << x << endl ;
   cout << "Y   : " << y << endl ;
   cout << "------------------------------------------------------------------------------------------" << endl ;

   ZZ m ;
   m = ZZ(12345) ;

   Vec<ZZ> sign = Sign(m,p,q,g,x) ;
   cout << "Message        : " << m << endl ;
   cout << "Signature" << endl ;
   cout << "r     : " << sign[0] << endl ;
   cout << "s     : " << sign[1] << endl ;
   bool v = Verify(m,sign,y,p,q,g) ;
   cout << "Valid : " << v << endl ;
   cout << "------------------------------------------------------------------------------------------" << endl ;


   sign[0] = sign[0] + 1 ;
   cout << "Message : " << m << endl ;
   cout << "Signature" << endl ;
   cout << "r     : " << sign[0] << endl ;
   cout << "s     : " << sign[1] << endl ;
   v = Verify(m,sign,y,p,q,g) ;
   cout << "Valid : " << v << endl ;
   cout << "------------------------------------------------------------------------------------------" << endl ;

   return 0 ;
}