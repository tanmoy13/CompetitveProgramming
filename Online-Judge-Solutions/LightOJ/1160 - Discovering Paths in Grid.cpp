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
//#define MOD              1000000007
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
int Set(int N,int pos)
{
    return N=N | (1<<pos);
}
int reset(int N,int pos)
{
    return N= N & ~(1<<pos);
}
bool check(int N,int pos)
{
    return (bool)(N & (1<<pos));
}
/*------------------------------------------------*/


/*
    Matrix Expo Optimization:
    --------------------------
        - We can precalculate every power 2^i of base matrix for every i.
        - Then for mat^x we can multiply every mat^(2^i) where i th bit is on in x.
*/

// int MOD=
ll MOD= 1000000007;

struct matrix
{
    ll mat[36][36];
    int row,col;

    matrix()
    {
        memset(mat,0,sizeof mat);
    }
    matrix(int a, int b)
    {
        row=a,col=b;
        memset(mat,0,sizeof mat);
    }

    void clear()
    {
        memset(mat,0,sizeof mat);
    }

    matrix operator*(const matrix &p) const
    {
//        assert(col == p.row);
        matrix temp;
        temp.row = row;
        temp.col = p.col;
        for (int i = 0; i < temp.row; i++)
        {
            for (int j = 0; j < temp.col; j++)
            {
                ll sum = 0;
                for (int k = 0; k <col;  k++)
                {
                    sum += (mat[i][k]*p.mat[k][j])%MOD;
                    sum%=MOD;
                }
                temp.mat[i][j] = sum;
            }
        }
        return temp;
    }
    matrix operator+ (const matrix &p) const
    {
//        assert(row==p.row && col==p.col);
        matrix temp;
        temp.row=row;
        temp.col=col;
        for(int i=0; i<temp.row; i++)
        {
            for(int j=0; j<temp.col; j++)
                temp.mat[i][j]=(mat[i][j]+p.mat[i][j])%MOD;;
        }
        return temp;
    }

    matrix identity()
    {
        matrix temp;
        temp.row=row;
        temp.col=col;
        for(int i=0; i<row; i++)
            temp.mat[i][i]=1;
        return temp;
    }

    matrix pow(ll pow)
    {
        matrix temp=(*this);
        matrix ret=(*this).identity();

        while(pow>0)
        {
            if(pow % 2==1)
                ret=ret*temp;
            temp=temp*temp;
            pow/=2;
        }
        return ret;
    }

    void show()
    {
        printf("-----------------------------\n");
        for(int i=0; i<row; i++)
        {
            cout<<"row == "<<i<<" -> ";
            for(int j=0; j<col; j++)
                printf("%lld ",mat[i][j]);
            printf("\n");
        }
        printf("-----------------------------\n");
    }

};




int mp[128],rmp[128];
vector<int>v;
int cnt=0;

matrix adj(35,35);
matrix pow2[50];


/**

Precal(): this function make the adjacency matrix of the transition.
For example:
Let a state u is 0001111 (15 in int).
Then there is only one adjacent state v for this u and that is -
    v = 0011110 (30 in int).

Precal function make this adjacent matrix for all possible states u and v.

There can be at most 35 values for u and v. Because from 7 position only 4 of them
have a 1. so 7C4 = 35.

*/


void show_bit(int a, int b)
{
    cout<<"-------------------------------"<<endl;
    bitset<7>u(a);
    bitset<7>v(b);
    DD(a,u);
    DD(b,v);
    cout<<"-------------------------------"<<endl;
}

//void gen_adjacent(int idx, int cur, int next)
//{
//    if(idx>=7)
//    {
////        if(POPCOUNT(next)==4)
//        {
//            show_bit(cur,next);
//            adj.mat[mp[cur]][mp[next]]=1;
//        }
//        return;
//    }
//
//    if(check(cur,idx)==0)
//        gen_adjacent(idx+1,cur,next);
//    else
//    {
//        if(idx-1>=0 && check(next,idx-1)==0)
//            gen_adjacent(idx+1,cur,Set(next,idx-1));
//        if(idx+1<7 && check(next,idx+1)==0)
//            gen_adjacent(idx+1,cur,Set(next,idx+1));
//    }
//}

bool isAdjacent(int a, int b)
{
    for(int i=0; i<7; i++)
    {
        if(check(a,i))
        {
            if(i==0)
            {
                if(check(b,i+1)==0) return false;
                else b=reset(b,i+1);
            }
            else if(i==6)
            {
                if(check(b,i-1)==0) return false;
                else b=reset(b,i-1);
            }
            else
            {
                if(check(b,i-1)) b=reset(b,i-1);
                else if(check(b,i+1)) b=reset(b,i+1);
                else return false;
            }
        }
    }
    return true;
}

void precal()
{
    for(int i=1; i<(1<<7); i++)
    {
        if(POPCOUNT(i)==4)
        {
            v.pb(i);
            mp[i]=cnt;
            rmp[cnt]=i;
            cnt++;
        }
    }

//    D(cnt);


    for(int i=0; i<SZ(v); i++)
    {
        for(int j=0; j<SZ(v); j++)
        {
            if(isAdjacent(v[i],v[j]))
                adj.mat[i][j]=1;
        }
    }


    ///matrix expo optimization part is here


    for(int i=0; i<32; i++)
    {
        ll p=(1LL<<i);
        pow2[i]=adj.pow(p);
    }
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif


    precal();

//    adj.show();
//
//    for(int i=0; i<adj.row; i++)
//    {
//        for(int j=0; j<adj.col; j++)
//        {
//            if(adj.mat[i][j]==1)
//            {
//                show_bit(rmp[i],rmp[j]);
//            }
//        }
//    }


//    vector<vector<int> > v;
//
//    for(int i=0; i<35; i++)
//    {
//        vector<int>temp;
//        for(int j=0; j<35; j++)
//        {
////            cout<<adj.mat[i][j]<<" ";
//            temp.push_back(adj.mat[i][j]);
//        }
////        cout<<endl;
//        v.push_back(temp);
//    }
//
//    sort(v.begin(),v.end());

//    for(int i=0;i<SZ(v);i++)
//    {
//        for(int j=0;j<SZ(v[i]);j++)
//        {
//            cout<<v[i][j]<<" ";
//        }
//        cout<<endl;
//    }

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ll n;
        sfl(n);
        n--;

        int mask=0;
        for(int i=0; i<7; i++)
        {
            int a;
            sf(a);
            if(a)
                mask=Set(mask,7-i-1);
        }

        PRINT_CASE;
        if(n==0)
        {
            printf("1\n");
            continue;
        }

        matrix powerd_mat(35,35);
        powerd_mat=powerd_mat.identity();
        for(int i=0; i<32; i++)
        {
            if((n & (1LL<<i)))
                powerd_mat=powerd_mat*pow2[i];
        }


        int id=mp[mask];


        ll ans=0;



        for(int i=0; i<35; i++)
        {
            ans=(ans+powerd_mat.mat[id][i])%MOD;
        }


        printf("%lld\n",ans);

    }


    return 0;
}



