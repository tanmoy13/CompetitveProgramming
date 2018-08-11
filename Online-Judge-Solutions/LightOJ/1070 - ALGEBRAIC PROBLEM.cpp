/*

Solution Idea: 

Meaning of the questions:
You p = a + b, q = ab

Calculating (a ^ n + b ^) mod2 ^ 64

practice:

mod 2 ^ 64 so open unsigned long long, llu on the line, reaches the upper limit will be automatically modulo.

Then the formula is. I was pushing the law found in the formula.

a ^ 2 + b ^ 2 = (a + b) * (a + b) -2 * a * b

a ^ 3 + b ^ 3 = (a ^ 2 + b ^ 2) * (a + b) -a * b (a + b)

a ^ 4 + b ^ 4 = (a ^ 3 + b ^ 3) * (a + b) -a * b (a ^ 2 + b ^ 2)

now --

1.a^n + b^n = (a^(n-1)+b^(n-1))*(a+b) - a*b*(a^(n-2)+b^(n-2))
 
2.  Xn = a^n + b^n

3 . Xn = pXn-1 + qXn-2

    (p q)      (Xn-1)         (pXn-1 + qXn-2)         (Xn  )
4.         x               =                      =
    (1 0)      (Xn-2)         ( Xn-1 +  0  )          (Xn-1)

5 . from this

    (p q)^(n-1)     (X1)     (Xn   )   
                x          =
    (1 0)           (X0)     (Xn-1)

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
// ll MOD=

struct matrix
{
    ull mat[2][2];
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
                temp.mat[i][j]=((mat[i][j])+(p.mat[i][j]));
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
                printf("%llu ",mat[i][j]);
            printf("\n");
        }
        printf("-----------------------------\n");
    }

};

/*--------------------------Matrix End---------------------*/


int main()
{

    ///freopen("in.txt","r",stdin);
    ///freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ll p,q,n;
        sfffl(p,q,n);
        matrix base(2,2);
        base.mat[0][0]=p;
        base.mat[0][1]=-q;
        base.mat[1][0]=1;

        matrix temp(2,1);
        temp.mat[0][0]=p;
        temp.mat[1][0]=2;

//        base.show();

        base=base.pow(n-1);
//        base.show();
//        temp.show();
        base=base*temp;
//        ull ans=(base.mat[0][0]*temp.mat[0][0])-(base.mat[0][1]*temp.mat[1][0]);

//        base.show();

        ull ans=base.mat[0][0];
        
        if(n==0) ans=2;
        
        PRINT_CASE;
        printf("%llu\n",ans);

    }

    return 0;
}
