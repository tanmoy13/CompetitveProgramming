ll dp[2001][2001];

ll nCr(int n, int r)
{
    if(r==0) return 1;
    if(n==r) return 1;
    ll &ret=dp[n][r];
    if(ret!=-1) return ret;
    ret=nCr(n-1,r)%MOD+nCr(n-1,r-1)%MOD; //recurrence relation
    ret%=MOD;
    return ret;
}
