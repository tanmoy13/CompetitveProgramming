/*
    Author: Tanmoy Datta
    Solution Idea:
        - At first take input and store the input in a pair array where first element of i_th pair is the value a_i  and second
          element of i_th pair is i.
        - Sort the pair array with with ascending order of a_i
        - Build a merge sort tree using the second element of each pair of sorted pair array.
        - Now for each query i,j,k at first check how many number in range i to j inclusive are present in left subtree of current
          node in merge sort tree. Let the value is x. So if x<=k then it's sure that the answer is in the left subtree. So we will
          go to left subtree of current node with k. Otherwise we will go to right subtree of current node with k-x;
        - In this manner when we reach to a leaf node we can say that this node contains the index of our answer.
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

#define segment_tree int l=n*2,r=l+1,mid=(b+e)/2
#define mx 100005

pii ara[mx];
int arr[mx];
vector<int>tree[3*mx];


void init(int n, int b, int e)
{
    if(b==e)
    {
        tree[n].pb(ara[b].ss);
        return;
    }
    segment_tree;
    init(l,b,mid);
    init(r,mid+1,e);
    merge(all(tree[l]),all(tree[r]),back_inserter(tree[n]));
}

int query(int n, int b, int e, int i, int j, int k)
{
    if(b==e)
    {
        return tree[n].back();
    }
    segment_tree;
    int x = upper_bound(all(tree[l]),j)-lower_bound(all(tree[l]),i);
    if(x>=k)
    {
        return query(l,b,mid,i,j,k);
    }
    else
        return query(r,mid+1,e,i,j,k-x);
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,m;
    sff(n,m);

    for(int i=1;i<=n;i++)
    {
        sf(ara[i].ff);
        ara[i].ss=i;
        arr[i]=ara[i].ff;
    }

    sort(ara+1,ara+n+1);

    init(1,1,n);

    while(m--)
    {
        int a,b,c;
        sfff(a,b,c);
        int ans=query(1,1,n,a,b,c);
        ans=arr[ans];
        printf("%d\n",ans);
    }


    return 0;
}
