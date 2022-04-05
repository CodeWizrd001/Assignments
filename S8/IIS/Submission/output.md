Q1 - a : Implementation of RSA using 512 bit parameters

```c++
// Implementation of RSA algorithm using 512 Bit keys

#include <NTL/ZZ.h>

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

   Vec<ZZ> keys = KeyGen() ;
   n = keys[0] ;
   e = keys[1] ;
   d = keys[2] ;

   ZZ m , c , t ;

   m = 2567 ;
   cout << "Message     : " << m << endl ;
   c = encrypt(m,e,n) ;
   cout << "Encrypted   : " << c << endl ;
   t = decrypt(c,d,n) ;
   cout << "Decrypted   : " << t << endl ;
}
```
Output : 
![RSA_512](/Submission/screenshots/RSA_512.jpg "RSA_512")

Q1 - b : Implementation of RSA using 1024 bit parameters

```c++
// Implementation of RSA algorithm using 1024 Bit keys

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define BIT_LENGTH 1024
#define ERR_THRESHOLD 1000 
// Error in range 2^(-ERR_THRESHOLD)

Vec<ZZ> KeyGen() 
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

   Vec<ZZ> keys = KeyGen() ;
   n = keys[0] ;
   e = keys[1] ;
   d = keys[2] ;

   ZZ m , c , t ;

   m = 2567 ;
   cout << "Message     : " << m << endl ;
   c = encrypt(m,e,n) ;
   cout << "Encrypted   : " << c << endl ;
   t = decrypt(c,d,n) ;
   cout << "Decrypted   : " << t << endl ;
}
```
Output : 
![RSA_1024](/Submission/screenshots/RSA_1024.jpg "RSA_1024")

Q2 - a : Implementation of ElGamal using 512 bit parameters

```c++
// Implementation of ElGamal algorithm using 512 Bit keys

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define BIT_LENGTH 512
#define ERR_THRESHOLD 1000
// Error in range 2^(-ERR_THRESHOLD)

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
   cout << "---------------------------------------------------------------" << endl ;

   ZZ x,y ;
   Vec<ZZ> keys = KeyGen(p,q,g) ;
   x = keys[0] ;
   y = keys[1] ;
   
   cout << "Keys" << endl ;
   cout << "X   : " << x << endl ;
   cout << "Y   : " << y << endl ;
   cout << "---------------------------------------------------------------" << endl ;

   ZZ c1 , c2 ;
   ZZ m ;

   m = 2567898 ;
   cout << "Message" << endl ;
   cout << m << endl ;
   cout << "---------------------------------------------------------------" << endl ;
   Vec<ZZ> c = encrypt(m,p,q,g,y) ;
   c1 = c[0] ;
   c2 = c[1] ;

   cout << "C1  : " << c1 << endl ;
   cout << "C2  : " << c2 << endl ;
   cout << "---------------------------------------------------------------" << endl ;

   ZZ t ;
   t = decrypt(c1,c2,x,p) ;

   cout << "Decrypted Message   : " << t << endl ;
   cout << "---------------------------------------------------------------" << endl ;
}
```
Output : 
![ElGamal_512](/Submission/screenshots/ElGamal_512.jpg "ElGamal_512")

Q2 - b : Implementation of ElGamal using 1024 bit parameters

```c++
// Implementation of ElGamal algorithm using 1024 Bit keys

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

#define BIT_LENGTH 1024
#define ERR_THRESHOLD 1000
// Error in range 2^(-ERR_THRESHOLD)

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
   cout << "---------------------------------------------------------------" << endl ;

   ZZ x,y ;
   Vec<ZZ> keys = KeyGen(p,q,g) ;
   x = keys[0] ;
   y = keys[1] ;
   
   cout << "Keys" << endl ;
   cout << "X   : " << x << endl ;
   cout << "Y   : " << y << endl ;
   cout << "---------------------------------------------------------------" << endl ;

   ZZ c1 , c2 ;
   ZZ m ;

   m = 123456 ;
   cout << "Message" << endl ;
   cout << m << endl ;
   cout << "---------------------------------------------------------------" << endl ;
   Vec<ZZ> c = encrypt(m,p,q,g,y) ;
   c1 = c[0] ;
   c2 = c[1] ;

   cout << "C1  : " << c1 << endl ;
   cout << "C2  : " << c2 << endl ;
   cout << "---------------------------------------------------------------" << endl ;

   ZZ t ;
   t = decrypt(c1,c2,x,p) ;

   cout << "Decrypted Message   : " << t << endl ;
   cout << "---------------------------------------------------------------" << endl ;
}
```
Output : 
![ElGamal_1024](/Submission/screenshots/ElGamal_1024.jpg "ElGamal_1024")

