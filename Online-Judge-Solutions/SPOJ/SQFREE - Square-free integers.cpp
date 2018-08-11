#include <bits/stdc++.h>

#define ms(a,b)          memset(a, b, sizeof(a))
#define pb(a)            push_back(a)

#define ss               second
#define sqr(x)           (x)*(x)

#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)


#define TEST_CASE(t)     for(int z=1;z<=t;z++)
#define ll long long

using namespace std;

#define mx 10000007

int ara[mx];
vector<ll>num,mobius,prime;
bitset<mx/2>vis;

void sieve()
{
    int x=mx/2,y=sqrt(mx)/2;

    for(int i=1;i<y;i++)
    {
        for(int j=i*(i+1)*2;j<x;j+=(2*i+1))
            vis[j]=1;
    }

    prime.pb(2);
    for(int i=3;i<mx;i+=2)
        if(vis[i/2]==0)
            prime.pb(i);

}

void precal()
{
    fill(ara,ara+mx,1);
    for(int i=0;prime[i]*prime[i]<mx;i++)
    {
        ll x=prime[i]*prime[i];
        for(int j=x;j<mx;j+=x)
            ara[j]=0;
    }

    for(int i=0;i<SZ(prime);i++)
    {
        int x=prime[i];
        for(int j=x;j<mx;j+=x)
            ara[j]*=-1;
    }

    for(int i=2;i<mx;i++)
    {
        if(ara[i]==0) continue;
        num.pb(i);
        mobius.pb(ara[i]);
    }

}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    sieve();
    precal();

    int t;
    sf(t);
    TEST_CASE(t)
    {
        ll n;
        sfl(n);

        ll ans=n;

        for(int i=0;i<SZ(num);i++)
        {
            ll x=num[i];
            ll zz=sqr(x);
            if(zz>n) break;
            int y=mobius[i];
            ans+=mobius[i]*(n/zz);
        }

        printf("%lld\n",ans);

    }

    return 0;
}
