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
int Set(int N,int pos){return N=N | (1<<pos);}
int reset(int N,int pos){return N= N & ~(1<<pos);}
bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

char sss[107];
string str[16];
int data[16][16];

int lps[107];

void phi(string s)
{
    int k=0;
    lps[0]=0;
    for(int i=1; i<SZ(s); i++)
    {
        while(k>0 && s[i]!=s[k]) k=lps[k-1];
        if(s[i]==s[k]) k++;
        lps[i]=k;
    }
}

int KMP(string T, string P)
{
    int k=0;
    for(int i=0; i<SZ(T); i++)
    {
        while(k>0 && T[i]!=P[k]) k=lps[k-1];
        if(T[i]==P[k]) k++;
        if(i==SZ(T)-1) return k;
        if(k==SZ(P)) return k;
    }
}

int dp[1<<16][16];
int cases[1<<16][16];
int n,zz;

int func(int mask, int last)
{
    if(__builtin_popcount(mask)==n) return 0;
    int &ret=dp[mask][last];
    int &cas=cases[mask][last];
    if(cas==zz) return ret;
    cas=zz;
    int p=INT_MAX;
    for(int i=0;i<n;i++)
    {
        if(check(mask,i)==0)
        {
//            p=min(p,SZ(str[i])-data[last][i]+func(Set(mask,i),i));
              int x=SZ(str[i])-data[last][i];
              int temp,new_last=last;
              if(x)
                new_last=i;
              temp=x+func(Set(mask,i),new_last);
             p=min(p,temp);
        }
    }
    return ret=p;
}


void path_print(int mask, int last)
{
    if(__builtin_popcount(mask)==n) return;
    string ret="Z";
    int p=INT_MAX;
    int next=0;
    for(int i=0;i<n;i++)
    {
        if(check(mask,i)) continue;
        int x=data[last][i];
        int y=SZ(str[i])-x;
        int new_last=last;
        if(y)
            new_last=i;
        int xx=y+func(Set(mask,i),new_last);
        if(xx<p)
        {
            p=xx;
            ret=str[i].substr(x);
            next=i;
        }
        else if(xx==p)
        {
            if(ret>str[i].substr(x))
            {
                ret=str[i].substr(x);
                next=i;
            }
        }
    }
    printf("%s",ret.c_str());
    if(SZ(ret))
        path_print(Set(mask,next),next);
    else
        path_print(Set(mask,next),last);
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        sf(n);
        for(int i=0; i<n; i++) scanf("%s",sss),str[i]=sss;

        sort(str,str+n);

//        for(int i=0;i<n;i++) cout<<str[i]<<endl;

        for(int i=0;i<n;i++)
        {
            phi(string(str[i]));
            for(int j=0;j<n;j++)
            {
                int a=KMP(string(str[j]),string(str[i]));
                data[j][i]=a;
//                cout<<str[j]<<endl;
//                cout<<str[i]<<endl;
//                cout<<a<<endl;
            }
        }

        int ans=INT_MAX;

//        ms(dp,-1);
          zz++;
        int start=0;
        for(int i=0;i<n;i++)
        {
            int temp=SZ(str[i])+func(Set(0,i),i);
            if(temp<ans)
            {
                start=i;
                ans=temp;
            }
        }

        PRINT_CASE;
//        cout<<ans<<endl;
        printf("%s",str[start].c_str());
        path_print(Set(0,start),start);
        printf("\n");
    }

    return 0;
}
