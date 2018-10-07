/*
    Author: Tanmoy Datta
    Solution Idea:
        - Optimal way to play the game is -
            1. If current player can take any treasure then he must take that.
            2. If All available pile contains two stones then opposite player will get all the treasure.
               As when current player remove a stone then opposite player take the treasure. This will continue till last.
            3. For all piles which contain more than two stones, players will take one by one by switching turn.
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

ll ara[2];
priority_queue<pii>Q1;
priority_queue<int>Q2;

class StoneGame
{
public:
    int getScore(vector <int> treasure, vector <int> stones)
    {
        ms(ara,0);
        int cur=0;
        for(int i=0;i<SZ(treasure);i++)
        {
            Q1.push(pii(-stones[i],treasure[i]));
        }
        while(!Q1.empty())
        {
            pii u=Q1.top();
            Q1.pop();
            u.ff=-u.ff;
            if(u.ff==1)
            {
                ara[cur]+=u.ss;
                cur=1-cur;
            }
            else if(u.ff==2)
            {
                Q2.push(-u.ss);
            }
            else
            {
                Q2.push(-u.ss);
                int x=u.ff-2;
                if(x%2)
                    cur=1-cur;
            }
        }
        while(!Q2.empty())
        {
            int u=-Q2.top();
            Q2.pop();
            ara[1-cur]+=u;
//            cur=1-cur;
        }
        return ara[0];
    }
};


template<typename T> void print( T a )
{
    cerr << a;
}

void print( long long a )
{
    cerr << a << "L";
}

void print( string a )
{
    cerr << '"' << a << '"';
}

template<typename T> void print( vector<T> a )
{
    cerr << "{";
    for ( int i = 0 ; i != a.size() ; i++ )
    {
        if ( i != 0 ) cerr << ", ";
        print( a[i] );
    }
    cerr << "}" << endl;
}

template<typename T> void assert_eq( int n, T have, T need )
{
    if ( have == need )
    {
        cerr << "Case " << n << " passed." << endl;
    }
    else
    {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}

template<typename T> void assert_eq( int n, vector<T> have, vector<T> need )
{
    if( have.size() != need.size() )
    {
        cerr << "Case " << n << " failed: returned " << have.size() << " elements; expected " << need.size() << " elements.";
        print( have );
        print( need );
        return;
    }
    for( int i= 0; i < have.size(); i++ )
    {
        if( have[i] != need[i] )
        {
            cerr << "Case " << n << " failed. Expected and returned array differ in position " << i << ".";
            print( have );
            print( need );
            return;
        }
    }
    cerr << "Case " << n << " passed." << endl;
}
void assert_eq( int n, string have, string need )
{
    if ( have == need )
    {
        cerr << "Case " << n << " passed." << endl;
    }
    else
    {
        cerr << "Case " << n << " failed: expected ";
        print( need );
        cerr << " received ";
        print( have );
        cerr << "." << endl;
    }
}

int main( int argc, char* argv[] )
{

    StoneGame objectStoneGame;

    //test case0
    vector <int> param00;
    param00.push_back(3);
    param00.push_back(2);
    vector <int> param01;
    param01.push_back(1);
    param01.push_back(2);
    int ret0 = objectStoneGame.getScore(param00,param01);
    int need0 = 5;
    assert_eq(0,ret0,need0);

    //test case1
    vector <int> param10;
    param10.push_back(5);
    param10.push_back(4);
    param10.push_back(3);
    param10.push_back(2);
    param10.push_back(1);
    vector <int> param11;
    param11.push_back(1);
    param11.push_back(1);
    param11.push_back(1);
    param11.push_back(1);
    param11.push_back(1);
    int ret1 = objectStoneGame.getScore(param10,param11);
    int need1 = 9;
    assert_eq(1,ret1,need1);

    //test case2
    vector <int> param20;
    param20.push_back(5);
    param20.push_back(5);
    vector <int> param21;
    param21.push_back(2);
    param21.push_back(2);
    int ret2 = objectStoneGame.getScore(param20,param21);
    int need2 = 0;
    assert_eq(2,ret2,need2);

    //test case3
    vector <int> param30;
    param30.push_back(1);
    vector <int> param31;
    param31.push_back(10);
    int ret3 = objectStoneGame.getScore(param30,param31);
    int need3 = 0;
    assert_eq(3,ret3,need3);

}
