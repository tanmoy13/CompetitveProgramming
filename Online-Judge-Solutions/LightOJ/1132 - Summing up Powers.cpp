/*

Soluton Idea:
--------------

f(x)=1^k+2^k+3^k+..........+x^k
f(1)=1
f(x+1)=f(x)+(x+1)^k

from Binomial Co efficient we know -
(x+1)^n= nC0 x^n + nC1 x^n-1 + nC2 x^n-2+..............+ nCn-1 x^1 + nCn x^0

details: http://lbv-pc.blogspot.com/2012/05/summing-up-powers.html

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
//#define MOD              1000000007
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



/*----------------------Matrix-----------------------*/

// int MOD=
// ll MOD= (1LL)<<32;

struct matrix
{
    unsigned int mat[52][52];
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
                    sum += ((mat[i][k]) * (p.mat[k][j]));
//                    sum%=MOD;
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
        for(int i=0;i<temp.row;i++)
        {
            for(int j=0;j<temp.col;j++)
                temp.mat[i][j]=((mat[i][j])+(p.mat[i][j]));;
        }
        return temp;
    }

    matrix identity()
    {
        matrix temp;
        temp.row=row;
        temp.col=col;
        for(int i=0;i<row;i++)
            temp.mat[i][i]=1;
        return temp;
    }

    matrix pow(ll pow)
    {
        matrix temp=(*this);
        matrix ret=(*this).identity();
        while(pow)
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
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
                printf("%lld ",mat[i][j]);
            printf("\n");
        }
        printf("-----------------------------\n");
    }

};

/*--------------------------Matrix End---------------------*/

unsigned int nCr[55][55];

void compute_nCr()
{
    nCr[0][0]=nCr[1][1]=1;
    for(int i=1;i<52;i++)
    {
        nCr[i][0]=1;
        for(int j=1;j<52;j++)
            nCr[i][j]=nCr[i-1][j]+nCr[i-1][j-1];
    }
}

int main()
{

//    freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    compute_nCr();

//    int a=5;
//    while(a--)
//    {
//        int a,b;
//        cin>>a>>b;
//        cout<<nCr[a][b]<<endl;
//    }

    TEST_CASE(t)
    {
        ll n,k;
        sffl(n,k);
        matrix base(k+2,k+2);

        base.mat[0][0]=1;

        for(int i=1;i<=k+1;i++)
        {
            base.mat[0][i]=nCr[k][i-1];
            base.mat[1][i]=nCr[k][i-1];
        }
        for(int i=2;i<=k+1;i++)
        {
            for(int j=i;j<=k+1;j++)
                base.mat[i][j]=nCr[k-i+1][j-i];
        }

//        base.show();

        matrix temp(k+2,1);
        for(int i=0;i<=k+1;i++)
            temp.mat[i][0]=1;

        base=base.pow(n-1);
//        base.show();
//        temp.show();
        base=base*temp;
        PRINT_CASE;
        printf("%u\n",base.mat[0][0]);



    }

    return 0;
}




