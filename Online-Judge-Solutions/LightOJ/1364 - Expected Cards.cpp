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

int C,D,H,S;

double dp[14][14][14][14][5][5];

bool check(int c, int d, int h, int s, int j1, int j2)
{
    if(j1==1)
        c++;
    else if(j1==2)
        d++;
    else if(j1==3)
        h++;
    else if(j1==4)
        s++;
    if(j2==1)
        c++;
    else if(j2==2)
        d++;
    else if(j2==3)
        h++;
    else if(j2==4)
        s++;
    if(c>=C && d>=D && h>=H && s>=S) return 1;
    return 0;
}

double func(int c, int d, int h, int s, int j1, int j2)
{
    if(check(c,d,h,s,j1,j2)) return 0.0;

    double &ret=dp[c][d][h][s][j1][j2];
    if(ret>=0.0) return ret;

    ret=1.0;

    int total=c+d+h+s;
    if(j1) total++;
    if(j2) total++;
    total=54-total;
    if(c<13)
        ret+=(((13.0-c)/total)*(func(c+1,d,h,s,j1,j2)));
    if(d<13)
        ret+=(((13.0-d)/total)*(func(c,d+1,h,s,j1,j2)));
    if(h<13)
        ret+=(((13.0-h)/total)*(func(c,d,h+1,s,j1,j2)));
    if(s<13)
        ret+=(((13.0-s)/total)*(func(c,d,h,s+1,j1,j2)));

    int joker=0;
    if(j1) joker++;
    if(j2) joker++;

    joker=2-joker;

    double temp=100000000;

    if(j1==0)
    {
        temp=min(temp,((1.0/total)*(func(c,d,h,s,1,j2))));
        temp=min(temp,((1.0/total)*(func(c,d,h,s,2,j2))));
        temp=min(temp,((1.0/total)*(func(c,d,h,s,3,j2))));
        temp=min(temp,((1.0/total)*(func(c,d,h,s,4,j2))));
        ret+=temp;
    }
    temp=10000000;
    if(j2==0)
    {
        temp=min(temp,((1.0/total)*(func(c,d,h,s,j1,1))));
        temp=min(temp,((1.0/total)*(func(c,d,h,s,j1,2))));
        temp=min(temp,((1.0/total)*(func(c,d,h,s,j1,3))));
        temp=min(temp,((1.0/total)*(func(c,d,h,s,j1,4))));
        ret+=temp;
    }
    return ret;
}


int main()
{

    ///freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        sfff(C,D,H);
        sf(S);
        int test=0;
        if(C>13)
            test+=(C-13);
        if(D>13)
            test+=(D-13);
        if(H>13)
            test+=(H-13);
        if(S>13)
            test+=(S-13);
        PRINT_CASE;
        if(test>2)
        {
            printf("-1\n");
            continue;
        }

        ms(dp,-1.0);
        printf("%.10lf\n",func(0,0,0,0,0,0));

    }

    return 0;
}
