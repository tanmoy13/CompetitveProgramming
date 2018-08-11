

/*
     If opportunity doesn't knock, build a door.

            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
            |S|.|S|.|R|.|A|.|S|.|A|.|M|.|K|
            +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    Success is how high you bounce when you hit bottom.
*/


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
#define CIN              ios_base::sync_with_stdio(0); cin.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define loop(i,n)        for(int i=0;i<n;i++)
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

int mm=1429431;

int tree[1429450*4];

void init(int n,int b, int e)
{
    if(b==e)
    {
        if(b%2==1) tree[n]=1;
        else tree[n]=0;
        return;
    }
    int mid=(b+e)/2;
    int l=n*2;
    int r=l+1;
    init(l,b,mid);
    init(r,mid+1,e);
    tree[n]=tree[l]+tree[r];
}

int query(int n, int b, int e, int x)
{
    if(x==1 && b==e) return b;
    int l=n*2;
    int r=l+1;
    int mid=(b+e)/2;
    if(x>tree[l]) return query(r,mid+1,e,x-tree[l]);
    else
        return query(l,b,mid,x);
}

void update(int n, int b, int e, int x)
{
    if(x==1 && b==e)
    {
        tree[n]=0;
        return;
    }
    int l=n*2;
    int r=l+1;
    int mid=(b+e)/2;
    if(x>tree[l]) update(r,mid+1,e,x-tree[l]);
    else
        update(l,b,mid,x);
    tree[n]=tree[l]+tree[r];
}

int main()
{

//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    init(1,1,mm);
    for(int i=2; i<=100000; i++)
    {
        int x=query(1,1,mm,i);
        int xx=x;
        while(x<tree[1])
        {
            update(1,1,mm,x);
            x+=xx;
            x-=1;
        }
    }

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int a;
        sf(a);
        PRINT_CASE;
        pf("%d\n",query(1,1,mm,a));
    }
    return 0;
}


