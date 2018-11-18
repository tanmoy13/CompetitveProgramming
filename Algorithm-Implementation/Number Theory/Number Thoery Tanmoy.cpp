//----------------Sieve--------------------

#define mx 50006
vector<int>prime;
bool vis[mx];

void sieve()
{
    int x=sqrt((int)mx);
    for(int i=3; i<=x; i+=2)
    {
        if(vis[i]==0)
        {
            for(int j=i*i; j<mx; j+=2*i)
                vis[j]=1;
        }
    }
    prime.pb(2);
    for(int i=3; i<mx; i+=2)
        if(vis[i]==0)
            prime.pb(i);
}


//-----------------Bitwise Sieve---------------

#define M 40000000
int marked[M/64 + 2];
vector<int>prime;
#define on(x) (marked[x/64] & (1<<((x%64)/2)))
#define mark(x)  marked[x/64] |= (1<<((x%64)/2))

bool isPrime(int num)
{
    return num > 1 && (num == 2 || ((num & 1) && !on(num)));
}

void sieve(int n)
{
    for (int i = 3; i * i < n; i += 2)
    {
        if (!on(i))
        {
            for (int j = i * i; j <= n; j += i + i)
            {
                mark(j);
            }
        }
    }
    prime.push_back(2);
    for(int i=3;i<M;i+=2)
    {
        if(isPrime(i))
            prime.pb(i);
    }
}




//----------------Number of Divisor---------

ll NOD(ll n)
{
    int root=sqrt(n);
    ll ret=1;
    for(int i=0;i<SZ(prime) && prime[i]<=root;i++)
    {
        if(n%prime[i]==0)
        {
            int cnt=1;
            while(n%prime[i]==0)
            {
                cnt++;
                n/=prime[i];
            }
            ret*=cnt;
            root=sqrt(n);
        }
    }
    if(n>1)
        ret*=2;
    return ret;
}


//----------------Mobius--------------------

int mu[mx];

void mobius()
{
    for(int i=1; i<mx; i++) mu[i]=1;
    int root=sqrt((int)mx);
    for(int i=0; i<SZ(prime) && prime[i]<=root; i++)
    {
        int x=prime[i];
        x=sqr(x);
        for(int j=x; j<mx; j+=x)
            mu[j]=0;
    }
    for(int i=0; i<SZ(prime); i++)
    {
        int x=prime[i];
        for(int j=x; j<mx; j+=x)
            mu[j]*=-1;
    }
}


//----------------euler totient 1 to n--------------------

int phi[mx];

void euler_totient()
{
    for(int i=0; i<mx; i++) phi[i]=i;
    for(int i=2; i<mx; i++)
    {
        if(phi[i]==i)
        {
            for(int j=i; j<mx; j+=i)
                phi[j]-=(phi[j]/i);
        }
    }
}

//----------------euler totient for n--------------------

ll euler_totient(ll n)
{
    int root=sqrt(n);
    ll ret=n;
    for(int i=0; i<SZ(prime) && prime[i]<=root; i++)
    {
        if(n%prime[i]==0)
        {
            while(n%prime[i]==0)
                n/=prime[i];
            root=sqrt(n);
            ret-=(ret/prime[i]);
        }
    }
    if(n>1)
    {
        ret-=(ret/n);
    }
    return ret;
}

//----------------extended euclid--------------------

long long ext_gcd (long long A, long long B, long long &X, long long &Y)
{
    long long x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1, y2 = 0;
    x1 = 0, y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y )
    {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    X = x2;
    Y = y2;
    return r2;
}


//----------------Mod Inverse--------------------

inline long long modInv (long long a, long long m)
{
    long long x, y;
    ext_gcd(a, m, x, y);
    x %= m;
    if (x < 0) x += m;
    return x;
}

//----------------bigmod--------------------

inline long long bigmod (long long a, long long p, long long m)
{
    long long res = 1 % m, x = a % m;
    while ( p )
    {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m;
        p >>= 1;
    }
    return res;
}

//----------------linear Diophantine equation--------------------

bool linearDiophantine ( long long A, long long B, long long C, long long &x, long long &y )
{
    int g = gcd ( A, B );
    if ( C % g != 0 ) return false; //No Solution

    int a = A / g, b = B / g, c = C / g;
    if ( g < 0 )   //Make Sure gcd(a,b) = 1
    {
        a *= -1;
        b *= -1;
        c *= -1;
    }
    ext_gcd( a, b, x, y ); //Solve ax + by = 1


    x *= c;
    y *= c; //ax + by = c
    return true; //Solution Exists
    //more solution {x+k*(b/g), y-k*(a/g)}
}

//-----------------Chinese Remainder-----------

long long CRT_weak(vector<long long>A, vector<long long>B)
{
    ll X=0;
    ll N=1;
    ll y,z;
    for(int i=0; i<SZ(B); i++)
        N*=B[i];
    for(int i=0; i<SZ(A); i++)
    {
        y=N/B[i];
        z=modInv(y,B[i]);
        X+=(A[i]*y*z);
        X%=N;
    }
    return (X+N)%N;
}


