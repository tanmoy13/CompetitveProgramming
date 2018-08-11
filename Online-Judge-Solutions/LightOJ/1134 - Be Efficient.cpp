/*
Solution Idea:
--------------
No need for dp+binary search :D :D can be solved in O(n).
observation (spoiler alert):
lets check the 2nd test case:
the array is : 1 2 3 4 5 6
we have to find consecutive subsequences that are divisible by 3.
let start summing up the array modulo 3.
the array becomes :
array index: 0 1 2 3 4 5
main Array : 1 2 3 4 5 6
cumulative sum modulo 3 : 1 0 0 1 0 0
now think, for any 2 element which have same reminder we can get a consecutive subsequence divisible by 3.
for example :
index 1 and index 4 both have cumulative reminder 0.
so we can construct a consecutive subsequence from index 2 to 4 which is divisible by 3 (why?? simple math). in this case (3+4+5) = 12.
for every index we have to know how many same reminder we have encountered so far. We can do it by keeping an reminder array.
If we simulate the process for the array we get :
for index 0 : 0 sub sequence.
for index 1 : 0
for index 2 : 1
for index 3: 1
for index 4: 2
for index 5: 3
total 7.
observe.... sequences which are started from index 0....are not considered so we need to add the 4 zeros so the answer is 7 + 4 = 11.
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

int ara[mx],mod_array[mx],cnt_array[mx];

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
        for(int i=0; i<n; i++) sf(ara[i]);
        int last=0;
        for(int i=0; i<n; i++)
        {
            mod_array[i]=(last+ara[i])%m;
            last=mod_array[i];
        }


        ll ans=0;
        ms(cnt_array,0);
        for(int i=n-1; i>=0; i--)
        {
            ans+=cnt_array[mod_array[i]];
            cnt_array[mod_array[i]]++;
        }

        ans+=cnt_array[0];

        PRINT_CASE;
        printf("%lld\n",ans);

    }

    return 0;
}
