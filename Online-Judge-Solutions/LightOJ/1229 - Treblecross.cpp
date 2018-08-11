#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

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
#define D(x)             cerr<<#x " = "<<(x)<<endl
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

//char str[400];

string str;

int dp[205];

int func(int m) // Calculating sprague grundy value
{
    if(m<=0) return 0;
    int &ret=dp[m];
    if(ret!=-1) return ret;
    set<int>st;
    for(int i=1;i<=m; i++)
    {
        st.insert(func(i-3)^func(m-i-2));
    }
    int x=0;
    while(st.find(x)!=st.end())x++;
    return ret=x;
}

bool solve(int idx) // trying every position
{
    if(str[idx]=='X') return 0;
    string temp=str;
    temp[idx]='X';
    for(int i=0;i<SZ(temp)-2;i++)
    {
        if(temp[i]=='X' && temp[i+1]=='X' && temp[i+2]=='X') return 1;
    }
    for(int i=0;i<SZ(temp)-2;i++)
    {
        if(temp[i]=='X' && temp[i+2]=='X') return 0;
    }
    for(int i=0;i<SZ(temp)-1;i++)
    {
        if(temp[i]=='X' && temp[i+1]=='X') return 0;
    }

    int ans=0,last=-1;
    for(int i=0;i<SZ(temp);i++)
    {
        if(temp[i]=='X')
        {
            if(last==-1)
                ans^=func(i-last-3);
            else
                ans^=func(i-last-5);
            last=i;
        }
    }
    ans^=func(SZ(temp)-last-3);
    return ans==0;
}

int main()
{
    CIN;
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
//    sf(t);
    cin>>t;
    ms(dp,-1);
    TEST_CASE(t)
    {
        cin>>str;
        vector<int>pos;
        for(int i=0;i<SZ(str);i++)
        {
            if(solve(i))
            {
                pos.pb(i+1);
            }
        }
        CASE_PRINT;
        if(SZ(pos)==0)
            cout<<0<<endl;
        else
        {
            cout<<pos[0];
            for(int i=1;i<SZ(pos);i++)
                cout<<" "<<pos[i];
            cout<<endl;
        }
    }

    return 0;
}
