/*
    Author: Tanmoy Datta
    Solution Idea:
        - First observation in this problem is we only need to check palindrome for substrings of length k and k+1.
          Here k and k+1 is for odd and even length palindrome.
        - Sort all the indexes where a palindrome ends in ascending order.
        - Now the only thing remain is the checking how much character we can take by taking the current index as
          starting index and add it to answer.

*/

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define VI               vector <int>
#define MOD              1000000007
#define fast_cin         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define UNIQUE(v)        (v).erase(unique((v).begin(),(v).end()),(v).end())
#define POPCOUNT         __builtin_popcountll
#define RIGHTMOST        __builtin_ctzll
#define LEFTMOST(x)      (63-__builtin_clzll((x)))
#define NUMDIGIT(x,y)    (((vlong)(log10((x))/log10((y))))+1)
#define NORM(x)          if(x>=mod) x-=mod;if(x<0) x+=mod;
#define ODD(x)           (((x)&1)==0?(0):(1))
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
#define D(x)        	 cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)          cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)       cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG              cerr << __LINE__ << ": Hi" << '\n'

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

/*---------------------Hashing---------------------*/

#define MH 100005

#define Base1 10000019
#define Base2 10000079

#define MOD1 1000000007
#define MOD2 1000000009

ll B1[MH],B2[MH];

void init_hash()
{
    B1[0]=B2[0]=1;
    for(int i=1; i<MH; i++)
    {
        B1[i]=(B1[i-1]*Base1)%MOD1;
        B2[i]=(B2[i-1]*Base2)%MOD2;
    }
}

struct Hash
{
    pll H[MH];
    int digit[MH];
    int len;

    Hash()
    {
        len=0;
        H[0]=pll(0,0);
    }

    void clear()
    {
        len=0;
        H[0]=pll(0,0);
    }

    void insert(char ch)
    {
        len++;
        digit[len]=ch-'a'+1;
        H[len].ff=(((H[len-1].ff*Base1)%MOD1)+digit[len])%MOD1;
        H[len].ss=(((H[len-1].ss*Base2)%MOD2)+digit[len])%MOD2;
    }

    pll substr(int l, int r) /// Here l and r is on 1 based indexing
    {
        if(l>len || r<1 || r<l) return pll(-1,-1);
        int sub_len=r-l+1;
        pll ans;
        ans.ff=(H[r].ff-((H[l-1].ff*B1[sub_len])%MOD1)+MOD1)%MOD1;
        ans.ss=(H[r].ss-((H[l-1].ss*B2[sub_len])%MOD2)+MOD2)%MOD2;
        return ans;
    }

    pll concate(pll h, int l, int r)
    {
        pll x=substr(l,r);
        int sub_len=r-l+1;
        h.ff=(((h.ff*B1[sub_len])%MOD1)+x.ff)%MOD1;
        h.ss=(((h.ss*B2[sub_len])%MOD2)+x.ss)%MOD2;
        return h;
    }


    bool operator==(const Hash& p) const
    {
        return len==p.len && H[len]==p.H[len];
    }

    pll & operator[](int index)
    {
        return H[index];
    }
};

Hash h1,h2;

int lcp(int id1, int id2, int l)
{
    int lo=1,hi=l;
    while(lo<=hi)
    {
        int mid=(lo+hi)/2;
        if(h1.substr(id1,id1+mid)==h2.substr(id2,id2+mid))
            lo=mid+1;
        else
            hi=mid-1;
    }
    return hi;
}

/*------------------Hashing End---------- ----------*/


int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif


    init_hash();
//    fast_cin;
    int t;
    cin>>t;
    TEST_CASE(t)
    {
        Hash h1,h2;
        h1.clear();
        h2.clear();

        string str;
        int k;
        cin>>k>>str;
        string revstr;
        revstr=str;
        reverse(all(revstr));

        for(int i=0; i<SZ(str); i++)
        {
            h1.insert(str[i]);
            h2.insert(revstr[i]);
        }

        deque<int>Q;
        bitset<100005>vis;
        for(int i=0; i<SZ(str); i++)
        {
            if(i+k-1<SZ(str))
            {
                int l1=i+1;
                int r1=i+k;
                int l2=SZ(str)-r1+1;
                int r2=SZ(str)-i;
                if(h1.substr(l1,r1)==h2.substr(l2,r2))
                {
                    Q.pb(r1-1);
                    vis[i]=1;
                }
            }
            if(i+k<SZ(str))
            {
                int l1=i+1;
                int r1=i+k+1;
                int l2=SZ(str)-r1+1;
                int r2=SZ(str)-i;
                if(h1.substr(l1,r1)==h2.substr(l2,r2))
                {
                    Q.pb(r1-1);
                }
            }
        }

        sort(all(Q));
        ll ans=0;

//        for(int x:Q)
//            cout<<x<<" ";

        for(int i=0; i<SZ(str); i++)
        {
            ll l,r;
            while(!Q.empty() && Q.front()<i+k-1)
                Q.pop_front();
            if(!Q.empty() && Q.front()==i+k-1 && vis[i]==0)
                Q.pop_front();
            l=i;
            if(Q.empty())
                r=SZ(str);
            else
                r=Q.front();
            ans+=r-l;
        }

        cout<<ans<<endl;

    }

    return 0;
}
