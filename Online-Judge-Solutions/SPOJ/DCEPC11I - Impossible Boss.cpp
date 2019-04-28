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

#define mx 100005

#define segment_tree int l=n*2,r=l+1,mid=(b+e)/2

ll ara[mx];

struct data
{
    ll sum;
    ll start;
    ll cnt;
};

data tree[4*mx];

ll get_sum(ll a, ll d, ll n)
{
    ll ret=(2*a+(n-1)*d)*n;
    ret/=2;
    return ret;
}

void push_down(int n, int b, int e)
{
    if(tree[n].cnt)
    {
        segment_tree;
        ll total=mid-b+1;
        tree[l].sum+=get_sum(tree[n].start,tree[n].cnt,total);
        tree[l].start+=tree[n].start;
        tree[l].cnt+=tree[n].cnt;
        ll rgt=tree[n].start+(total)*tree[n].cnt;

        total=e-mid;
        tree[r].sum+=get_sum(rgt,tree[n].cnt,total);
        tree[r].start+=rgt;
        tree[r].cnt+=tree[n].cnt;

        tree[n].start=0;
        tree[n].cnt=0;
    }
}

void update(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        ll temp=b-i+1;
        tree[n].sum+=get_sum(temp,1,e-b+1);
        tree[n].start+=temp;
        tree[n].cnt++;
        return;
    }

    segment_tree;

    push_down(n,b,e);

    update(l,b,mid,i,j);
    update(r,mid+1,e,i,j);

    tree[n].sum=tree[l].sum+tree[r].sum;

}

ll query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return 0;
    if(b>=i && e<=j)
    {
        return tree[n].sum;
    }
    segment_tree;
    push_down(n,b,e);

    ll p=query(l,b,mid,i,j);
    ll q=query(r,mid+1,e,i,j);
    return p+q;
}

//char str[10];

//ll bigmod(ll n, ll p)
//{
//    ll ret=1;
//    while(p>0)
//    {
//        if(p%2)
//            ret=(ret*n)%MOD;
//        n=(n*n)%MOD;
//        p/=2;
//    }
//    return ret;
//}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif


    int n,q;
    sff(n,q);

//    for(int i=1;i<=n;i++)
//    {
//        sfl(ara[i]);
//        ara[i]%=MOD;
//    }
//
    int a,b,c;

    while(q--)
    {
        sfff(c,a,b);
        if(c==0)
        {
//            sff(a,b);
//            a++;
//            if(a<=b)
                update(1,1,n,a,b);
        }
        else
        {
//            sf(a);
            ll ans=query(1,1,n,a,b);
//            ll ans=bigmod(3,p);
//            ans=(ans*ara[a])%MOD;
            printf("%lld\n",ans);
        }
    }

    return 0;
}
