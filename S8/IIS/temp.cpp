#include <NTL/ZZ_pXFactoring.h>
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
   // cout << "P : " << p << ":" << NumBits(p) << ":" << ProbPrime(p) << endl ;
   // cout << "Q : " << q << ":" << NumBits(q) << ":" << ProbPrime(q) << endl ;
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

   // Random select 1 < e < phi
   // find d , inverse e with respect to phi

}