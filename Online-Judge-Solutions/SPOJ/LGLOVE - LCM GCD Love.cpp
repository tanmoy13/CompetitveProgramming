/*
    Author: Tanmoy Datta
    Solution Idea:
        - Most important observation for this problem is after any update the number must be in range 0 to 300000.
        - So we can precalculate lcm(1,2,3....X) for every X from 1 to 300000.
        - Now if you think carefully you will find that lcm of a range in array B comes from the maximum number in the given range
          in array A and on the other hand gcd come from the minimum.
        - We can process update and query operation for range update and min max query using a segment tree with lazy propagation.
*/

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
#define VI               vector <int>
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
#define D(x)        	 cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)          cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)       cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG              cerr << __LINE__ << ": Hi" << '\n'

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
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

#define mx 300006


/*----------------Sieve--------------------*/
vector<int>prime;
bool vis[mx];

void sieve()
{
    int x=sqrt((int)mx);
    for(int i=3; i<=x; i+=2)
    {
        if(vis[i]==0)
        {
            for(int j=i*i; j<mx; j+=2*i)
                vis[j]=1;
        }
    }
    prime.pb(2);
    for(int i=3; i<mx; i+=2)
        if(vis[i]==0)
            prime.pb(i);
}

long long bigmod (long long a, long long p, long long m)
{
    long long res = 1 % m, x = a % m;
    while (p>0)
    {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m;
        p >>= 1;
    }
    return res;
}

int cnt_power[mx];
ll lcmm[mx];

void init()
{
    ll num=1;
    lcmm[1]=1;
    for(int i=2; i<mx; i++)
    {
        ll x=i;
        ll root=sqrt(x);
        for(int j=0; j<SZ(prime) && prime[j]<=root; j++)
        {
            if(x%prime[j]==0)
            {
                int cnt=0;
                while(x%prime[j]==0)
                {
                    cnt++;
                    x/=prime[j];
                }
                root=sqrt(x);
                ll y=max(0,cnt-cnt_power[prime[j]]);
                ll temp=bigmod(prime[j],y,MOD);
                cnt_power[prime[j]]=max(cnt_power[prime[j]],cnt);
                num=(num*temp)%MOD;
            }
        }
        if(x>1)
        {
            if(cnt_power[x]==0)
            {
                num=(num*x)%MOD;
                cnt_power[x]=1;
            }
        }
        lcmm[i]=num;
    }

}

#define segment_tree int l=n*2,r=l+1,mid=(b+e)/2

struct data
{
    ll maxi,mini,lazy;
};

data tree[3*mx];

void push_down(int n, int b, int e)
{
    segment_tree;
    if(tree[n].lazy)
    {
        tree[l].maxi+=tree[n].lazy;
        tree[l].mini+=tree[n].lazy;
        tree[l].lazy+=tree[n].lazy;
        tree[r].maxi+=tree[n].lazy;
        tree[r].mini+=tree[n].lazy;
        tree[r].lazy+=tree[n].lazy;
        tree[n].lazy=0;
    }
}

void update(int n, int b, int e, int i, int j, ll val, int type=0)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        if(type==1)
        {
            tree[n].maxi=val;
            tree[n].mini=val;
            tree[n].lazy=0;
            return;
        }
        else
        {
            tree[n].maxi+=val;
            tree[n].mini+=val;
            tree[n].lazy+=val;
            return;
        }
    }
    segment_tree;
    push_down(n,b,e);
    update(l,b,mid,i,j,val,type);
    update(r,mid+1,e,i,j,val,type);
    tree[n].maxi=max(tree[l].maxi,tree[r].maxi);
    tree[n].mini=min(tree[l].mini,tree[r].mini);
}

ll query(int n, int b, int e, int i, int j, int type)
{
    if(b>j || e<i)
    {
        if(type==0) return (1LL<<50);
        if(type==1) return 0;
    }
    if(b>=i && e<=j)
    {
        if(type==0)
            return tree[n].mini;
        if(type==1)
            return tree[n].maxi;
    }
    segment_tree;
    push_down(n,b,e);
    ll p=query(l,b,mid,i,j,type);
    ll q=query(r,mid+1,e,i,j,type);
    if(type==0)
        return min(p,q);
    if(type==1)
        return max(p,q);
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    sieve();
    init();

    int n,m;
    sff(n,m);

    for(int i=1; i<=n; i++)
    {
        ll a;
        sfl(a);
        update(1,1,n,i,i,a,1);
    }

    int t,i,j,p;
    while(m--)
    {
        sfff(t,i,j);
        i++;
        j++;
        if(t==0)
        {
            sf(p);
            update(1,1,n,i,j,p);
        }
        else if(t==1)
        {
            ll x = query(1,1,n,i,j,1);
            printf("%lld\n",lcmm[x]);
        }
        else if(t==2)
        {
            ll x=query(1,1,n,i,j,0);
            printf("%lld\n",lcmm[x]);
        }
    }

    return 0;
}
