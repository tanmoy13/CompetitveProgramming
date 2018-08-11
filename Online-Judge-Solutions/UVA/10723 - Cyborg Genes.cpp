#include <bits/stdc++.h>

#define pii             pair <int,int>
#define sc              scanf
#define pf              printf
#define Pi              2*acos(0.0)
#define ms(a,b)         memset(a, b, sizeof(a))
#define pb(a)           push_back(a)
#define MP              make_pair
#define db              double
#define ll              long long
#define EPS             10E-10
#define ff              first
#define ss              second
#define sqr(x)          (x)*(x)
#define D(x)            cout<<#x " = "<<(x)<<endl
#define VI              vector <int>
#define DBG             pf("Hi\n")
#define MOD             100007
#define MAX             10000
#define CIN             ios_base::sync_with_stdio(0); cin.tie(0)
#define SZ(a)           (int)a.size()
#define sf(a)           scanf("%d",&a)
#define sfl(a)          scanf("%lld",&a)
#define sff(a,b)        scanf("%d %d",&a,&b)
#define sffl(a,b)       scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)     scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)    scanf("%lld %lld %lld",&a,&b,&c)
#define loop(i,n)       for(int i=0;i<n;i++)
#define REP(i,a,b)      for(int i=a;i<b;i++)
#define TEST_CASE(t)    for(int z=1;z<=t;z++)
#define PRINT_CASE      printf("Case %d: ",z)
#define all(a)          a.begin(),a.end()
#define intlim          2147483648
#define inf             1000000
#define ull             unsigned long long

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

string s1,s2;

int dp[35][35];
ll dp2[35][35][65];

int sz1,sz2,len;

int LCS(int i, int j)
{
    if(i>=sz1 || j>=sz2) return 0;

    int &ret=dp[i][j];
    if(ret!=-1) return ret;

    ret=0;

    if(s1[i]==s2[j])
    {
        ret=1+LCS(i+1,j+1);
    }
    else
        ret=max(LCS(i+1,j),LCS(i,j+1));
    return ret;

}

ll cnt_str(int i, int j, int l)
{
    if(i>=sz1)
    {
        l+=sz2-j;
        if(l==len) return 1;
        else return 0;
    }

    if(j>=sz2)
    {
        l+=sz1-i;
        if(l==len) return 1;
        else return 0;
    }

    ll &ret= dp2[i][j][l];
    if(ret!=-1) return ret;
    ret=0;

    if(s1[i]==s2[j])
    {
        ret=cnt_str(i+1,j+1,l+1);
    }
    else
    {
        ret+=cnt_str(i+1,j,l+1);
        ret+=cnt_str(i,j+1,l+1);
    }
    return ret;
}

int main()
{
//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);
//    CIN;
    int t;
    cin>>t;
    getchar();
    TEST_CASE(t)
    {
//        cin>>s1>>s2;
        getline(cin,s1);
        getline(cin,s2);
        sz1=SZ(s1);
        sz2=SZ(s2);

        cout<<"Case #"<<z<<": ";
        ms(dp,-1);
        ms(dp2,-1);
        len=sz1+sz2-LCS(0,0);
        cout<<len<<" ";
        cout<<cnt_str(0,0,0)<<endl;

    }
    return 0;
}
