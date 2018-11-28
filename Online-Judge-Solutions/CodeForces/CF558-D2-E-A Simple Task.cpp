/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - We can solve this problem using counting sort.
        - If we know the count value of every character in between the range l to r then we can do the following-
            - For increasing sorting we have to place the character in ascending order in between the range.
            - In descending for decreasing.
        - We can perform the above operation over a range using a segment tree with lazy propagation.
        - So we need 26 segment tree each for every character from a to z.
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

#define mx 100005
#define segment_tree int l=n*2,r=l+1,mid=(b+e)/2

char str[mx];

struct data
{
    int cnt[27];
    int lazy;
    data()
    {
        ms(cnt,0);
        lazy=0;
    }
    void clear()
    {
        lazy=0;
        ms(cnt,0);
    }
    void add(data a)
    {
        for(int i=1;i<=26;i++)
            cnt[i]+=a.cnt[i];
    }
};

data tree[6*mx];

void push_down(int n, int b, int e)
{
    if(tree[n].lazy>0)
    {
        segment_tree;
        tree[l].clear();
        int x=tree[n].lazy;
        tree[l].lazy=x;
        int totall=mid-b+1;
        tree[l].cnt[x]=totall;

        tree[r].clear();
        int totalr=e-mid;
        tree[r].lazy=x;
        tree[r].cnt[x]=totalr;

        tree[n].lazy=0;
    }
    tree[n].lazy=0;
}

void push_up(int n, int l, int r)
{
    tree[n].clear();
    tree[n].add(tree[l]);
    tree[n].add(tree[r]);
}

void update(int n, int b, int e, int i, int j, int val)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        tree[n].clear();
        tree[n].lazy=val;
        int total=e-b+1;
        tree[n].cnt[val]=total;
        return;
    }
    segment_tree;
    push_down(n,b,e);
    update(l,b,mid,i,j,val);
    update(r,mid+1,e,i,j,val);
    push_up(n,l,r);
}

data query(int n, int b, int e, int i, int j)
{
    if(b>j || e<i) return tree[0];
    if(b>=i && e<=j)
    {
        return tree[n];
    }
    segment_tree;
    push_down(n,b,e);
    data p=query(l,b,mid,i,j);
    data q=query(r,mid+1,e,i,j);
    p.add(q);
    return p;
}


int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,q;
    sff(n,q);
    scanf("%s",str);

    for(int i=1; i<=n; i++)
    {
        int cur=str[i-1]-'a'+1;
        update(1,1,n,i,i,cur);
    }

    while(q--)
    {
        int l,r,c;
        sfff(l,r,c);

        data ret=query(1,1,n,l,r);

        if(c==0)
        {
            int cur=l;
            for(int i=26; i>0; i--)
            {
                if(ret.cnt[i]>0)
                {
                    int x=ret.cnt[i];
                    update(1,1,n,cur,cur+x-1,i);
                    cur+=x;
                }
            }
        }
        else
        {
            int cur=l;
            for(int i=1; i<=26; i++)
            {
                if(ret.cnt[i]>0)
                {
                    int x=ret.cnt[i];
                    update(1,1,n,cur,cur+x-1,i);
                    cur+=x;
                }
            }
        }
    }

    for(int i=1; i<=n; i++)
    {
        data ret=query(1,1,n,i,i);
        int pos=0;
        while(ret.cnt[pos]==0 && pos<27)
            pos++;
        pos--;
        printf("%c",char('a'+pos));
    }

    return 0;
}
