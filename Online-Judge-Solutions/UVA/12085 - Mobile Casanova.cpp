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

ll getNum(string str)
{
    stringstream ss;
    ss<<str;
    ll ret;
    ss>>ret;
    return ret;
}

char sss[1000];

void print(string str, string str1)
{
    int i=0,j=0;
    while(str[i]==str1[j])
    {
        pf("%c",str[i]);
        i++,j++;
    }
    while(i<SZ(str))
    {
        pf("%c",str[i]);
        i++;
    }
    pf("-");
    while(j<SZ(str1))
    {
         pf("%c",str1[j]);
        j++;
    }
    pf("\n");
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int n;
    int z=0;
    while(sf(n)==1 && n)
    {
        z++;
        ll last=0;
        string last_str;
        string last_last;
        int cnt=0;
        LINE_PRINT_CASE;
        for(int i=0; i<n; i++)
        {
            scanf("%s",sss);
            string str=sss;
            ll num=getNum(str);
            if(last==0)
            {
                last=num;
                last_str=str;
                cnt=1;
                continue;
            }

            if(num-last==1)
            {
                cnt++;
                last_last=str;
                last=num;
            }
            else
            {
                if(cnt>1)
                    print(last_str,last_last);
                else
                    pf("%s\n",last_str.c_str());
                last=num;
                last_str=str;
                cnt=1;
            }
        }

        if(cnt>1)
        {
            print(last_str,last_last);
        }
        else
            pf("%s\n",last_str.c_str());

        pf("\n");
    }

    return 0;
}
