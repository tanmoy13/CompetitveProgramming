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

struct node
{
    int val;
    node *l,*r;
    node(int a=0,node *b=NULL, node *c=NULL):val(a),l(b),r(c) {}
};

node *root[mx];

//node *init(int b, int e)
//{
//    if(b==e)
//    {
//        node *p = new node;
//        return p;
//    }
//    node *ret = new node;
//    int mid=(b+e)/2;
//    ret->l=init(b,mid);
//    ret->r=init(mid+1,e);
//    ret->val=ret->l->val+ret->r->val;
//    return ret;
//}

node *update(node *cur, int b, int e, int i)
{
    if(b>i || e<i) return cur;
    if(b==e && b==i)
    {
        node *p = new node(1);
        return p;
    }
    node *ret=new node;
    int mid=(b+e)/2;
    ret->l=update(cur?cur->l:NULL,b,mid,i);
    ret->r=update(cur?cur->r:NULL,mid+1,e,i);
    if(ret->l)
        ret->val+=ret->l->val;
    if(ret->r)
        ret->val+=ret->r->val;
    return ret;
}

int query(node *cur, node *prev, int b, int e, int k)
{
    if(k==1 && b==e)
    {
        return b;
    }
    int mid=(b+e)/2;

    int temp=0;
    if(cur && cur->l)
        temp=cur->l->val;
    if(cur!=prev && prev && prev->l) temp-=prev->l->val;
    if(temp>=k)
        return query(cur->l,prev?prev->l:NULL,b,mid,k);
    else
        return query(cur->r,prev?prev->r:NULL,mid+1,e,k-temp);
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,m;
    sff(n,m);
    const int mx_node=1000000009;
//    root[0]=init(1,mx_node);

    map<int,int>mp1,mp2;
    int cnt=0;
    vector<int>v,v1;
    for(int i=0; i<n; i++)
    {
        int a;
        sf(a);
        v.pb(a);
        v1.pb(a);
    }
    sort(all(v));
    for(int i=0; i<SZ(v); i++)
    {
        int a=v[i];
        if(mp1[a]==0)
        {
            mp1[a]=++cnt;
            mp2[cnt]=a;
        }
    }
    cnt+=5;
    for(int i=1; i<=n; i++)
    {

        int val=mp1[v1[i-1]];
        root[i]=update(root[i-1],1,cnt,val);
//        DD(i,root[i]->val);
    }

    while(m--)
    {
        int a,b,k;
        sfff(a,b,k);
        int ans=query(root[b],root[a-1],1,cnt,k);
        ans=mp2[ans];
        printf("%d\n",ans);
    }


    return 0;
}

