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
#define CASE_PRINT       cout<<"Case "<<z<<": "
#define all(a)           a.begin(),a.end()
#define intlim           2147483648
#define infinity         (1<<28)
#define ull              unsigned long long
#define gcd(a, b)        __gcd(a, b)
#define lcm(a, b)        ((a)*((b)/gcd(a,b)))

using namespace std;


/*----------------------Graph Moves----------------*/
const int fx[]= {+1,-1,+0,+0};
const int fy[]= {+0,+0,+1,-1};
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
    pii a,b,c;
};

string graph[15];
map<pii,bool>mp;
int n;

bool vis[10][10][10][10][10][10];
int dis[10][10][10][10][10][10];

bool check(pii aa)
{
    if(aa.ff>=0 && aa.ff<n && aa.ss>=0 && aa.ss<n && graph[aa.ff][aa.ss]!='#')
        return 1;
    return 0;
}


int bfs(data src)
{
    vis[src.a.ff][src.a.ss][src.b.ff][src.b.ss][src.c.ff][src.c.ss]=1;
    dis[src.a.ff][src.a.ss][src.b.ff][src.b.ss][src.c.ff][src.c.ss]=0;
    queue<data>Q;
    Q.push(src);
    while(!Q.empty())
    {
        data u=Q.front();
        Q.pop();
        if(mp[u.a] && mp[u.b] && mp[u.c] && u.a!=u.b && u.a!=u.c && u.b!=u.c)
        {

            return dis[u.a.ff][u.a.ss][u.b.ff][u.b.ss][u.c.ff][u.c.ss];
        }
        for(int i=0; i<4; i++)
        {
            data v;
            pii aa=pii(u.a.ff+fx[i],u.a.ss+fy[i]);
            if(!check(aa)) aa=u.a;
            pii bb=pii(u.b.ff+fx[i],u.b.ss+fy[i]);
            if(!check(bb)) bb=u.b;
            pii cc=pii(u.c.ff+fx[i],u.c.ss+fy[i]);
            if(!check(cc)) cc=u.c;

            if(aa==bb)
            {
                if(bb==cc)
                    cc=u.c;
                aa=u.a;
                bb=u.b;
            }
            if(aa==cc)
            {
                aa=u.a;
                cc=u.c;
            }
            if(bb==cc)
            {
                bb=u.b;
                cc=u.c;
                if(bb==aa)
                    aa=u.a;
            }

            v.a=aa;
            v.b=bb;
            v.c=cc;
            if(vis[v.a.ff][v.a.ss][v.b.ff][v.b.ss][v.c.ff][v.c.ss]==0)
            {
                vis[v.a.ff][v.a.ss][v.b.ff][v.b.ss][v.c.ff][v.c.ss]=1;
                dis[v.a.ff][v.a.ss][v.b.ff][v.b.ss][v.c.ff][v.c.ss]=dis[u.a.ff][u.a.ss][u.b.ff][u.b.ss][u.c.ff][u.c.ss]+1;
                Q.push(v);
            }
        }

    }
    return -1;
}

int main()
{

    ///freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);
    CIN;
    int t;
    cin>>t;
    TEST_CASE(t)
    {
        cin>>n;
        loop(i,n) cin>>graph[i];
        mp.clear();
        data src;
        loop(i,n) loop(j,n)
        {
            if(graph[i][j]=='X') mp[pii(i,j)]=1;
            if(graph[i][j]=='A') src.a=pii(i,j);
            if(graph[i][j]=='B') src.b=pii(i,j);
            if(graph[i][j]=='C') src.c=pii(i,j);
        }

        ms(vis,0);
        ms(dis,0);
        int ans=bfs(src);
        CASE_PRINT;
        if(ans==-1)
            cout<<"trapped"<<endl;
        else
            cout<<ans<<endl;
    }

    return 0;
}

