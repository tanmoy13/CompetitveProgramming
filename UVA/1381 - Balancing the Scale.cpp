#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define D(x)             cerr<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
#define MOD              1000000007
#define fast_cin         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define UNIQUE(v)        (v).erase(unique((v).begin(),(v).end()),(v).end())
#define POPCOUNT         __builtin_popcountll
#define RIGHTMOST        __builtin_ctzll
#define LEFTMOST(x)      (63-__builtin_clzll((x)))
#define NUMDIGIT(x,y)    (((vlong)(log10((x))/log10((y))))+1)
#define NORM(x)          if(x>=mod) x-=mod;if(x<0) x+=mod;
#define ODD(x)           (((x)&1)==0?(0):(1))
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

//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


/*----------------------Graph Moves----------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

/*-----------------------Bitmask------------------*/
int Set(int N,int pos)
{
    return N=N | (1<<pos);
}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos)
{
    return (bool)(N & (1<<pos));
}
/*------------------------------------------------*/



bool vis[1<<17];
vector<int>masks;


void select4(int mask, vector<int>temp)
{
    if(POPCOUNT(mask)==4)
    {
        if(vis[mask]==0)
        {
            masks.pb(mask);
            vis[mask]=1;
        }
        return;
    }

    if(vis[mask]) return;
    vis[mask]=1;

    for(int i=0; i<16; i++)
    {
        if(check(mask,i)==0)
        {
            temp.pb(i);
            select4(Set(mask,i),temp);
            temp.pop_back();
        }
    }
}

int ara[20];

ll cnt[1<<17];

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    select4(0, {});

    int a=0;
    int z=0;
    while(sf(a) && a)
    {
        z++;
        ara[0]=a;
        for(int i=1; i<16; i++)
            sf(ara[i]);
        sort(ara,ara+16);
        ms(cnt,0);
        vector<int>v[10245];

        for(int i=0; i<SZ(masks); i++)
        {
//            D(i);
            vector<int>v1;
            int mask=masks[i];
            for(int j=0; j<16; j++)
            {
                if(check(mask,j))
                    v1.pb(ara[j]);
            }

            do
            {
                int sum=v1[0]+2*v1[1]+3*v1[2]+4*v1[3];
                for(int j=0; j<SZ(v[sum]); j++)
                {
                    if(v[sum][j]&mask) continue;
                    cnt[v[sum][j]|mask]++;
                }
                v[sum].pb(mask);
            }
            while(next_permutation(all(v1)));
        }

        int mask=(1<<16)-1;
        ll ans=0;
        for(int i=0; i<=mask; i++)
        {
            ans+=cnt[i]*cnt[mask^i];
        }
        PRINT_CASE;
        printf("%lld\n",ans/2);

    }
    return 0;
}



