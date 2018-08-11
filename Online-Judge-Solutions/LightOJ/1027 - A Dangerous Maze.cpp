/*
I can tell you about the way I interpreted it, but usually in math/statistics problems there are many ways to understand a concept. When you understand it in your own terms, maybe you can find an easier way to model the problem :).

Let's consider test case #3:
3
3 -6 -9

There are 3 doors, and we are to find the expected amount of time it will take to get out of the maze. Let's call that expected value E. Now, E has to be equal to the average of the times that it takes to get out from each door, correct? Let's say T1 is the amount of time to get out of the maze when taking door #1, and T2 and T3 are defined similarly. Then:
E = (T1 + T2 + T3) / 3

It's easy to see that T1 is 3, but what about T2 and T3? You can think about it like this: if you take door number 2, you will spend 6 minutes going through the maze, and you end up at the starting point, and from there, how much time will it take you to get out? Well, E is the expected time it will take you to get out from the start, right? So, you can say:
T2 = 6 + E
T3 = 9 + E

Putting all that together, the original equation becomes:
E = 3/3 + (6/3 + E/3) + (9/3 + E/3)
E = 6 + 2E/3
E/3 = 6
E = 18

So the final answer is 18. Incidentally, you can see that something curious happens when there is no answer: if all doors take you back to the beginning, then all the occurrences of E in the equation can be cancelled, so you're left with a mathematical relation where you can't find a solution for E. Hope that helps :)
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
#define CASE_PRINT       cout<<"Case "<<z<<": "
#define all(a)           a.begin(),a.end()
#define intlim           2147483648
#define infinity         (1<<28)
#define ull              unsigned long long
#define gcd(a, b)        __gcd(a, b)
#define lcm(a, b)        ((a)*((b)/gcd(a,b)))

using namespace std;


/*----------------------Graph Moves----------------*/
//const int fx[]= {+1,-1,+0,+0};
//const int fy[]= {+0,+0,+1,-1};
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


int main()
{
    CIN;
    int t;
    cin>>t;
    TEST_CASE(t)
    {
        int n;
        cin>>n;
        int cnt_neg=0,sum=0;
        for(int i=0; i<n; i++)
        {
            int a;
            cin>>a;
            sum+=abs(a);
            if(a<0)
                cnt_neg++;
        }

        int deno=n-cnt_neg;
        CASE_PRINT;
        if(deno==0)
        {
            cout<<"inf"<<endl;
            continue;
        }
        int gcd = gcd(deno,sum);
        cout<<sum/gcd<<"/"<<deno/gcd<<endl;

    }
    return 0;
}
