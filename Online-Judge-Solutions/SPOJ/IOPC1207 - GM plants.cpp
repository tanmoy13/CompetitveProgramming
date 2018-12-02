/*
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - This problem can be solved using segment tree with lazy propagation.
        - Most important observation for this problem is we don't need a 3d segment tree.
          We can process every dimension independently and calculate result from them.
        - Now Build 3 segment tree for 3 dimension.
        - Each node of a segment tree hold 3 information. They are -
                - red : number of red node under this subtree.
                - green : number of green node under this subtree.
                - lazy : lazy flag to store whether we need to push or process this subtree.
        - Initially all nodes are green so for each leaf node of segment tree green=1 and red=0 and lazy=0
          and red value for all node in the tree must be zero.
        - So when a update operation will come on a node we can process it by simply swapping the red and green
          value for this range and mark a lazy so we can process it's subtree in future.
        - So in this way we can process every update operation for each of the dimensions.
        - Now for a query operation over a range the answer will be like this -
                answer = (redX*redY*redZ)+(redX*greenY*greenZ)+(greenX*redY*greenZ)+(greenX*greenY*redZ)
        - Here (redX*redY*redZ) is the number of intersection point which are colored 3 times. as if we color
          it 1st time it becomes red, green for 2nd times and again red for 3rd times. so we need to handle only 3rd time
          case and 1st time as we just want to know about red points.
        - And (redX*redY*redZ) is the number of intersection points which are colored red once for the impact of X axis.
          and formula is same for Y and Z axis.
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

#define mx 100005
#define segment_tree int l=n*2,r=l+1,mid=(b+e)/2


struct data
{
    ll red,green,lazy;
};

data tree[3][6*mx];

void init(int n, int b, int e, int idx)
{
    if(b==e)
    {
        tree[idx][n].green=1;
        tree[idx][n].red=0;
        tree[idx][n].lazy=0;
        return;
    }
    segment_tree;
    init(l,b,mid,idx);
    init(r,mid+1,e,idx);
    tree[idx][n].green=tree[idx][l].green+tree[idx][r].green;
    tree[idx][n].red=tree[idx][l].red+tree[idx][r].red;
    tree[idx][n].lazy=0;
}

void push_down(int n, int l, int r, int idx)
{
    if(tree[idx][n].lazy)
    {
        tree[idx][l].lazy^=1LL;
        tree[idx][r].lazy^=1LL;
        swap(tree[idx][l].green,tree[idx][l].red);
        swap(tree[idx][r].green,tree[idx][r].red);
        tree[idx][n].lazy=0;
    }
}

void update(int n, int b, int e, int i, int j, int idx)
{
    if(b>j || e<i) return;
    if(b>=i && e<=j)
    {
        tree[idx][n].lazy^=1LL;
        swap(tree[idx][n].green,tree[idx][n].red);
        return;
    }
    segment_tree;
    push_down(n,l,r,idx);
    update(l,b,mid,i,j,idx);
    update(r,mid+1,e,i,j,idx);
    tree[idx][n].green=tree[idx][l].green+tree[idx][r].green;
    tree[idx][n].red=tree[idx][l].red+tree[idx][r].red;
}

ll query(int n, int b, int e ,int i, int j, int idx)
{
    if(b>j || e<i) return 0;
    if(b>=i && e<=j)
    {
        return tree[idx][n].red;
    }
    segment_tree;
    push_down(n,l,r,idx);
    ll p=query(l,b,mid,i,j,idx);
    ll q=query(r,mid+1,e,i,j,idx);
    return p+q;
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ll n,m,k,q;
        sfffl(n,m,k);
        sfl(q);
        init(1,1,n,0);
        init(1,1,m,1);
        init(1,1,k,2);

        int x,a,b,c,d,e,f;

        while(q--)
        {
            sf(x);
            if(x==0)
            {
                sff(a,b);
                a++;
                b++;
                update(1,1,n,a,b,0);
            }
            else if(x==1)
            {
                sff(a,b);
                a++;
                b++;
                update(1,1,m,a,b,1);
            }
            else if(x==2)
            {
                sff(a,b);
                a++;
                b++;
                update(1,1,k,a,b,2);
            }
            else
            {
                sfff(a,b,c);
                sfff(d,e,f);
                a++;
                b++;
                c++;
                d++;
                e++;
                f++;
                ll xx=query(1,1,n,a,d,0);
                ll yy=query(1,1,m,b,e,1);
                ll zz=query(1,1,k,c,f,2);

                ll ansx=(e-b+1-yy)*(f-c+1-zz)*xx;
                ll ansy=(d-a+1-xx)*(f-c+1-zz)*yy;
                ll ansz=(d-a+1-xx)*(e-b+1-yy)*zz;

                ll ans=ansx+ansy+ansz+(xx*yy*zz);

                printf("%lld\n",ans);


            }

        }

    }


    return 0;
}
