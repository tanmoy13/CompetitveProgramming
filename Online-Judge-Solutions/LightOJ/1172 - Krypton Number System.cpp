/**
    Author: Tanmoy Datta

    Solution Idea:
    ~~~~~~~~~~~~~~
        - The main idea behind this problem is dynamic programming.
        - DP[i,j] = number of ways to make score i where last used coin is j.
        - Base case of the problem is DP[0,0]=0 and DP[0,1]...DP[0,B-1]=1
        - So let for base 3-
            DP[n,0] = DP[n-1,1]+DP[n-4,2]
            DP[n,1] = DP[n-1,0]+DP[n-1,2]
            DP[n,2] = DP[n-4,0]+DP[n-1,1]
        So we can store DP as column matrix and make a transition matrix A. and perform matrix expo over A.
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
#define sqr(x)           ((x)*(x))
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


/*
    Matrix Expo Optimization:
    --------------------------
        - We can precalculate every power 2^i of base matrix for every i.
        - Then for mat^x we can multiply every mat^(2^i) where i th bit is on in x.
*/

// int MOD=
// ll MOD=

struct matrix
{
    unsigned int mat[151][151];
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

    matrix operator*(const matrix &p) const
    {
        assert(col == p.row);
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
                    sum += (mat[i][k]*p.mat[k][j]);
                }
                temp.mat[i][j] = sum;
            }
        }
        return temp;
    }
    matrix operator+ (const matrix &p) const
    {
        assert(row==p.row && col==p.col);
        matrix temp;
        temp.row=row;
        temp.col=col;
        for(int i=0; i<temp.row; i++)
        {
            for(int j=0; j<temp.col; j++)
                temp.mat[i][j]=(mat[i][j]+p.mat[i][j]);
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
        while(pow)
        {
            if(pow & 1LL)
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
            for(int j=0; j<col; j++)
                printf("%lld ",mat[i][j]);
            printf("\n");
        }
        printf("-----------------------------\n");
    }

};


unsigned int dp[7][30][6];

void init_dp(int base, int till)
{

    for(int i=1; i<base; i++)
        dp[base][0][i]=1;

    for(int i=1; i<till; i++)
    {
        for(int j=0; j<base; j++)
        {
            dp[base][i][j]=0;
            for(int k=0; k<base; k++)
            {
                if(j==k) continue;
                int prev=sqr(k-j);
                if(i-prev<0) continue;
                dp[base][i][j]+=dp[base][i-prev][k];
            }
        }
    }
}

matrix base[7];
matrix A[7];

void init_base()
{
    for(int i=2; i<=6; i++)
    {
//        D(i);
        init_dp(i,sqr(i-1));
        base[i].row=sqr(i-1)*(i);
        base[i].col=1;

        for(int j=0,temp=0; j<base[i].row; temp++)
        {
            for(int k=0; k<i; k++)
            {
//               D(j);
                base[i].mat[j][0]=dp[i][temp][k];
                j++;
            }
        }

//       base[i].show();
    }
}

void init_A()
{
    for(int i=2; i<=6; i++) ///base
    {
        A[i].row=sqr(i-1)*(i);
        A[i].col=sqr(i-1)*(i);

        int just_pick_up = (sqr(i-1)-1)*i;

        for(int j=0; j<just_pick_up; j++)
        {
            A[i].mat[j][j+i]=1;
        }

        int current_pos=max((sqr(i-1)-1)*i,2);
        if(i==2)
        {
            A[i].mat[0][1]=1;
            A[i].mat[1][0]=1;
        }
        else
        {
            for(int j=just_pick_up,cur=0; j<A[i].row; j++,cur++)
            {
                for(int k=0; k<i; k++)
                {
                    if(cur==k) continue;
                    int diff=sqr(abs(k-cur))-1;
                    int target=(j-diff*i)+(k-cur);
                    A[i].mat[j][target]=1;
                }
            }
        }
//        D(i);
//        A[i].show();
    }
}

matrix pow2[7][30];

void precall()
{
    for(int i=2; i<7; i++)
    {
        for(int j=0; j<30; j++)
        {
            int p=1<<j;
            pow2[i][j]=A[i].pow(p);
        }
    }
}

int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
//#endif

    init_base();
    init_A();
    precall();

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int b,p;
        sff(b,p);

        PRINT_CASE;

        unsigned int ans=0;

        if(sqr(b-1)-1>=p)
        {
            for(int i=0; i<b; i++)
                ans+=dp[b][p][i];
            printf("%u\n",ans);
            continue;
        }

        p=p-sqr(b-1)+1;


        matrix temp=A[b].identity();
//        temp.show();
        for(int i=0; i<30; i++)
        {
            if(p&(1<<i))
                temp=temp*pow2[b][i];
        }

        temp=temp*base[b];

        for(int i=temp.row-1,j=0; j<b; j++,i--)
        {
            ans+=temp.mat[i][0];
        }

        printf("%u\n",ans);

    }

    return 0;
}


