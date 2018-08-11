#include <bits/stdc++.h>

#define pii              pair <int,int>
#define pll              pair <long long,long long>
#define sc               scanf
#define pf               printf
#define Pi               2*acos(0.0)
#define ms(a,b)          memset(a, b, sizeof(a))
#define pb(a)            push_back(a)
#define MP               make_pair
#define db               double
#define ll               long long
#define EPS              10E-10
#define ff               first
#define ss               second
#define sqr(x)           (x)*(x)
#define D(x)             cout<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
#define MOD              1000000007
#define CIN              ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define loop(i,n)        for(int i=0;i<n;i++)
#define loop1(i,n)       for(int i=1;i<=n;i++)
#define REP(i,a,b)       for(int i=a;i<b;i++)
#define RREP(i,a,b)      for(int i=a;i>=b;i--)
#define TEST_CASE(t)     for(int z=1;z<=t;z++)
#define PRINT_CASE       printf("Case %d: ",z)
#define LINE_PRINT_CASE  printf("Case %d:\n",z)
#define CASE_PRINT       cout<<"Case "<<z<<": "
#define all(a)           a.begin(),a.end()
#define intlim           2147483648
#define infinity         (1<<28)
#define ull              unsigned long long
#define gcd(a, b)        __gcd(a, b)
#define lcm(a, b)        ((a)*((b)/gcd(a,b)))

using namespace std;


/*----------------------Graph Moves----------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

/*-----------------------Bitmask------------------*/
int Set(int N,int pos){return N=N | (1<<pos);}
int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

int s,m,n;

int m1,m2,ara[102],cost[102];

int dp[102][1<<8][1<<8];
int cases[102][1<<8][1<<8];
int zz=0;

int func(int idx, int mask1, int mask2)
{
    if(__builtin_popcount(mask1)==s && __builtin_popcount(mask2)==s) return 0;
    if(idx>=n) return (1<<20);
    int &ret=dp[idx][mask1][mask2];
    int &cas=cases[idx][mask1][mask2];
    if(cas==zz) return ret;
    cas=zz;
    ret=INT_MAX;
    int mm1=mask1,mm2=mask2;
    for(int i=0;i<s;i++)
    {
        if(check(ara[idx],i))
        {
            if(check(mm1,i))
                mm2=Set(mm2,i);
            else
                mm1=Set(mm1,i);
        }
    }

    ret=min(ret,cost[idx]+func(idx+1,mm1,mm2));
    ret=min(ret,func(idx+1,mask1,mask2));
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    while(cin>>s>>m>>n && s)
    {
        ll ans=0;
        string str;
        getchar();
        m1=0,m2=0;
        ms(ara,0);
        for(int i=0;i<m;i++)
        {
            getline(cin,str);
            stringstream ss;
            ss<<str;
            vector<int>v;
            int a;
            while(ss>>a)
            {
                v.pb(a);
            }

            ans+=v[0];

            for(int j=1;j<SZ(v);j++)
            {
                v[j]--;
                if(check(m1,v[j]))
                {
                    if(check(m2,v[j])) continue;
                    m2=Set(m2,v[j]);
                }
                else
                    m1=Set(m1,v[j]);
            }
        }

        for(int i=0;i<n;i++)
        {
            getline(cin,str);
            stringstream ss;
            ss<<str;
            vector<int>v;
            int a;
            while(ss>>a)
            {
                v.pb(a);
            }

            cost[i]=v[0];
            for(int j=1;j<SZ(v);j++)
            {
                v[j]--;
                ara[i]=Set(ara[i],v[j]);
            }
        }
        zz++;
        ans+=func(0,m1,m2);

        cout<<ans<<endl;

    }

    return 0;
}
