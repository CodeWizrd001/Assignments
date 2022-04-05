// Implementation of Digital Signature using RSA
// Hash related functions are stored in crypto.h

#include <NTL/ZZ.h>
#include "crypto.h"

using namespace std;
using namespace NTL;

#define BIT_LENGTH 512
#define ERR_THRESHOLD 1000 
// Error in range 2^(-ERR_THRESHOLD)

Vec<ZZ> KeyGen() 
{
   ZZ p , q , n , phi , e , d ;
   Vec<ZZ> v ;
   v.FixLength(3) ;

   GenPrime(p,BIT_LENGTH/2,ERR_THRESHOLD) ;
   GenPrime(q,BIT_LENGTH/2,ERR_THRESHOLD) ;
   n = p * q ;
   phi = (p-1) * (q-1) ;

   ZZ t ;
   t = 0 ;
   e = 0 ;
   while (t != 1 && e != 1) 
   {
      e = RandomBnd(phi) ;
      t = GCD(e,phi) ;
   }
   d = InvMod(e,phi) ;
   
   v[0] = n ;
   v[1] = e ;
   v[2] = d ;
   return v ;
}

//Sign
ZZ Sign(ZZ m,ZZ d,ZZ n) 
{
   ZZ c ;
   ZZ h = Hash(m) ;
   c = PowerMod(h,d,n) ;
   return c ;
}

// Verify
bool Verify(ZZ m,ZZ sigma,ZZ e,ZZ n) 
{
   ZZ c ;
   ZZ h = Hash(m) ;
   ZZ h_ = PowerMod(sigma,e,n) ;
   if (h == h_)
      return 1 ;
   else
      return 0 ;
}

int main()
{
   ZZ p , q , n , phi , e , d ;

   Vec<ZZ> keys = KeyGen() ;
   n = keys[0] ;
   e = keys[1] ;
   d = keys[2] ;

   ZZ m , sigma ;

   m = 2567 ;
   ZZ h = Hash(m) ;        // Some hash of message M
   
   cout << "Message        : " << m << endl ;
   cout << "Hashed Message : " << h << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
   
   sigma = Sign(m,d,n) ;
   cout << "Sign    : " << sigma << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
   
   bool t = Verify(m,sigma,e,n) ;
   cout << "Pass 1" << endl ;
   cout << "Message : " << m << endl ;
   cout << "Sign    : " << sigma << endl ;
   cout << "Valid   : " << t << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
   
   bool t1 = Verify(m,sigma + 1,e,n) ;
   cout << "Pass 2" << endl ;
   cout << "Message : " << m << endl ;
   cout << "Sign    : " << sigma + 1 << endl ;
   cout << "Valid   : " << t1 << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
}