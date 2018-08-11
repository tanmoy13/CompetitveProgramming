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
//const int fx[]={-1,-1,+0,+0};
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

void move(int &x, int &y, char dir)
{
    if(dir=='N')
        y++;
    else if(dir=='S')
        y--;
    else if(dir=='W')
        x--;
    else if(dir=='E')
        x++;
}

void set_dir(char &cur_dir, char rotate)
{
    if(cur_dir=='N')
    {
        if(rotate=='L')
            cur_dir='W';
        else
            cur_dir='E';
    }
    else if(cur_dir=='W')
    {
        if(rotate=='L')
            cur_dir='S';
        else
            cur_dir='N';
    }
    else if(cur_dir=='S')
    {
        if(rotate=='L')
            cur_dir='E';
        else
            cur_dir='W';
    }
    else if(cur_dir=='E')
    {
        if(rotate=='L')
            cur_dir='N';
        else
            cur_dir='S';
    }
}

bool lost[105][105];

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int n,m;
    cin>>n>>m;
    int x,y;
    char dir;
    while(cin>>x>>y>>dir)
    {
        string str;
        cin>>str;
        bool check=0;
        for(int i=0;i<SZ(str);i++)
        {
            if(str[i]=='F')
            {
                int a=x,b=y;
                move(x,y,dir);
                if(x<0 || x>n || y<0 || y>m)
                {
                    if(lost[a][b])
                    {
                        x=a;
                        y=b;
                        continue;
                    }
                    lost[a][b]=1;
                    cout<<a<<" "<<b<<" "<<dir<<" "<<"LOST"<<endl;
                    check=1;
                    break;
                }
            }
            else
            {
                set_dir(dir,str[i]);
            }
        }
        if(check==0)
            cout<<x<<" "<<y<<" "<<dir<<endl;

    }


    return 0;
}
