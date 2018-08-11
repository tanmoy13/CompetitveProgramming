/*
Hint : https://www.quora.com/How-can-the-SPOJ-problem-GSS2-be-solved/answer/Brian-Bi?srid=29u8
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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


int ara[mx+5];
int last[2*mx+5];
ll ans[mx+5];

struct data
{
    int l,r,id;
};

vector<data>queries;

struct data1
{
    ll sum,lazy,best_lazy,ans;
    data1()
    {
        sum=lazy=best_lazy=ans=0;
    }
};

data1 tree[3*mx];

void push_down(data1 &cur, data1 &lft, data1 &rgt)
{
//    if(cur.lazy || cur.best_lazy)
//    {
        lft.best_lazy=max(lft.best_lazy,lft.lazy+cur.best_lazy);
        lft.lazy+=cur.lazy;
        lft.ans=max(lft.ans,lft.sum+cur.best_lazy);
        lft.sum=lft.sum+cur.lazy;
        rgt.best_lazy=max(rgt.best_lazy,rgt.lazy+cur.best_lazy);
        rgt.lazy+=cur.lazy;
        rgt.ans=max(rgt.ans,rgt.sum+cur.best_lazy);
        rgt.sum+=cur.lazy;
        cur.lazy=cur.best_lazy=0;
//    }
}

void push_up(data1 &cur, data1 &lft, data1 &rgt)
{
    cur.ans=max(lft.ans,rgt.ans);
    cur.sum=max(lft.sum,rgt.sum);
}


void update(int n, int b, int e, int i, int j, ll val)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        tree[n].best_lazy=max(tree[n].best_lazy,tree[n].lazy+val);
        tree[n].lazy+=val;
        tree[n].ans=max(tree[n].ans,tree[n].sum+val);
        tree[n].sum+=val;
        return;
    }
    segment_tree;
    push_down(tree[n],tree[l],tree[r]);
    update(l,b,mid,i,j,val);
    update(r,mid+1,e,i,j,val);
    push_up(tree[n],tree[l],tree[r]);
}

data1 query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return data1();
    if(b>=i && e<=j)
    {
        return tree[n];
    }
    segment_tree;
    push_down(tree[n],tree[l],tree[r]);
    data1 p=query(l,b,mid,i,j);
    data1 q=query(r,mid+1,e,i,j);
    data1 ret;
    push_up(ret,p,q);
    return ret;
}


int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int n;
    sf(n);
    for(int i=1; i<=n; i++) sf(ara[i]);
    int m;
    sf(m);
    data a;
    for(int i=0; i<m; i++)
    {
        sff(a.l,a.r);
        a.id=i;
        queries.pb(a);
    }

    sort(all(queries),[](data a,data b)
    {
        return a.r<b.r;
    });

    int idx=0;
    for(int i=1; i<=n && idx<SZ(queries); i++)
    {
//        if(last[mx+ara[i]]!=0)
//        {
//            update(1,1,n,last[mx+ara[i]],0);
//        }
        int xx=last[mx+ara[i]]+1;
        update(1,1,n,xx,i,ara[i]);
        last[mx+ara[i]]=i;
        while(idx<SZ(queries) && queries[idx].r==i)
        {
            ans[queries[idx].id]=query(1,1,n,queries[idx].l,queries[idx].r).ans;
            idx++;
        }
    }

    for(int i=0; i<m; i++)
        printf("%lld\n",ans[i]);



    return 0;
}
