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
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

ll dp[18][2][2][2][18];
string str;


ll func(int idx, bool isstart, bool issmall, bool tight, int pos)
{
    int temp=SZ(str)-pos;
    if(idx>=pos+(temp/2+temp%2) && isstart)
    {
        if(tight==0) return 1;
        return 0;
    }
    if(idx>=SZ(str)) return 0;
    int start=0;
    ll &ret=dp[idx][isstart][issmall][tight][pos];
    if(ret!=-1) return ret;
    ret=0;
    if(isstart)
    {
        if(issmall)
        {
            for(int i=0; i<=9; i++)
                ret+=func(idx+1,1,1,0,pos);
        }
        else
        {
            for(int i=0; i<str[idx]-'0'; i++)
                ret+=func(idx+1,1,1,0,pos);
            if(tight==0)
            {
                if(str[SZ(str)-idx-1]>=str[idx])
                    ret+=func(idx+1,1,0,0,pos);
                else
                    ret+=func(idx+1,1,0,1,pos);
            }
            else
            {
                if(str[SZ(str)-idx-1]>str[idx] && (SZ(str)-idx-1>idx))
                    ret+=func(idx+1,1,0,0,pos);
                else
                    ret+=func(idx+1,1,0,1,pos);
            }

        }

    }
    else
    {
        if(issmall)
        {
            for(int i=1; i<=9; i++)
                ret+=func(idx+1,1,1,0,idx);
        }
        else
        {
            for(int i=1; i<str[idx]-'0'; i++)
                ret+=func(idx+1,1,1,0,idx);
            if(str[SZ(str)-idx-1]>=str[idx])
                ret+=func(idx+1,1,0,0,idx);
            else
                ret+=func(idx+1,1,0,1,idx);
        }
    }
    if(isstart==0)
        ret+=func(idx+1,0,1,0,0);
    return ret;
}

ll call(ll n)
{
    if(n<0) return 0;
    if(n==0) return 1;
    stringstream ss;
    ss<<n;
    ss>>str;
    ms(dp,-1);
    ll ret=func(0,0,0,0,0)+1; // Extra +1 for 0
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ll a,b;
        sffl(a,b);
        if(a>b)
            swap(a,b);

        ll ans=call(b)-call(a-1);
        PRINT_CASE;
        printf("%lld\n",ans);

    }

    return 0;
}
