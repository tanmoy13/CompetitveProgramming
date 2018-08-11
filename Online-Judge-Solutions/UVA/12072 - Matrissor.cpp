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
#define LINE_PRINT_CASE  printf("Matrix #%d\n",z)
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

pll ara[55];

ll dp[55][55], cost[55][55], precal[55][55], k;

//ll func(int l, int r)
//{
//    if(l>=r) return 0;
//    ll &ret=dp[l][r];
//    if(ret!=-1) return ret;
//    ll p=(1LL<<62);
//    for(int i=l;i<r;i++)
//    {
//        ll k=ara[l].ff*ara[i].ss*ara[r].ss;
//        k+=func(l,i);
//        k+=func(i+1,r);
//        p=min(p,k);
//    }
//    return ret=p;
//}

ll func(int l, int r)
{
    if(l==r)
    {
        cost[l][r]=0;
        return 0;
    }
    ll &ret=dp[l][r];
    if(ret!=-1) return ret;
    if(precal[l][r]<=k)
    {
        cost[l][r]=precal[l][r];
        return ret=1;
    }
    ll p;
    cost[l][r]=p=(1LL<<62);
    for(int i=l; i<r; i++)
    {
        ll temp=ara[l].ff*ara[i].ss*ara[r].ss;
        if(temp>k) continue;
        ll lft=func(l,i);
        if(lft>=(1LL<<62)) continue;
        ll rgt=func(i+1,r);
        if(rgt>=(1LL<<62)) continue;
        ll total=lft+rgt;
        if(lft && cost[l][i]+temp<=k)
            temp+=cost[l][i];
        else
            total++;
        if(total<p || (total==p && temp<cost[l][r]))
        {
            p=total;
            cost[l][r]=temp;
        }
    }
    return ret=p;
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
        loop(i,n)sffl(ara[i].ff,ara[i].ss);
//        ms(dp,-1);
        ms(precal,0);
//        cout<<func(0,n-1)<<endl;

        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                precal[i][j]=precal[i][j-1]+(ara[i].ff*ara[j].ff*ara[j].ss);
            }
        }

//        for(int i=0; i<n; i++,cout<<endl)
//            for(int j=0; j<n; j++)
//                cout<<precal[i][j]<<" ";
        int q;
        sf(q);
        LINE_PRINT_CASE;
        while(q--)
        {
            sf(k);
            ms(dp,-1);
            ll ans=func(0,n-1);
            if(ans>=(1LL<<62))
                pf("Impossible.\n");
            else
                printf("%lld\n",ans);
        }
        printf("\n");
    }

    return 0;
}
