

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
    int u,cost;
    data(int a,int b)
    {
        u=a,cost=b;
    }
    bool operator < (const data &p) const
    {
        return cost>p.cost;
    }
};


vector<int>graph[600],cost[600];
ll dis[600];
bool vis[600];
set<int>st;
int f,k;

void all_clear(int n)
{
    for(int i=0;i<=550;i++)
    {
        graph[i].clear();
        cost[i].clear();
        dis[i]=(1<<28);
        vis[i]=0;
    }
    st.clear();
}


ll dijkastra(int src)
{
    for(int i=0;i<600;i++) dis[i]=(1<<28);

    priority_queue<data>Q;

    stlloop(st)
    {
        dis[*it]=0;
        Q.push(data(*it,0));
    }
    Q.push(data(src,0));
    dis[src]=0;
    ll ret=0;

    while(!Q.empty())
        {
            data u=Q.top();
            Q.pop();
            for(int i=0;i<SZ(graph[u.u]);i++)
            {
                int v=graph[u.u][i];
                if(u.cost+cost[u.u][i]<dis[v])
                {
                    dis[v]=u.cost+cost[u.u][i];
                    Q.push(data(v,dis[v]));
                }

            }
        }

        for(int i=1;i<=k;i++)
            ret=max(ret,dis[i]);
        return ret;
}


int main()
{

//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
//    CIN;
    int t;
    cin>>t;
    TEST_CASE(t)
    {
//        vector<int>source;
        cin>>f>>k;

        all_clear(k);
        st.clear();

        for(int i=0;i<f;i++)
        {
            int a;
            cin>>a;
            dis[a]=0;
            st.insert(a);
            vis[a]=1;
        }

            string str;
            getline(cin,str);

        while(1)
        {
            getline(cin,str);
            stringstream ss(str);
            if(str.empty()) break;
            int a,b,c;
            ss>>a>>b>>c;
            graph[a].pb(b);
            graph[b].pb(a);
            cost[a].pb(c);
            cost[b].pb(c);
        }



        int ans=1,maxi=100000000;
        for(int i=1;i<=k;i++)
        {
            if(vis[i]==0)
            {
                ll temp=dijkastra(i);
                if(temp<maxi)
                {
                    maxi=temp;
                    ans=i;
                }
            }
        }

        cout<<ans<<endl;
        if(z!=t)
            cout<<endl;
    }

    return 0;
}
