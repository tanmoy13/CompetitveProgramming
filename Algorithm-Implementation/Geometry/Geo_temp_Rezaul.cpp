#include <bits/stdc++.h>
#define SEG_TREE int lnd = nd * 2, rnd = lnd + 1, mid = (b + e) / 2
#define filein freopen ("input.txt", "r", stdin)
#define fileout freopen ("output.txt", "w", stdout)
#define D(x) cerr << #x << ": " << x << endl

using namespace std;
typedef long long ll;

const int maxn = 0;

namespace Geometry
{
    #define M_PI (acos(-1.0))
    typedef double T;
    /// Point
    struct pt
    {
        T x,y;
        pt() {}
        pt(T _x, T _y):x(_x), y(_y) {}
        pt operator + (pt p)
        {
            return {x+p.x, y+p.y};
        }
        pt operator - (pt p)
        {
            return {x-p.x, y-p.y};
        }
        pt operator * (T d)
        {
            return {x*d, y*d};
        }
        pt operator * (pt d)  /// I added for General linear transformation, not sure about that function
        {
            return {x*d.x, y*d.y};
        }
        pt operator / (T d)
        {
            return {x/d, y/d};/// only for floating point
        }
        pt operator / (pt d) /// I added for General linear transformation, not sure about that function
        {
            return {x/d.x, y/d.y};
        }
        bool operator < (const pt& p) const
        {
            if (x != p.x)
                return x < p.x;
            return y < p.y;
        }
        bool operator == (pt b)
        {
            return x == b.x && y == b.y;
        }
        bool operator != (pt b)
        {
            return !(*(this) == b);
        }
        friend ostream& operator<<(ostream& os,const pt p)
        {
            return os << "("<< p.x << "," << p.y << ")";
        }
        friend istream& operator>>(istream& is, pt &p) {
            is >> p.x >> p.y;
            return is;
        }


    };

    T sq (pt p)
    {
        return p.x * p.x + p.y * p.y;
    }

    double Abs (pt p)
    {
        return sqrtl (sq (p));
    }

    pt translate (pt v, pt p)   ///To translate an object by a vector v
    {
        return p + v;
    }

