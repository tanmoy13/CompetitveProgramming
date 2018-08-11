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

pll dp[32][2][3][7][32][32];
int cases[32][2][3][7][32][32];
string str,ideal_str;
ll st,ed,mxone,ideal,k;
int zz=0;

pll func(int idx, int issmall, ll mod3, ll mod7, int miss, int one)
{
    if(idx>=SZ(str))
    {
        if(mod3==0 && mod7!=0 && miss<=k && one<=mxone) return pll(1,0);
        return pll(0,0);
    }
    if(one>mxone || miss>k) return pll(0,0);
    pll &ret=dp[idx][issmall][mod3][mod7][miss][one];
    int &cas=cases[idx][issmall][mod3][mod7][miss][one];
    if(cas==zz) return ret;
    cas=zz;
    ret=pll(0,0);
    if(issmall)
    {
        ll pos=SZ(str)-idx-1;
        pos=1LL<<pos;
        pll temp=func(idx+1,1,(mod3+pos)%3,(mod7+pos)%7,miss+(ideal_str[idx]!='1'),one+1);
        ret.ff+=temp.ff;
        ret.ss+=(pos*temp.ff)+temp.ss;
        temp=func(idx+1,1,mod3,mod7,miss+(ideal_str[idx]!='0'),one);
        ret.ff+=temp.ff;
        ret.ss+=temp.ss;
    }
    else
    {
        pll temp;
        if(str[idx]=='0')
        {
            temp=func(idx+1,0,mod3,mod7,miss+(ideal_str[idx]!='0'),one);
            ret.ff+=temp.ff;
            ret.ss+=temp.ss;
        }
        else
        {
            temp=func(idx+1,1,mod3,mod7,miss+(ideal_str[idx]!='0'),one);
            ret.ff+=temp.ff;
            ret.ss+=temp.ss;
            ll pos=SZ(str)-idx-1;
            pos=1LL<<pos;
            temp=func(idx+1,0,(mod3+pos)%3,(mod7+pos)%7,miss+(ideal_str[idx]!='1'),one+1);
            ret.ff+=temp.ff;
            ret.ss+=(pos*temp.ff)+temp.ss;
        }
    }
    return ret;
}

ll call(ll n)
{
    if(n<0) return 0;
    bitset<32>temp(n);
    str=temp.to_string();
    zz++;
    ll ret=func(0,0,0,0,0,0).ss;
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
        sfffl(st,ed,mxone);
        sffl(ideal,k);
        bitset<32>temp(ideal);
        ideal_str=temp.to_string();

        ll a=call(ed);
        ll b=call(st-1);

        PRINT_CASE;
        printf("%lld\n",a-b);

    }

    return 0;
}