Q3 : Implementation of ECC using F-192 parameters

Header Files with Necessary Utils for ECC Arithmetics

```c++
#include <NTL/ZZ.h>
#include <bitset>

using namespace NTL ;
using namespace std ;

ZZ modInverse(ZZ x,ZZ p) 
{
    for(ZZ i=ZZ(0);i<p;i+=1)
        if(MulMod(i,x,p) == 1)
            return i ;
    return ZZ(-1) ;
}

class Point {
    private:
        ZZ p ;
        ZZ a ;
        ZZ b ;
        string zztostring(ZZ num)
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
    public:
        ZZ x ;
        ZZ y ;

        Point(ZZ x_,ZZ y_,ZZ p_,ZZ a_=ZZ(0),ZZ b_=ZZ(0)) 
        {
            x = x_ ;
            y = y_ ;
            p = p_ ;
            a = a_ ;
            b = b_ ;
        }

        Point(const Point &P) 
        {
            x = P.x ;
            y = P.y ;
            p = P.p ;
            a = P.a ;
            b = P.b ;
        }

        ZZ get_a() 
        {
            return a ;
        }

        ZZ get_b() 
        {
            return b ;
        }

        ZZ get_p()
        {
            return p ;
        }

        void display() 
        {
            cout << "Point(" 
                 << x << "," 
                 << y << "," 
                 << p << ")" << endl ;
        }

        string toString() 
        {
            string str = "Point(" ;
            str += zztostring(x) ;
            str += "," ;
            str += zztostring(y) ;
            str += "," ;
            str += zztostring(p) ;
            str += ")" ;
            return str ;
        }

        Point inverse()
        {
            Point P = copy() ;
            P.y = (-P.y) % P.p ;
            return P ; 
        }

        Point copy() 
        {
            Point P = Point(x,y,p,a,b) ;
            return P ;
        }

        bool Eq(Point const &obj)
        {
            if(obj.x == x && obj.y == y && obj.p == p && obj.a == a && obj.b == b)
                return 1 ;
            else 
                return 0 ;
        }

        Point Double()
        {
            ZZ l ;
            ZZ t_y ;
            try {
                t_y = InvMod(MulMod(ZZ(2),y,p),p) ;
            } catch(InvModErrorObject &e) {
                cout << "Error: " << e.what() << endl ;
                return Point(ZZ(-1),ZZ(-1),ZZ(-1)) ;
            } 
            catch(...) {
                cout << "[!] Double : Non Invertible Point" << endl ;
                return Point(ZZ(-1),ZZ(-1),ZZ(p),ZZ(a),ZZ(b)) ;
            }
            l = MulMod(ZZ(3) * power(x,2) + a,t_y,p) ;

            // cout << "[+] Check 2" << endl ;
            ZZ fx = (power(l,2)-x-x) % p ;
            
            // cout << "[+] Check 3" << endl ;
            ZZ t = x - fx ;
            ZZ fy = (l*t - y) % p ;
            
            return Point(fx,fy,p,a,b) ;
        }

        ostream& operator<<(ostream &out) 
        {
            out << "Point(" << x << "," << y << "," << p << "," << a << "," << b << ")" ;
            return out ;
        }

        Point operator + (Point const &obj)
        {
            if(p != obj.p)
                cout << "[+] Invalid Operands" << endl ;
            ZZ y_ = obj.y - y ;
            ZZ x_ = obj.x - x ;

            if(obj.y == 0 && obj.x == 0)
                return Point(x,y,p,a,b) ;
            if(y == 0 && x == 0)
                return Point(obj.x,obj.y,obj.p,obj.a,obj.b) ;
            
            // cout << "[+] Check 1" << endl ;
            ZZ l ;
            if(Eq(obj))
            {
                ZZ t_y ;
                try {
                    t_y = InvMod(MulMod(ZZ(2),y,p),p) ;
                } catch(...) {
                    cout << "[!] + if : Non Invertible Point" << endl ;
                    return Point(ZZ(-1),ZZ(-1),ZZ(p),ZZ(a),ZZ(b)) ;
                }
                l = MulMod(ZZ(3) * power(x,2) + a,t_y,p) ;
            }
            else 
            {
                ZZ t_x ;
                try {
                    x_ = x_ % p ;
                    t_x = InvMod(x_,p) ;
                } catch(...) {
                    cout << "[!] + else : Non Invertible Point : " << x_ << endl ;
                    cout << "[!] GCD : " << GCD(x_,p) << endl ;
                    return Point(ZZ(-1),ZZ(-1),ZZ(p),ZZ(a),ZZ(b)) ;
                }
                l = MulMod(y_,t_x,p) ;
            }
            // cout << "L  : " << l << endl ;
            // cout << "[+] Check 2" << endl ;
            ZZ fx = (power(l,2)-x-obj.x) % p ;
            // cout << "[+] Check 3" << endl ;
            ZZ t = x - fx ;
            ZZ fy = (l*t - y) % p ;
            // cout << "Fx : " << fx << endl ;
            // cout << "Fy : " << fy << endl ;

            return Point(fx,fy,p,a,b) ;
        }

        Point operator * (ZZ const &obj)
        {
            return scalarMul(obj) ;
        }

        Point operator * (int const &obj)
        {
            return scalarMul(ZZ(obj)) ;
        }

        // Scalar Multiplication of Point
        Point scalarMul(ZZ const &k)
        {
            Point P = copy() ;
            Point ans = Point(ZZ(0),ZZ(0),p,a,b) ;
            unsigned char* p = new unsigned char[NumBytes(k)];
            BytesFromZZ(p, k, NumBytes(k)); // pp = byte-representation of N
            for(int i=0;i<NumBytes(k);i+=1) 
            {
                bitset<8> x(p[i]) ;         // x = binary representation of p[i]
                for(int j=0;j<8;j+=1)
                {
                    // cout << x[j] << " : " << endl ;
                    if(x[j] == 1)
                        ans = ans + P ;
                    P = P.Double() ;
                }
            }
            delete[] p;
            return ans ;
        }
} ; 
```

