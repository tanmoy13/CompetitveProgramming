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

#define mx 50004
#define segment int l=n*2,r=l+1,mid=(b+e)/2
struct data
{
    ll sum,lft_sum,rgt_sum,ans;
};

data mini;

data tree[3*mx];

ll ara[mx];

void update(int n, int b, int e, int i)
{
    if(b>i || e<i) return;
    if(b==e && e==i)
    {
        tree[n].ans=ara[b];
        tree[n].lft_sum=ara[b];
        tree[n].rgt_sum=ara[b];
        tree[n].sum=ara[b];
        return;
    }

    segment;

    update(l,b,mid,i);
    update(r,mid+1,e,i);

    tree[n].sum=tree[l].sum+tree[r].sum;
    tree[n].lft_sum=max(tree[r].lft_sum,tree[r].sum+tree[l].lft_sum);
    tree[n].rgt_sum=max(tree[l].rgt_sum,tree[l].sum+tree[r].rgt_sum);
    tree[n].ans=max(tree[l].ans,tree[r].ans);
    tree[n].ans=max(tree[n].ans,tree[n].sum);
    tree[n].ans=max(tree[n].ans,tree[n].lft_sum);
    tree[n].ans=max(tree[n].ans,tree[n].rgt_sum);
    tree[n].ans=max(tree[n].ans,tree[l].lft_sum+tree[r].rgt_sum);
}

data query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return mini;
    if(b>=i && e<=j)
        return tree[n];
    segment;

    data p=query(l,b,mid,i,j);
    data q=query(r,mid+1,e,i,j);
    data ret;
    ret.sum=p.sum+q.sum;
    ret.lft_sum=max(q.lft_sum,q.sum+p.lft_sum);
    ret.rgt_sum=max(p.rgt_sum,p.sum+q.rgt_sum);
    ret.ans=max(ret.sum,max(p.ans,q.ans));
    ret.ans=max(ret.ans,p.lft_sum+q.rgt_sum);
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    mini.ans=mini.lft_sum=mini.rgt_sum=mini.sum=-10000000000;

    int n;
    sf(n);
    loop1(i,n) sfl(ara[i]);

    for(int i=1;i<=n;i++)
        update(1,1,n,i);
    int q;
    sf(q);
    while(q--)
    {
        int a;
        sf(a);
        if(a==0)
        {
            ll a,b;
            sffl(a,b);
            ara[a]=b;
            update(1,1,n,a);
        }
        else
        {
            int a,b;
            sff(a,b);
            data ans=query(1,1,n,a,b);
            pf("%lld\n",ans.ans);
        }
    }

    return 0;
}



