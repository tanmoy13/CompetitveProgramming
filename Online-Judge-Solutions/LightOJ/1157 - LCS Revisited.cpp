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
#define MOD              1000007
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
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

#define mx 1005

char s1[mx],s2[mx];

ll dp[mx][mx];
ll lcs[mx][mx];




int main()
{
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        scanf("%s %s",s1,s2);
        int l1=strlen(s1);
        int l2=strlen(s2);

        ms(dp,0);

        for(int i=0; i<=l1; i++)
        {
            dp[i][0]=1;
        }

        for(int i=0; i<=l2; i++)
        {
            dp[0][i]=1;
        }

        ms(lcs,0);

        for(int i=1; i<=l1; i++)
            for(int j=1; j<=l2; j++)
            {
                if(s1[i-1]==s2[j-1])
                {
                    lcs[i][j]=1+lcs[i-1][j-1];
                    dp[i][j]=dp[i-1][j-1];
                }
                else if(lcs[i-1][j]>lcs[i][j-1])
                {
                    lcs[i][j]=lcs[i-1][j];
                    dp[i][j]=dp[i-1][j];
                }
                else if(lcs[i-1][j]<lcs[i][j-1])
                {
                    lcs[i][j]=lcs[i][j-1];
                    dp[i][j]=dp[i][j-1];
                }
                else
                {
                    lcs[i][j]=lcs[i][j-1];
                    int bad=0;
                    if(lcs[i-1][j-1]==lcs[i][j])
                        bad=dp[i-1][j-1];
                    dp[i][j]=(((dp[i-1][j]+dp[i][j-1]-bad)+MOD)%MOD);
                }
            }

        PRINT_CASE;
        printf("%d\n",dp[l1][l2]);
    }

    return 0;
}
