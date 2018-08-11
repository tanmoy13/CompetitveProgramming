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
#define PRINT_CASE       printf("Case #%d: ",z)
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

#define piii pair<int, pair<int,int> >

int n,f,t;

int cost[30][30];
bool vis[5][30][30];
int dis[5][30][30];
int dis2[5][30][30];
void dijkastra(pii src, int id)
{
    loop(i,30) loop(j,30) dis[id][i][j]=1<<30,dis2[id][i][j]=1<<30;
    dis[id][src.ff][src.ss]=0;
    dis2[id][src.ff][src.ss]=0;
    queue<piii>Q;
    Q.push(piii(-0,src));
    while(!Q.empty())
    {
        piii u=Q.front();
        Q.pop();
        u.ff=-u.ff;
        for(int i=0; i<4; i++)
        {
            int x=u.ss.ff+fx[i];
            int y=u.ss.ss+fy[i];
            if(x<0 || x>=n || y<0 || y>=n) continue;
            if(dis[id][x][y]>u.ff+cost[u.ss.ff][u.ss.ss] && dis2[id][u.ss.ff][u.ss.ss]+1<=t)
            {
                dis2[id][x][y]=1+dis2[id][u.ss.ff][u.ss.ss];
                dis[id][x][y]=u.ff+cost[u.ss.ff][u.ss.ss];
                Q.push(piii(-dis[id][x][y],pii(x,y)));
            }
        }
    }
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int z=0;
    while(sfff(n,f,t) && (n||f||t))
    {
        z++;
        loop(i,n)loop(j,n) sf(cost[i][j]);
        vector<pii>frnd;
        loop(i,f)
        {
            int a,b;
            sff(a,b);
            frnd.pb(pii(a,b));
        }

        loop(i,f) dijkastra(frnd[i],i);

        int ans=INT_MAX;
        pii dst;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                bool check=0;
                for(int k=0;k<f;k++)
                {
                    if(dis[k][i][j]>=(1<<30))
                    {
                        check=1;
                        break;
                    }
                }
                if(check) continue;

                for(int k=0;k<f;k++)
                {
                    if(dis2[k][i][j]>t)
                    {
                        check=1;
                        break;
                    }
                }

                if(check) continue;
                int temp=0;
                for(int k=0;k<f;k++)
                {
                    temp+=dis[k][i][j];
                }
                if(temp<ans)
                {
                    ans=temp;
                    dst=pii(i,j);
                }
            }

            PRINT_CASE;
            if(ans==INT_MAX)
                pf("Impossible.\n");
            else
                pf("Selected city (%d,%d) with minimum cost %d.\n",dst.ff,dst.ss,ans);

    }


    return 0;
}

