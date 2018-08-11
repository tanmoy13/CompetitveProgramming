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

#define mx 3162378

bitset<mx/2>vis;
vector<ll>prime;

void sieve()
{
    int x=mx/2,y=sqrt(mx)/2;
    for(int i=1;i<y;i++)
    {
        if(vis[i]==0)
        {
            for(int j=i*(i+1)*2;j<x;j+=(2*i)+1)
                vis[j]=1;
        }
    }
    prime.pb(2);
    for(int i=3;i<mx;i+=2)
        if(vis[i/2]==0)
        prime.pb(i);
}

vector<pll>prime_factor;

vector<ll>divisors;

void generate_divisor(int idx, ll num)
{
    if(idx>=SZ(prime_factor))
    {
        divisors.pb(num);
        return;
    }
    ll next=prime_factor[idx].ff;
    for(int i=0;i<prime_factor[idx].ss;i++)
    {
        generate_divisor(idx+1,num*next);
        next*=prime_factor[idx].ff;
    }
    generate_divisor(idx+1,num);
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    sieve();
//    D(SZ(prime));
//    for(int i=0;i<100;i++)
//        cout<<prime[i]<<" ";

    ll n;
    while(sfl(n) && n)
    {
        ll num=n;
        ll ans=0;
        ll divisor=1;
        int root=sqrt(n);
        for(int i=0;i<SZ(prime) && prime[i]<=root;i++)
        {
            if(n%prime[i]==0)
            {
                ll cnt=0;
                while(n%prime[i]==0)
                {
                    cnt++;
                    n/=prime[i];
                }
                root=sqrt(n);
                divisor*=(cnt+1);
                prime_factor.pb(pll(prime[i],cnt));
            }
        }
        if(n>1)
        {
            prime_factor.pb(pll(n,1));
            divisor*=2;
        }

//        D(divisor);

        generate_divisor(0,1);

//        for(int i=0;i<SZ(divisors);i++)
//            cout<<divisors[i]<<" ";
//        cout<<endl;

        for(int i=0;i<SZ(divisors);i++)
        {
            ll num1=num;
            if(divisors[i]==1) continue;
            while(num1%divisors[i]==0)
            {
                ans++;
                num1/=divisors[i];
            }
        }

        printf("%lld %lld\n",num,ans);
        prime_factor.clear();
        divisors.clear();

    }


    return 0;
}
