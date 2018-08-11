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
struct data
{
    ll sum,sqrsum,lazy,upd;
};

data tree[3*mx];

ll ara[mx];

void push_down(int n, int b, int e)
{
    segment_tree;
    if(tree[n].upd)
    {
        tree[l].lazy=0;
        tree[r].lazy=0;
        tree[l].sum=(mid-b+1)*tree[n].upd;
        tree[l].sqrsum=(mid-b+1)*sqr(tree[n].upd);
        tree[r].sum=(e-mid)*tree[n].upd;
        tree[r].sqrsum=(e-mid)*sqr(tree[n].upd);
        tree[l].upd=tree[n].upd;
        tree[r].upd=tree[n].upd;
        tree[n].upd=0;
    }
    if(tree[n].lazy)
    {
//        tree[l].lazy+=tree[n].lazy;
//        tree[l].status=1;
//        tree[r].lazy+=tree[n].lazy;
//        tree[r].status=1;
//        tree[n].status=0;
        tree[l].sqrsum+=(tree[l].sum*(2*tree[n].lazy))+(mid-b+1)*sqr(tree[n].lazy);
        tree[r].sqrsum+=(tree[r].sum*(2*tree[n].lazy))+(e-mid)*sqr(tree[n].lazy);
        tree[l].sum+=(mid-b+1)*tree[n].lazy;
        tree[r].sum+=(e-mid)*tree[n].lazy;
        tree[l].lazy+=tree[n].lazy;
        tree[r].lazy+=tree[n].lazy;
        tree[n].lazy=0;
    }
}

void init(int n, int b, int e)
{
    if(b==e)
    {
        tree[n].sum=ara[b];
        tree[n].sqrsum=sqr(ara[b]);
        tree[n].lazy=0;
        tree[n].upd=0;
        return;
    }
    segment_tree;
    init(l,b,mid);
    init(r,mid+1,e);
    tree[n].sum=tree[l].sum+tree[r].sum;
    tree[n].sqrsum=tree[l].sqrsum+tree[r].sqrsum;
    tree[n].lazy=0;
    tree[n].upd=0;
}

void update(int n, int b, int e, int i, int j, ll val, int type)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        if(type==0)
        {
            tree[n].sum=(e-b+1)*val;
            tree[n].sqrsum=(e-b+1)*sqr(val);
            tree[n].lazy=0;
            tree[n].upd=val;
        }
        else
        {
            tree[n].sqrsum+=(tree[n].sum*2*val)+((e-b+1)*sqr(val));
            tree[n].sum+=(e-b+1)*val;
            tree[n].lazy+=val;
        }
        return;
    }

    push_down(n,b,e);

    segment_tree;

    update(l,b,mid,i,j,val,type);
    update(r,mid+1,e,i,j,val,type);
    tree[n].sum=tree[l].sum+tree[r].sum;
    tree[n].sqrsum=tree[l].sqrsum+tree[r].sqrsum;
}

ll query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return 0;
    if(b>=i && e<=j)
        return tree[n].sqrsum;
    push_down(n,b,e);
    segment_tree;
    ll p=query(l,b,mid,i,j);
    ll q=query(r,mid+1,e,i,j);
    return p+q;
}

int main()
{
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,q;
        sff(n,q);
        loop1(i,n) sfl(ara[i]);
        init(1,1,n);
        LINE_PRINT_CASE;
        while(q--)
        {
            int a,b,c,d;
            sfff(a,b,c);
            if(a==2)
            {
                ll ans=query(1,1,n,b,c);
                printf("%lld\n",ans);
            }
            else
            {
                sf(d);
                if(a==1)
                    update(1,1,n,b,c,d,1);
                else
                    update(1,1,n,b,c,d,0);
            }
        }
    }

    return 0;
}
