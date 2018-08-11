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

#define mx 1000006
ll mobius[mx];
bool vis[mx];
ll n,m;

void precal()
{
    for(int i=2;i<mx;)
    {
        for(int j=i+i;j<mx;j+=i)
            mobius[j]++;
        for(++i;;i++)
            if(mobius[i]==0) break;
    }

    for(int i=2;i<mx;i++)
    {
        if(mobius[i]==1)
        {
            for(int j=i;j<mx;j+=i)
                vis[j]=1;
        }
    }

}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    precal();
    TEST_CASE(t)
    {
        sffl(n,m);
        if(n>m) swap(n,m);

        ll ans=n*m;
//        ms(mobius,0);
//        ms(vis,0);
        for(ll i=2;i<=n;i++)
        {
            if(vis[i]==1) continue;
            ll x=(m/i)*(n/i);
            if(mobius[i]==0)
                ans-=x;
            else if(mobius[i]%2==1)
                ans-=x;
            else
                ans+=x;
//            for(ll j=i;j<=n;j*=i) vis[j]=1;
        }

        if(n) ans++;
        if(m) ans++;
        PRINT_CASE;
        printf("%lld\n",ans);

    }

    return 0;
}



/*
There are many observations to make in order to get to a working solution.
* For every lattice point (i, j), the ray that intersects it is unique and it's identified by the pair , where g is the gcd of i and j.
* The problem is now reduced to counting the number of irreducible fractions  such that a ≤ N and b ≤ M. This is the same as counting for every i between 1 and N, the amount of numbers in the range [1, M] that are coprime with i.
* Consider a certain number x with prime factors p1, p2. How do we know how many numbers in range [1, M] are coprime with it? That's equal to M minus the amount of multiples of p1 minus the amount of multiples of p2 plus the amount of multiples of p1 * p2. This is inclusion-exclusion, and in general, if the amount of elements is even, we add, otherwise, we subtract.
* So now we have a working (but slow) solution: Iterate over every i in the range [1, N] and for every i, factorize it, try out all combinations of primes and then, for every combination that results in a number k, add  if the amount of primes is even or subtract  if the amount of primes is odd.
* The previous approach is very slow for two reasons: You'll be factorizing each number every time and you'll be doing a lot of repeated work. Every combination of primes you try out at each step will result in a certain number k. A crucial observation is that the higher exponent of that number k will be 1, because we're trying combinations of different primes. Another crucial observation is that this number k will be seen  times in total. Finally, each time we see it, it will contribute by  to the final answer (or  if the amount of primes is odd).
* Knowing all this, we can precalculate a lot of stuff and then solve each test case in O(N). We should precalculate the amount of prime factors of every number in the range [1, 106] (this can be done with a simple sieve), and we should cross out numbers that have some prime with an exponent higher than 1 (in other words, multiples of some square). Once we have precalculated all that, we simply iterate from 1 to N and for every number x that we didn't cross out, we add (or subtract)  to our answer.
* Final observations: We should add 2 to our answer (the two borders). If N = 0, the answer is 1, except M = 0 too, in which case the answer is 0.
*/
