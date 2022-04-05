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