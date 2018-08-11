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

#define mx 100005

int SA[mx],tempSA[mx];
int RA[mx],tempRA[mx];
int c[mx];
int LCP[mx],PLCP[mx],Phi[mx];
char str[mx];
int n;

void counting_sort(int k)
{
    int maxi=max(300,n);
    ms(c,0);
    for(int i=0; i<n; i++)
    {
        int a=i+k<n?RA[i+k]:0;
        c[a]++;
    }
    for(int i=0,sum=0; i<maxi; i++)
    {
        int x=c[i];
        c[i]=sum;
        sum+=x;
    }

    for(int i=0; i<n; i++)
    {
        int a=SA[i]+k<n?RA[SA[i]+k]:0;
        int b=c[a];
        c[a]++;
        tempSA[b]=SA[i];
    }

    for(int i=0; i<n; i++)
        SA[i]=tempSA[i];
}

void build_Suffix_Array()
{
    for(int i=0; i<n; i++)
    {
        RA[i]=str[i];
        SA[i]=i;
    }

    for(int k=1; k<n; k*=2)
    {
        counting_sort(k);
        counting_sort(0);
        int r=0;
        tempRA[SA[0]]=r=0;
        for(int i=1; i<n; i++)
        {
            if(RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])
                tempRA[SA[i]]=r;
            else
                tempRA[SA[i]]=++r;
        }
        for(int i=0; i<n; i++)
        {
            RA[i]=tempRA[i];
        }
        if(RA[SA[n-1]]==n-1) break;
    }
}

void build_LCP()
{
    Phi[SA[0]]=-1;
    for(int i=1; i<n; i++)
        Phi[SA[i]]=SA[i-1];
    for(int i=0,L=0; i<n; i++)
    {
//        D(i);
        if(Phi[i]==-1)
        {
            PLCP[i]=0;
            continue;
        }
        while(str[i+L]==str[Phi[i]+L]) L++;
        PLCP[i]=L;
        L=max(L-1,0);
    }

    for(int i=0; i<n; i++)
        LCP[i]=PLCP[SA[i]];
}



int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

//    int t;
//    sf(t);
//    TEST_CASE(t)
    {
        scanf("%s",str);
        string str1=str;
        strcat(str,"$");
        n=strlen(str);
        build_Suffix_Array();
        build_LCP();

//        for(int i=0; i<n; i++)
//            cout<<SA[i]<<" ";
//        cout<<endl;
//        for(int i=0; i<n; i++)
//            cout<<LCP[i]<<" ";
//        cout<<endl;


        int string_len=SZ(str1);

        int q;
        sf(q);
        while(q--)
        {
            ll k;
            sfl(k);
            ll ans=0;
            int pos=0,len=0;
            for(int i=1;i<n;i++)
            {
                int temp=string_len-SA[i]-LCP[i];
                if(ans+temp<k)
                    ans+=temp;
                else
                {
                    pos=SA[i];
                    len=ans+temp-k;
                    len=LCP[i]+temp-len;
                    break;
                }
            }
            pf("%s\n",str1.substr(pos,len).c_str());
        }

    }

    return 0;
}
