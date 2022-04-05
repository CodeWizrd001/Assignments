// Implementation of Digital Signature using ECC 

#include <openssl/sha.h>
#include <bits/stdc++.h>
#include <NTL/ZZ.h>
#include <string.h>
#include <vector>
#include <string>
#include <bitset>

using namespace std;
using namespace NTL;

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

            ZZ fx = (power(l,2)-x-x) % p ;
            
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
            ZZ fx = (power(l,2)-x-obj.x) % p ;
            ZZ t = x - fx ;
            ZZ fy = (l*t - y) % p ;

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
                    if(x[j] == 1)
                        ans = ans + P ;
                    P = P.Double() ;
                }
            }
            delete[] p;
            return ans ;
        }
} ; 

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
   cout << "Pass 1 : " << endl ;
   cout << "Signature : " << endl ;
   cout << "r    : " << sign[0] << endl ;
   cout << "s    : " << sign[1] << endl ;
   bool t = Verify(sign,n,Pm,bobKey.publicKey,BasePoint) ;
   cout << "Valid   : " << t << endl ;
   cout << "--------------------------------------------------------" << endl ;

   sign[0] = sign[0] + 1234 ;
   cout << "Pass 2 - [With Tampering] " << endl ;
   cout << "Signature : " << endl ;
   cout << "r    : " << sign[0] << endl ;
   cout << "s    : " << sign[1] << endl ;
   t = Verify(sign,n,Pm,bobKey.publicKey,BasePoint) ;
   cout << "Valid   : " << t << endl ;
   cout << "--------------------------------------------------------" << endl ;
}