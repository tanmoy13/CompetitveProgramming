/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Build palindromic tree by inserting characters one by one and calculate number of palindrome suffix ends
          in current position and save it to array suffix[].
        - Similarly calculate number of palindrome prefix ends in current position and save it to array prefix[]. We can do this
          by building another palindromic tree with reverse of input string.
        - now ans is summation of for all i ans+=suffix[i]*prefix[i];

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
#define sqr(x)           ((x)*(x))
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

///***Note: String must be in 1 based indexing

#define mx 300005

int tree[mx][26];
int len[mx],link[mx];
int idx,t;

///ms(tree,0) optimization
//int cas;
//int visi[mx][26];

char str[mx];
ll cnt[mx];
void init_tree()
{
    len[1]=-1,link[1]=1;
    len[2]= 0,link[2]=1;
    ms(cnt,0);
    ms(tree,0);
//    cas++;
    idx=t=2;
}

void insert(int p)
{
    while(str[p-len[t]-1]!=str[p]) t=link[t];
    int x=link[t];
    while(str[p-len[x]-1]!=str[p]) x=link[x];
    int c=str[p]-'a';
    if(!tree[t][c])
    {
        tree[t][c]=++idx;
        len[idx]=len[t]+2;
        link[idx]=(len[idx]==1)?2:tree[x][c];
    }
    t=tree[t][c];
    cnt[t]=1+cnt[link[t]];
}


ll suffix[mx],preffix[mx];


int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    scanf("%s",str+1);
    int l=strlen(str+1);

    init_tree();

//    D(str+1);

    for(int i=1; i<=l; i++)
    {
        insert(i);
        suffix[i]=cnt[t];
    }

    reverse(str+1,str+l+1);

    init_tree();

    for(int i=1;i<=l;i++)
    {
        insert(i);
        preffix[i]=cnt[t];
    }

    ll ans=0;

    for(int i=1;i<=l;i++)
    {
        int idx2=l-i;
        ans+=suffix[i]*preffix[idx2];
    }

    printf("%lld\n",ans);


    return 0;
}