    pt scale (pt c, double factor, pt p)  ///To scale an object by a certain ratio factor around a center
    {
        return c + (p - c) * factor;
    }
    pt rot(pt p, double a) /// To rotate a point by angle a;
    {
        return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};
    }

    pt perp(pt p) /// To rotate a point 90 degree
    {
        return {-p.y, p.x};
    }

    pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq) /// so far don't know about that function
    {
        return fp + (r-p) * (fq-fp) / (q-p);
    }

    T dot(pt v, pt w)
    {
        return v.x*w.x + v.y*w.y;
    }

    bool isPerp(pt v, pt w)
    {
        return dot(v,w) == 0;
    }

    double angle(pt v, pt w) /// Find the smallest angle of two vector
    {
        double cosTheta = dot(v,w) / Abs(v) / Abs(w);
        return acos(max(-1.0, min(1.0, cosTheta)));
    }

    T cross(pt v, pt w)
    {
        return v.x*w.y - v.y*w.x;
    }

    T orient(pt a, pt b, pt c)
    {
        return cross(b-a,c-a);   /// if c is left side +ve, c is right side -ve, on line 0
    }
    bool inAngle(pt a, pt b, pt c, pt p) /// if p is in the angle
    {
        assert(orient(a,b,c) != 0);
        if (orient(a,b,c) < 0)
            swap(b,c);
        return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
    }

    double orientedAngle(pt a, pt b, pt c) /// the actual angle from ab to ac
    {
        if (orient(a,b,c) >= 0)
            return angle(b-a, c-a);
        else
            return 2*M_PI - angle(b-a, c-a);
    }

    ///line
    struct line
    {
        pt v;
        T c;
        line () {}
        //From points P and Q
        line (pt p, pt q)
        {
            v = (q - p);
            this->c = cross (v, p);
        }
        //From equation ax + by = c
        line (T a, T b, T c)
        {
            v = pt (b, -a);
            this->c = c;
        }
        //From direction vector v and offset c
        line (pt v, T c)
        {
            this->v = v;
            this->c = c;
        }
        double getY(double x){ ///self made, not sure if it is okay
            assert(v.x != 0);
            double ret = (double)(c + v.y * x) / v.x;
            return ret;
        }
        double getX(double y){ ///self made, not sure if it is okay
            assert(v.y != 0);
            double ret = (double)(c - v.x * y) / -v.y;
            return ret;
        }
        T side(pt p) ///which side a point is
        {
            return cross(v,p)-c;
        }
        double dist (pt p) /// point to line dist
        {
            return abs (side (p)) / Abs (v);
        }

        double sqDist(pt p) ///square dist
        {
            return side(p)*side(p) / (double)sq(v);
        }

        line perpThrough (pt p) /// perpendicular line with point p
        {
            return line (p, p + perp (v));
        }

        bool cmpProj (pt p, pt q) /// compare function to sort points on a line
        {
            return dot (v, p) < dot (v, q);
        }

        line translate (pt t)  /// translate with vector t
        {
            return line (v, c + cross (v, t));
        }

        line shiftLeft (double dist) /// translate with distance dist
        {
            return line (v, c + dist * Abs (v));
        }
        pt proj (pt p)
        {
            return p - perp (v) * side (p) / sq (v);
        }

        pt refl (pt p)
        {
            return p - perp (v) * 2 * side (p) / sq (v);
        }
    };

    bool areParallel (line l1, line l2)
    {
        return (l1.v.x * l2.v.y == l1.v.y * l2.v.x);
    }

    bool areSame (line l1, line l2)
    {
        return areParallel (l1, l2) and (l1.v.x * l2.c == l2.v.x * l1.c) and (l1.v.y * l2.c == l2.v.y * l1.c);
    }

    bool inter (line l1, line l2, pt& out){
        T d = cross (l1.v, l2.v);
        if (d == 0) return false;
        out = (l2.v * l1.c - l1.v * l2.c) / d;
        return true;
    }

    line intBisector (line l1, line l2, bool interior) /// if change sign then returns the other one
    {
        assert (cross (l1.v, l2.v) != 0);
        double sign = interior ? 1 : -1;
        return line (l2.v / Abs (l2.v) + l1.v * sign / Abs (l1.v),
                     l2.c / Abs (l2.v) + l1.c * sign / Abs (l1.v));
    }





    ///segment
    bool inDisk (pt a, pt b, pt p)  /// check weather point p is in diameter AB
    {
        return dot (a - p, b - p) <= 0;
    }

    bool onSegment (pt a, pt b, pt p)  /// check weather point p is in segment AB
    {
        return orient (a, b, p) == 0 and inDisk (a, b, p);
    }

    bool properInter (pt a, pt b, pt c, pt d, pt& i)
    {
        double oa = orient (c, d, a),
               ob = orient (c, d, b),
               oc = orient (a, b, c),
               od = orient (a, b, d);

        //Proper intersection exists iff opposite signs
        if (oa * ob < 0 and oc * od < 0)
        {
            i = (a * ob - b * oa) / (ob - oa);
            return true;
        }
        return false;
    }

    // To create sets of points we need a comparison function
    struct cmpX
    {
        bool operator()(pt a, pt b)
        {
            return make_pair(a.x, a.y) < make_pair(b.x, b.y);
        }
    };
    set<pt,cmpX> inters(pt a, pt b, pt c, pt d)
    {
        pt out;
        if (properInter(a,b,c,d,out))
            return {out};
        set<pt,cmpX> s;
        if (onSegment(c,d,a))
            s.insert(a);
        if (onSegment(c,d,b))
            s.insert(b);
        if (onSegment(a,b,c))
            s.insert(c);
        if (onSegment(a,b,d))
            s.insert(d);
        return s;
    }

    double segPoint (pt a, pt b, pt p) /// returns distance from a point p to segment AB
    {
        if (a != b)
        {
            line l (a, b);
            if (l.cmpProj(a, p) and l.cmpProj(p, b))
                return l.dist(p);
        }
        return min (Abs (p - a), Abs (p - b));
    }

    double segSeg (pt a, pt b, pt c, pt d) /// returns distance from a segment AB to segment CD
    {
        pt dummy;
        if (properInter(a, b, c, d, dummy))
            return 0;
        return min (min (min (segPoint(a, b, c), segPoint(a, b, d)), segPoint(c, d, a)), segPoint(c, d, b));
    }

    //int latticePoints (pt a, pt b){
    //    //requires int representation
    //    return __gcd (abs (a.x - b.x), abs (a.y - b.y)) + 1;
    //}






    /// Polygon


    bool isConvex (vector <pt>& p)
    {
        bool hasPos = false, hasNeg = false;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            int o = orient (p[i], p[(i + 1) % n], p[(i + 2) % n]);
            if (o > 0)
                hasPos = true;
            if (o < 0)
                hasNeg = true;
        }
        return !(hasPos and hasNeg);
    }

    double areaTriangle (pt a, pt b, pt c)
    {
        return abs (cross (b - a, c - a)) / 2.0;
    }

    double areaPolygon (const vector <pt>& p)
    {
        double area = 0.0;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            area += cross (p[i], p[(i + 1) % n]);
        }
        return fabs (area) / 2.0;
    }

    bool pointInPolygon(const vector <pt>& p, pt q) /// returns true if pt q is in polygon p (from rezaul, i don't know how ti works)
    {
        bool c = false;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            int j = (i + 1) % p.size();
            if ((p[i].y <= q.y and q.y < p[j].y or p[j].y <= q.y and q.y < p[i].y) and
                    q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
                c = !c;
        }
        return c;
    }

    pt centroidPolygon (vector <pt>& p) ///from rezaul, i don't know about that
    {
        pt c (0,0);
        double scale = 6.0 * areaPolygon(p);
    //    if (scale < eps) return c;
        for (int i = 0, n = p.size(); i < n; i++)
        {
            int j = (i + 1) % n;
            c = c + (p[i] + p[j]) * cross (p[i], p[j]);
        }
        return c / scale;
    }






    ///Circle

    pt circumCenter (pt a, pt b, pt c)  ///return the center of the circle go through point a, b, c
    {
        b = b - a;
        c = c - a;
        assert (cross (b, c) != 0);
        return a + perp (b * sq (c) - c * sq (b)) / cross (b, c) / 2;
    }

    bool circle2PtsRad (pt p1, pt p2, double r, pt& c)
    {
        double d2 = sq (p1 - p2);
        double det = r * r / d2 - 0.25;
        if (det < 0.0)
            return false;
        double h = sqrt (det);
        c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
        c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
        return true;
    }

    int circleLine (pt c, double r, line l, pair <pt,pt>& out)  ///circle line intersection
    {
        double h2 = r * r - l.sqDist(c);
        if (h2 < 0)
            return 0; // the line doesn't touch the circle;
        pt p = l.proj (c);
        pt h = l.v * sqrt (h2) / Abs (l.v);
        out = make_pair (p - h, p + h);
        return 1 + (h2 > 0);
    }

    int circleCircle (pt c1, double r1, pt c2, double r2, pair <pt,pt>& out)  ///circle circle intersection
    {
        pt d = c2 - c1;
        double d2 = sq (d);
        if (d2 == 0)   //concentric circles
        {
            assert (r1 != r2);
            return 0;
        }
        double pd = (d2 + r1 * r1 - r2 * r2) / 2;
        double h2 = r1 * r1 - pd * pd / d2; // h ^ 2
        if (h2 < 0)
            return 0;
        pt p = c1 + d * pd / d2, h = perp(d) * sqrt (h2 / d2);
        out = make_pair (p - h, p + h);
        return 1 + h2 > 0;
    }

    int tangents (pt c1, double r1, pt c2, double r2, bool inner, vector <pair <pt, pt >>& out)
    {
        if (inner)
            r2 = -r2;                                      /// returns tangent( the line which touch a circle in one point) of two circle,
        pt d = c2 - c1;                                           ///the same code can be used to find the tangent to a circle passing through a point by setting r2 to 0
        double dr = r1 - r2, d2 = sq (d), h2 = d2 - dr * dr;
        if (d2 == 0 or h2 < 0)
        {
            assert (h2 != 0);
            return 0;
        }
        for (int sign :
                {
                    -1, 1
                })
        {
            pt v = pt (d * dr + perp (d) * sqrt (h2) * sign) / d2;
            out.push_back (make_pair (c1 + v * r1, c2 + v * r2));
        }
        return 1 + (h2 > 0);
    }

    //Convex Hull - Monotone Chain
    pt H[100000 + 5];
    vector < pt >  monotoneChain (vector <pt>& points)  ///from rezaul
    {
        sort (points.begin(), points.end());
        vector < pt > ret;
        ret.clear();
        int st = 0;
        for (int i = 0, sz = points.size(); i < sz; i++)
        {
            while (st >= 2 and orient (H[st - 2], H[st - 1], points[i]) < 0)
                st--;
            H[st++] = points[i];
        }
        int taken = st - 1;
        for (int i = points.size() - 2; i >= 0; i--)
        {
            while (st >= taken + 2 and orient (H[st - 2], H[st - 1], points[i]) < 0)
                st--;
            H[st++] = points[i];
        }
        for(int i = 0; i < st; i++) ret.push_back(H[i]);
        return ret;
    }


    double cosA(double a, double b, double c)
    {
        double val = b * b + c * c - a * a;
        val /= (2 * b * c);
        return acos(val);
    }
    double triangle(double a, double b, double c)
    {
        double s = a + b + c;
        s /= 2;
        return sqrtl(s * (s - a) * (s - b) * (s - c));
    }
}

using namespace Geometry;

const double inf = 1000000000000000;

double eps = 1e-8;

bool LineSegInter(line l, pt a, pt b, pt& out){
    if(l.side(a) * l.side(b) > eps) return false;
    return inter(l, line(a, b), out);
}

int main(){
//    filein;
    int n;
    vector < pt > v1, v2;
    while(cin>>n){
        if(n == 0) break;
        v1.clear();
        v2.clear();

        for(int i = 0; i < n; i++){
            pt x;
            cin>>x;
            v1.push_back(x);
            v2.push_back(pt(x.x, x.y - 1));
        }
        double maxi = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                line l(v1[i], v2[j]);
                int k;
                for(k = 0; k < n; k++){
                    pt intersect;
                    if(!LineSegInter(l, v1[k], v2[k], intersect)){
                        if(k){
                            if(LineSegInter(l, v1[k], v1[k - 1], intersect)) maxi = max(maxi, intersect.x);
                            if(LineSegInter(l, v2[k], v2[k - 1], intersect)) maxi = max(maxi, intersect.x);
                        }
                        break;
                    }
                }
                if(k == n){
                    maxi = max(maxi, v1[n - 1].x);
                }
            }
        }
        printf("%.2f\n", maxi);
    }
}
