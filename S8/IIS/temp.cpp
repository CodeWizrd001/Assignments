#include <NTL/ZZ.h>
#include <openssl/sha.h>

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
      res += hex[i];
   }
   return res ;
}

string numberToString(ZZ num)
{
    long len = ceil(log(num)/log(128));
    char str[len];
    for(long i = len-1; i >= 0; i--)
    {
        str[i] = conv<int>(num % 128);
        num /= 128;
    }

    return (string) str;
}

// Some Hash Function
ZZ Hash(ZZ m,ZZ p)
{
   // convert m to string
   string s = numberToString(m);
   unsigned char *str = (unsigned char*)s.c_str();
   unsigned char hash[SHA_DIGEST_LENGTH]; // == 20
   SHA1(str, sizeof(str) - 1, hash);
   ZZ h = hexToZZ(hexdigest(hash, SHA_DIGEST_LENGTH)) % p;
   return h ;
}

//Sign
ZZ Sign(ZZ h,ZZ d,ZZ n) 
{
   ZZ c ;
   c = PowerMod(h,d,n) ;
   return c ;
}

// Verify
bool Verify(ZZ m,ZZ sigma,ZZ e,ZZ n) 
{
   ZZ c ;
   ZZ h = Hash(m,n) ;
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
   ZZ h = Hash(m,n) ;        // Some hash of message M
   h = m ;

   cout << "Message        : " << m << endl ;
   cout << "Hashed Message : " << h << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
   
   sigma = Sign(m,d,n) ;
   cout << "Sign   : " << sigma << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
   
   bool t = Verify(h,sigma,e,n) ;
   cout << "Pass 1" << endl ;
   cout << "Message : " << m << endl ;
   cout << "Sign    : " << sigma << endl ;
   cout << "Valid   : " << t << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
   
   bool t1 = Verify(h,sigma + 1,e,n) ;
   cout << "Pass 2" << endl ;
   cout << "Message : " << m << endl ;
   cout << "Sign    : " << sigma + 1 << endl ;
   cout << "Valid   : " << t1 << endl ;
   cout << "--------------------------------------------------------------------------------------" << endl ;
}