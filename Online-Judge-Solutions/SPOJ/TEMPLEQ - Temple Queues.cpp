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


int mp[mx],rmp[mx];

int tree[3*mx], lazy[3*mx];
vector<pii>v;

void push_down(int n, int l, int r)
{
    if(lazy[n])
    {
        tree[l]+=lazy[n];
        tree[r]+=lazy[n];
        lazy[l]+=lazy[n];
        lazy[r]+=lazy[n];
        lazy[n]=0;
    }
}

void init(int n, int b, int e)
{
    if(b==e)
    {
        tree[n]=v[b-1].ff;
        lazy[n]=0;
        return;
    }
    segment_tree;
    init(l,b,mid);
    init(r,mid+1,e);
    tree[n]=max(tree[l],tree[r]);
    lazy[n]=0;
}

int query_rgt(int n, int b, int e, int i, int j, int val)
{
    if(j<i) return e+1;
    if(b>j || e<i) return -1;
    if(b>=i && e<=j && tree[n]<=val) return e+1;
    if(b==e)
    {
        return b;
    }
    segment_tree;
    push_down(n,l,r);
    int p=-1,q=-1;
    p=query_rgt(l,b,mid,i,j,val);
    if(p==-1 || p==mid+1)
        q=query_rgt(r,mid+1,e,i,j,val);
    return max(p,q);
}

void update(int n, int b, int e, int i, int j, int val)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        tree[n]+=val;
        lazy[n]+=val;
        return;
    }
    segment_tree;
    push_down(n,l,r);
    update(l,b,mid,i,j,val);
    update(r,mid+1,e,i,j,val);
    tree[n]=max(tree[l],tree[r]);
}


int query(int n, int b, int e, int val)
{
    if(b==e)
    {
        return b;
    }
    segment_tree;
    push_down(n,l,r);
    if(tree[l]<val)
        return query(r,mid+1,e,val);
    else
        return query(l,b,mid,val);
}

int get_val(int n, int b, int e, int i)
{
    if(b>i || e<i) return 0;
    if(b==e)
        return tree[n];
    segment_tree;
    push_down(n,l,r);
    int p=get_val(l,b,mid,i);
    int q=get_val(r,mid+1,e,i);
    return max(p,q);
}


int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,m;
    sff(n,m);


    for(int i=1; i<=n; i++)
    {
        int a;
        sf(a);
        v.pb(pii(a,i));
    }

    sort(all(v));

    for(int i=0; i<n; i++)
    {
        int idx=i+1;
        mp[v[i].ss]=idx;
        rmp[idx]=v[i].ss;
    }

    init(1,1,n);

    while(m--)
    {
        int a,b;
        sff(a,b);
        if(a==1)
        {
            int idx=mp[b];
            int val=get_val(1,1,n,idx);
//            val++;
            int idxRgt=query_rgt(1,1,n,idx+1,n,val);
            idxRgt--;
            if(idxRgt==idx)
            {
                update(1,1,n,idx,idx,1);
            }
            else
            {
                int tempid=rmp[idxRgt];
                swap(mp[b],mp[tempid]);
                swap(rmp[idx],rmp[idxRgt]);
                update(1,1,n,idxRgt,idxRgt,1);
            }
        }
        else if(a==2)
        {
            int ans=0;
            if(tree[1]>=b)
            {
                int idx=query(1,1,n,b);
                ans=n-idx+1;
            }
            printf("%d\n",ans);
        }
        else
        {
            if(tree[1]<b) continue;
            int idx=query(1,1,n,b);
            update(1,1,n,idx,n,-1);
        }
    }


    return 0;
}
