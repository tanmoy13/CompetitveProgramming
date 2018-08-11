//#include <bits/stdc++.h>
//
//#define pii              pair <int,int>
//#define pll              pair <long long,long long>
//#define sc               scanf
//#define pf               printf
//#define Pi               2*acos(0.0)
//#define ms(a,b)          memset(a, b, sizeof(a))
//#define pb(a)            push_back(a)
//#define MP               make_pair
//#define db               double
//#define ll               long long
//#define EPS              10E-10
//#define ff               first
//#define ss               second
//#define sqr(x)           (x)*(x)
//#define D(x)             cout<<#x " = "<<(x)<<endl
//#define VI               vector <int>
//#define DBG              pf("Hi\n")
//#define MOD              1000000007
//#define CIN              ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
//#define SZ(a)            (int)a.size()
//#define sf(a)            scanf("%d",&a)
//#define sfl(a)           scanf("%lld",&a)
//#define sff(a,b)         scanf("%d %d",&a,&b)
//#define sffl(a,b)        scanf("%lld %lld",&a,&b)
//#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
//#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
//#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
//#define loop(i,n)        for(int i=0;i<n;i++)
//#define loop1(i,n)       for(int i=1;i<=n;i++)
//#define REP(i,a,b)       for(int i=a;i<b;i++)
//#define RREP(i,a,b)      for(int i=a;i>=b;i--)
//#define TEST_CASE(t)     for(int z=1;z<=t;z++)
//#define PRINT_CASE       printf("Case %d:\n",z)
//#define CASE_PRINT       cout<<"Case "<<z<<":"<<endl
//#define all(a)           a.begin(),a.end()
//#define intlim           2147483648
//#define infinity         (1<<28)
//#define ull              unsigned long long
//#define gcd(a, b)        __gcd(a, b)
//#define lcm(a, b)        ((a)*((b)/gcd(a,b)))
//
//using namespace std;
//
//
///*----------------------Graph Moves----------------*/
////const int fx[]={+1,-1,+0,+0};
////const int fy[]={+0,+0,+1,-1};
////const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
////const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
////const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
////const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
///*------------------------------------------------*/
//
///*-----------------------Bitmask------------------*/
////int Set(int N,int pos){return N=N | (1<<pos);}
////int reset(int N,int pos){return N= N & ~(1<<pos);}
////bool check(int N,int pos){return (bool)(N & (1<<pos));}
///*------------------------------------------------*/
//
//map<string,int>mp;
//char s1[200],s2[100005];
//
//int main()
//{
//
//
////    freopen("in.txt","r",stdin);
//    ///freopen("out.txt","w",stdout);
//    int t;
//
//    sf(t);
//    TEST_CASE(t)
//    {
//        int n;
//        sf(n);
//        getchar();
//        loop(i,n)
//        {
//            sc("%s",s1);
//            int l=strlen(s1);
//            string str(s1,s1+l);
//            if(SZ(str)>3)
//                sort(str.begin()+1,str.end()-1);
//            mp[str]++;
//        }
//
//        sf(n);
//
//        getchar();
//
//        PRINT_CASE;
//
//        for(int i=0; i<n; i++)
//        {
//            ll ans=1;
//            gets(s2);
//            int l=strlen(s2);
//            string str(s2,s2+l);
//            stringstream ss;
//            ss<<str;
//            while(ss>>str)
//            {
//                if(SZ(str)>3)
//                    sort(str.begin()+1,str.end()-1);
//                ans*=mp[str];
//            }
//            pf("%lld\n",ans);
//
//        }
//
//        mp.clear();
//    }
//
//    return 0;
//}



#include <bits/stdc++.h>
#define LL  long long
#define REP(i,n) for(int i=0;i<n;i++)
#define REV(i,n) for(int i=n-1;i>=0;i--)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define pri(a) cout<<a<<endl
#define prii(a,b) cout<<a<<" "<<b<<endl
#define priii(a,b,c) cout<<a<<" "<<b<<" "<<c<<endl
#define hi printf("Hello World\n");
using namespace std;

const int INF = 1<<29;
const int MX  = 1e5+10;

int main()
{
    string mnth[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    string m1,m2;
    LL T,d1,d2,y1,y2;
    char ch;

    map <string, int> mp;

    REP(i,12)  mp[mnth[i]] = i;

    cin>>T;

    FOR(i,1,T)
    {
        cin>>m1>>d1>>ch>>y1;
        cin>>m2>>d2>>ch>>y2;

        if(mp[m1] > 1) y1++;
        /// if first month greater than february, then we don't need that yr, can subtract that

        if(mp[m2] == 0 or (mp[m2]==1 and d2<29)) y2--;
        ///if last mnth less than feb 29, then we don't need that yr, subtract also

        LL ans = y2/4 - (y1-1)/4;
        ans -= y2/100 - (y1-1)/100;
        ans += y2/400 - (y1-1)/400;

        printf("Case %d: %lld\n", i, ans);
    }
    return 0;
}
