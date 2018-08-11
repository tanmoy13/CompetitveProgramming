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
#define MOD              100000007
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

ll numbers[1000006];
int cnt=0;
void generate_num()
{
    for(ll i=2;i<=100000;i++)
    {
        ll num=i*i;
        while(num<=10000000000)
        {
          numbers[cnt++]=num;
          num*=i;
        }
    }

    sort(numbers,numbers+cnt);
    cnt=unique(numbers,numbers+cnt)-numbers;
    numbers[cnt++]=1000000000000000;

}

ll fact[1000006];

void gen_fact()
{
    fact[0]=1;
    for(int i=1;i<=1000005;i++)
    {
        fact[i]=(fact[i-1]*i)%MOD;
    }
}

ll mod_inv(ll n, ll pow)
{
    if(pow==0) return 1;
    if(pow%2==0)
    {
        ll ret=mod_inv(n,pow/2)%MOD;
        return (ret*ret)%MOD;
    }
    return ((n%MOD)*(mod_inv(n,pow-1)%MOD))%MOD;
}



int main()
{

    ///freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    generate_num();
    gen_fact();

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ll a,b;
        sffl(a,b);

        ll r=upper_bound(numbers,numbers+cnt,b)-numbers;
        ll l=lower_bound(numbers,numbers+cnt,a)-numbers;
        ll n=(r-l);
        PRINT_CASE;
        if(n==0)
            pf("0\n");
        else
        {
            ll ans=(fact[n+1]*fact[n])%MOD;
            ans=mod_inv(ans,MOD-2);
            ans=(fact[2*n]*ans)%MOD;
            pf("%lld\n",ans);
        }


    }

    return 0;
}
