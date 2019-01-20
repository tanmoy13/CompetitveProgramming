/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - If the input array is already sorted then answer is 0.
        - If the input don't contain any lucky number then answer is -1.
        - Otherwise select any lucky number and swap all number according to their sorted order position using that lucky number.
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

bool check(ll n)
{
    while(n)
    {
        int x=n%10;
        n/=10;
        if(x!=4 && x!=7) return false;
    }
    return true;
}

#define mx 100005

ll ara[mx],bra[mx];
vector<int>v;
deque<int>Q[mx];
map<ll,int>mp;

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n;
    sf(n);
    ll lucky=-1;



    for(int i=1; i<=n; i++)
    {
        ll x;
        sfl(x);
        ara[i]=bra[i]=x;
        if(check(x))
            lucky=x;
        v.pb(x);
    }

    sort(all(v));
    UNIQUE(v);

    for(int i=0,j=1;i<SZ(v);i++)
    {
        mp[v[i]]=j++;
    }

    for(int i=1;i<=n;i++)
    {
        ll x=ara[i];
        x=mp[x];
        Q[x].pb(i);
    }



    sort(bra+1,bra+1+n);
    bool checkk=0;
    for(int i=1;i<=n;i++)
    {
        if(ara[i]!=bra[i])
        {
            checkk=1;
        }
    }

    vector<pii>ans;
    if(checkk==0)
    {
        printf("0\n");
        return 0;
    }
    if(lucky==-1)
    {
        printf("-1\n");
        return 0;
    }

    for(int i=1; i<=n; i++)
    {
        ll b=bra[i];
        ll a=ara[i];
        if(ara[i]==bra[i])
        {
            Q[mp[b]].erase(find(all(Q[mp[b]]),i));
            if(b==lucky)
            {
                if(Q[mp[b]].empty())
                {
                    Q[mp[b]].pb(i);
                }
            }
            continue;
        }

        if(b==lucky)
        {
            continue;
        }

        if(a==lucky)
        {
            int x=i;
            int y=Q[mp[b]].front();
            Q[mp[b]].pop_front();
            Q[mp[lucky]].erase(find(all(Q[mp[lucky]]),i));
            Q[mp[lucky]].push_back(y);
            ans.pb(pii(i,y));
//            DDD(i,ara[i],ara[y]);
            swap(ara[i],ara[y]);

        }
        else
        {
            int x=i;
            Q[mp[a]].erase(find(all(Q[mp[a]]),i));
            int y=Q[mp[lucky]].front();
            Q[mp[lucky]].pop_front();
            Q[mp[a]].push_front(y);
            swap(ara[i],ara[y]);
            ans.pb(pii(i,y));
            x=Q[mp[b]].front();
            Q[mp[b]].pop_front();
            Q[mp[lucky]].push_front(x);
            ans.pb(pii(i,x));
//            DDD(i,ara[i],ara[x]);
            swap(ara[i],ara[x]);
        }




    }

    printf("%d\n",SZ(ans));

    for(int i=0; i<SZ(ans); i++)
        printf("%d %d\n",ans[i].ff,ans[i].ss);



    return 0;
}
