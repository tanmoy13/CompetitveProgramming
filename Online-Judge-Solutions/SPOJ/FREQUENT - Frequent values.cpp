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
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

#define mx 100005

pii block[mx];

int dp[mx][20];

int ara[mx],id[mx],cnt=0,table[mx];

int func(int idx, int p)
{
    if(idx>cnt) return 0;
    if(p==0)
    {
        return dp[idx][p]=table[idx];
    }
    int &ret=dp[idx][p];
    if(ret!=-1) return ret;
    ret=max(func(idx,p-1),func(idx+(1<<(p-1)),p-1));
    return ret;
}

int query(int l, int r)
{
    if(r<l) return 0;
    if(l==r) return table[l];
    int log=(int)log2(r-l);
    return max(func(l,log),func(r-(1<<log)+1,log));
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int n,q;
    while(sf(n))
    {
        if(n==0) break;
        sf(q);
        for(int i=1; i<=n; i++)
        {
            sf(ara[i]);
        }
        cnt=0;
        ms(table,0);
        ms(dp,-1);
//        ms(block,0);
//        ms(id,0);
        for(int i=1; i<=n; i++)
        {
            int j=i;
            cnt++;
            block[cnt].ff=i;
            while(ara[j]==ara[i] && j<=n)
            {
                id[j]=cnt;
                table[cnt]++;
                j++;
            }
            j--;
            block[cnt].ss=j;
            i=j;
        }

        while(q--)
        {
            int a,b;
            sff(a,b);
            if(id[a]==id[b])
            {
                printf("%d\n",b-a+1);
            }
            else
            {
                int l=id[a];
                int r=id[b];
                int ans=0;
                ans=max(ans,block[l].ss-a+1);
                l++;
                ans=max(ans,b-block[r].ff+1);
                r--;
                ans=max(ans,query(l,r));
                printf("%d\n",ans);
            }
        }

    }

    return 0;
}
