/*
    Author: Tanmoy Datta

    Solution Idea:
        - We can solve this problem for independent row and column.
        - A row query depends on the current row set value and number of column update after this row set.
        - Similarly a column query depends on the current column set value and number of row update after this column set
        - So we can assign a unique time stamp id on every operation.
        - On a row query we need to check the current set value of this row and time stamp of this row set operation.
          Let current row set value is 0 and time stamp on this operation is X.
        - Then  the answer for this query is N-Y. where is N is number number of elements in row and Y is
          number of column_set 1 operation with time stamp > T.
        - Similarly we can do this for row set value 1 then we need to consider column set 0 operation and in this
          case the answer for this query is Y. We can do the same thing for column query.
        - As well as we can get the Y value by suing some data structure like pbds in c++ (Ordered Set) or segment tree, or BIT.
        - Here is some resource for learning pbds-
            * https://codeforces.com/blog/entry/11080
            * https://www.geeksforgeeks.org/policy-based-data-structures-g/

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

#define mx 500005

ordered_set row1,row0,col1,col0;

int last_time_row[mx],last_time_row_val[mx],last_time_col[mx],last_time_col_val[mx];

int n,q;
int Time=0;

void remove_last_row(int idx)
{
    int a=last_time_row[idx];
    int b=last_time_row_val[idx];
    if(b==0)
    {
        if(a)
        {
            row0.erase(a);
        }
    }
    else
    {
        if(a)
        {
            row1.erase(a);
        }
    }
}

void remove_last_col(int idx)
{
    int a=last_time_col[idx];
    int b=last_time_col_val[idx];
    if(b==0)
    {
        if(a)
        {
            col0.erase(a);
        }
    }
    else
    {
        if(a)
        {
            col1.erase(a);
        }
    }
}

void update_row(int idx, int val)
{
    remove_last_row(idx);
    Time++;
    last_time_row[idx]=Time;
    last_time_row_val[idx]=val;
    if(val==0)
    {
        row0.insert(Time);
    }
    else
    {
        row1.insert(Time);
    }
}

void update_col(int idx, int val)
{
    remove_last_col(idx);
    Time++;
    last_time_col[idx]=Time;
    last_time_col_val[idx]=val;
    if(val==0)
    {
        col0.insert(Time);
    }
    else
    {
        col1.insert(Time);
    }
}

int query_row(int idx)
{
    int a=last_time_row[idx];
    int b=last_time_row_val[idx];

    if(b==0)
    {
        int x=col1.size()-col1.order_of_key(a);
        return n-x;
    }
    else if(b==1)
    {
        int x=col0.size()-col0.order_of_key(a);
        return x;
    }
}

int query_col(int idx)
{
    int a=last_time_col[idx];
    int b=last_time_col_val[idx];

    if(b==0)
    {
        int x=row1.size()-row1.order_of_key(a);
        return n-x;
    }
    else if(b==1)
    {
        int x=row0.size()-row0.order_of_key(a);
        return x;
    }
}

char s1[10];

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    sff(n,q);
    while(q--)
    {
        scanf(" %s",s1);
        string str=(s1);
        if(str=="RowQuery")
        {
            int idx;
            sf(idx);
            int ans=query_row(idx);
            printf("%d\n",ans);
        }
        else if(str=="ColQuery")
        {
            int idx;
            sf(idx);
            int ans=query_col(idx);
            printf("%d\n",ans);
        }
        else if(str=="RowSet")
        {
            int idx, val;
            sff(idx,val);
            update_row(idx,val);
        }
        else if(str=="ColSet")
        {
            int idx,val;
            sff(idx,val);
            update_col(idx,val);
        }
    }


    return 0;
}
