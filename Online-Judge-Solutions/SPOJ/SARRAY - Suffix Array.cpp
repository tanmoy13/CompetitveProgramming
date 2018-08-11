/*

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

//    int t;
//    sf(t);
//    TEST_CASE(t)
//    {
        int n;
//        sf(n);
//        getchar();
//        gets(ara);
        scanf("%s",ara);
//        string str=ara;
        n=strlen(ara);
//        str+=str;
//        n*=2;
        for(int i=0;i<n;i++)
        {
            position[i]=ara[i];
        }

        for(int steep=1;steep<n;steep*=2)
        {
            vector<data>v(n);
            for(int i=0;i<n;i++)
            {
                int a=position[i];
                int b;
                if(i+steep>=n)
                    b=-1;
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
//            if(suffix_ara[i]<n/2)
//            {
//                pf("%d\n",suffix_ara[i]);
////                pf("%s\n",str.substr(suffix_ara[i]).c_str());
////                break;
//            }
            pf("%d\n",suffix_ara[i]);
        }
//    }

    return 0;
}

*/


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
int count_sort[mx];
char str[mx],pattern[mx];

//int Phi[mx],LCP[mx],PLCP[mx];

int n;

void counting_sort(int k)
{
    ms(count_sort,0);
    int maxi=max(300,n);
    for(int i=0; i<n; i++)
    {
        int a=i+k<n?RA[i+k]:0;
        count_sort[a]++;
    }
    for(int i=0,sum=0; i<maxi; i++)
    {
        int x=count_sort[i];
        count_sort[i]=sum;
        sum+=x;
    }

    for(int i=0; i<n; i++)
    {
        int a=SA[i]+k<n?RA[SA[i]+k]:0;
        int b=count_sort[a];
        count_sort[a]++;
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
        int r;
        tempRA[SA[0]]=r=0;
        for(int i=1; i<n; i++)
        {
            if(RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])
                tempRA[SA[i]]=r;
            else
                tempRA[SA[i]]=++r;
        }
        for(int i=0; i<n; i++)
            RA[i]=tempRA[i];
        if(RA[SA[n-1]]==n-1) break;
    }
}

//void compute_LCP()
//{
//    int l=0;
//    Phi[SA[0]]=-1;
//    for(int i=1; i<n; i++)
//        Phi[SA[i]]=SA[i-1];
//    for(int i=0,L=0; i<n; i++)
//    {
//        if(Phi[i]==-1)
//        {
//            PLCP[i]=0;
//            continue;
//        }
//        while(str[i+L]==str[Phi[i]+L])
//        {
////            D(str[i+L]);
////            D(str[Phi[i]+L]);
//            L++;
//        }
//        PLCP[i]=L;
//        L=max(L-1,0);
//    }
//
//    for(int i=0; i<n; i++)
//        LCP[i]=PLCP[SA[i]];
//
//}
//
//int find_pattern(int len)
//{
//    int lo=0,hi=n-1;
//    while(lo<hi)
//    {
//        int mid=(lo+hi)/2;
//        int res=strncmp(str+SA[mid],pattern,len);
//        if(res>=0) hi=mid;
//        else
//            lo=mid+1;
//    }
//    ll ret=lo;
//    if(strncmp(str+SA[ret],pattern,len)!=0) return 0;
//    lo=0,hi=n-1;
//    while(lo<hi)
//    {
//        int mid=(lo+hi)/2;
//        int res=strncmp(str+SA[mid],pattern,len);
//        if(res>0) hi=mid;
//        else
//            lo=mid+1;
//    }
//
//    if(strncmp(str+SA[hi],pattern,len)!=0) hi--;
//    return hi-ret+1;
//}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

//    int t;
//    sf(t);
//    TEST_CASE(t)
//    {
        scanf("%s",str);
        strcat(str,"$");
        n=strlen(str);
        build_Suffix_Array();

        for(int i=1;i<n;i++)
            pf("%d\n",SA[i]);

//    }

    return 0;
}

