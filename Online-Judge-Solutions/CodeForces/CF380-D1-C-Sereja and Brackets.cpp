/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - This problem can be solved using segment tree.
        - Build a segment tree where each node contains three information and they are-
            - Open: No of opening braces in this subtree which are not matched with any closing braces.
            - Close: No of closing braces in this subtree which are not matched with any opening braces.
            - ans: No of braces which are matched.
        - Now we can merge two node like this-
            - let x=min(number of Open in left subtree, number of Close in right subtree)
            - then merged Open = (Left Open + Right Open - x). Because we have matched x open so we have to subtract it.
            - ans merged Close = (Left Close + Right Close - x). For the same reason.
        - In this way we can process every query.
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

#define mx 1000006
#define segmet_tree int l=n*2,r=l+1,mid=(b+e)/2

struct data
{
    int open,close,ans;
    data()
    {
        open=0;
        close=0;
        ans=0;
    }
};

data tree[3*mx];

char str[mx];

void build(int n, int b, int e)
{
    if(b==e)
    {
        tree[n].ans=0;
        tree[n].open=(str[b]=='(');
        tree[n].close=(str[b]==')');
        return;
    }
    segmet_tree;
    build(l,b,mid);
    build(r,mid+1,e);
    tree[n].ans=tree[l].ans+tree[r].ans;
    int x=min(tree[l].open,tree[r].close);
    tree[n].ans+=x;
    tree[n].open=tree[l].open+tree[r].open-x;
    tree[n].close=tree[l].close+tree[r].close-x;
}

data query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return data();
    if(b>=i && e<=j)
    {
        return tree[n];
    }
    segmet_tree;
    data p=query(l,b,mid,i,j);
    data q=query(r,mid+1,e,i,j);
    data ret;
    ret.ans=p.ans+q.ans;
    int x=min(p.open,q.close);
    ret.ans+=x;
    ret.open=p.open+q.open-x;
    ret.close=p.close+q.close-x;
    return ret;
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    scanf(" %s",str+1);

    int n=strlen(str+1);

//    D(n);
    build(1,1,n);

    int q;
    sf(q);
    while(q--)
    {
        int l,r;
        sff(l,r);

        data temp=query(1,1,n,l,r);

        printf("%d\n",temp.ans*2);

    }


    return 0;
}
