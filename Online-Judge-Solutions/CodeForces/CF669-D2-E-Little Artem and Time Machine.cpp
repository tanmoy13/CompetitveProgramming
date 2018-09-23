/*
        Author: Tanmoy Datta
        Solution idea:
            - At first we need to compress the input values and take 2 ordered set for each number one for addition time and one for erase time.
            - For 1st type query we just need to insert the current time in addition ordered set of the given value.
            - For 2nd type query we just need to insert the current time in erase ordered set of the given value.
            - For 3rd type query we need to query number of element in addition ordered set of given numbers which are <=t let it is X and number
              of element in erase ordered set which are <=t let it is Y. Then our answer for 3rd query is X-Y;
*/


/*

    The problem is solvable in several ways. Please investigate and maybe write some of the other approaches.

===

Normal segment tree
	https://github.com/3agwa/CompetitiveProgramming/blob/master/CodeForces/CF669-D2-E.cpp	[with Compress Values]
	http://codeforces.com/contest/669/submission/17495492
	http://codeforces.com/contest/669/submission/17493836
	http://codeforces.com/contest/669/submission/17495865


Implicit segment tree
	Materials:
		https://www.quora.com/What-are-the-differences-among-dynamic-segment-tree-%E2%80%98implicit-segment-tree%E2%80%99-and-persistent-segment-tree)
		https://discuss.codechef.com/questions/86728/implicit-segment-tree-dynamic-segment-tree

	https://github.com/3agwa/CompetitiveProgramming/blob/master/CodeForces/CF669-D2-E.cpp%20implicit%20segment%20tree

Binary Index Tree
	http://codeforces.com/contest/669/submission/17491017
	http://codeforces.com/contest/669/submission/17493817
	http://codeforces.com/contest/669/submission/17492979


Sqrt Decomposition or what?
	See editorials for Sqrt Decomposition
	http://codeforces.com/contest/669/submission/17496546
	http://codeforces.com/contest/669/submission/17492382
	http://codeforces.com/contest/669/submission/17493172


Order-statistic tree (http://codeforces.com/blog/entry/11080)
	http://codeforces.com/contest/669/submission/17493518
	http://codeforces.com/contest/669/submission/17497293

Balanced BST
	http://codeforces.com/contest/669/submission/17493393	RedBlack Tree
	http://codeforces.com/contest/669/submission/17495303	Treap

    by  Mostafa Saad sir.
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

using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


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
    ll type,t,val;
    data()
    {

    }
};

vector<data>input;
map<ll,int>mp;

#define mx 100005

ordered_set come[mx],go[mx];

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    vector<ll>v1;
    int n;
    sf(n);
    for(int i=0;i<n;i++)
    {
        data a;
        sfffl(a.type,a.t,a.val);
        input.pb(a);
        v1.pb(a.val);
    }

    sort(all(v1));
    int cnt=0;
    for(int i=0;i<SZ(v1);i++)
    {
        ll a=v1[i];
        if(mp[a]==0)
        {
            mp[a]=++cnt;
        }
    }

    for(int i=0;i<n;i++)
    {
        ll a,b,c;
        a=input[i].type;
        b=input[i].t;
        c=input[i].val;
        c=mp[c];
        if(a==1)
        {
            come[c].insert(b);
        }
        else if(a==2)
        {
            go[c].insert(b);
        }
        else if(a==3)
        {
            int x=come[c].order_of_key(b+1);
            int y=go[c].order_of_key(b+1);
            printf("%d\n",x-y);
        }

    }
    return 0;
}
