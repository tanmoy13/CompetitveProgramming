/*
- A clique is a subset of vertices of an undirected graph such that every two distinct
  vertices in the clique are adjacent; that is, its induced subgraph is complete.
- This algorithm find the maximum number of clique in a undirected graph.
- Take input in adjacency matrix as arr[u][v]=1.
- maxClique() return the number of vertices in maximum clique and they are in vector<ll>clique.
*/

ll n, k, arr[60][60];
ll N[60], res;
vector <ll> clique;

void BronKerbosch(ll n, ll R, ll P, ll X) {
    if (P == 0LL && X == 0LL) {
        ll t = 0;
        vector <ll> v;
        for (ll i = 0; i < n; i++)
            if ((1ll << i) & R)
                t ++, v.pb (i + 1);
        if (t > res) {
            res = t;
            clique = v;
        }
        res = max(res, t);
        return;
    }
    ll u = 0;
    while (!((1ll<<u) & (P|X)))
        u ++;
    for (ll v = 0; v < n; v++) {
        if (((1ll << v) & P) && !((1ll << v) & N[u])) {
            BronKerbosch(n, R | (1ll << v), P & N[v], X & N[v]);
            P -= (1ll << v);
            X |= (1ll << v);
        }
    }
}

ll maxClique () {
    res = -1;
    for (ll i = 1; i <= n; i++) {
        N[i] = 0;
        for (ll j = 1; j <= n; j++) {
            if (arr[i][j]) {
                N[i - 1] |= ( 1ll << (j - 1) );
            }
        }
    }
    BronKerbosch(n, 0, (1ll << n) - 1, 0);
    return res;
}

