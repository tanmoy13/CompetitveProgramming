#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

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

struct data
{
    int type,x,st,ed,id;
};

vector<int>x,y;
vector<data>v;

bool cmp(data a, data b)
{
    if(a.x<b.x) return true;
    if(a.x==b.x)
        return a.type<b.type;
    return false;
}

#define mx 300005

int tree[mx];

void update(int idx, int val)
{
    for(; idx<mx && idx; idx+=(idx&-idx))
        tree[idx]+=val;
}

int query(int idx)
{
    int ret=0;
    for(; idx; idx-=(idx&-idx))
        ret+=tree[idx];
    return ret;
}

int ans[mx];

int main()
{
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n,m;
        sff(n,m);
        for(int i=0; i<n; i++)
        {
            int a,b;
            sff(a,b);
            data temp;
            temp.type=2;
            temp.x=a;
            temp.ed=temp.st=b;
            v.pb(temp);
            x.pb(a);
            y.pb(b);
        }

        for(int i=0; i<m; i++)
        {
            int a,b,c,d;
            sff(a,b);
            sff(c,d);
            x.pb(a);
            x.pb(c);
            y.pb(b);
            y.pb(d);
            data temp;
            temp.type=3;
            temp.x=c;
            temp.st=b;
            temp.ed=d;
            temp.id=i;
            v.pb(temp);
            data temp1;
            temp1.type=1;
            temp1.x=a;
            temp1.st=b;
            temp1.ed=d;
            temp1.id=i;
            v.pb(temp1);
        }

//    sort(all(x));
        sort(all(y));
        sort(all(v),cmp);

        for(int i=0; i<SZ(v); i++)
        {
            data temp=v[i];
            if(temp.type==1)
            {
                int a=lower_bound(all(y),temp.st)-y.begin()+1;
                int b=lower_bound(all(y),temp.ed)-y.begin()+1;
                int xx=query(b);
                int yy=query(a-1);
                ans[temp.id]=xx-yy;
            }
            else if(temp.type==3)
            {
                int a=lower_bound(all(y),temp.st)-y.begin()+1;
                int b=lower_bound(all(y),temp.ed)-y.begin()+1;
                int xx=query(b);
                int yy=query(a-1);
                ans[temp.id]=(xx-yy)-ans[temp.id];
            }
            else
            {
                int a=lower_bound(all(y),temp.st)-y.begin()+1;
                update(a,1);
//            int yy=query(a-1); // Never do this while range update on BIT -_-
//            ans[temp.id]=xx;
            }
        }

        LINE_PRINT_CASE;
        for(int i=0; i<m; i++)
            printf("%d\n",ans[i]);
        ms(tree,0);
        x.clear();
        y.clear();
        v.clear();
    }
    return 0;
}
