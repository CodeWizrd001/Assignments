#include <NTL/ZZ.h>

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
        ZZ x ;
        ZZ y ;
        ZZ p ;
        ZZ a ;
        ZZ b ;
    public:
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

        void display() 
        {
            cout << "Point(" << x << "," << y << "," << p << ")" << endl ;
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

            ZZ t_y = InvMod(MulMod(ZZ(2),y,p),p) ;
            l = MulMod(ZZ(3) * power(x,2) + a,t_y,p) ;

            // cout << "[+] Check 2" << endl ;
            ZZ fx = (power(l,2)) % p ;
            
            // cout << "[+] Check 3" << endl ;
            ZZ t = x - fx ;
            ZZ fy = (l*t - y) % p ;
            
            return Point(fx,fy,p,a,b) ;
        }

        Point operator + (Point const &obj)
        {
            if(p != obj.p)
                cout << "[+] Invalid Operands" << endl ;
            ZZ y_ = obj.y - y ;
            ZZ x_ = obj.x - x ;
            
            // cout << "[+] Check 1" << endl ;
            ZZ l ;
            if(Eq(obj))
            {
                ZZ t_y = InvMod(MulMod(ZZ(2),y,p),p) ;
                l = MulMod(ZZ(3) * power(x,2) + a,t_y,p) ;
            }
            else 
            {
                ZZ t_x = InvMod(x_,p) ;
                l = MulMod(y_,t_x,p) ;
            }
            cout << "L  : " << l << endl ;
            // cout << "[+] Check 2" << endl ;
            ZZ fx = (power(l,2)-x-obj.x) % p ;
            // cout << "[+] Check 3" << endl ;
            ZZ t = x - fx ;
            ZZ fy = (l*t - y) % p ;
            return Point(fx,fy,p,a,b) ;
        }
} ; 