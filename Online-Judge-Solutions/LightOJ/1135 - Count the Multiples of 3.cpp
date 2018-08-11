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
#define PRINT_CASE       printf("Case %d:\n",z)
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
 
struct data
{
    int zero, one, two, prop, sum;
};
 
data tree[3*100005];
 
void push_up(int n)
{
    tree[n].one=tree[n*2].one+tree[n*2+1].one;
    tree[n].two=tree[n*2].two+tree[n*2+1].two;
    tree[n].zero=tree[n*2].zero+tree[n*2+1].zero;
}
 
 
 
void swap_number(int n, int cnt)
{
    if(cnt==0) return;
    else if(cnt==1)
    {
        int temp=tree[n].zero;
        tree[n].zero=tree[n].two;
        tree[n].two=tree[n].one;
        tree[n].one=temp;
    }
    else if(cnt==2)
    {
        int temp=tree[n].zero;
        tree[n].zero=tree[n].two;
        tree[n].two=tree[n].one;
        tree[n].one=temp;
        temp=tree[n].zero;
        tree[n].zero=tree[n].two;
        tree[n].two=tree[n].one;
        tree[n].one=temp;
    }
}
 
void push_down(int n, int b, int e)
{
    if(tree[n].prop!=0)
    {
        int mid=(b+e)/2;
        tree[n].prop%=3;
        tree[2*n].prop+=tree[n].prop;
        tree[2*n+1].prop+=tree[n].prop;
        swap_number(2*n,tree[n].prop);
        swap_number(2*n+1,tree[n].prop);
        tree[n].prop=0;
    }
}
 
void init(int n, int b, int e)
{
    if(b==e)
    {
        tree[n].zero=1;
        tree[n].one=0;
        tree[n].two=0;
        return;
    }
 
    int l=n*2;
    int r=l+1;
    int mid=(b+e)/2;
    init(l,b,mid);
    init(r,mid+1,e);
    push_up(n);
}
 
void update(int n, int b, int e, int i, int j, int x)
{
    if(i>e || j<b) return;
    if(b>=i && e<=j)
    {
        tree[n].prop+=x;
        swap_number(n,x);
        return;
    }
    push_down(n,b,e);
    int l=n*2;
    int r=l+1;
    int mid=(b+e)/2;
    update(l,b,mid,i,j,x);
    update(r,mid+1,e,i,j,x);
    push_up(n);
}
 
int query(int n, int b, int e, int i, int j)
{
    if(i>e || j<b) return 0;
    if(b>=i && e<=j) return tree[n].zero;
 
    push_down(n,b,e);
 
    int l=n*2;
    int r=l+1;
    int mid=(b+e)/2;
 
    int p=query(l,b,mid,i,j);
    int q=query(r,mid+1,e,i,j);
 
    return p+q;
}
 
int main()
{
//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);
 
    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,q;
        sff(n,q);
        PRINT_CASE;
        init(1,1,n);
        while(q--)
        {
            int a,b,c;
            sfff(a,b,c);
            b++,c++;
            if(a==0)
            {
                update(1,1,n,b,c,1);
            }
            else
            {
                printf("%d\n",query(1,1,n,b,c));
            }
        }
        ms(tree,0);
    }
 
    return 0;
}
