

#include <bits/stdc++.h>

#define pii pair <int,int>
#define sc scanf
#define pf printf
#define Pi 2*acos(0.0)
#define ms(a,b) memset(a, b, sizeof(a))
#define pb(a) push_back(a)
#define MP make_pair
#define oo 1<<29
#define dd double
#define ll long long
#define EPS 10E-10
#define ff first
#define ss second
#define MAX 10000
#define CIN ios_base::sync_with_stdio(0)
#define SZ(a) (int)a.size()
#define getint(a) scanf("%d",&a)
#define loop(i,n) for(int i=0;i<n;i++)
#define TEST_CASE(t) for(int z=1;z<=t;z++)
#define PRINT_CASE printf("Case %d: ",z)
#define all(a) a.begin(),a.end()
#define intlim 2147483648
#define inf 1000000
#define rtintlim 46340
#define llim 9223372036854775808
#define rtllim 3037000499
#define ull unsigned long long
#define I int

using namespace std;

double angle (double a, double b, double c)
{
    return acos((a*a+b*b-c*c)/(2.0*a*b));
}
int main()
{

    ///freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);
    int t;
    cin>>t;
    TEST_CASE(t)
    {
        double r1,r2,r3;
        cin>>r1>>r2>>r3;
        double a,b,c;
        a=r1+r2;
        b=r3+r2;
        c=r3+r1;
        double s=(a+b+c)/2;
        double area = sqrt(s*(s-a)*(s-b)*(s-c));
        area-=angle(a,b,c)/2*r2*r2;
        area-=angle(a,c,b)/2*r1*r1;
        area-=angle(b,c,a)/2*r3*r3;
//        PRINT_CASE;
        pf("%.06lf\n",area);
    }
    return 0;
}
