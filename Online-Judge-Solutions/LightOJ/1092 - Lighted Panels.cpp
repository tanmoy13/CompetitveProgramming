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
#define infinity         10000
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
int Set(int N,int pos){return N=N | (1<<pos);}
int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

int grid[10];
char str[100];

int dp[8][1<<8][1<<8];
 int n,m;

int func(int idx, int mask, int prev_mask)
{
    if(idx>=n)
    {
        if(prev_mask==(1<<m)-1) return 0;
        return infinity;
    }

    int &ret=dp[idx][mask][prev_mask];
    if(ret!=-1) return ret;

    int p=infinity;
    for(int i=0;i<(1<<m);i++)
    {
        int ara[]={prev_mask,mask,grid[idx+1]};
        int cnt=0;
        for(int j=0;j<m;j++)
        {
            if(check(i,j)==0) continue;
            cnt++;
            for(int k=0;k<3;k++) ara[k]^=(1<<j);
            if(j+1<m)
                for(int k=0;k<3;k++) ara[k]^=(1<<(j+1));
            if(j-1>=0)
                for(int k=0;k<3;k++) ara[k]^=(1<<(j-1));
        }

        if(idx==0)
            p=min(p,cnt+func(idx+1,ara[2],ara[1]));
        else
        {
            if(ara[0]==(1<<m)-1)
                p=min(p,cnt+func(idx+1,ara[2],ara[1]));
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
        ms(grid,0);
        sff(n,m);
        for(int i=0;i<n;i++)
        {
            scanf("%s",str);
            for(int j=0;j<m;j++)
            {
                if(str[j]=='*') grid[i]=Set(grid[i],j);
            }
        }

        ms(dp,-1);
        PRINT_CASE;
        if(func(0,grid[0],0)>=infinity)
            pf("impossible\n");
        else
            printf("%d\n",func(0,grid[0],0));

    }

    return 0;
}
