/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - Sort and take the unique value of the given array.
        - Then find maximum bipertite match of two element.
        - An element has an edge with another element if it divides that element.
        - After finding maximum bipertite match. Now about printing in lexicographical order.
        - Start from the lowest value. You will only be able to print it if
          total_number_of_printed_element+maximum_bipertite_match_excluding_its_multiples==maximum bipertite match.
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

#define mx 205

vector<int>v;

int match[mx];
int vis[mx];
int cas;

bool find_matching(int idx)
{
    if(vis[idx]==cas) return false;
    vis[idx]=cas;
    for(int i=SZ(v); i<2*SZ(v); i++)
    {
        int x=i-SZ(v);
        if(x==idx) continue;
        if(v[x]%v[idx]==0 && match[i]==-1)
        {
            match[idx]=i;
            match[i]=idx;
            return true;
        }
    }

    for(int i=SZ(v); i<2*SZ(v); i++)
    {
        int x=i-SZ(v);
        if(x==idx) continue;
        if(v[x]%v[idx]==0 && find_matching(match[i]))
        {
            match[idx]=i;
            match[i]=idx;
            return true;
        }
    }
    return false;
}

int matching()
{
    int ret=0;
    ms(match,-1);
    for(int i=0; i<SZ(v); i++)
    {
        if(match[i]==-1)
        {
            cas++;
            bool x=find_matching(i);
            if(x) ret++;
        }
    }
    return ret;
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
////#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        v.clear();
        ms(vis,0);
        cas=0;
        int n;
        sf(n);
        int a;
        for(int i=0; i<n; i++)
        {
            sf(a);
            v.pb(a);
        }

        sort(all(v));
        UNIQUE(v);

        int bpm=matching();
        int mis=SZ(v)-bpm;
        int taken=0,idx=0;

//        DD(bpm,mis);

        vector<int>ans;

        while(taken<mis && idx<SZ(v))
        {
            taken++;
            vector<int>temp=v;
            vector<int>temp1;
            for(int i=idx+1; i<SZ(v); i++)
            {
                if(v[i]%v[idx])
                    temp1.pb(v[i]);
            }

            v.clear();
            v=temp1;

            int temp_bpm=matching();
            int temp_mis=SZ(v)-temp_bpm;

            if(taken+temp_mis==mis)
            {
                ans.pb(temp[idx]);
                idx=0;
            }
            else
            {
                taken--;
                v=temp;
                idx++;
            }
        }
//        sort(all(ans));
        PRINT_CASE;
        for(int i=0; i<SZ(ans); i++)
        {
            printf("%d",ans[i]);
            if(i<SZ(ans)-1)
                printf(" ");

        }
        printf("\n");


    }

    return 0;
}