ECC Implementation in C++

```c++
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
```
Output : 
![ECC](/Submission/screenshots/ECC.jpg "ECC")

Q4 - a : Digital Signature Implementation using RSA

Header Files with Necessary Utils for SHA Hash

```c++
#include <openssl/sha.h>
#include <bits/stdc++.h>
#include <string>
#include <NTL/ZZ.h>

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
```

```c++
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
```
Output : 
![DS_RSA](/Submission/screenshots/DS_RSA.jpg "DS_RSA")

Q4 - b : Digital Signature Implementation using ElGamal

```c++
// Implementation of Digital Signature using ElGamal algorithm
// Hash related functions are stored in crypto.h

#include <NTL/ZZ.h>

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
```
Output : 
![DS_ElGamal](/Submission/screenshots/DS_ElGamal.jpg "DS_ElGamal")

Q4 - c : Digital Signature Implementation using ECC 

```c++
// Implementation of Digital Signature using ECC 
// Point Arithmetics and supporting functions are stored in ECC.h
// Hash related functions are stored in crypto.h

#include "ECC.h"
#include "crypto.h"

#include <string.h>
#include <vector>
#include <openssl/sha.h>

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

// Sign
Vec<ZZ> Sign(Point Pm,ZZ privateKey,ZZ sessionKey,ZZ n,Point BasePoint)
{
   Vec<ZZ> v ;
   v.FixLength(2) ;

   Point R = BasePoint * sessionKey ;
   ZZ r = R.x ;

   ZZ s = (InvMod(sessionKey,n) * (Hash(Pm.toString()) + privateKey * r)) % n ;

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
   
   ZZ u = (Hash(Pm.toString()) * w)%n ;
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
```
Output : 
![DS_ECC](/Submission/screenshots/DS_ECC.jpg "DS_ECC")