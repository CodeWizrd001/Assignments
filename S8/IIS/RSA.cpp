// Implementation of RSA algorithm using 512 Bit keys

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define ERR_THRESHOLD 1000 
// Error in range 2^(-ERR_THRESHOLD)

Vec<ZZ> KeyGen(long BIT_LENGTH) 
{
   ZZ p , q , n , phi , e , d ;
   Vec<ZZ> v ;
   v.FixLength(3) ;

   GenPrime(p,BIT_LENGTH,ERR_THRESHOLD) ;
   GenPrime(q,BIT_LENGTH,ERR_THRESHOLD) ;
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

   ZZ m , c , t ;

   long KEY_SIZE = 512 ;
   cout << "[+] Using " << KEY_SIZE << " bit keys" << endl ;

   Vec<ZZ> keys = KeyGen(KEY_SIZE) ;
   n = keys[0] ;
   e = keys[1] ;
   d = keys[2] ;

   cout << "[+] Generated Keys : " << endl ;
   cout << "N : " << n << endl ;
   cout << "E : " << e << endl ;
   cout << "D : " << d << endl ;
   cout << "-------------------------------------------------------------------------------------" ;

   m = 2567 ;
   cout << "Message     : " << m << endl ;
   c = encrypt(m,e,n) ;
   cout << "Encrypted   : " << c << endl ;
   t = decrypt(c,d,n) ;
   cout << "Decrypted   : " << t << endl ;
   cout << "-------------------------------------------------------------------------------------" ;

   KEY_SIZE = 1024 ;
   cout << "[+] Using " << KEY_SIZE << " bit keys" << endl ;

   keys = KeyGen(KEY_SIZE) ;
   n = keys[0] ;
   e = keys[1] ;
   d = keys[2] ;

   cout << "[+] Generated Keys : " << endl ;
   cout << "N : " << n << endl ;
   cout << "E : " << e << endl ;
   cout << "D : " << d << endl ;
   cout << "-------------------------------------------------------------------------------------" ;

   m = 123456 ;
   cout << "Message     : " << m << endl ;
   c = encrypt(m,e,n) ;
   cout << "Encrypted   : " << c << endl ;
   t = decrypt(c,d,n) ;
   cout << "Decrypted   : " << t << endl ;
   cout << "-------------------------------------------------------------------------------------" ;
}