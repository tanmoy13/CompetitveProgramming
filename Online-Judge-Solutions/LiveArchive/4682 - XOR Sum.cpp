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
template <class T>
T Set(T N,T pos)
{
    T x=1;
    return N=N | (x<<pos);
}
template <class T>
T reset(T N,T pos)
{
    T x=1;
    return N= N & ~(x<<pos);
}
template <class T>
bool check(T N,T pos)
{
    T x=1;
    return (bool)(N & (x<<pos));
}
/*------------------------------------------------*/

#define mx 2000005

int trie[mx][2],node;

void insert(int val)
{
    int cur=0;
    for(int i=31; i>=0; i--)
    {
        int a=check(val,i);
        if(trie[cur][a]==-1)
        {
            trie[cur][a]=++node;
            trie[node][0]=trie[node][1]=-1;
        }
        cur=trie[cur][a];
    }
}

ll query(int val)
{
    ll ret=0;
    int cur=0;
    for(int i=31; i>=0; i--)
    {
        int a=check(val,i);
        if(trie[cur][a^1]!=-1)
        {
            ret=Set(ret,(ll)i);
            cur=trie[cur][a^1];
        }
        else
            cur=trie[cur][a];
    }
    return ret;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n;
        sf(n);
//        ms(trie,-1);
        trie[0][0]=trie[0][1]=-1;
        node=0;
        ll ans=0;
        ll temp=0;
        insert(0);
        for(int i=0; i<n; i++)
        {
            int a;
            sf(a);
            temp^=a;
            insert(temp);
            ans=max(ans,query(temp));
        }
        printf("%d\n",ans);
//        if(z<t)
//            printf(" ");
    }
//    printf("\n");

    return 0;
}

