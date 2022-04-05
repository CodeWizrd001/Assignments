// Implementation of Digital Signature using RSA
// Hash related functions are stored in crypto.h

#include <NTL/ZZ.h>
#include <openssl/sha.h>
#include <bits/stdc++.h>
#include <string>

using namespace std;
using namespace NTL;

char *hexdigest(unsigned char *md, int len)
{
    static char buf[80];
    int i;
    for (i = 0; i < len; i++)
        sprintf(buf + i * 2, "%02x", md[i]);
    return buf;
}

ZZ hexToZZ(char *hex)
{
   ZZ res = ZZ(0);
   int i;
   for (i = 0; i < strlen(hex); i += 1)
   {
      res <<= 4;
      char x = hex[i];
      if(x>='0' && x <='9')
         res += hex[i]-48;
      else if(x>='a' && x <='f')
         res += hex[i]-87;
      else if(x>='A' && x <='F')
         res += hex[i]-55;
   }
   return res ;
}

string numberToString(ZZ num)
{
    string s = "";
    while (num > 0)
    {
        s += (num % 10) + '0';
        num /= 10;
    }
    reverse(s.begin(), s.end());
    return s;
}

// SHA1
ZZ Hash(string s)
{
    unsigned char hash[SHA_DIGEST_LENGTH]; // == 20

    SHA_CTX sha1;
    SHA1_Init(&sha1);
    SHA1_Update(&sha1, s.c_str(), s.length());
    SHA1_Final(hash, &sha1);

    ZZ h = hexToZZ(hexdigest(hash, SHA_DIGEST_LENGTH));
    return h ;
}

ZZ Hash(ZZ m)
{
    string s = numberToString(m);
    return Hash(s);
}

ZZ Hash(char *m)
{
    string s = m;
    return Hash(s);
}

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
   cout << "Pass 2 - [With Tampering]" << endl ;
   cout << "Message : " << m << endl ;
   cout << "Sign    : " << sigma + 1 << endl ;
   cout << "Valid   : " << t1 << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
}