#define mx 100005

vector<int>g[mx];
int par[mx],level[mx];


void dfs(int u, int p, int lvl) {
    par[u]=p;
    level[u]=lvl;
    for(int i=0; i<SZ(g[u]); i++) {
        int v=g[u][i];
        if(v==p) continue;
        dfs(v,u,lvl+1);
    }
}


int dp[20][mx];

int call(int p, int u) {
    if(p==0)
        return par[u];
    int &ret=dp[p][u];
    if(ret!=-1) return ret;
    int x=call(p-1,u);
    int y=call(p-1,x);
    return ret=y;
}


int query(int a, int b) {
    if(level[a]<level[b])
        swap(a,b);

    for(int i=19; i>=0; i--) {
        int x=call(i,a);
        if(level[x]>=level[b])
            a=x;
    }


    if(a==b) return a;

    for(int i=19; i>=0; i--) {
        int x=call(i,a);
        int y=call(i,b);
        if(x!=y) {
            a=x;
            b=y;
        }
    }

    return par[a];
}
