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

char str[201];

int dp[102][3][3];

int grundy(int len, int lft, int rgt)
{
    if(len<=0) return 0;
    if(len==1 && lft==rgt && lft!=2) return 1;
    if(len==1 && lft!=rgt && lft!=2 && rgt!=2 ) return 0;
    int &ret=dp[len][lft][rgt];
    if(ret!=-1) return ret;
    set<int>st;
    for(int i=1; i<=len; i++)
    {
        int a=0,b=0;
        if(i==1)
        {
            if(lft!=0)
                {a=grundy(i-1,lft,0)^grundy(len-i,0,rgt);st.insert(a);}
            if(lft!=1)
                {b=grundy(i-1,lft,1)^grundy(len-i,1,rgt);st.insert(b);}
        }
        else if(i==len)
        {
            if(rgt!=0)
                {a=grundy(i-1,lft,0)^grundy(len-i,0,rgt);st.insert(a);}
            if(rgt!=1)
                {b=grundy(i-1,lft,1)^grundy(len-i,1,rgt);st.insert(b);}
        }
        else
        {
            a=grundy(i-1,lft,0)^grundy(len-i,0,rgt);
            b=grundy(i-1,lft,1)^grundy(len-i,1,rgt);
            st.insert(a);
            st.insert(b);
        }
    }

    int x=0;
    while(st.find(x)!=st.end()) x++;
    return ret=x;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    ms(dp,-1);
    TEST_CASE(t)
    {
        scanf(" %s",str);
        int ans=0;
        int len=strlen(str);
        int last=-1;
        for(int i=0; i<len; i++)
        {
            if(str[i]!='.')
            {
                if(str[i]=='O')
                {
                    ans^=grundy(i-last-1,2,0);
                }
                else
                {
                    ans^=grundy(i-last-1,2,1);
                }
                last=i;
                break;
            }
        }

        for(int i=last+1; i<len; i++)
        {
            if(str[i]!='.')
            {
                if(str[i]=='O')
                {
                    ans^=grundy(i-last-1,str[last]=='X',0);
                }
                else
                {
                    ans^=grundy(i-last-1,str[last]=='X',1);
                }
                last=i;
            }
        }
        if(last==-1)
            ans^=grundy(len-last-1,2,2);
        else
            ans^=grundy(len-last-1,str[last]=='X',2);

        PRINT_CASE;

        int cnt=0;
        for(int i=0; i<len; i++) cnt+=(str[i]!='.');
        if(cnt%2==0)
        {

            if(ans)
                printf("Yes\n");
            else
                printf("No\n");
        }
        else
        {
            if(ans==0)
                printf("Yes\n");
            else
                printf("No\n");
        }
    }

    return 0;
}
