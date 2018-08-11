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


char ara[100005];

struct data
{
    pii rank;
    int pos;
};

bool cmp(data a, data b)
{
    return a.rank<b.rank;
}

int suffix_ara[200005];

int position[200005];

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
        getchar();
        gets(ara);
        string str=ara;
        str+=str;
        n*=2;
        for(int i=0;i<n;i++)
        {
            position[i]=str[i]-'a';
        }

        for(int steep=1;steep<n;steep*=2)
        {
            vector<data>v(n);
            for(int i=0;i<n;i++)
            {
                int a=position[i];
                int b;
                if(i+steep>=n)
                    b=100000000;
                else
                    b=position[i+steep];
                v[i].rank=pii(a,b);
                v[i].pos=i;
            }

            sort(all(v),cmp);

            position[v[0].pos]=0;
            suffix_ara[0]=v[0].pos;

            for(int i=1;i<n;i++)
            {
                suffix_ara[i]=v[i].pos;
                if(v[i].rank==v[i-1].rank)
                    position[v[i].pos]=position[v[i-1].pos];
                else
                    position[v[i].pos]=i;
            }
        }

        for(int i=0;i<n;i++)
        {
            if(suffix_ara[i]<n/2)
            {
                pf("%d\n",suffix_ara[i]);
//                pf("%s\n",str.substr(suffix_ara[i]).c_str());
                break;
            }
        }
    }

    return 0;
}
