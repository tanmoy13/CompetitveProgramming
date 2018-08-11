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
const int fx[]= {-1,-1,+1,+1}; // Knights Move
const int fy[]= {+1,-1,+1,-1}; // Knights Move
/*------------------------------------------------*/

/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

int r,c,m,n;

bool vis[105][105];
bool grid[105][105];

void BFS(int x,int y)
{
    if(grid[x][y]==1) return;
    vis[x][y]=1;
    queue<pii>Q;
    Q.push(pii(x,y));
    while(!Q.empty())
    {
        pii u=Q.front();
        Q.pop();
        for(int i=0; i<4; i++)
        {
            int xx=u.ff+(fx[i]*m);
            int yy=u.ss+(fy[i]*n);
            if(xx<0 || xx>=r || yy<0|| yy>=c || grid[xx][yy] || vis[xx][yy]) continue;
            vis[xx][yy]=1;
            Q.push(pii(xx,yy));
        }
        for(int i=0; i<4; i++)
        {
            int xx=u.ff+(fx[i]*n);
            int yy=u.ss+(fy[i]*m);
            if(xx<0 || xx>=r || yy<0|| yy>=c || grid[xx][yy] || vis[xx][yy]) continue;
            vis[xx][yy]=1;
            Q.push(pii(xx,yy));
        }
    }
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        sff(r,c);
        sff(m,n);
        ms(vis,0);
        ms(grid,0);
        int kk;
        sf(kk);
        while(kk--)
        {
            int a,b;
            sff(a,b);
            grid[a][b]=1;
        }

        BFS(0,0);

        int odd=0,even=0;

        for(int i=0; i<r; i++)
            for(int j=0; j<c; j++)
            {
                if(vis[i][j])
                {
                    set<pii>st;
                    for(int k=0; k<4; k++)
                    {
                        int xx=i+(fx[k]*m);
                        int yy=j+(fy[k]*n);
                        if(xx<0 || xx>=r || yy<0 || yy>=c || grid[xx][yy]) continue;
                        if(vis[xx][yy])
                            st.insert(pii(xx,yy));
                    }
                    for(int k=0; k<4; k++)
                    {
                        int xx=i+(fx[k]*n);
                        int yy=j+(fy[k]*m);
                        if(xx<0 || xx>=r || yy<0 || yy>=c || grid[xx][yy]) continue;
                        if(vis[xx][yy])
                            st.insert(pii(xx,yy));
                    }
                    if(st.size()%2) odd++;
                    else
                        even++;
                }

            }
        PRINT_CASE;
        printf("%d %d\n",even,odd);

    }

    return 0;
}
